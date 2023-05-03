#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class ragdoll_player : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline ragdoll_player g_ragdoll_player("ragdoll", "Ragdoll Player", "Ragdolls the player", 0);
	}
}
