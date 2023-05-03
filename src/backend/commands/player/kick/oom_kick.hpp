#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class oom_kick : public player_command
	{
		using player_command::player_command;

		std::chrono::system_clock::time_point last_oom_kick_time{};

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline oom_kick g_oom_kick("oomkick", "OOM Kick", "Causes the player to be kicked with an alert. This kick has a high chance of backfiring in its current state", 0, false);
	}
}
