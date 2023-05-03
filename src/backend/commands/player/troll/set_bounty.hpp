#pragma once

#include "backend/bool_command.hpp"
#include "backend/player_command.hpp"

namespace big
{
	class set_bounty : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline set_bounty g_bounty("bounty", "Bounty", "Sets a 10k bounty on the player", 0);
		inline bool_command g_anonymous_bounty("anonbounty", "Anonymous Bounty", "Don't show your name when setting a bounty on someone",
		    g.session.anonymous_bounty);
	}
}
