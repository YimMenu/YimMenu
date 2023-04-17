#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"

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
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);

				ENTITY::FREEZE_ENTITY_POSITION(ped, false);
				ENTITY::FREEZE_ENTITY_POSITION(vehicle, false);

				STREAMING::SET_FOCUS_ENTITY(ped);
			}

			return;
		}

		const auto target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());

		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
		HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);

		ENTITY::FREEZE_ENTITY_POSITION(ped, true);
		ENTITY::FREEZE_ENTITY_POSITION(vehicle, true);

		STREAMING::SET_FOCUS_ENTITY(target);

		bReset = false;
	}
}
