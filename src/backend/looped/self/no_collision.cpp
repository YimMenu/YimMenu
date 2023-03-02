#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"

#include <base/phArchetype.hpp>
#include <base/phBoundComposite.hpp>

namespace big
{
	class no_collision : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player)
				((rage::phBoundComposite*)g_local_player->m_navigation->m_damp->m_bound)
				    ->m_bounds[0]
				    ->m_bounding_box_max_xyz_margin_w.w = -1;
		}

		virtual void on_disable() override
		{
			if (g_local_player)
				((rage::phBoundComposite*)g_local_player->m_navigation->m_damp->m_bound)
				    ->m_bounds[0]
				    ->m_bounding_box_max_xyz_margin_w.w = 0.25;
		}
	};
	no_collision
	    g_no_collision("nocollision", "No Collision", "Allows you to walk through vehicles and most obstacles", g.self.no_collision);
}
