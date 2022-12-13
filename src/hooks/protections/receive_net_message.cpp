#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "util/session.hpp"
#include "util/spam.hpp"
#include "util/kick.hpp"
#include <network/Network.hpp>

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
			msgType = rage::eNetMessage::MsgInvalid;
			return false;
		}
		length = extended ? 16 : 8;
		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit), length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	void gamer_handle_deserialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		constexpr int PC_PLATFORM = 3;
		if ((hnd.m_platform = buf.Read<uint8_t>(8)) != PC_PLATFORM)
			return;

		buf.ReadInt64((int64_t*)&hnd.m_rockstar_id, 64);
		hnd.unk_0009 = buf.Read<uint8_t>(8);
	}

	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
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
				case rage::eNetMessage::MsgTextMessage:
				case rage::eNetMessage::MsgTextMessage2:
				{
					char message[256];
					buffer.ReadString(message, 256);

					if (player->is_spammer)
						return true;

					if (spam::is_text_spam(message))
					{
						if (g->session.log_chat_messages)
							spam::log_chat(message, player, true);
						player->is_spammer = true;
						if (g->session.kick_chat_spammers)
							kick::breakup_kick(player);
						return true;
					}
					else
					{
						if (g->session.log_chat_messages)
							spam::log_chat(message, player, false);
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
							g_notification_service->push_error("Protections", std::format("{} tried to OOM kick you!", player->get_name()));
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
								pl = g_player_service->get_by_host_token(gta_util::get_network()->m_game_session_ptr->m_peers[i]->m_peer_data.m_host_token);
								break;
							}
						}
					}

					if (player && pl && player->id() != pl->id() && count == 1 && frame->m_msg_id == -1)
					{
						g_notification_service->push_error("Warning!", std::format("{} breakup kicked {}!", player->get_name(), pl->get_name()));
						session::add_infraction(player, Infraction::BREAKUP_KICK_DETECTED);
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
					if (self->get_net_data() && self->get_net_data()->m_gamer_handle_2.m_rockstar_id == handle.m_rockstar_id)
					{
						session::add_infraction(player, Infraction::TRIED_KICK_PLAYER);
						g_notification_service->push_error("Protections", std::format("{} tried to lost connection kick you!", player->get_name()));
						return true;
					}

					for (auto& [_, plyr] : g_player_service->players())
					{
						if (plyr->get_net_data() && plyr != player && player->get_net_data()->m_gamer_handle_2.m_rockstar_id == handle.m_rockstar_id)
						{
							session::add_infraction(player, Infraction::LOST_CONNECTION_KICK_DETECTED);
							g_notification_service->push_error("Protections", std::format("{} tried to lost connection kick {}!", player->get_name(), plyr->get_name()));
							return true;
						}
					}

					break;
				}
				case rage::eNetMessage::MsgSessionEstablished:
				{
					rage::rlGamerHandle handle{ 0 };
					if (player && player->get_net_data())
					{
						uint64_t session_id;
						buffer.ReadQWord(&session_id, 64);
						gamer_handle_deserialize(handle, buffer);
						if (session_id == gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id)
						{
							if (handle.m_rockstar_id != player->get_net_data()->m_gamer_handle_2.m_rockstar_id)
							{
								session::add_infraction(player, Infraction::SPOOFED_ROCKSTAR_ID); // TODO: store this RID
							}
						}
					}
					break;
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

					return true; // block desync kicks as host
				}
				case rage::eNetMessage::MsgRequestObjectIds:
				{
					if (player && player->block_join)
					{
						g_notification_service->push("Join Blocker", std::format("Trying to prevent {} from joining...", player->get_name()));
						return true;
					}
					break;
				}
				case rage::eNetMessage::MsgScriptHostRequest:
				{
					CGameScriptId script;
					script_id_deserialize(script, buffer);

					if (script.m_hash == RAGE_JOAAT("freemode") && g->session.force_script_host)
						return true;
					
					break;
				}
				}
			}
		}

		return g_hooking->get_original<hooks::receive_net_message>()(netConnectionManager, a2, frame);
	}
}
