#include "backend/looped/looped.hpp"
#include "services/player_service.hpp"
#include "util/globals.hpp"

namespace big
{
	void looped::player_never_wanted()
	{
		if (g->player.player_never_wanted && g_player_service->get_selected()->is_valid())
		{
			globals::clear_wanted_player(g_player_service->get_selected()->id());
		}
	}
}
