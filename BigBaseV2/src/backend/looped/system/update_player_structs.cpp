#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	static bool busy = false;

	void looped::system_update_players()
	{
		if (busy) return;
		busy = true;

		int friend_count = 0;
		int player_count = 0;

		for (Player i = 0; i < 32; i++)
		{
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i) && i != PLAYER::PLAYER_ID())
			{
				// if (!g.players[i].is_online) // tell user player joined

				g.players[i].id = i;
				g.players[i].is_online = true;

				int iNetworkHandle[26];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, &iNetworkHandle[0], 13);
				NETWORK::NETWORK_IS_HANDLE_VALID(&iNetworkHandle[0], 13) && NETWORK::NETWORK_IS_FRIEND(&iNetworkHandle[0]);

				if (NETWORK::NETWORK_IS_HANDLE_VALID(iNetworkHandle, 13) && NETWORK::NETWORK_IS_FRIEND(iNetworkHandle))
				{
					g.players[i].is_friend = true;

					friend_count++;
				}
				else player_count++;

				strcpy(g.players[i].name, PLAYER::GET_PLAYER_NAME(i));
			}
			else
			{
				g.players[i].is_online = false;
				g.players[i].is_friend = false;
			}

			script::get_current()->yield();
		}

		g.friend_count = friend_count;
		g.player_count = player_count;

		busy = false;
	}
}