#pragma once
#include "natives.hpp"
#include "pointers.hpp"
#include "gta_util.hpp"
#include "script.hpp"
#include "gta/enums.hpp"
#include "fiber_pool.hpp"
#include "script/globals/GlobalPlayerBD.hpp"
#include "core/scr_globals.hpp"


namespace big
{
	inline bool orbital_drone_t;

	class orbital_drone
	{

	private:
		void cam_nav();
		void orbital_cannon_explosion();
		void detect_player(Entity ent);
	public:
		Cam cam;
		bool lock;
		Entity lock_ent;
		Vector3 groundpos;
		Vector3 startpos;
		int scaleform;
		bool tp;
	public:
		bool initialized;
		void tick();
		void initialize()
		{
			if (this->initialized)
			{
				this->destruct();
				return;
			}

			if (*g_pointers->m_is_session_started && gta_util::get_network_player_mgr()->m_local_net_player
			    && gta_util::get_network_player_mgr()->m_local_net_player->m_player_info->m_ped)
			{
				rage::fvector3 playerpos =
				    *gta_util::get_network_player_mgr()->m_local_net_player->m_player_info->m_ped->m_navigation->get_position();

				this->startpos = {playerpos.x, playerpos.y, playerpos.z};

				this->cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
				CAM::SET_CAM_COORD(this->cam, playerpos.x, playerpos.y, playerpos.z + 100.f);
				CAM::SET_CAM_ROT(this->cam, -90.f, 0, 0, 2);
				CAM::SET_CAM_FOV(this->cam, 100.f);
				CAM::SET_CAM_ACTIVE(this->cam, true);
				CAM::RENDER_SCRIPT_CAMS(true, true, 1000, true, false, 0);

				this->scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("ORBITAL_CANNON_CAM");

				for (size_t i = 0; i < 10 && !GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->scaleform); i++)
				{
					script::get_current()->yield();
				}

				if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->scaleform))
				{
					GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->scaleform, "showSurveillance");
					GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(0.f);
					GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				}

				HUD::SET_BIGMAP_ACTIVE(true, false);
				HUD::LOCK_MINIMAP_ANGLE(0);

				this->initialized = true;
			}
		}
		void destruct()
		{
			initialized = false;

			Entity self = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(self, true))
				self = PED::GET_VEHICLE_PED_IS_IN(self, false);

			ENTITY::FREEZE_ENTITY_POSITION(self, 0);

			ENTITY::SET_ENTITY_VISIBLE(self, true, 0);

			CAM::RENDER_SCRIPT_CAMS(false, true, 1000, true, false, 0);

			Vector3 tppos = this->startpos;

			if (tp)
			{
				tppos = this->groundpos;

				if (groundpos.z < PATHFIND::GET_APPROX_FLOOR_FOR_POINT(groundpos.x, groundpos.z))
					groundpos.z = PATHFIND::GET_APPROX_FLOOR_FOR_POINT(groundpos.x, groundpos.z);
			}


			if (!tp)
				ENTITY::SET_ENTITY_COORDS(self, tppos.x, tppos.y, tppos.z, 0, 0, 0, 0);
			else
				ENTITY::SET_ENTITY_COORDS(self, tppos.x, tppos.y, tppos.z, 0, 0, 0, 0);

			CAM::SET_CAM_ACTIVE(this->cam, false);
			CAM::DESTROY_CAM(this->cam, 1);

			HUD::UNLOCK_MINIMAP_ANGLE();

			this->lock_ent = -1;
			this->lock     = false;

			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()].OrbitalBitset.Clear(eOrbitalBitset::kOrbitalCannonActive);
			tp = false;
		}

	};

	inline orbital_drone g_orbital_drone_service;

}