#include "features.hpp"
#include "pointers.hpp"

namespace big
{
	static bool bReset = true;
	void features::spectate_player()
	{
		if (g_selectedPlayerId == -1 || !g_selectedPlayer.is_online || !g_temp.spectate_player)
		{
			if (g_temp.spectate_player) g_temp.spectate_player = false;

			if (!bReset)
			{
				bReset = true;

				g_pointers->m_spectate_player(false, -1);
			}

			return;
		}

		g_pointers->m_spectate_player(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayerId));

		bReset = false;
	}
}