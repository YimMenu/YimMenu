#include "services/players/player_service.hpp"
#include "util/session.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "hooking.hpp"

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

				case rage::eNetMessage::CMsgKickPlayer: // From maybegreat48
				{
					uint64_t session_id;
					uint64_t peer_id;
					buffer.ReadQWord(&session_id, 64);
					buffer.ReadQWord(&peer_id, 64);
					uint8_t reason; // KickReason
					buffer.ReadByte(&reason, 3);
					int64_t _rid;
					buffer.ReadInt64(&_rid, 64);
					rage::rlGamerHandle handle(_rid);

					LOG(INFO) << "RID?: " << _rid << " " << handle.m_rockstar_id << ", REASON?: " << reason << ", SESSION_ID: " << session_id;

					if ((KickReason)reason == KickReason::VOTED_OUT)
						g_notification_service->push_error("Protections", "You were kicked by the host"); // mod menus breakup the host here to prevent being kicked. Can't rejoin here
																										  // due to blacklist. RID spoofing may help

					if ((KickReason)reason == KickReason::PEER_COMPLAINTS)
					{
						g_fiber_pool->queue_job([]
						{
							session::join_by_session_info((*g_pointers->m_network)->m_last_joined_session.m_session_info);
						});

						for (auto& [_, plyr] : g_player_service->players())
						{
							if (plyr->get_net_data() && plyr->get_net_data()->m_rockstar_id2 == handle.m_rockstar_id)
							{
								g_notification_service->push_error("Protections", fmt::format("Desynced by {}. REJOINING SESSION", plyr->get_name()));
								return true;
							}
						}

						g_notification_service->push_error("Protections", fmt::format("Desynced! REJOINING SESSION"));
					}

					return true;

				}

				// Breakup Kick. From maybegreat48
				case rage::eNetMessage::CMsgRemoveGamersFromSessionCmd:
				{
					player_ptr pl;
					uint64_t session_id;
					buffer.ReadQWord(&session_id, 64);
					int32_t count;
					buffer.ReadInt32(&count, 6);
					LOG(G3LOG_DEBUG) << "RECEIVED PACKET | Type: MsgRemoveGamersFromSessionCmd | Sender: " << (player ? player->get_name() : "<UNKNOWN>");
					LOG(G3LOG_DEBUG) << "                | Message ID " << (frame->m_msg_id == -1 ? "IS" : "IS NOT") << " equal to -1";
					LOG(G3LOG_DEBUG) << "                | Count: " << count;
					pl = nullptr;
					for (int i = 0; i < count; i++)
					{
						uint64_t peer_id;
						buffer.ReadQWord((uint64_t*)&peer_id, 64);
						for (std::uint32_t i = 0; i < (*g_pointers->m_network)->m_game_session_ptr->m_peer_count; i++)
						{
							if ((*g_pointers->m_network)->m_game_session_ptr->m_peers[i]->m_peer_data.m_peer_id == peer_id)
							{
								pl = g_player_service->get_by_host_token((*g_pointers->m_network)->m_game_session_ptr->m_peers[i]->m_peer_data.m_host_token);
								break;
							}
						}
						LOG(G3LOG_DEBUG) << "                | Player: " << (pl ? pl->get_name() : std::to_string(peer_id).data());
					}

					// I removed "unk" logging here

					if (player && pl && player->id() != pl->id() && count == 1)
					{
						g_notification_service->push_error("Warning!", fmt::format("{} breakup kicked {}!", player->get_name(), pl->get_name()));
						return true; // does this block the breakup kick?
					}
				}

				// Desync Kick
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
