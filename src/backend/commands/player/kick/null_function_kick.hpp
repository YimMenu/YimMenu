#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class null_function_kick : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline null_function_kick g_null_function_kick("nfkick", "Null Function Kick", "It may take around 15 seconds for the player to actually leave the session", 0);
	}
}
