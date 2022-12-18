#include "hooking.hpp"
#include "gta_util.hpp"
#include <network/Network.hpp>
#include <network/RemoteGamerInfoMsg.hpp>

// https://stackoverflow.com/questions/8120062/generate-random-64-bit-integer
unsigned
static rand256()
{
	static unsigned const limit = RAND_MAX - RAND_MAX % 256;
	unsigned result = rand();
	while (result >= limit)
	{
		result = rand();
	}
	return result % 256;
}

unsigned long long
static rand64bits()
{
	unsigned long long results = 0ULL;
	for (int count = 8; count > 0; --count)
	{
		results = 256U * results + rand256();
	}
	return results;
}

namespace big
{
	bool hooks::add_player_to_session(rage::netConnectionManager* mgr, int receiver_msg_id, int* out_command_hndl, RemoteGamerInfoMsg* msg, int flags, void* unk)
	{
		if (msg->m_gamer_info.m_gamer_handle_2.m_rockstar_id == g_local_player->m_player_info->m_net_player_data.m_gamer_handle_2.m_rockstar_id && gta_util::get_network()->m_game_session_ptr->is_host() && g.protections.lessen_breakups)
		{
			std::uint64_t host_token = -1;

			auto session = gta_util::get_network()->m_game_session_ptr;
			for (int i = 0; i < session->m_player_count; i++)
			{
				if (session->m_players[i]->m_msg_id == receiver_msg_id)
				{
					host_token = session->m_players[i]->m_player_data.m_host_token;
					break;
				}
			}

			std::uint64_t peer_id = rand64bits();
			g.m_spoofed_peer_ids.emplace(host_token, peer_id);
			msg->m_gamer_info.m_peer_id_2 = peer_id;
		}

		return g_hooking->get_original<hooks::add_player_to_session>()(mgr, receiver_msg_id, out_command_hndl, msg, flags, unk);
	}
}