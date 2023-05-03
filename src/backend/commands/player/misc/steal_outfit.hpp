#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class steal_outfit : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline steal_outfit g_steal_outfit("copyoutfit", "Steal Outfit", "Copies the player's outfit to your ped", 0, false);
	}
}
