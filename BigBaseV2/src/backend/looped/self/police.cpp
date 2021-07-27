#include "backend/looped/looped.hpp"

namespace big
{
	static int iLastWantedLevel = 0;

	void looped::self_police()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;

		if (g.self.never_wanted)
			g_local_player->m_player_info->m_wanted_level = 0;
		else if (g.self.wanted_level != iLastWantedLevel)
			g_local_player->m_player_info->m_wanted_level = g.self.wanted_level;
	}
}