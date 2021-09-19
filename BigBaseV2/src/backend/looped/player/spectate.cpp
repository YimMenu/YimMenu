#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	static bool bReset = true;

	void looped::player_specate()
	{
		if (!g.selected_player.is_online || !g.player.spectating)
		{
			if (g.player.spectating) g.player.spectating = false;

			if (!bReset)
			{
				bReset = true;

				g_pointers->m_spectate_player(false, -1);
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);
			}

			return;
		}

		Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id);

		g_pointers->m_spectate_player(true, target);
		HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);

		bReset = false;
	}
}