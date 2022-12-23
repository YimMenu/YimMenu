#include "natives.hpp"
#include "backend/looped_command.hpp"

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

	no_vehicle_water_collision g_no_vehicle_water_collision("driveunder", "Drive Underwater", "Allows you to drive underwater", g.vehicle.no_water_collision);
}
