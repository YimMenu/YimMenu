#pragma once

#include "backend/bool_command.hpp"
#include "backend/player_command.hpp"

namespace big
{
	class breakup_kick : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline breakup_kick g_breakup_kick("breakup", "Breakup Kick", "Nearly unblockable but could be detected by others", 0, false);
		inline bool_command g_show_cheating_message("breakupcheating", "Show Cheating Message", "Shows a \"was detected cheating and has been removed from the session\" instead of the usual leave message when the player gets kicked",
		    g.session.show_cheating_message);
	}
}
