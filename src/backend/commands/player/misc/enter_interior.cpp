#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/misc.hpp"

namespace big
{
	class enter_interior : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (*scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(318).at(6).as<int*>() == -1)
			{
				g_notification_service->push_error("Enter Interior", "Player does not seem to be in an interior");
				return;
			}

			int owner = *scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(318).at(9).as<int*>();
			if (owner == -1)
				owner = player->id();

			*script_global(1950108).at(3684).as<int*>() = 0;
			*script_global(1950108).at(3682).as<int*>() = 1;
			*script_global(1950108).at(4780).as<int*>() = 1;
			*script_global(1950108).at(3218).as<int*>() = 1; // this doesnt exists at all?
			*script_global(1950108).at(3214).as<int*>() = 1; // ^
			*script_global(1950108).at(3689).as<int*>() = 1;

			// misc::set_bit(script_global(1950108).at(1).as<int*>(), 22);
			misc::set_bit(script_global(1950108).as<int*>(), 6);
			misc::clear_bit(script_global(1950108).at(1).as<int*>(), 9);

			*script_global(1950108).at(3346).as<int*>() = owner;
			*script_global(1950108).at(3683).as<int*>() = *scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(318).at(6).as<int*>();
		}
	};

	enter_interior g_enter_interior("enterint", "Enter Interior", "Enters the player's interior", 0, false);
}