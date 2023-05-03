#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class unlock_vehicle : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline unlock_vehicle g_unlock_vehicle("unlockveh", "Unlock Vehicle Doors", "Unlocks Vehicle Doors", 0);
	}
}
