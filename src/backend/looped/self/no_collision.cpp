#include "no_collision.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"

#include <base/phArchetype.hpp>
#include <base/phBoundComposite.hpp>

namespace big
{
	void no_collision::on_tick()
	{
		if (g_local_player)
			((rage::phBoundComposite*)g_local_player->m_navigation->m_damp->m_bound)
			    ->m_bounds[0]
			    ->m_bounding_box_max_xyz_margin_w.w = -1;
	}

	void no_collision::on_disable()
	{
		if (g_local_player)
			((rage::phBoundComposite*)g_local_player->m_navigation->m_damp->m_bound)
			    ->m_bounds[0]
			    ->m_bounding_box_max_xyz_margin_w.w = 0.25;
	}
}
