#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class no_vehicle_water_collision : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player && g_local_player->m_vehicle)
				g_local_player->m_vehicle->m_navigation->m_damp->m_water_collision = 0;
		}

		virtual void on_disable() override
		{
			if (g_local_player && g_local_player->m_vehicle)
				g_local_player->m_vehicle->m_navigation->m_damp->m_water_collision = 1;
		}
	};

	no_vehicle_water_collision
	    g_no_vehicle_water_collision("driveunder", "NO_COLLISION_WATER", "NO_COLLISION_WATER_DESC", g.vehicle.no_water_collision);
}
