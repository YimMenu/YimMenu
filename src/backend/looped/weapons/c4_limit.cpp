#include "backend/looped/looped.hpp"

namespace big
{
	void looped::weapons_c4_limit()
	{
		if (g_local_player)
		{
			if (g.weapons.increased_c4_limit)
				g_local_player->fired_sticky_bombs = 0;
			if (g.weapons.increased_flare_limit)
				g_local_player->fired_flares = 0;
		}
	}
}
