#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class teleport_to_player : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline teleport_to_player g_teleport_to_player("playertp", "Teleport", "Teleports you to the player", 0, false);
	}
}
