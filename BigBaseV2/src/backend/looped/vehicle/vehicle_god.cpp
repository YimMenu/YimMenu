#include "backend/looped/looped.hpp"
#include "util/misc.hpp"

namespace big
{
	static bool last_veh_god = false;
	void looped::vehicle_god_mode()
	{
		if ((!g->vehicle.god_mode && last_veh_god == g->vehicle.god_mode) || g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			return;

		if (g->vehicle.god_mode && g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING)
		{
			g_local_player->m_vehicle->m_deform_god = 0x8C;
			misc::set_bit((int*)&g_local_player->m_vehicle->m_damage_bits, 8);
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;
			misc::clear_bit((int*)&g_local_player->m_vehicle->m_damage_bits, 8);
		}

		last_veh_god = g->vehicle.god_mode;
	}
}