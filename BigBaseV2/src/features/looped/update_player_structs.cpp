#include "features.hpp"

namespace big
{
	void features::update_player_structs()
	{
		QUEUE_JOB_BEGIN_CLAUSE(= )
		{
			for (UINT16 i = 0; i < 32; i++)
			{
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
				{
					if (!g_players[i].is_online) features::join_message((Player)i);

					g_players[i].is_online = true;

					int iNetworkHandle[26];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, &iNetworkHandle[0], 13);
					NETWORK::NETWORK_IS_HANDLE_VALID(&iNetworkHandle[0], 13) && NETWORK::NETWORK_IS_FRIEND(&iNetworkHandle[0]);

					g_players[i].is_friend = NETWORK::NETWORK_IS_HANDLE_VALID(iNetworkHandle, 13) && NETWORK::NETWORK_IS_FRIEND(iNetworkHandle);

					strcpy(g_players[i].name, PLAYER::GET_PLAYER_NAME(i));
				}
				else
				{
					g_players[i].is_online = false;
					g_players[i].is_friend = false;
				}

				script::get_current()->yield();
			}
		}QUEUE_JOB_END_CLAUSE
	}
}