#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class burst_tyres : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline burst_tyres g_burst_tyres("burstwheels", "Burst Vehicle Tyres", "Removes their tyres.", 0);
	}
}
