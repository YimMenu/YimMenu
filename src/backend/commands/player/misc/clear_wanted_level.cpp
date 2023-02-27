#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/globals.hpp"

namespace big
{
	class clear_wanted_level : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::FRIENDLY;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			globals::clear_wanted_player(player->id());
		}
	};

	clear_wanted_level g_clear_wanted_level("clearwanted", "Clear Wanted Level", "Clears the player's wanted level", 0);
}