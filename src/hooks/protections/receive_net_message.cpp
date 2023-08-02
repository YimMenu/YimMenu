#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "backend/player_command.hpp"
#include "core/data/packet_types.hpp"
#include "gta/net_game_event.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "lua/lua_manager.hpp"
#include "natives.hpp"
#include "script/scriptIdBase.hpp"
#include "services/players/player_service.hpp"
#include "util/session.hpp"
#include "util/spam.hpp"

#include <network/Network.hpp>
#include <network/netTime.hpp>


inline void gamer_handle_deserialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
{
	constexpr int PC_PLATFORM = 3;
	if ((hnd.m_platform = buf.Read<uint8_t>(8)) != PC_PLATFORM)
		return;

	buf.ReadInt64((int64_t*)&hnd.m_rockstar_id, 64);
	hnd.unk_0009 = buf.Read<uint8_t>(8);
}

inline bool is_kick_instruction(rage::datBitBuffer& buffer)
{
	rage::rlGamerHandle sender, receiver;
	char name[18];
	gamer_handle_deserialize(sender, buffer);
	gamer_handle_deserialize(receiver, buffer);
	buffer.ReadString(name, 17);
	int instruction = buffer.Read<int>(32);
	return instruction == 8;
}

namespace big
{
	bool get_msg_type(rage::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
		    buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1))
		{
			msgType = rage::eNetMessage::MsgInvalid;
			return false;
		}
		length = extended ? 16 : 8;
		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
		    length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash      = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}

	bool hooks::receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame)
	{
		if (frame->get_event_type() != rage::netConnection::InFrame::EventType::FrameReceived)
			return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);

		if (frame->m_data == nullptr || frame->m_length == 0)
			return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);

		rage::datBitBuffer buffer(frame->m_data, frame->m_length);
		buffer.m_flagBits = 1;

		rage::eNetMessage msgType;
		player_ptr player;

		for (uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_player_count; i++)
		{
			if (gta_util::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_peer_id_2 == frame->m_peer_id)
			{
				player = g_player_service->get_by_host_token(
				    gta_util::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token);
				break;
			}
		}

		if (!get_msg_type(msgType, buffer))
			return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);

		if (player)
		{
			switch (msgType)
			{
			case rage::eNetMessage::MsgTextMessage:
			case rage::eNetMessage::MsgTextMessage2:
			{
				char message[256];
				buffer.ReadString(message, 256);

				if (player->is_spammer)
					return true;

				if (spam::is_text_spam(message))
				{
					if (g.session.log_chat_messages)
						spam::log_chat(message, player, true);
					player->is_spammer = true;
					if (g.session.kick_chat_spammers)
					{
						if (g_player_service->get_self()->is_host())
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("breakup")))->call(player, {}),
							    dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(player, {});

						dynamic_cast<player_command*>(command::get(RAGE_JOAAT("endkick")))->call(player, {});
						dynamic_cast<player_command*>(command::get(RAGE_JOAAT("nfkick")))->call(player, {});
					}
					return true;
				}
				else
				{
					if (g.session.log_chat_messages)
						spam::log_chat(message, player, false);

					if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
						command::process(std::string(message + 1), std::make_shared<chat_command_context>(player));
					else
						g_lua_manager->trigger_event<menu_event::ChatMessageReceived>(player->id(), message);

					if (msgType == rage::eNetMessage::MsgTextMessage && g_pointers->m_gta.m_chat_data && player->get_net_data())
					{
						rage::rlGamerHandle temp{};
						gamer_handle_deserialize(temp, buffer);
						bool is_team = buffer.Read<bool>(1);

						g_pointers->m_gta.m_handle_chat_message(*g_pointers->m_gta.m_chat_data,
						    nullptr,
						    &player->get_net_data()->m_gamer_handle,
						    message,
						    is_team);
						return true;
					}
				}
				break;
			}
			case rage::eNetMessage::MsgScriptMigrateHost:
			{
				if (player->m_host_migration_rate_limit.process())
				{
					if (player->m_host_migration_rate_limit.exceeded_last_process())
					{
						session::add_infraction(player, Infraction::TRIED_KICK_PLAYER);
						g_notification_service->push_error("PROTECTIONS"_T.data(),
						    std::vformat("OOM_KICK"_T, std::make_format_args(player->get_name())));
					}
					return true;
				}
				break;
			}
			case rage::eNetMessage::MsgNetComplaint:
			{
				uint64_t host_token{};
				buffer.ReadQWord(&host_token, 64);
				if (player && host_token != player->get_net_data()->m_host_token && !player->exposed_desync_protection)
				{
					session::add_infraction(player, Infraction::DESYNC_PROTECTION);
					player->exposed_desync_protection = true;
				}
				return true;
			}
			case rage::eNetMessage::MsgScriptHostRequest:
			{
				CGameScriptId script;
				script_id_deserialize(script, buffer);

				if (script.m_hash == RAGE_JOAAT("freemode") && g.session.force_script_host)
					return true;

				break;
			}
			case rage::eNetMessage::MsgNetTimeSync:
			{
				int action         = buffer.Read<int>(2);
				uint32_t counter   = buffer.Read<uint32_t>(32);
				uint32_t token     = buffer.Read<uint32_t>(32);
				uint32_t timestamp = buffer.Read<uint32_t>(32);
				uint32_t time_diff = (*g_pointers->m_gta.m_network_time)->m_time_offset + frame->m_timestamp;

				if (action == 0)
				{
					player->player_time_value = timestamp;
					player->player_time_value_received_time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
					if (!player->time_difference || time_diff > player->time_difference.value())
						player->time_difference = time_diff;
				}
				break;
			}
			case rage::eNetMessage::MsgTransitionGamerInstruction:
			{
				// it doesn't work but a certain p2c uses it
				if (is_kick_instruction(buffer))
				{
					g.reactions.gamer_instruction_kick.process(player);
					return true;
				}
				break;
			}
			case rage::eNetMessage::MsgKickPlayer:
			{
				KickReason reason = buffer.Read<KickReason>(3);

				if (!player->is_host())
					return true;

				if (reason == KickReason::VOTED_OUT)
				{
					g_notification_service->push_warning("Protections", "You have been kicked by the host");
					return true;
				}

				break;
			}
			case rage::eNetMessage::MsgRadioStationSyncRequest:
			{
				if (player->block_radio_requests)
					return true;

				if (player->m_radio_request_rate_limit.process())
				{
					if (player->m_radio_request_rate_limit.exceeded_last_process())
					{
						session::add_infraction(player, Infraction::TRIED_KICK_PLAYER);
						g_notification_service->push_error("PROTECTIONS"_T.data(),
						    std::vformat("OOM_KICK"_T, std::make_format_args(player->get_name())));
						player->block_radio_requests = true;
					}
					return true;
				}

				break;
			}
			}
		}
		else
		{
			switch (msgType)
			{
			case rage::eNetMessage::MsgScriptMigrateHost: return true;
			case rage::eNetMessage::MsgRadioStationSyncRequest: return true;
			}
		}

		if (g.debug.logs.packet_logs && msgType != rage::eNetMessage::MsgCloneSync && msgType != rage::eNetMessage::MsgPackedCloneSyncACKs && msgType != rage::eNetMessage::MsgPackedEvents && msgType != rage::eNetMessage::MsgPackedReliables && msgType != rage::eNetMessage::MsgPackedEventReliablesMsgs && msgType != rage::eNetMessage::MsgNetArrayMgrUpdate && msgType != rage::eNetMessage::MsgNetArrayMgrSplitUpdateAck && msgType != rage::eNetMessage::MsgNetArrayMgrUpdateAck && msgType != rage::eNetMessage::MsgScriptHandshakeAck && msgType != rage::eNetMessage::MsgScriptHandshake && msgType != rage::eNetMessage::MsgScriptJoin && msgType != rage::eNetMessage::MsgScriptJoinAck && msgType != rage::eNetMessage::MsgScriptJoinHostAck && msgType != rage::eNetMessage::MsgRequestObjectIds && msgType != rage::eNetMessage::MsgInformObjectIds && msgType != rage::eNetMessage::MsgNetTimeSync)
		{
			const char* packet_type = "<UNKNOWN>";
			for (const auto& p : packet_types)
			{
				if (p.second == (int)msgType)
				{
					packet_type = p.first;
					break;
				}
			}

			LOG(VERBOSE) << "RECEIVED PACKET | Type: " << packet_type << " | Length: " << frame->m_length << " | Sender: "
			             << (player ? player->get_name() :
			                          std::format("<M:{}>, <C:{:X}>, <P:{}>",
			                              (int)frame->m_msg_id,
			                              frame->m_connection_identifier,
			                              frame->m_peer_id)
			                              .c_str())
			             << " | " << HEX_TO_UPPER((int)msgType);
		}

		return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);
	}
}
