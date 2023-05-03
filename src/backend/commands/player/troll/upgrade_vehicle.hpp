#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class upgrade_vehicle : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline upgrade_vehicle g_upgrade_vehicle("upgradeveh", "Upgrade Vehicle", "Upgrades players vehicle", 0);
	}
}
