#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/troll.hpp"

namespace big
{
	class set_bounty : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			troll::set_bounty_on_player(player, 10000);
		}
	};

	set_bounty g_bounty("bounty", "Bounty", "Sets a 10k bounty on the player", 0);
}