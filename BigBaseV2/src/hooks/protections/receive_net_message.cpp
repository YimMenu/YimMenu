#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include <natives.hpp>
#include "gta_util.hpp"

namespace big
{
	bool get_msg_type(rage::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1)) {
			msgType = rage::eNetMessage::CMsgInvalid;
			return false;
		}
		length = extended ? 16 : 8;
		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit), length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	bool hooks::receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame)
	{
		if (frame->get_event_type() == rage::netConnection::InFrame::EventType::FrameReceived)
		{
			rage::datBitBuffer buffer((uint8_t*)frame->m_data, frame->m_length);
			buffer.m_flagBits = 1;
			rage::eNetMessage msgType;
			player_ptr player;
			for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_player_count; i++)
			{
				if (gta_util::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_peer_id_2 == frame->m_peer_id)
				{
					player = g_player_service->get_by_host_token(gta_util::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token);
					break;
				}
			}
			if (player && get_msg_type(msgType, buffer))
			{
				switch (msgType)
				{
				case rage::eNetMessage::CMsgScriptMigrateHost:
				{
					if (std::chrono::system_clock::now() - player->m_last_transition_msg_sent < 200ms)
					{
						if (player->m_num_failed_transition_attempts++ == 20)
						{
							g_notification_service->push_error("Protections", std::format("{} tried to OOM kick you!", player->get_name()));
						}
						return true;
					}
					else
					{
						player->m_last_transition_msg_sent = std::chrono::system_clock::now();
						player->m_num_failed_transition_attempts = 0;
					}
					break;
				}
				case rage::eNetMessage::CMsgRemoveGamersFromSessionCmd:
				{
					player_ptr pl;
					uint64_t session_id;
					buffer.ReadQWord(&session_id, 64);
					uint32_t count;
					buffer.ReadDword(&count, 6);
					pl = nullptr;
					for (std::uint32_t i = 0; i < count; i++)
					{
						uint64_t peer_id;
						buffer.ReadQWord((uint64_t*)&peer_id, 64);
						for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_peer_count; i++)
						{
							if (gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_peer_id_2 == peer_id)
							{
								pl = g_player_service->get_by_host_token(gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_host_token);
								break;
							}
						}
					}
					if (player && pl && player->id() != pl->id() && count == 1 && frame->m_msg_id == -1)
					{
						g_notification_service->push_error("Warning!", std::format("{} breakup kicked {}!", player->get_name(), pl->get_name()));
					}
					break;
				}
				}
			}
		}

		return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);
	}
}
