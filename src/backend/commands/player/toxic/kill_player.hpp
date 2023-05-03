#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class kill_player : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline kill_player g_kill_player("kill", "Kill Player", "Kills the player, bypassing most forms of interior godmode", 0);
	}
}
