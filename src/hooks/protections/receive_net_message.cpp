#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "backend/player_command.hpp"
#include "core/data/packet_types.hpp"
#include "gta/enums.hpp"
#include "gta/net_game_event.hpp"
#include "gta_util.hpp"
#include "hooking/hooking.hpp"
#include "lua/lua_manager.hpp"
#include "natives.hpp"
#include "script/scriptIdBase.hpp"
#include "services/players/player_service.hpp"
#include "util/chat.hpp"
#include "util/session.hpp"

#include <network/Network.hpp>
#include <network/netTime.hpp>
#include <network/P2pSecurity.hpp>


inline void gamer_handle_deserialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
{
	if ((hnd.m_platform = buf.Read<uint8_t>(sizeof(hnd.m_platform) * 8)) != rage::rlPlatforms::PC)
		return;

	buf.ReadRockstarId(&hnd.m_rockstar_id);
	hnd.m_padding = buf.Read<uint8_t>(sizeof(hnd.m_padding) * 8);
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
	bool try_read_secondary_header(rage::datBitBuffer& buffer)
	{
		auto data = buffer.Read<std::uint32_t>(20);
		return data == 0x8C253 || data == 0x8924F;
	}

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
		else
			id.m_position_hash = 0;

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
		else
			id.m_instance_id = -1;
	}

	static void script_id_serialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		buffer.Write<uint32_t>(id.m_hash, 32);
		buffer.Write<uint32_t>(id.m_timestamp, 32);

		if (id.m_position_hash != 0)
		{
			buffer.Write<bool>(true, 1);
			buffer.Write<uint32_t>(id.m_position_hash, 32);
		}
		else
		{
			buffer.Write<bool>(false, 1);
		}

		if (id.m_instance_id != -1)
		{
			buffer.Write<bool>(true, 1);
			buffer.Write<int32_t>(id.m_instance_id, 8);
		}
		else
		{
			buffer.Write<bool>(false, 1);
		}
	}

	void log_net_message(rage::eNetMessage message_type, rage::datBitBuffer& data_buffer, rage::netConnection::InFrame* frame)
	{
		if (g.debug.logs.packet_logs == 1 || //ALL
		    (g.debug.logs.packet_logs == 2 && message_type != rage::eNetMessage::MsgCloneSync && message_type != rage::eNetMessage::MsgPackedCloneSyncACKs && message_type != rage::eNetMessage::MsgPackedEvents && message_type != rage::eNetMessage::MsgPackedReliables && message_type != rage::eNetMessage::MsgPackedEventReliablesMsgs && message_type != rage::eNetMessage::MsgNetArrayMgrUpdate && message_type != rage::eNetMessage::MsgNetArrayMgrSplitUpdateAck && message_type != rage::eNetMessage::MsgNetArrayMgrUpdateAck && message_type != rage::eNetMessage::MsgScriptHandshakeAck && message_type != rage::eNetMessage::MsgScriptHandshake && message_type != rage::eNetMessage::MsgScriptJoin && message_type != rage::eNetMessage::MsgScriptJoinAck && message_type != rage::eNetMessage::MsgScriptJoinHostAck && message_type != rage::eNetMessage::MsgRequestObjectIds && message_type != rage::eNetMessage::MsgInformObjectIds && message_type != rage::eNetMessage::MsgNetTimeSync)) //FILTERED
		{
			const char* packet_type = "<UNKNOWN>";
			for (const auto& p : packet_types)
			{
				if (p.second == (int)message_type)
				{
					packet_type = p.first;
					break;
				}
			}

			auto now        = std::chrono::system_clock::now();
			auto ms         = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
			auto timer      = std::chrono::system_clock::to_time_t(now);
			auto local_time = *std::localtime(&timer);

			auto peer = g_pointers->m_gta.m_get_peer_by_security_id(frame->m_security_id);

			std::string name = "";
			rage::rlGamerHandle rid{};

			if (peer)
			{
				if (peer->m_info.handle.m_platform == 3)
					rid = peer->m_info.handle;
				else if (peer->m_unverified_handle.m_platform == 3)
					rid = peer->m_unverified_handle;
				name = peer->m_info.name;
			}

			if (name.empty())
				name = "???";

			std::string log_msg = std::format("PKT | {} (0x{:X}) [size=0x{:X}, cxnId={:X}, peerId={}, msgId={}] from {} ({})",
			    packet_type,
			    (int)message_type,
			    frame->m_length,
			    frame->m_connection_identifier,
			    frame->m_peer_id,
			    frame->m_msg_id,
			    name,
			    rid.m_rockstar_id);

			std::ostringstream pkt_data_log;


			static std::ofstream log(g_file_manager.get_project_file("./packets.log").get_path(), std::ios::app);
			log << "[" << std::put_time(&local_time, "%m/%d/%Y %I:%M:%S") << ":" << std::setfill('0') << std::setw(3) << ms.count() << " " << std::put_time(&local_time, "%p") << "] " << log_msg << std::endl;
			log.flush();

			LOG(VERBOSE) << log_msg;
		}
	}

	bool is_host_of_session(rage::snSession* session, std::uint32_t peer_id)
	{
		if (!session || peer_id != -1)
			return false;

		if (auto player = session->get_player_by_token(session->m_host_token))
			return player->m_player_data.m_peer_id_2 == peer_id;

		return false;
	}

	bool handle_block_script(player_ptr player, CGameScriptId& script, int msg_id)
	{
		if (script.m_hash == "carmod_shop"_J)
		{
			LOGF(stream::net_messages, WARNING, "Denying script request from {} (hash={:X}, instance={})", player->get_name(), script.m_hash, script.m_instance_id);

			packet pkt;
			pkt.write_message(rage::eNetMessage::MsgScriptJoinHostAck);
			script_id_serialize(script, pkt.m_buffer);
			pkt.write<int16_t>(-1, 16);
			pkt.write<int16_t>(-1, 16);
			pkt.write<bool>(false, 1);
			pkt.write<int>(2, 3);
			pkt.send(msg_id);

			return true;
		}

		return false;
	}

	bool hooks::receive_net_message(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame)
	{
		if (frame->get_event_type() != rage::netConnection::InFrame::EventType::FrameReceived && frame->get_event_type() != (rage::netConnection::InFrame::EventType)0)
			return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);

		if (frame->m_data == nullptr || frame->m_length == 0 || frame->m_connection_identifier == 2)
			return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);

		rage::datBitBuffer buffer(frame->m_data, frame->m_length);
		buffer.m_flagBits = 1;

		if (try_read_secondary_header(buffer))
		{
			buffer = rage::datBitBuffer(((char*)frame->m_data) + 7, frame->m_length - 7);
			buffer.m_flagBits = 1;
		}
		else
		{
			buffer.Seek(0);
		}

		rage::eNetMessage msgType;

		if (!get_msg_type(msgType, buffer))
		{
			LOGF(stream::net_messages, WARNING, "Received message that we cannot parse from cxn id {}", frame->m_connection_identifier);
			return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);
		}

		if (g.debug.logs.packet_logs) [[unlikely]]
		{
			log_net_message(msgType, buffer, frame);
		}

		rage::snSession* session = nullptr; // game unless proven otherwise

		if (gta_util::get_network()->m_transition_session_ptr
		    && gta_util::get_network()->m_transition_session_ptr->m_connection_identifier == frame->m_connection_identifier)
		{
			session = gta_util::get_network()->m_transition_session_ptr;
		}
		else
		{
			session = gta_util::get_network()->m_game_session_ptr;
		}

		player_ptr player = nullptr; // WILL be null until we get their physical

		for (uint32_t i = 0; i < gta_util::get_network()->m_game_session_ptr->m_player_count; i++)
		{
			if (auto player_iter = gta_util::get_network()->m_game_session_ptr->m_players[i])
			{
				if (frame && player_iter->m_player_data.m_peer_id_2 == frame->m_peer_id)
				{
					player = g_player_service->get_by_host_token(
					    gta_util::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token);
					break;
				}
			}
		}

		auto peer = g_pointers->m_gta.m_get_peer_by_security_id(frame->m_security_id); // will never be null in most cases, contains unspoofable data

		switch (msgType)
		{
		case rage::eNetMessage::MsgScriptJoin:
		{
			CGameScriptId script;
			script_id_deserialize(script, buffer);

			LOGF(stream::net_messages, VERBOSE, "{} sent request to join script {:X}", peer->m_info.name, script.m_hash);

			if (player && handle_block_script(player, script, frame->m_msg_id))
				return true;

			break;
		}
		case rage::eNetMessage::MsgScriptHostRequest:
		{
			CGameScriptId script;
			script_id_deserialize(script, buffer);

			if (script.m_hash == "freemode"_J && g.session.force_script_host)
				return true;

			break;
		}
		case rage::eNetMessage::MsgKickPlayer:
		{
			KickReason reason = buffer.Read<KickReason>(3);

			if (!is_host_of_session(gta_util::get_network()->m_game_session_ptr, frame->m_peer_id))
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgKickPlayer, but they are not the host", peer->m_info.name);
				return true;
			}

			if (reason == KickReason::VOTED_OUT)
			{
				g_notification_service.push_warning("PROTECTIONS"_T.data(), "YOU_HAVE_BEEN_KICKED"_T.data());
				return true;
			}

			LOGF(stream::net_messages, VERBOSE, "{} sent us a MsgKickPlayer, reason = {}", peer->m_info.name, (int)reason);
			break;
		}
		case rage::eNetMessage::MsgRadioStationSyncRequest:
		{
			if (player && player->block_radio_requests)
				return true;

			if (!session || !session->is_host())
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRadioStationSyncRequest, but we are not the host", player->get_name());
				return true;
			}

			if (player)
			{
				if (player->block_radio_requests)
					return true;

				if (player->m_radio_request_rate_limit.process())
				{
					if (player->m_radio_request_rate_limit.exceeded_last_process())
					{
						session::add_infraction(player, Infraction::TRIED_KICK_PLAYER);
						g_notification_service.push_error("PROTECTIONS"_T.data(),
						    std::vformat("OOM_KICK"_T, std::make_format_args(player->get_name())));
						player->block_radio_requests = true;
					}
					return true;
				}
			}
			else
			{
				static rate_limiter unk_player_radio_requests{1s, 5};

				if (unk_player_radio_requests.process())
				{
					if (unk_player_radio_requests.exceeded_last_process())
					{
						g_notification_service.push_error("PROTECTIONS"_T.data(), std::vformat("OOM_KICK"_T.data(), std::make_format_args(peer->m_info.name)));
					}
					return true;
				}
			}
			break;
		}
		case rage::eNetMessage::MsgRadioStationSync:
		{
			if (!session || is_host_of_session(session, frame->m_peer_id))
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRadioStationSync, but is not the host", peer->m_info.name);
				return true;
			}

			break;
		}
		case rage::eNetMessage::MsgRoamingJoinBubbleAck:
		{
			int status = buffer.Read<int>(2);
			int bubble = buffer.Read<int>(4);

			if (status == 0 && bubble == 10)
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingJoinBubbleAck with a null bubble id", peer->m_info.name);
				if (player)
					g.reactions.break_game.process(player);
				return true;
			}
			else if (status == 0)
			{
				LOGF(stream::net_messages, WARNING, "{} wants us to join their bubble {}, but this is not a good idea", peer->m_info.name, bubble);
				return true;
			}

			break;
		}
		case rage::eNetMessage::MsgRoamingInitialBubble:
		{
			// should not get this after the host has joined
			if (player && g_player_service->get_self()->id() != -1)
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host has already joined (and so have we)", peer->m_info.name);
				return true;
			}

			int my_bubble = buffer.Read<int>(4);
			int my_pid = buffer.Read<int>(6);
			int their_bubble = buffer.Read<int>(4);
			int their_pid = buffer.Read<int>(6);

			if (their_bubble == 10) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host doesn't have a bubble?", peer->m_info.name);
				return true;
			}

			if (my_bubble == 10) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host didn't actually give us a valid bubble", peer->m_info.name);
				return true;
			}

			if (my_bubble > 10 || their_bubble > 10) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host is trying to crash us by giving us an out of bounds bubble id", peer->m_info.name);
				return true;
			}

			if (my_bubble != 0) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble with a non-standard bubble id: {}", peer->m_info.name, my_bubble);
			}

			if (my_bubble != their_bubble) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host's bubble id doesn't match our bubble id ({} != {})", peer->m_info.name, their_bubble, my_bubble);
				return true;
			}

			if (my_pid >= 32 || their_pid >= 32) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host gave us invalid player ids (or made us pick our own player ids)", peer->m_info.name);
			}

			if (my_pid == their_pid) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgRoamingInitialBubble, but the host has the same player id as us", peer->m_info.name);
				return true;
			}

			break;
		}
		case rage::eNetMessage::MsgNonPhysicalData:
		{
			auto peer = g_pointers->m_gta.m_get_peer_by_security_id(frame->m_security_id);
			buffer.Read<int>(7); // size
			int bubble_id = buffer.Read<int>(4);
			int player_id = buffer.Read<int>(6);

			if (player)
			{
				return true; // we don't need this message anymore
			}

			if (bubble_id == 10) [[unlikely]]
			{
				LOGF(stream::net_messages, VERBOSE, "{} sent MsgNonPhysicalData and indicated that they are not in a bubble", peer->m_info.name);
				return true; // might as well drop it
			}

			if (bubble_id > 10) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgNonPhysicalData, but are trying to crash us by giving us an out of bounds bubble id", peer->m_info.name);
				return true;
			}

			if (bubble_id != 0) [[unlikely]]
			{
				LOGF(stream::net_messages, WARNING, "{} sent MsgNonPhysicalData with a non-standard bubble id: {}. This may cause problems during join", peer->m_info.name, bubble_id);
			}

			if (player_id >= 32) [[unlikely]]
			{
				LOG(WARNING) << peer->m_info.name << " sent MsgNonPhysicalData, but has an invalid player id (or is trying to make us pick our own)";
				return true;
			}

			if (g_player_service->get_self() && g_player_service->get_self()->id() != -1
				&& g_player_service->get_self()->id() == player_id) [[unlikely]]
			{
				LOGF(stream::net_messages, VERBOSE, "{} sent MsgNonPhysicalData, but are trying to replace us", peer->m_info.name);
				return true;
			}

			for (auto& player : g_player_service->players())
			{
				if (player.second->id() == player_id) [[unlikely]]
				{
					LOGF(stream::net_messages, VERBOSE, "{} sent MsgNonPhysicalData, but are trying to replace {}", peer->m_info.name, player.second->get_name());
					return true;
				}
			}

			break;
		}
		default:
		{
			if ((int)msgType > 0x91) [[unlikely]]
			{
				if (peer)
					LOGF(stream::net_messages, WARNING, "{} sent a message that does not exist: {:X}", peer->m_info.name, (int)msgType);

				// dumb modders
				if (player)
				{
					session::add_infraction(player, Infraction::SENT_MODDER_BEACONS);
				}
				else if (peer)
				{
					g_player_service->mark_player_as_sending_modder_beacons(peer->m_info.handle.m_rockstar_id);
				}
			}
		}
		}

		if (player)
		{
			switch (msgType)
			{
			case rage::eNetMessage::MsgTextMessage:
			case rage::eNetMessage::MsgTextMessage2:
			{
				char message[256];
				rage::rlGamerHandle handle{};
				bool is_team;
				buffer.ReadString(message, sizeof(message));
				gamer_handle_deserialize(handle, buffer);
				buffer.ReadBool(&is_team);

				if (player->is_spammer)
					return true;

				if (auto spam_reason = chat::is_text_spam(message, player))
				{
					if (g.session.log_chat_messages)
						chat::log_chat(message, player, spam_reason, is_team);
					g_notification_service.push("PROTECTIONS"_T.data(),

					    std::format("{} {}", player->get_name(), "IS_A_SPAMMER"_T.data()));
					player->is_spammer = true;
					if (g.session.kick_chat_spammers
					    && !(player->is_trusted || (player->is_friend() && g.session.trust_friends) || g.session.trust_session))
					{
						dynamic_cast<player_command*>(command::get("smartkick"_J))->call(player, {});
					}
					return true;
				}
				else
				{
					if (g.session.log_chat_messages)
						chat::log_chat(message, player, SpamReason::NOT_A_SPAMMER, is_team);
					if (g.session.chat_translator.enabled)
					{
						chat_message new_message{player->get_name(), message};
						translate_queue.push(new_message);
					}

					if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
						command::process(std::string(message + 1), std::make_shared<chat_command_context>(player));
					else
						g_lua_manager->trigger_event<menu_event::ChatMessageReceived>(player->id(), message);

					if (msgType == rage::eNetMessage::MsgTextMessage && g_pointers->m_gta.m_chat_data && player->get_net_data())
					{
						buffer.Seek(0);
						return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame); // Call original function since we can't seem to handle it
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
						g_notification_service.push_error("PROTECTIONS"_T.data(),
						    std::vformat("OOM_KICK"_T, std::make_format_args(player->get_name())));
					}
					return true;
				}
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
			
			}

		}

		return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);
	}
}
