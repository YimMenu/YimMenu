#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class send_to_island : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline send_to_island g_send_to_island("cayotp", "TP To Cayo Perico", "Teleports the player to Cayo Perico", 0);
	}
}
