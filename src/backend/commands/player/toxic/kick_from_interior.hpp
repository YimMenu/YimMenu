#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class kick_from_interior : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline kick_from_interior g_kick_from_interior("intkick", "Kick From Interior", "Kicks the player from the interior they are in", 0);
	}
}
