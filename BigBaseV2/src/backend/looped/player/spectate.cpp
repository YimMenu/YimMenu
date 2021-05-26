#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big
{
	static Ped spectated_ped = -1;
	static bool bLastSpectating = false;

	void looped::player_specate()
	{
		Ped player = PLAYER::GET_PLAYER_PED(g.selected_player.id);

		if (player != spectated_ped || (!bLastSpectating && bLastSpectating != g.player.spectating))
			g_pointers->m_spectate_player(g.player.spectating, player);

		bLastSpectating = g.player.spectating;
	}
}