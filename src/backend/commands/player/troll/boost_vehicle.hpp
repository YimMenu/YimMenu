#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class boost_vehicle : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline boost_vehicle g_boost_vehicle("boostveh", "Boost Vehicle", "Boosts their car very fast.", 0);
	}
}
