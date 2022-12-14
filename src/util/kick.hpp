#pragma once
#include "pointers.hpp"
#include "gta_util.hpp"
#include <network/Network.hpp>
#include "packet.hpp"
#include "gta/script_handler.hpp"
#include "util/scripts.hpp"

namespace
{
	void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(&hnd.m_platform), 8);
		if (*reinterpret_cast<uint8_t*>(&hnd.m_platform) == 3)
		{
			buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
			buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(reinterpret_cast<__int64>(&hnd) + 9), 8);
		}
	}
}

namespace big::kick
{
	inline void bail_kick(player_ptr target)
	{
		const size_t arg_count = 3;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::NetworkBail,
			(int64_t)self::id,
			*scr_globals::gpbd_fm_3.at(target->id(), scr_globals::size::gpbd_fm_3).at(510).as<int64_t*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void kick_player_script_host(player_ptr target)
	{
		if (!scripts::force_host(RAGE_JOAAT("freemode")))
		{
			g_notification_service->push_error("Kick", "Force script host failed!");
			return;
		}

		*scr_globals::gsbd_kicking.at(target->id(), 1).as<bool*>() = true;
	}

	inline void end_session_kick(player_ptr target)
	{
		if (!scripts::force_host(RAGE_JOAAT("freemode")))
		{
			g_notification_service->push_error("Kick", "Force script host failed!");
			return;
		}

		g_player_service->m_player_to_use_end_session_kick = target;
		*scr_globals::gsbd.as<int*>() = (int)(__rdtsc() % 50000) + 6; // making the game trigger the broadcast is a bit difficult and requires a little bit of tampering with the value and luck
	}

	inline std::chrono::system_clock::time_point last_oom_kick_time{};
	inline void oom_kick(player_ptr target)
	{
		if (std::chrono::system_clock::now() - last_oom_kick_time < 7s)
		{
			g_notification_service->push_error("Kick", "Don't spam this or it will backfire");
			return;
		}

		last_oom_kick_time = std::chrono::system_clock::now();

		if (auto freemode = gta_util::find_script_thread(RAGE_JOAAT("freemode")))
		{
			packet msg{};
			msg.write_message(rage::eNetMessage::MsgScriptMigrateHost);
			freemode->m_handler->get_id()->serialize(&msg.m_buffer);
			msg.write<int>(0, 16);
			msg.write<int>(0, 32);
			auto msg_id = target->get_net_game_player()->m_msg_id;
			for (int j = 0; j < 2100; j++)
			{
				msg.send(msg_id);
			}
		}
	}

	inline void lost_connection_kick(player_ptr target)
	{
		if (gta_util::get_network()->m_game_session_ptr->is_host())
		{
			g_notification_service->push_error("Kick", "Cannot use the lost connection kick while host");
			return;
		}

		packet msg{};
		msg.write_message(rage::eNetMessage::MsgLostConnectionToHost);
		msg.write<uint64_t>(gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id, 64);
		gamer_handle_serialize((*(rage::rlGamerHandle*)(&target->get_net_data()->m_gamer_handle_2.m_rockstar_id)), msg);
		for (auto& [_, plyr] : g_player_service->players())
		{
			if (plyr->is_host())
			{
				msg.send(plyr->get_session_player()->m_msg_id);
				break;
			}
		}
	}

	inline void breakup_kick(player_ptr target)
	{
		rage::snMsgRemoveGamersFromSessionCmd cmd{};
		cmd.m_session_id = gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id;
		cmd.m_num_peers = 1;
		cmd.m_peer_ids[0] = target->get_session_peer()->m_peer_data.m_peer_id_2;

		g_pointers->m_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, target->get_session_player(), &cmd);
		for (auto& [_, plyr] : g_player_service->players())
		{
			if (plyr->id() != target->id())
				g_pointers->m_send_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
					g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr, (int)plyr->get_session_player()->m_player_data.m_peer_id_2),
					gta_util::get_network()->m_game_session_ptr->m_connection_identifier, &cmd, 0x1000000);
		}
	}

	inline void host_kick(player_ptr target)
	{
		if (!g_player_service->get_self()->is_host())
		{
			g_notification_service->push_error("Kick", "You have to be the session host");
			return;
		}

		rage::snMsgRemoveGamersFromSessionCmd cmd{};
		cmd.m_session_id = gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id;
		cmd.m_num_peers = 1;
		cmd.m_peer_ids[0] = target->get_session_peer()->m_peer_data.m_peer_id_2;

		g_pointers->m_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, target->get_session_player(), &cmd);
	}

	inline void complaint_kick(player_ptr target)
	{
		if (gta_util::get_network()->m_game_session_ptr->is_host())
		{
			g_notification_service->push_error("Kick", "Cannot use the complaint kick while host");
			return;
		}

		g_player_service->m_player_to_use_complaint_kick = target;
	}

	inline void null_function_kick(player_ptr target)
	{
		const size_t arg_count = 15;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::InteriorControl,
			(int64_t)self::id,
			(int64_t)(int)-1
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}
}