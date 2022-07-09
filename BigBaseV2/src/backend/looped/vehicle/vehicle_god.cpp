#include "backend/looped/looped.hpp"
#include "util/misc.hpp"

namespace big
{
	static uint32_t lastProofBits = 0;

	void looped::vehicle_god_mode()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
		{
			return;
		}

		if (g->vehicle.god_mode && g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING)
		{
			g_local_player->m_vehicle->m_deform_god = 0x8C;
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;
		}

		uint32_t proofBits = g->vehicle.proof_mask;
		uint32_t changedProofBits = proofBits ^ lastProofBits;
		uint32_t changedOrEnabledProofBits = proofBits | changedProofBits;

		if (changedOrEnabledProofBits)
		{
			uint32_t unchangedBits = g_local_player->m_damage_bits & ~changedOrEnabledProofBits;
			g_local_player->m_damage_bits = unchangedBits | proofBits;
			lastProofBits = proofBits;
		}
	}
}