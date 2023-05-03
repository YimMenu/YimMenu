#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class enter_interior : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline enter_interior g_enter_interior("enterint", "Enter Interior", "Enters the player's interior", 0, false);
	}
}
