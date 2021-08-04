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

		int friend_count = g.friend_count;
		int player_count = g.player_count;

		for (Player i = 0; i < 32; i++)
		{
			if (NETWORK::NETWORK_IS_PLAYER_ACTIVE(i))
			{
				if (g.players[i].is_online) continue;

				g.players[i].id = i;
				g.players[i].is_online = true;

				int iNetworkHandle[26];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, &iNetworkHandle[0], 13);
				bool is_friend = NETWORK::NETWORK_IS_HANDLE_VALID(&iNetworkHandle[0], 13) && NETWORK::NETWORK_IS_FRIEND(&iNetworkHandle[0]);

				if (is_friend)
				{
					g.players[i].is_friend = true;

					friend_count++;
				}
				else player_count++;

				strcpy(g.players[i].name, PLAYER::GET_PLAYER_NAME(i));

				g.players[i].net_player = g_pointers->m_get_net_game_player(i);

				notify::player_joined(g.players[i]);
			}
			else if (g.players[i].is_online)
			{
				if (g.players[i].is_friend) friend_count--;
				else player_count--;

				g.players[i].is_friend = false;
				g.players[i].is_online = false;
			}

			script::get_current()->yield();
		}

		g.friend_count = friend_count;
		g.player_count = player_count;

		busy = false;
	}
}