#include "no_water_collision.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"

namespace big
{
	void no_water_collision::on_tick()
	{
		if (g_local_player)
			g_local_player->m_navigation->m_damp->m_water_collision = 0;
	}

	void no_water_collision::on_disable()
	{
		if (g_local_player)
			g_local_player->m_navigation->m_damp->m_water_collision = 1;
	}
}
