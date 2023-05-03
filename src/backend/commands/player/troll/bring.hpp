#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class bring : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline bring g_bring("bring", "Bring", "Teleports the player to you", 0, false);
	}
}
