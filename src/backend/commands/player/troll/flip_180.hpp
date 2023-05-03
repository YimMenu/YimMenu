#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class flip_180 : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline flip_180 g_flip_180("flip180", "Rotate 180", "Rotates their car around", 0);
	}
}
