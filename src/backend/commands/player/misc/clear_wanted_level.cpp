#include "clear_wanted_level.hpp"

#include "util/globals.hpp"

namespace big
{
	CommandAccessLevel clear_wanted_level::get_access_level()
	{
		return CommandAccessLevel::FRIENDLY;
	}

	void clear_wanted_level::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		globals::clear_wanted_player(player->id());
	}
}
