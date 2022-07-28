#include "backend/looped/looped.hpp"
#include "services/players/player_service.hpp"
#include "natives.hpp"

namespace big
{
	void looped::self_aimbot()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;
		if (g->self.aimbot && !NETWORK::NETWORK_IS_IN_SPECTATOR_MODE() && !NETWORK::NETWORK_IS_ACTIVITY_SPECTATOR() && !HUD::IS_PAUSE_MENU_ACTIVE() && !ENTITY::IS_ENTITY_DEAD(self::ped, false))
		{
			for (auto& item : g_player_service->players())
			{
				if (auto const& plyr = item.second;
					plyr->id() != self::id && GetAsyncKeyState(VK_LBUTTON))
				{
					if (auto const targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr->id());
						ENTITY::DOES_ENTITY_EXIST(targetPed) && ENTITY::GET_ENTITY_HEALTH(targetPed) > 0)
					{
						if (g->self.aimbot_exclude_friend && plyr->is_friend()) continue;

						auto const playerPos = ENTITY::GET_ENTITY_COORDS(self::ped, true);
						auto const targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, true);

						float screenX, screenY;
						if (auto const distance = SYSTEM::VDIST(playerPos.x, playerPos.y, playerPos.z, targetPos.x, targetPos.y, targetPos.z);
							GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY)
							&& ENTITY::IS_ENTITY_VISIBLE(targetPed)
							&& (distance < 500 && distance > 2)
							&& ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, targetPed, 17))
						{
							Vector3 selfPed = ENTITY::GET_ENTITY_COORDS(self::ped, true);
							auto const targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0); //For Head ->31086, For Neck ->39317
							PED::SET_PED_SHOOTS_AT_COORD(self::ped, targetCoords.x, targetCoords.y, targetCoords.z, true);
							GRAPHICS::DRAW_LINE(selfPed.x, selfPed.y, selfPed.z, targetCoords.x, targetCoords.y, targetCoords.z, 208, 0, 240, 255);
						}
					}
				}
			}
		}
	}
}