#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class give_health : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline give_health g_give_health("givehealth", "Give Health", "Gives the player some health", 0);
	}
}
