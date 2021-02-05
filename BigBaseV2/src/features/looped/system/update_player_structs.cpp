#include "features/sys.hpp"
#include <algorithm>
#include "fiber_pool.hpp"
#include  "script.hpp"

namespace big
{
	void sys::update_player_structs()
	{
		player players[32];

		for (uint8_t i = 0; i < 32; i++)
		{
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			{
				// if (!g_players[i].is_online) features::join_message((Player)i);

				players[i].id = i;
				players[i].is_online = true;

				int iNetworkHandle[26];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, &iNetworkHandle[0], 13);
				NETWORK::NETWORK_IS_HANDLE_VALID(&iNetworkHandle[0], 13) && NETWORK::NETWORK_IS_FRIEND(&iNetworkHandle[0]);

				players[i].is_friend = NETWORK::NETWORK_IS_HANDLE_VALID(iNetworkHandle, 13) && NETWORK::NETWORK_IS_FRIEND(iNetworkHandle);

				strcpy(players[i].name, PLAYER::GET_PLAYER_NAME(i));
			}
			else
			{
				players[i].is_online = false;
				players[i].is_friend = false;
			}

			script::get_current()->yield();
		}

		std::sort(std::begin(players), std::end(players));

		g_players.clear();
		for (uint8_t i = 0; i < 32; i++)
		{
			player player = players[i];

			if (player.id == PLAYER::PLAYER_ID()) g_player = player;

			g_players.emplace(player.id, player);
		}
	}
}