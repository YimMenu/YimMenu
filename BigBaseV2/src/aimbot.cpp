#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "./views/view.hpp"
#include "util/misc.hpp"

namespace big
{

	void aim(bool boolean)
	{
		if (boolean)
		{
			Player player = self::id;
			Ped playerPed = self::ped;

			for (auto& item : g_player_service->m_players)
			{
				const auto& plyr = item.second;
				if (plyr->id() != self::id)
				{
					if (GetAsyncKeyState(VK_LBUTTON))
					{
						Ped targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr->id());
						bool ff = true;
						BOOL exists = ENTITY::DOES_ENTITY_EXIST(targetPed);


						Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, true);
						int health = ENTITY::GET_ENTITY_HEALTH(targetPed);
						Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true);
						float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, targetPos.x, targetPos.y, targetPos.z, TRUE);
						if (exists && health > 0 && ff)
						{
							float screenX, screenY;
							BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
							if (ENTITY::IS_ENTITY_VISIBLE(targetPed) && onScreen && (distance < 500 && distance > 2))
							{
								if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, targetPed, 17))
								{
									Vector3 targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0); //For Head ->31086, For Neck ->39317
									PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, true);
								}
							}
						}
					}
				}
			}

			//for (int i = 0; i < 32; i++)
			//{
			//	if (i != player)
			//	{
			//		if (GetAsyncKeyState(VK_LBUTTON))
			//		{

			//			Ped targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			//			bool ff = true;
			//			BOOL exists = ENTITY::DOES_ENTITY_EXIST(targetPed);


			//			Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, true);
			//			int health = ENTITY::GET_ENTITY_HEALTH(targetPed);
			//			Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, true);
			//			float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, targetPos.x, targetPos.y, targetPos.z, TRUE);
			//			if (exists && health > 0 && ff)
			//			{
			//				float screenX, screenY;
			//				BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
			//				if (ENTITY::IS_ENTITY_VISIBLE(targetPed) && onScreen && (distance < 500 && distance > 2))
			//				{
			//					if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, targetPed, 17))
			//					{
			//						Vector3 targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0); //For Head ->31086, For Neck ->39317
			//						PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, true);
			//					}
			//				}
			//			}
			//		}
			//	}
			//}

		}

	}


	bool boolaim = false;
	void looped::self_aim()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;
		bool bchek = g->self.aim;
		if (bchek || (!bchek && bchek != boolaim))
		{

			aim(g->self.aim);
			bchek = g->self.aim;



		}


	}
}