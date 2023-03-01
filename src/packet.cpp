#include "packet.hpp"

#include "common.hpp"
#include "gta_util.hpp"
#include "services/players/player_service.hpp"

#include <network/Network.hpp>

namespace big
{
	packet::packet() :
	    m_buffer(m_data, 0x4000)
	{
	}

	void packet::send(uint32_t msg_id)
	{
		g_pointers->m_queue_packet(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
		    msg_id,
		    m_data,
		    (m_buffer.m_curBit + 7) >> 3,
		    1,
		    nullptr);
	}

	void packet::send(player_ptr player, int connection_id)
	{
		send(player->get_session_player()->m_player_data.m_peer_id_2, connection_id);
	}

	void packet::send(int peer_id, int connection_id)
	{
		auto mgr  = gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr;
		auto peer = g_pointers->m_get_connection_peer(mgr, peer_id);
		g_pointers->m_send_packet(mgr, peer, connection_id, m_data, (m_buffer.m_curBit + 7) >> 3, 0x1000000);
	}
}