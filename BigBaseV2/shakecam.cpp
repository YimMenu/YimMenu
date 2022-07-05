#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{

	void looped::player_shakecam() {
		Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
		{
			if (g->player.shakecam && g_player_service->get_selected()->is_valid())
			{
				{
					Vector3 targetCords = ENTITY::GET_ENTITY_COORDS(PlayerPed, true);
					FIRE::ADD_EXPLOSION(targetCords.x, targetCords.y, targetCords.z, 0, 0.f, false, true, 1000.f, true);
				}
			}
		}
	}
}