#include "natives.hpp"
#include "pointers.hpp"
#include "network/CNetworkPlayerMgr.hpp"
#include "orbital_drone.h"
#include "vehicle/CVehicle.hpp"
#include "services/players/player_service.hpp"
#include "util/entity.hpp"
#include "util/toxic.hpp"
#include "gui.hpp"

namespace big::orbitaldrone
{
	void orbital_cannon_esp()
	{
		for (auto p : (*g_pointers->m_network_player_mgr)->m_player_list)
		{
			if (p && p->m_player_info->m_ped && p != (*g_pointers->m_network_player_mgr)->m_local_net_player)
			{
				rage::fvector3 playerpedpos = *p->m_player_info->m_ped->m_navigation->get_position();

				rage::fvector2 screenpos{};
				HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(playerpedpos.x,
				    playerpedpos.y,
				    playerpedpos.z,
				    &screenpos.x,
				    &screenpos.y);
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::SET_TEXT_FONT(4);
				HUD::SET_TEXT_SCALE(0.3f, 0.463);
				HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(p->get_name());
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(screenpos.x, screenpos.y, 0);
			}
		}
	}

	static bool nav_override;
	static float nav_multiplier = 1.f;

	void detect_player(Entity ent)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ent))
			return;

		if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
		{
			CVehicle* vehpointer = reinterpret_cast<CVehicle*>(g_pointers->m_handle_to_ptr(ent));

			if (vehpointer)
			{
				for (auto player : g_player_service->players() | std::ranges::views::values)
				{
					if (player)
					{
						if (vehpointer->m_driver)
						{
							if (player->get_ped() == vehpointer->m_driver)
							{
								g_player_service->set_selected(player);
								return;
							}
						}

						for (auto p : vehpointer->m_passengers)
						{
							if (p)
							{
								if (player->get_ped() == p)
								{
									g_player_service->set_selected(player);
									return;
								}
							}
						}
					}
				}
			}
		}

		if (PED::IS_PED_A_PLAYER(ent))
		{
			for (auto p : g_player_service->players() | std::ranges::views::values)
			{
				if (p)
				{
					if (g_pointers->m_ptr_to_handle(p->get_ped()) == ent)
						g_player_service->set_selected(p);

				}
			}
		}
	}

	void OrbitalDrone::tick()
	{
		if (!this->initialized)
			return;


		//for (auto p : navmethods::generatedpos)
		//	draw_box_on_generatedpos(p);

		PAD::ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(2);
		PAD::DISABLE_CONTROL_ACTION(0, 24, true);
		PAD::DISABLE_CONTROL_ACTION(0, 257, true);
		PAD::DISABLE_CONTROL_ACTION(0, 142, true);
		PAD::DISABLE_CONTROL_ACTION(0, 141, true);
		PAD::DISABLE_CONTROL_ACTION(0, 140, true);
		PAD::DISABLE_CONTROL_ACTION(0, 263, true);
		PAD::DISABLE_CONTROL_ACTION(0, 264, true);
		PAD::DISABLE_CONTROL_ACTION(0, 143, true);
		PAD::DISABLE_CONTROL_ACTION(2, 200, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_SELECT_NEXT_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_SELECT_PREV_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_WEAPON_WHEEL_NEXT, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_WEAPON_WHEEL_PREV, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_VEH_NEXT_RADIO, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_VEH_PREV_RADIO, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_DUCK, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int) ControllerInputs::INPUT_VEH_SPECIAL, true);
		HUD::DISPLAY_AMMO_THIS_FRAME(false);
		HUD::HUD_FORCE_WEAPON_WHEEL(false);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(19);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(2);
		//HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(1);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(3);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(4);

		Vector3 campos = CAM::GET_CAM_COORD(this->cam);
		Vector3 camrot = CAM::GET_CAM_ROT(this->cam, 0);

		Entity self = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(self, true) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(self, false), -1, false) == self)
			self = PED::GET_VEHICLE_PED_IS_IN(self, false);

		ENTITY::SET_ENTITY_COORDS(self, campos.x, campos.y, campos.z + 15, 0, 0, 0, 0);

		ENTITY::FREEZE_ENTITY_POSITION(self, 1);
		ENTITY::SET_ENTITY_VISIBLE(self, false, 0);

		this->cam_nav();
		//orbital_cannon_esp();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(this->scaleform, 255, 255, 255, 0, 1);

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_FRONTEND_RDOWN) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_FRONTEND_RDOWN))
		{
			this->tp = true;
			g_fiber_pool->queue_job([=] {
				this->~OrbitalDrone();
			});
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_JUMP)
		    || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_JUMP && !g_gui->is_open()))
		{
			this->lock_ent = entity::get_entity_closest_to_middle_of_screen();
			this->lock     = true;

			detect_player(this->lock_ent);
			//navmethods::generatedpos.clear();
			//
			//for (size_t i = 0; i < 50; i++)
			//{
			//	navmethods::generatedpos.push_back(navmethods::generate_appropriate_coords(this->groundpos, 50.f, false, false, false).coord);
			//}
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_ATTACK) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_ATTACK))
		{
			g_fiber_pool->queue_job([=] {
				this->orbital_cannon_explosion();
			});
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_ARREST)
		    || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_ARREST) && !g_gui->is_open())
		{
			//g_fiber_pool->queue_job([=] {
			//	Policing::spawn_roadblock(this->groundpos, 3);
			//});
		}

		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_PARACHUTE_BRAKE_RIGHT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_PARACHUTE_BRAKE_RIGHT))
		{
			nav_override   = true;
			nav_multiplier = 3.f;
		}

		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_PARACHUTE_BRAKE_LEFT) || PAD::IS_DISABLED_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_PARACHUTE_BRAKE_LEFT))
		{
			nav_override   = true;
			nav_multiplier = 0.25f;
		}

		if (!nav_override)
			nav_multiplier = 1.f;
		else
			nav_override = false;
	}

	void OrbitalDrone::cam_nav()
	{
		if (!this->initialized || !CAM::DOES_CAM_EXIST(this->cam))
			return;

		Vector3 campos   = CAM::GET_CAM_COORD(this->cam);
		Vector3 finalpos = CAM::GET_CAM_COORD(this->cam);

		MISC::GET_GROUND_Z_FOR_3D_COORD(finalpos.x, finalpos.y, finalpos.z, &finalpos.z, false, false);

		this->groundpos = {campos.x, campos.y, finalpos.z};

		float minz = finalpos.z + 10;
		float maxz = 1500.f;

		if (campos.z < minz)
			CAM::SET_CAM_COORD(this->cam, campos.x, campos.y, minz);
		if (campos.z > maxz)
			CAM::SET_CAM_COORD(this->cam, campos.x, campos.y, maxz);

		Vector3 movepos;
		bool moved = false;
			
		float leftstick_xaxis  = PAD::GET_CONTROL_NORMAL(2, (int) ControllerInputs::INPUT_SCRIPT_LEFT_AXIS_X);
		float leftstick_yaxis  = -PAD::GET_CONTROL_NORMAL(2, (int) ControllerInputs::INPUT_SCRIPT_LEFT_AXIS_Y);
		float rightstick_yaxis = PAD::GET_CONTROL_NORMAL(2, (int) ControllerInputs::INPUT_SCRIPT_RIGHT_AXIS_Y);

		//LEFT
		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_LEFT_ONLY) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_LEFT_ONLY))
		{
			if (leftstick_xaxis == 0)
				movepos = {campos.x - ((campos.z / 50) * nav_multiplier), campos.y, campos.z};
			else
				movepos = {campos.x + ((leftstick_xaxis * 5) * nav_multiplier), campos.y, campos.z};
			moved      = true;
			this->lock = false;
		}
		//RIGHT
		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_RIGHT) || PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_RIGHT))
		{
			if (leftstick_xaxis == 0)
				movepos = moved ? Vector3(movepos.x + ((movepos.z / 50) * nav_multiplier), movepos.y, movepos.z) :
				                  Vector3(campos.x + ((campos.z / 50) * nav_multiplier), campos.y, campos.z);
			else
				movepos = moved ? Vector3(movepos.x + ((leftstick_xaxis * 5) * nav_multiplier), movepos.y, movepos.z) :
				                  Vector3(campos.x + ((leftstick_xaxis * 5) * nav_multiplier), campos.y, campos.z);
			moved      = true;
			this->lock = false;
		}
		//UP
		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_UP_ONLY) || PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_UP_ONLY))
		{
			if (leftstick_yaxis == 0)
				movepos = moved ? Vector3(movepos.x, movepos.y + ((movepos.z / 50) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y + ((campos.z / 50) * nav_multiplier), campos.z);
			else
				movepos = moved ? Vector3(movepos.x, movepos.y + ((leftstick_yaxis * 5) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y + ((leftstick_yaxis * 5) * nav_multiplier), campos.z);
			moved      = true;
			this->lock = false;
		}
		//DOWN
		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_DOWN) || PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_MOVE_DOWN))
		{
			if (leftstick_yaxis == 0)
				movepos = moved ? Vector3(movepos.x, movepos.y + ((movepos.z / 50) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y - ((campos.z / 50) * nav_multiplier), campos.z);
			else
				movepos = moved ? Vector3(movepos.x, movepos.y + ((leftstick_yaxis * 5) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y + ((leftstick_yaxis * 5) * nav_multiplier), campos.z);
			moved      = true;
			this->lock = false;
		}

		//ZOOM IN
		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_VEH_SLOWMO_UP_ONLY)
		    || PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_VEH_SLOWMO_UP_ONLY) && !g_gui->is_open())
		{
			if (campos.z > minz)
			{
				movepos = moved ? Vector3(movepos.x, movepos.y, movepos.z - movepos.z / 20) :
				                  Vector3(campos.x, campos.y, campos.z - campos.z / 20);
				moved   = true;
			}
		}

		//ZOOM OUT
		if (PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_VEH_SLOWMO_DOWN_ONLY)
		    || PAD::IS_CONTROL_PRESSED(2, (int) ControllerInputs::INPUT_VEH_SLOWMO_DOWN_ONLY) && !g_gui->is_open())
		{
			if (campos.z < maxz)
			{
				movepos = moved ? Vector3(movepos.x, movepos.y, movepos.z + movepos.z / 20) :
				                  Vector3(campos.x, campos.y, campos.z + campos.z / 20);
				moved   = true;
			}
		}

		//ZOOM IN CONTROLLER
		if (rightstick_yaxis && !g_gui->is_open())
		{
			//if (campos.z > minz && campos.z < maxz) {
			movepos = moved ? Vector3(movepos.x, movepos.y, movepos.z + (rightstick_yaxis * 5)) :
			                  Vector3(campos.x, campos.y, campos.z + (rightstick_yaxis * 5));
			moved   = true;
			//}
		}

		if (this->lock && ENTITY::DOES_ENTITY_EXIST(this->lock_ent) && this->lock_ent != -1)
		{
			Vector3 targetpos = ENTITY::GET_ENTITY_COORDS(this->lock_ent, 0);
			if (moved)
				CAM::SET_CAM_COORD(this->cam, targetpos.x, targetpos.y, movepos.z);
			else
				CAM::SET_CAM_COORD(this->cam, targetpos.x, targetpos.y, campos.z);
		}

		if (moved)
		{
			CAM::SET_CAM_COORD(this->cam, movepos.x, movepos.y, movepos.z);

			moved = false;
		}
	}

	void OrbitalDrone::orbital_cannon_explosion()
	{
		if (g_gui->is_open())
			return;

		Vector3 campos = CAM::GET_CAM_COORD(this->cam);
		Vector3 entpos = ENTITY::GET_ENTITY_COORDS(entity::get_entity_closest_to_middle_of_screen(), 0);

		if (ENTITY::DOES_ENTITY_EXIST(g_pointers->m_ptr_to_handle( g_player_service->get_selected()->get_ped())))
		{
			toxic::blame_explode_coord(g_player_service->get_selected(), this->groundpos, eExplosionTag::EXP_TAG_ORBITAL_CANNON, 1.f, TRUE, TRUE, 1.f);

			if (MISC::GET_DISTANCE_BETWEEN_COORDS(campos.x, campos.y, campos.z, entpos.x, entpos.y, entpos.z, false) < 10)
				toxic::blame_explode_coord(g_player_service->get_selected(), entpos, eExplosionTag::EXP_TAG_ORBITAL_CANNON, 1.f, TRUE, TRUE, 1.f);
		}
		else
		{
			toxic::blame_explode_coord(g_player_service->get_self(), this->groundpos, eExplosionTag::EXP_TAG_ORBITAL_CANNON, 1.f, TRUE, TRUE, 1.f);
			if (MISC::GET_DISTANCE_BETWEEN_COORDS(campos.x, campos.y, campos.z, entpos.x, entpos.y, entpos.z, false) < 10)
				toxic::blame_explode_coord(g_player_service->get_self(), entpos, eExplosionTag::EXP_TAG_ORBITAL_CANNON, 1.f, TRUE, TRUE, 1.f);
		}


		if (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_xm_orbital"))
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_xm_orbital");

			for (int i = 0; i < 10 && !STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_xm_orbital"); i++)
			{
				script::get_current()->yield();
			}
		}

		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_xm_orbital"))
		{
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_xm_orbital");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_xm_orbital_blast",
			    this->groundpos.x,
			    this->groundpos.y,
			    this->groundpos.z,
			    0.f,
			    0.f,
			    0.f,
			    1.f,
			    0,
			    0,
			    0,
			    true);
		}
	}
}