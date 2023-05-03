#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class kill_engine : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline kill_engine g_kill_engine("killengine", "Kill Vehicle Engine", "Breaks their engine", 0);
	}
}
