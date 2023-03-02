#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "backend/player_command.hpp"
#include "core/data/packet_types.hpp"
#include "gta/net_game_event.hpp"
#include "gta/script_id.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "natives.hpp"
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

		for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_player_count; i++)
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
						((player_command*)command::get(RAGE_JOAAT("breakup")))->call(player, {});
					}
					return true;
				}
				else
				{
					if (g.session.log_chat_messages)
						spam::log_chat(message, player, false);

					if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
						command::process(std::string(message + 1), std::make_shared<chat_command_context>(player));
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
			case rage::eNetMessage::MsgRemoveGamersFromSessionCmd:
			{
				player_ptr pl;
				uint64_t session_id;
				buffer.ReadQWord(&session_id, 64);
				uint32_t count;
				buffer.ReadDword(&count, 6);
				for (std::uint32_t i = 0; i < count; i++)
				{
					uint64_t peer_id;
					buffer.ReadQWord(&peer_id, 64);
					for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_peer_count; i++)
					{
						if (gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_peer_id_2 == peer_id)
						{
							pl = g_player_service->get_by_host_token(
							    gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_host_token);
							break;
						}
					}
				}

				if (player && pl && player->id() != pl->id() && count == 1 && frame->m_msg_id == -1)
				{
					if (g_player_service->get_self()->is_host())
					{
						g.reactions.breakup_others.process(player, pl);
						session::add_infraction(player, Infraction::BREAKUP_KICK_DETECTED);

						if (g.reactions.breakup_others.block)
							return true;

						if (g.reactions.breakup_others.karma)
							((player_command*)command::get(RAGE_JOAAT("breakup")))->call(player, {});
					}
					else
					{
						g.reactions.breakup_others.process(player, pl);
						session::add_infraction(player, Infraction::BREAKUP_KICK_DETECTED);

						if (g.reactions.breakup_others.karma)
							((player_command*)command::get(RAGE_JOAAT("breakup")))->call(player, {});
					}
				}

				break;
			}
			case rage::eNetMessage::MsgLostConnectionToHost:
			{
				uint64_t session_id;
				buffer.ReadQWord(&session_id, 64);
				rage::rlGamerHandle handle;
				gamer_handle_deserialize(handle, buffer);

				auto self = g_player_service->get_self();
				if (self->get_net_data() && self->get_net_data()->m_gamer_handle.m_rockstar_id == handle.m_rockstar_id)
				{
					session::add_infraction(player, Infraction::TRIED_KICK_PLAYER);
					g.reactions.lost_connection_kick.process(player);
					return true;
				}

				for (auto& [_, plyr] : g_player_service->players())
				{
					if (plyr->get_net_data() && plyr != player
					    && plyr->get_net_data()->m_gamer_handle.m_rockstar_id == handle.m_rockstar_id)
					{
						session::add_infraction(player, Infraction::LOST_CONNECTION_KICK_DETECTED);
						g.reactions.lost_connection_kick_others.process(player, plyr);

						if (g.reactions.lost_connection_kick_others.block)
							return true;
						else
							break;
					}
				}

				if (player->get_net_data() && player->get_net_data()->m_gamer_handle.m_rockstar_id == handle.m_rockstar_id)
					break;
				else
					return true;
			}
			case rage::eNetMessage::MsgNetComplaint:
			{
				uint64_t host_token{};
				buffer.ReadQWord(&host_token, 64);

				std::vector<CNetGamePlayer*> players;

				uint32_t num_of_tokens{};
				buffer.ReadDword(&num_of_tokens, 32);

				if (player && host_token != player->get_net_data()->m_host_token && !player->exposed_desync_protection)
				{
					session::add_infraction(player, Infraction::DESYNC_PROTECTION);
					player->exposed_desync_protection = true;
				}

				return true;// block desync kicks as host
			}
			case rage::eNetMessage::MsgRequestObjectIds:
			{
				if (player->block_join)
				{
					g_notification_service->push("BLOCK_JOIN"_T.data(),
					    std::vformat("BLOCK_JOIN_PREVENT_PLAYER_JOIN"_T, std::make_format_args(player->get_name())));
					return true;
				}
				break;
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
				uint32_t time_diff = (*g_pointers->m_network_time)->m_time_offset + frame->m_timestamp;

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
				if (is_kick_instruction(buffer))
				{
					g.reactions.gamer_instruction_kick.process(player);
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
			case rage::eNetMessage::MsgLostConnectionToHost:
			{
				uint64_t session_id;
				buffer.ReadQWord(&session_id, 64);
				rage::rlGamerHandle handle;
				gamer_handle_deserialize(handle, buffer);

				auto self = g_player_service->get_self();
				if (self->get_net_data() && self->get_net_data()->m_gamer_handle.m_rockstar_id == handle.m_rockstar_id)
				{
					g_notification_service->push_error("KICK"_T.data(), "REMOTE_KICK_LOST_CONNECTION"_T.data());
					return true;
				}

				for (auto& [_, plyr] : g_player_service->players())
				{
					if (plyr->get_net_data() && plyr->get_net_data()->m_gamer_handle.m_rockstar_id == handle.m_rockstar_id)
					{
						g_notification_service->push_error("KICK"_T.data(), std::vformat("REMOTE_KICK_LOST_CONNECTION_PLAYER"_T, std::make_format_args(plyr->get_name())));
						return true;
					}
				}

				return true;
			}
			case rage::eNetMessage::MsgRemoveGamersFromSessionCmd:
			{
				if (!g_player_service->get_self()->is_host())
					break;

				player_ptr target;
				uint64_t session_id;
				buffer.ReadQWord(&session_id, 64);
				uint32_t count;
				buffer.ReadDword(&count, 6);
				for (std::uint32_t i = 0; i < count; i++)
				{
					uint64_t peer_id;
					buffer.ReadQWord(&peer_id, 64);

					if (g_player_service->get_self()->get_net_data() && g_player_service->get_self()->get_net_data()->m_peer_id_2 == peer_id)
					{
						target = g_player_service->get_self();
					}
					else
					{
						for (std::uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_peer_count; i++)
						{
							if (gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_peer_id_2 == peer_id)
							{
								target = g_player_service->get_by_host_token(
								    gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_host_token);
								break;
							}
						}
					}
				}

				if (target && count == 1 && frame->m_msg_id == -1)
				{
					if (target->id() == g_player_service->get_self()->id())
						g_notification_service->push_error("KICK"_T.data(), "REMOTE_KICK_BREAKUP"_T.data());
					else
						g_notification_service->push_error("KICK"_T.data(),
						    std::vformat("REMOTE_KICK_BREAKUP_PLAYER"_T, std::make_format_args(target->get_name())));
				}

				return true;
			}
			case rage::eNetMessage::MsgTransitionGamerInstruction:
			{
				if (is_kick_instruction(buffer))
				{
					g_notification_service->push_error("KICK"_T.data(), "REMOTE_KICK_GAMER_INSTRUCTION"_T.data());
					return true;
				}
				break;
			}
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
