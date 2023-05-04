#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class script_host_kick : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline script_host_kick g_script_host_kick("shkick", "Script Host Kick", "Blocked by most menus", 0, false);
	}
}
