#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{

	void looped::player_freezeplayer() {
		Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
		{
			if (g->player.freezeplayer && g_player_service->get_selected()->is_valid())
			{
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(PlayerPed);
				TASK::CLEAR_PED_TASKS(PlayerPed);
				TASK::CLEAR_PED_SECONDARY_TASK(PlayerPed);
			}
		}
	}
}