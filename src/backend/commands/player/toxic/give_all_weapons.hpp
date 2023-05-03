#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class give_all_weapons : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	class give_all_weapons_all : public command
	{
		using command::command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline give_all_weapons g_give_all_weapons("giveweaps", "Give Weapons", "Gives all weapons to the player", 0, false);
		inline give_all_weapons_all g_give_all_weapons_all("giveweapsall", "Give Weapons", "Gives weapons to everyone. Don't spam this or you will crash", 0);
	}
}
