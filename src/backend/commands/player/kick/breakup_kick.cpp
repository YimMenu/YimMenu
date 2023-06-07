#include "backend/bool_command.hpp"
#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <network/Network.hpp>

namespace big
{
	class breakup_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			rage::snMsgRemoveGamersFromSessionCmd cmd{};
			cmd.m_session_id  = gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id;
			cmd.m_num_peers   = 1;
			cmd.m_peer_ids[0] = player->get_session_peer()->m_peer_data.m_peer_id_2;

			if (g.session.show_cheating_message)
				cmd.m_unk = 19;

			if (gta_util::get_network()->m_game_session.is_host())
			{
				g_pointers->m_gta.m_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, player->get_session_player(), &cmd);
			}
			else if (player->is_host())
			{
				for (auto& [_, plyr] : g_player_service->players())
				{
					if (plyr->id() != player->id())
						g_pointers->m_gta.m_send_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
						    g_pointers->m_gta.m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
						        (int)plyr->get_session_player()->m_player_data.m_peer_id_2),
						    gta_util::get_network()->m_game_session_ptr->m_connection_identifier,
						    &cmd,
						    0x1000000);
				}

				g_pointers->m_gta.m_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, player->get_session_player(), &cmd);
			}
			else
			{
				for (auto& [_, plyr] : g_player_service->players())
				{
					if (plyr->is_host())
					{
						g_pointers->m_gta.m_send_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
						    g_pointers->m_gta.m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
						        (int)plyr->get_session_player()->m_player_data.m_peer_id_2),
						    gta_util::get_network()->m_game_session_ptr->m_connection_identifier,
						    &cmd,
						    0x1000000);

						break;
					}
				}
			}
		}
	};

	breakup_kick g_breakup_kick("breakup", "BREAKUP_KICK", "BREAKUP_KICK_DESC", 0, false);
	bool_command g_show_cheating_message("breakupcheating", "BREAKUP_KICK_SHOW_CHEATING", "BREAKUP_KICK_SHOW_CHEATING_DESC",
	    g.session.show_cheating_message);
}