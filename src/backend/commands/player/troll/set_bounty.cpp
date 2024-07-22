#include "backend/bool_command.hpp"
#include "backend/player_command.hpp"
#include "util/troll.hpp"

namespace big
{
	class set_bounty : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			troll::set_bounty_on_player(player, 10000, g.session.anonymous_bounty);
		}
	};

	set_bounty g_bounty("bounty", "BOUNTY", "BOUNTY_DESC", 0);
	bool_command g_anonymous_bounty("anonbounty", "BOUNTY_ANON", "BOUNTY_ANON_DESC", g.session.anonymous_bounty);
}
