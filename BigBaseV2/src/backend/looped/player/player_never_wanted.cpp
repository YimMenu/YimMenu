#include "backend/looped/looped.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"

namespace big
{
	void looped::player_never_wanted(const player_ptr &player)
	{
		if (player->never_wanted)
		{
			globals::clear_wanted_player(player->id());
		}
	}
}
