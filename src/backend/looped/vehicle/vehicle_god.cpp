#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/misc.hpp"

namespace big
{
	static uint32_t last_bits                   = 0;
	static float last_water_collistion_strength = 0;
	static bool last_driving;

	void looped::vehicle_god_mode()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
		{
			return;
		}

		if (!PED::GET_PED_CONFIG_FLAG(self::ped, 62, false))
		{
			if (last_driving)
			{
				g_local_player->m_vehicle->m_deform_god  = 0x9C;
				g_local_player->m_vehicle->m_damage_bits = 0;
			}

			last_driving = false;
			return;
		}

		last_driving = true;

		if (g.vehicle.god_mode || g.vehicle.proof_collision)
		{
			g_local_player->m_vehicle->m_deform_god = 0x8C;
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;
		}

		uint32_t bits                    = g.vehicle.proof_mask;
		uint32_t changed_bits            = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = g_local_player->m_vehicle->m_damage_bits & ~changed_or_enabled_bits;
			g_local_player->m_vehicle->m_damage_bits = unchanged_bits | bits;
			last_bits                                = bits;
		}
	}
}