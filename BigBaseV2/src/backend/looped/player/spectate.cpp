#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/player_service.hpp"

namespace big
{
	static bool bReset = true;

	void looped::player_spectate()
	{
		if (!g_player_service->get_selected()->is_valid() || !g->player.spectating)
		{
			if (g->player.spectating) g->player.spectating = false;

			if (!bReset)
			{
				bReset = true;

				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, -1);
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);

				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
			}

			return;
		}

		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());

		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
		HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);

		ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);

		bReset = false;
	}
}