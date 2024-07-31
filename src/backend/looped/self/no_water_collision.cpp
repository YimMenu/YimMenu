#include "backend/looped_command.hpp"

namespace big
{
	class no_water_collision : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player) [[likely]]
				g_local_player->m_navigation->m_damp->m_water_collision = 0;
		}

		virtual void on_disable() override
		{
			if (g_local_player) [[likely]]
				g_local_player->m_navigation->m_damp->m_water_collision = 1;
		}
	};

	no_water_collision g_no_water_collision("walkunder", "WALK_UNDERWATER", "WALK_UNDERWATER_DESC", g.self.no_water_collision);
}
