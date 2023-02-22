#include "gta_util.hpp"
#include "hooking.hpp"
#include "services/players/player_service.hpp"

#include <network/CMsgTextMessage.hpp>
#include <network/Network.hpp>

namespace big
{
	bool hooks::send_chat_net_message(rage::netConnectionManager* mgr, int receiver_msg_id, CMsgTextMessage* msg, int flags, void* unk)
	{
		if (g.m_spoofed_peer_ids.contains(msg->m_peer_id))
			msg->m_peer_id = g.m_spoofed_peer_ids[msg->m_peer_id];

		return g_hooking->get_original<hooks::send_chat_net_message>()(mgr, receiver_msg_id, msg, flags, unk);
	}
}