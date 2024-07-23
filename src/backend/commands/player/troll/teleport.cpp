#include "util/teleport.hpp"
#include "backend/player_command.hpp"

namespace big
{
	class teleport_to_player : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			teleport::to_player(player->id());
		}
	};

	teleport_to_player g_teleport_to_player("playertp", "TELEPORT", "TELEPORT_DESC", 0, false);
}