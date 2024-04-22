#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "util/police.hpp"

namespace big
{
	void looped::self_police()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) [[unlikely]]
			return;

		static bool bLast = false;

		bool b = g.self.never_wanted;

		if (b)
		{
			g_local_player->m_player_info->m_wanted_level = 0;
			police::m_max_wanted_level->apply();
			police::m_max_wanted_level_2->apply();
			bLast = b;
		}
		else if (b != bLast)
		{
			police::m_max_wanted_level->restore();
			police::m_max_wanted_level_2->restore();
			bLast = b;
		}

		if (g.self.force_wanted_level && !b)
			g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;
	}
}