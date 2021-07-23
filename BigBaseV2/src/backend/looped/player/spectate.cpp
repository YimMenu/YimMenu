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
			}

			return;
		}

		g_pointers->m_spectate_player(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id));

		bReset = false;
	}
}