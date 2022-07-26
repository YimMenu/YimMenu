#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{

	void looped::player_freezeallplayers() {

		{
			for (int i = 0; i < 32; i++)
			{
				bool ExcludeSelf = self::id == i;

				if (!ExcludeSelf && g_player_service->get_selected()->is_valid())
				{

					if (g->player.freezeallplayers)
					{
						Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(PlayerPed);
						TASK::CLEAR_PED_TASKS(PlayerPed);
						TASK::CLEAR_PED_SECONDARY_TASK(PlayerPed);
					}
				}
			}
		}
	}
}