#include "backend/bool_command.hpp"
#include "backend/int_command.hpp"
#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	static bool bReset = true;

	void looped::player_spectate() 
	{
		const auto vehicle = self::veh;
		const auto ped     = self::ped;

		if (!g_player_service->get_selected()->is_valid() || !g.player.spectating)
		{
			if (g.player.spectating)
				g.player.spectating = false;

			if (!bReset)
			{
				bReset = true;

				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
				NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(false);
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);
				HUD::SET_BLIP_ALPHA(HUD::GET_MAIN_PLAYER_BLIP_ID(), 255);

				STREAMING::SET_FOCUS_ENTITY(ped);
			}

			return;
		}

		const auto target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());

		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
		NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(false);
		HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);
		HUD::SET_BLIP_ALPHA(HUD::GET_MAIN_PLAYER_BLIP_ID(), 255);

		STREAMING::SET_FOCUS_ENTITY(target);

		if (g.player.override_cam_distance)
			CAM::SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(1.f, (float)g.player.cam_distance);

		bReset = false;
	}

	bool_command g_override_cam_distance("overridecamdistance", "BACKEND_LOOPED_PLAYER_OVERRIDE_CAM_DISTANCE", "BACKEND_LOOPED_PLAYER_OVERRIDE_CAM_DISTANCE_DESC", g.player.override_cam_distance);
	int_command g_override_cam_distance_int("overridecamdistanceint", "BACKEND_LOOPED_PLAYER_OVERRIDE_CAM_DISTANCE_INT", "BACKEND_LOOPED_PLAYER_OVERRIDE_CAM_DISTANCE_INT_DESC", g.player.cam_distance, 1, 200);
}
