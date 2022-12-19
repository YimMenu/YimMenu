#include "backend/looped/looped.hpp"
#include "base/phArchetype.hpp"
#include "base/phBoundComposite.hpp"

namespace big
{
	static bool bLastNoCollsion = false;

	void looped::self_no_collision()
	{
		if (g_local_player == nullptr) return;

		bool bNoCollsion = g.self.no_collision;

		if (bNoCollsion)
		{
			((rage::phBoundComposite*)g_local_player->m_navigation->m_damp->m_bound)->m_bounds[0]->m_bounding_box_max_xyz_margin_w.w = -1;
			bLastNoCollsion = bNoCollsion;
		}
		else if (bNoCollsion != bLastNoCollsion)
		{
			((rage::phBoundComposite*)g_local_player->m_navigation->m_damp->m_bound)->m_bounds[0]->m_bounding_box_max_xyz_margin_w.w = 0.25;
			bLastNoCollsion = bNoCollsion;
		}
	}
}
