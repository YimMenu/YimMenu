#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/notify.hpp"

namespace big
{
	static bool busy = false;

	void looped::system_update_players()
	{
		if (busy) return;
		busy = true;

		for (Player i = 0; i < 32; i++)
		{
			CPlayer& player = g.players[i];

			if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
			{
				strcpy(g.players[i].name, PLAYER::GET_PLAYER_NAME(i));

				player.net_player = g_pointers->m_get_net_game_player(i);

				if (player.is_online)
					continue;

				player.id = i;
				player.is_online = true;

				int iNetworkHandle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, iNetworkHandle, 13);
				bool is_friend = NETWORK::NETWORK_IS_HANDLE_VALID(&iNetworkHandle[0], 13) && NETWORK::NETWORK_IS_FRIEND(&iNetworkHandle[0]);

				if (is_friend)
				{
					player.is_friend = true;

					g.friend_count++;
				}
				else g.player_count++;

				notify::player_joined(player);
			}
			else if (player.is_online)
			{
				if (player.is_friend) g.friend_count--;
				else g.player_count--;

				player.is_friend = false;
				player.is_online = false;
			}

			script::get_current()->yield();
		}

		busy = false;
	}
}