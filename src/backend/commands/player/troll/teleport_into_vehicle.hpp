#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class teleport_into_vehicle : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline teleport_into_vehicle g_teleport_into_vehicle("playervehtp", "Teleport Into Vehicle", "Teleports into the players vehicle. Spectate the player beforehand for best results", 0, false);
	}
}
