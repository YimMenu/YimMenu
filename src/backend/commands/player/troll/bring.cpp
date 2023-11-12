#include "backend/player_command.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class bring : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			teleport::bring_player(player);
		}
	};

	bring g_bring("bring", "Bring", "Teleports the player to you", 0, false);
}