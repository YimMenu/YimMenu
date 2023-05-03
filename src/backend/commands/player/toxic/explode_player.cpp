#include "explode_player.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/toxic.hpp"

namespace big
{
	CommandAccessLevel explode_player::get_access_level()
	{
		return CommandAccessLevel::AGGRESSIVE;
	}

	void explode_player::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		toxic::blame_explode_player(player, player, EXP_TAG_SUBMARINE_BIG, 9999.0f, true, false, 9999.0f);
	}
}
