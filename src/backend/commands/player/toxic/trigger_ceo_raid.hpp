#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class trigger_ceo_raid : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline trigger_ceo_raid g_trigger_ceo_raid("ceoraid", "Trigger Special Cargo Raid", "The player has to be in a CEO for this to work", 0);
	}
}
