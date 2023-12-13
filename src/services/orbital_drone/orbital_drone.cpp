#include "orbital_drone.hpp"

#include "backend/bool_command.hpp"
#include "gui.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script/globals/GlobalPlayerBD.hpp"
#include "services/players/player_service.hpp"
#include "util/entity.hpp"
#include "util/toxic.hpp"
#include "vehicle/CVehicle.hpp"


namespace big
{
	bool_command g_orbital_drone("orbitaldrone", "ORBITAL_DRONE", "ORBITAL_DRONE_DESC",
	    g.world.orbital_drone.enabled);

	static bool nav_override;
	static float nav_multiplier = 1.f;

	void orbital_drone::init()
	{
		if (m_initialized)
		{
			destroy();
			return;
		}

		if (g_local_player)
		{
			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].OrbitalBitset.Set(eOrbitalBitset::kOrbitalCannonActive);
			const auto player_pos = *g_local_player->get_position();

			m_start_pos = {player_pos.x, player_pos.y, player_pos.z};

			m_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
			CAM::SET_CAM_COORD(m_cam, player_pos.x, player_pos.y, player_pos.z + 100.f);
			CAM::SET_CAM_ROT(m_cam, -90.f, 0, 0, 2);
			CAM::SET_CAM_FOV(m_cam, 100.f);
			CAM::SET_CAM_ACTIVE(m_cam, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 1000, true, false, 0);

			m_scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("ORBITAL_CANNON_CAM");

			for (size_t i = 0; i < 10 && !GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleform); i++)
			{
				script::get_current()->yield();
			}

			if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleform))
			{
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleform, "showSurveillance");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0.f);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
			}

			HUD::SET_BIGMAP_ACTIVE(true, false);
			HUD::LOCK_MINIMAP_ANGLE(0);

			m_initialized = true;
		}
	}

	void orbital_drone::destroy()
	{
		m_initialized = false;

		Entity self = self::ped;
		if (PED::IS_PED_IN_ANY_VEHICLE(self, true))
			self = PED::GET_VEHICLE_PED_IS_IN(self, false);

		ENTITY::FREEZE_ENTITY_POSITION(self, 0);

		ENTITY::SET_ENTITY_VISIBLE(self, true, 0);

		CAM::RENDER_SCRIPT_CAMS(false, true, 1000, true, false, 0);

		Vector3 tp_pos = m_start_pos;

		if (m_should_tp)
		{
			tp_pos = m_ground_pos;

			if (m_ground_pos.z < PATHFIND::GET_APPROX_FLOOR_FOR_POINT(m_ground_pos.x, m_ground_pos.z))
				m_ground_pos.z = PATHFIND::GET_APPROX_FLOOR_FOR_POINT(m_ground_pos.x, m_ground_pos.z);
		}

		if (!m_should_tp)
			ENTITY::SET_ENTITY_COORDS(self, tp_pos.x, tp_pos.y, tp_pos.z, 0, 0, 0, 0);
		else
			ENTITY::SET_ENTITY_COORDS(self, tp_pos.x, tp_pos.y, tp_pos.z, 0, 0, 0, 0);

		CAM::SET_CAM_ACTIVE(m_cam, false);
		CAM::DESTROY_CAM(m_cam, 1);

		HUD::UNLOCK_MINIMAP_ANGLE();

		m_lock_ent = -1;
		m_lock     = false;

		scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].OrbitalBitset.Clear(eOrbitalBitset::kOrbitalCannonActive);
		m_should_tp = false;
	}

	void orbital_drone::cam_nav()
	{
		if (!m_initialized || !CAM::DOES_CAM_EXIST(m_cam))
			return;

		Vector3 campos   = CAM::GET_CAM_COORD(m_cam);
		Vector3 finalpos = CAM::GET_CAM_COORD(m_cam);

		MISC::GET_GROUND_Z_FOR_3D_COORD(finalpos.x, finalpos.y, finalpos.z, &finalpos.z, false, false);

		m_ground_pos = {campos.x, campos.y, finalpos.z};

		float minz = finalpos.z + 10;
		float maxz = 1500.f;

		if (campos.z < minz)
			CAM::SET_CAM_COORD(m_cam, campos.x, campos.y, minz);
		if (campos.z > maxz)
			CAM::SET_CAM_COORD(m_cam, campos.x, campos.y, maxz);

		HUD::SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME(campos.x, campos.y);

		Vector3 movepos;
		bool moved = false;

		float leftstick_xaxis  = PAD::GET_CONTROL_NORMAL(2, (int)ControllerInputs::INPUT_SCRIPT_LEFT_AXIS_X);
		float leftstick_yaxis  = -PAD::GET_CONTROL_NORMAL(2, (int)ControllerInputs::INPUT_SCRIPT_LEFT_AXIS_Y);
		float rightstick_yaxis = PAD::GET_CONTROL_NORMAL(2, (int)ControllerInputs::INPUT_SCRIPT_RIGHT_AXIS_Y);

		//LEFT
		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
		{
			if (leftstick_xaxis == 0)
				movepos = {campos.x - ((campos.z / 50) * nav_multiplier), campos.y, campos.z};
			else
				movepos = {campos.x + ((leftstick_xaxis * 5) * nav_multiplier), campos.y, campos.z};
			moved  = true;
			m_lock = false;
		}
		//RIGHT
		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_RIGHT) || PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_RIGHT))
		{
			if (leftstick_xaxis == 0)
				movepos = moved ? Vector3(movepos.x + ((movepos.z / 50) * nav_multiplier), movepos.y, movepos.z) :
				                  Vector3(campos.x + ((campos.z / 50) * nav_multiplier), campos.y, campos.z);
			else
				movepos = moved ? Vector3(movepos.x + ((leftstick_xaxis * 5) * nav_multiplier), movepos.y, movepos.z) :
				                  Vector3(campos.x + ((leftstick_xaxis * 5) * nav_multiplier), campos.y, campos.z);
			moved  = true;
			m_lock = false;
		}
		//UP
		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_UP_ONLY) || PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
		{
			if (leftstick_yaxis == 0)
				movepos = moved ? Vector3(movepos.x, movepos.y + ((movepos.z / 50) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y + ((campos.z / 50) * nav_multiplier), campos.z);
			else
				movepos = moved ? Vector3(movepos.x, movepos.y + ((leftstick_yaxis * 5) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y + ((leftstick_yaxis * 5) * nav_multiplier), campos.z);
			moved  = true;
			m_lock = false;
		}
		//DOWN
		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_DOWN) || PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_MOVE_DOWN))
		{
			if (leftstick_yaxis == 0)
				movepos = moved ? Vector3(movepos.x, movepos.y + ((movepos.z / 50) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y - ((campos.z / 50) * nav_multiplier), campos.z);
			else
				movepos = moved ? Vector3(movepos.x, movepos.y + ((leftstick_yaxis * 5) * nav_multiplier), movepos.z) :
				                  Vector3(campos.x, campos.y + ((leftstick_yaxis * 5) * nav_multiplier), campos.z);
			moved  = true;
			m_lock = false;
		}

		//ZOOM IN
		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_SLOWMO_UP_ONLY)
		    || PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_SLOWMO_UP_ONLY) && !g_gui->is_open())
		{
			if (campos.z > minz)
			{
				movepos = moved ? Vector3(movepos.x, movepos.y, movepos.z - movepos.z / 20) :
				                  Vector3(campos.x, campos.y, campos.z - campos.z / 20);
				moved   = true;
			}
		}

		//ZOOM OUT
		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_SLOWMO_DOWN_ONLY)
		    || PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_SLOWMO_DOWN_ONLY) && !g_gui->is_open())
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
			movepos = moved ? Vector3(movepos.x, movepos.y, movepos.z + (rightstick_yaxis * 5)) :
			                  Vector3(campos.x, campos.y, campos.z + (rightstick_yaxis * 5));
			moved   = true;
		}

		if (m_lock && ENTITY::DOES_ENTITY_EXIST(m_lock_ent) && m_lock_ent != -1)
		{
			Vector3 targetpos = ENTITY::GET_ENTITY_COORDS(m_lock_ent, 0);
			if (moved)
				CAM::SET_CAM_COORD(m_cam, targetpos.x, targetpos.y, movepos.z);
			else
				CAM::SET_CAM_COORD(m_cam, targetpos.x, targetpos.y, campos.z);
		}

		if (moved)
		{
			CAM::SET_CAM_COORD(m_cam, movepos.x, movepos.y, movepos.z);

			moved = false;
		}
	}

	void orbital_drone::tick()
	{
		if (!m_initialized)
			return;

		PAD::ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(2);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK2, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_MELEE_ATTACK_HEAVY, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_MELEE_ATTACK_LIGHT, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_MELEE_ATTACK1, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_MELEE_ATTACK2, true);
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_MELEE_BLOCK, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_FRONTEND_PAUSE_ALTERNATE, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_SELECT_NEXT_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_SELECT_PREV_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_VEH_NEXT_RADIO, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_VEH_PREV_RADIO, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_DUCK, true);
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_VEH_SPECIAL, true);
		HUD::DISPLAY_AMMO_THIS_FRAME(false);
		HUD::HUD_FORCE_WEAPON_WHEEL(false);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(19);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(2);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(1);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(3);
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(4);

		Vector3 cam_pos = CAM::GET_CAM_COORD(m_cam);
		Vector3 cam_rot = CAM::GET_CAM_ROT(m_cam, 0);

		Entity self = self::ped;
		if (PED::IS_PED_IN_ANY_VEHICLE(self, true) && VEHICLE::GET_PED_IN_VEHICLE_SEAT(self::veh, -1, false) == self)
			self = self::veh;

		ENTITY::SET_ENTITY_COORDS(self, cam_pos.x, cam_pos.y, cam_pos.z + 15, 0, 0, 0, 0);

		ENTITY::FREEZE_ENTITY_POSITION(self, 1);
		ENTITY::SET_ENTITY_VISIBLE(self, false, 0);

		cam_nav();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(m_scaleform, 255, 255, 255, 0, 1);

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_FRONTEND_RDOWN) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_FRONTEND_RDOWN))
		{
			m_should_tp = true;
			destroy();
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_JUMP)
		    || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_JUMP && !g_gui->is_open()))
		{
			m_lock_ent = entity::get_entity_closest_to_middle_of_screen();
			m_lock     = true;

			if (*g_pointers->m_gta.m_is_session_started && g.world.orbital_drone.detect_player)
				detect_player(m_lock_ent);
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_ATTACK) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_ATTACK))
		{
			orbital_cannon_explosion();
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_ARREST)
		    || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_ARREST) && !g_gui->is_open())
		{
			//For Future Features
		}

		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_PARACHUTE_BRAKE_RIGHT) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_PARACHUTE_BRAKE_RIGHT))
		{
			nav_override   = true;
			nav_multiplier = g.world.orbital_drone.nav_ovverride_fast;
		}

		if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_PARACHUTE_BRAKE_LEFT) || PAD::IS_DISABLED_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_PARACHUTE_BRAKE_LEFT))
		{
			nav_override   = true;
			nav_multiplier = g.world.orbital_drone.nav_ovverride_slow;
		}

		if (!nav_override)
			nav_multiplier = 1.f;
		else
			nav_override = false;
	}

	void orbital_drone::detect_player(Entity ent)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(ent))
			return;

		if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
		{
			const auto vehicle = reinterpret_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(ent));
			if (vehicle)
			{
				for (const auto& player : g_player_service->players() | std::ranges::views::values)
				{
					if (player && vehicle->m_driver)
					{
						if (player->get_ped() == vehicle->m_driver)
						{
							g_player_service->set_selected(player);
							return;
						}

						for (const auto ped : vehicle->m_passengers)
						{
							if (ped && player->get_ped() == ped)
							{
								g_player_service->set_selected(player);
								return;
							}
						}
					}
				}
			}
		}

		if (PED::IS_PED_A_PLAYER(ent))
		{
			for (auto player : g_player_service->players() | std::ranges::views::values)
			{
				if (player)
				{
					if (const auto ped_ptr = player->get_ped(); ped_ptr && g_pointers->m_gta.m_ptr_to_handle(ped_ptr) == ent)
					{
						g_player_service->set_selected(player);
					}
				}
			}
		}
	}

	void orbital_drone::orbital_cannon_explosion()
	{
		if (g_gui->is_open())
			return;

		Vector3 campos = CAM::GET_CAM_COORD(m_cam);
		Vector3 entpos = ENTITY::GET_ENTITY_COORDS(entity::get_entity_closest_to_middle_of_screen(), 0);

		toxic::blame_explode_coord(*g_pointers->m_gta.m_is_session_started ? g_player_service->get_self() : nullptr, m_ground_pos, eExplosionTag::EXP_TAG_ORBITAL_CANNON, 1.f, TRUE, TRUE, 1.f);
		if (MISC::GET_DISTANCE_BETWEEN_COORDS(campos.x, campos.y, campos.z, entpos.x, entpos.y, entpos.z, false) < 10)
			toxic::blame_explode_coord(*g_pointers->m_gta.m_is_session_started ? g_player_service->get_self() : nullptr, entpos, eExplosionTag::EXP_TAG_ORBITAL_CANNON, 1.f, TRUE, TRUE, 1.f);

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
			    m_ground_pos.x,
			    m_ground_pos.y,
			    m_ground_pos.z,
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