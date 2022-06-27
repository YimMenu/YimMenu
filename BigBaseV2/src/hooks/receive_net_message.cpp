#include "hooking.hpp"
#include "services/player_service.hpp"

namespace big
{

	inline bool get_message_type(rage::netConnection::MessageType& msg_type, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1))
		{
			msg_type = rage::netConnection::MessageType::MsgInvalid;
			return false;
		}

		length = extended ? 16 : 8;

		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit), length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msg_type, length))
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
			rage::netConnection::MessageType msg_type;

			const auto player = g_player_service->get_by_msg_id(frame->m_msg_id);
			if (player && get_message_type(msg_type, buffer))
			{
				switch (msg_type)
				{
					//Desync Kick
					case rage::netConnection::MessageType::MsgNetComplaint:
					{
						uint64_t host_token{};
						buffer.ReadQWord(&host_token, 64);

						std::vector<CNetGamePlayer*> players;

						uint32_t num_of_host_token{};
						buffer.ReadDword(&num_of_host_token, 32);

						if (num_of_host_token <= 64) {

							std::vector<uint64_t> host_token_list{};
							for (uint32_t i = 0; i < num_of_host_token; i++) {

								uint64_t array_element{};
								buffer.ReadQWord(&array_element, 64);
								host_token_list.push_back(array_element);

								const auto big_player = g_player_service->get_by_host_token(array_element);
								if (big_player)
									if (CNetGamePlayer* net_player = big_player->get_net_game_player())
										players.push_back(net_player);
							}

						}

						buffer.Seek(0);

						if (!players.empty())
						{
							const auto& player = players.at(0);
							if (player && player->is_valid())
							{
								player->m_complaints = 65535;
								g_notification_service->push_warning("Blocked Kick", std::string("Blocked desync kick from ") + player->get_name());
							}
						}

						return false;
					}

				}
			}
		}

		return g_hooking->m_receive_net_message_hook.get_original<decltype(&hooks::receive_net_message)>()(netConnectionManager, a2, frame);
	}
}
