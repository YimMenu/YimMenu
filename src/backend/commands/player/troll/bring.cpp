#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class bring : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			teleport::bring_player(player);
		}
	};

	bring g_bring("bring", "Bring", "Teleports the player to you if they are in a vehicle", 0);
}