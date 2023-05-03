#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class remote_control_vehicle : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline remote_control_vehicle g_remote_control_vehicle("rcplayer", "Remote Control Vehicle", "Take control of the player's vehicle. Spectate the player beforehand for best results", 0, false);
	}
}
