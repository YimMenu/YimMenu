#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include <natives.hpp>

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
		if (frame->get_type() == 4)
		{
			rage::datBitBuffer buffer((uint8_t*)frame->m_data, frame->m_length);
			buffer.m_flagBits = 1;
			rage::eNetMessage msgType;
			const auto player = g_player_service->get_by_msg_id(frame->m_msg_id);
			if (player && get_msg_type(msgType, buffer))
			{
				switch (msgType)
				{
				//Desync Kick
				case rage::eNetMessage::CMsgNetComplaint:
				{
					uint64_t hostToken;
					buffer.ReadQWord(&hostToken, 0x40);
					buffer.Seek(0);
					player_ptr sender = g_player_service->get_by_host_token(hostToken);
					sender->get_net_game_player()->m_complaints = USHRT_MAX; //Sender
					g_notification_service->push_warning("Blocked Kick", fmt::format("Desync kick from {}", sender->get_name()));
					buffer.Seek(0);
					return false;
				}

				case rage::eNetMessage::CMsgScriptMigrateHost:
				{
					if (std::chrono::system_clock::now() - player->m_last_transition_msg_sent < 200ms)
					{
						if (player->m_num_failed_transition_attempts++ == 20)
						{
							g_notification_service->push_error("Protections", fmt::format("{} tried to OOM kick you!", player->get_name()));
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

				}
			}
		}

		return g_hooking->m_receive_net_message_hook.get_original<decltype(&hooks::receive_net_message)>()(netConnectionManager, a2, frame);
	}
}
