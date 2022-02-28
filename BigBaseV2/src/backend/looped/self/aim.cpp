#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{

	void aim(bool boolean)
	{
		if (boolean)
		{
			int player = PLAYER::PLAYER_ID();
			int playerPed = PLAYER::PLAYER_PED_ID();
			int iNetworkHandle[13];


			for (int i = 0; i < 32; i++)
			{
				if (i != player)
				{
					if (GetAsyncKeyState(VK_XBUTTON2))
					{
						Ped targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, iNetworkHandle, 13);
						bool is_friend = NETWORK::NETWORK_IS_HANDLE_VALID(&iNetworkHandle[0], 13) && NETWORK::NETWORK_IS_FRIEND(&iNetworkHandle[0]);
						bool ff = false;
						if (g->self.friends)
						{
							ff = true;

						}
						else if (!g->self.friends)
						{
							if (is_friend)
							{
								ff = false;
							}
							else if (!is_friend)
							{
								ff = true;
							}
						}
						Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, true);
						BOOL exists = ENTITY::DOES_ENTITY_EXIST(targetPed);
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
									Vector3 targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0);
									PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, true);
								}
							}
						}
					}
				}
			}

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