#include "backend/looped/looped.hpp"
#include "util/toxic.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::player_never_wanted(const player_ptr &player)
	{
		if (player->never_wanted)
		{
			toxic::clear_wanted_player(player->id());
		}
	}
}
