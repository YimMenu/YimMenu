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

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			if (!g_player_service->get_self()->is_host() || !player->get_net_data())
				return;

			rage::snMsgRemoveGamersFromSessionCmd cmd{};
			cmd.m_session_id = gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id;
			cmd.m_num_peers  = 1;
			cmd.m_handles[0] = player->get_net_data()->m_gamer_handle;

			if (g.session.show_cheating_message)
				cmd.m_unk = 19;

			g_pointers->m_gta.m_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, player->get_session_player(), &cmd);
		}
	};

	breakup_kick g_breakup_kick("breakup", "BREAKUP_KICK", "BREAKUP_KICK_DESC", 0, false);
	bool_command g_show_cheating_message("breakupcheating", "BREAKUP_KICK_SHOW_CHEATING", "BREAKUP_KICK_SHOW_CHEATING_DESC",
	    g.session.show_cheating_message);
}