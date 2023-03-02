#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"

namespace big
{
	class no_water_collision : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player)
				g_local_player->m_navigation->m_damp->m_water_collision = 0;
		}

		virtual void on_disable() override
		{
			if (g_local_player)
				g_local_player->m_navigation->m_damp->m_water_collision = 1;
		}
	};

	no_water_collision
	    g_no_water_collision("walkunder", "Walk Underwater", "Allows you to walk and shoot underwater", g.self.no_water_collision);
}
