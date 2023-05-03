#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class force_into_mission : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline force_into_mission g_force_into_mission("mission", "Force Into Mission", "Forces the player into a gunrunning mission", 0);
	}
}
