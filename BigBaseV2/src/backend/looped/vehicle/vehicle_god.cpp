#include "backend/looped/looped.hpp"

namespace big
{
	static bool last_veh_god = false;
	void looped::vehicle_god_mode()
	{
		if ((!g.vehicle.god_mode && last_veh_god == g.vehicle.god_mode) || g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			return;

		if (g.vehicle.god_mode && g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING)
		{
			g_local_player->m_vehicle->m_deform_god = 0x8C;
			g_local_player->m_vehicle->m_godmode = 0x1;
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;
			g_local_player->m_vehicle->m_godmode = 0x0;
		}

		last_veh_god = g.vehicle.god_mode;
	}
}