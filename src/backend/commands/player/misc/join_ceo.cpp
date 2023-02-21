#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_function.hpp"

namespace big
{
	class join_ceo : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			scr_functions::join_ceo({player->id(), 0, false, false});
		}
	};

	join_ceo g_join_ceo("joinceo", "Join CEO/MC", "Joins the player's CEO/MC", 0, false);
}