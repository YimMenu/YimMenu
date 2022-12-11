#include "common.hpp"
#include "packet.hpp"
#include "services/players/player_service.hpp"
#include "gta_util.hpp"
#include <network/Network.hpp>

namespace big
{
	packet::packet() :
		m_buffer(m_data, 0x4000)
	{
	}

	void packet::send(uint32_t msg_id)
	{
		g_pointers->m_queue_packet(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr, msg_id, m_data, (m_buffer.m_curBit + 7) >> 3, 1, nullptr);
	}
}