#include "backend/looped/looped.hpp"

namespace big
{
	static bool bLastNoCollsion = false;

	void looped::self_no_collision()
	{
		if (g_local_player == nullptr) return;

		bool bNoCollsion = g->self.no_collision;

		if (bNoCollsion)
		{
			g_local_player->m_navigation->m_damp->m_bound_composite->m_bound_capsule_list->m_bound_capsule->m_collision = -1;
			bLastNoCollsion = bNoCollsion;
		}
		else if (bNoCollsion != bLastNoCollsion)
		{
			g_local_player->m_navigation->m_damp->m_bound_composite->m_bound_capsule_list->m_bound_capsule->m_collision = 0.25;
			bLastNoCollsion = bNoCollsion;
		}
	}
}
