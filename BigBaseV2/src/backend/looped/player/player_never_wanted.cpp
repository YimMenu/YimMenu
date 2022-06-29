#include "backend/looped/looped.hpp"
#include "util/toxic.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::player_never_wanted()
	{
		if (g->player.player_never_wanted && g_player_service->get_selected()->is_valid())
		{
			toxic::clear_wanted_player(g_player_service->get_selected()->id());
		}
	}
}
