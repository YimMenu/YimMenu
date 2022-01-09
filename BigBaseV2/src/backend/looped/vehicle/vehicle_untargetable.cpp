#include "backend/looped/looped.hpp"

namespace big
{
	void looped::vehicle_untargetable()
	{
		if (!g.vehicle.untargetable || g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			return;

		if (g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
		{
			g_local_player->m_vehicle->m_is_targetable = 0x0;
			g_local_player->m_vehicle->m_rocket_recharge_speed = 5.f;
		}
		else
		{
			g_local_player->m_vehicle->m_is_targetable = 0x1;
			g_local_player->m_vehicle->m_rocket_recharge_speed = 1.f;
		}
	}
}