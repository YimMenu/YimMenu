#include "backend/looped/looped.hpp"
#include "util/misc.hpp"

namespace big
{
	static uint32_t last_bits = 0;
	static float last_water_collistion_strength = 0;

	void looped::vehicle_god_mode()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
		{
			return;
		}

		if (
			(g.vehicle.god_mode || g.vehicle.proof_collision) &&
			g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING
		) {
			g_local_player->m_vehicle->m_deform_god = 0x8C;
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;
		}

		uint32_t bits = g.vehicle.proof_mask;
		uint32_t changed_bits = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = g_local_player->m_vehicle->m_damage_bits & ~changed_or_enabled_bits;
			g_local_player->m_vehicle->m_damage_bits = unchanged_bits | bits;
			last_bits = bits;
		}
	}
}