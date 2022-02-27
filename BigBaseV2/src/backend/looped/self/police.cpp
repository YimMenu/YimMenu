#include "backend/looped/looped.hpp"

namespace big
{
	void looped::self_police()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;

		auto playerInfo = g_local_player->m_player_info;

		if (g->self.never_wanted)
			playerInfo->m_wanted_level = 0;
		else if (g->self.force_wanted_level)
			playerInfo->m_wanted_level = g->self.wanted_level;
	}
}