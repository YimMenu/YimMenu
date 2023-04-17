#include "util/teleport.hpp"

#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class teleport_to_player : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			teleport::to_player(player->id());
		}
	};

	teleport_to_player g_teleport_to_player("playertp", "Teleport", "Teleports you to the player", 0, false);
}