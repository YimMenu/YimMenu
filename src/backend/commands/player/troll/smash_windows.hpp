#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class smash_windows : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline smash_windows g_smash_windows("smashwindows", "Smash Vehicle Windows", "Smashes all their windows", 0);
	}
}
