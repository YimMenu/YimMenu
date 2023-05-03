#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class turn_into_beast : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	class turn_into_beast_all : public command
	{
		using command::command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline turn_into_beast g_turn_into_beast("beast", "Turn Into Beast", "Turns the player into the beast", 0, false);
		inline turn_into_beast_all g_turn_into_beast_all("beastall", "Turn Everyone Into Beast", "Turns everyone into the beast, including you", 0);
	}
}
