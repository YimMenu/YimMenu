#include "features/util.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	static bool bReset = true;

	void util::spectate_player()
	{
		if (g_selectedPlayer.id == -1 || !g_selectedPlayer.is_online || !g_temp.is_spectating)
		{
			if (g_temp.is_spectating) g_temp.is_spectating = false;

			if (!bReset)
			{
				bReset = true;

				g_pointers->m_spectate_player(false, -1);
			}

			return;
		}

		g_pointers->m_spectate_player(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_selectedPlayer.id));

		bReset = false;
	}
}