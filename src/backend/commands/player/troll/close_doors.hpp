#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class close_doors : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline close_doors g_close_doors("closedoors", "Close Vehicle Doors", "Closes all vehicle doors", 0);
	}
}
