#include "hooking.hpp"
#include "gta_util.hpp"
#include "services/players/player_service.hpp"
#include <network/Network.hpp>
#include <network/CMsgTextMessage.hpp>

namespace big
{
	bool hooks::send_chat_net_message(rage::netConnectionManager* mgr, int receiver_msg_id, CMsgTextMessage* msg, int flags, void* unk)
	{
		std::uint64_t host_token = -1;
		for (auto& [_, plyr] : g_player_service->players())
		{
			if (plyr->get_net_game_player()->m_msg_id == receiver_msg_id)
			{
				host_token = plyr->get_net_data()->m_host_token;
				break;
			}
		}

		if (g.m_spoofed_peer_ids.contains(host_token))
			msg->m_peer_id = g.m_spoofed_peer_ids[host_token];

		return g_hooking->get_original<hooks::send_chat_net_message>()(mgr, receiver_msg_id, msg, flags, unk);
	}
}