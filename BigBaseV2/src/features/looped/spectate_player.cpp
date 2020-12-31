#include "features.hpp"
#include "pointers.hpp"

namespace big
{
	void features::spectate_player()
	{
		if (g_selectedPlayer == -1 || !g_players[g_selectedPlayer].is_online || !g_temp.spectate_player)
		{
			if (g_temp.spectate_player) g_temp.spectate_player = false;

			g_pointers->m_spectate_player(false, -1);

			return;
		}

		g_pointers->m_spectate_player(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer));
	}
}