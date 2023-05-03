#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class remove_all_weapons : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline remove_all_weapons g_remove_all_weapons("remweaps", "Remove All Weapons", "Remove all weapons from the player", 0);
	}
}
