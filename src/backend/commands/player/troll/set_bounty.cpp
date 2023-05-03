#include "set_bounty.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/troll.hpp"

namespace big
{
	void set_bounty::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		troll::set_bounty_on_player(player, 10000, g.session.anonymous_bounty);
	}
}
