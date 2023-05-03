#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class stop_vehicle : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline stop_vehicle g_stop_vehicle("stopveh", "Stop Vehicle", "Stops players vehicle", 0);
	}
}
