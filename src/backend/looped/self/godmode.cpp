#include "backend/looped/looped.hpp"
#include "util/water.hpp"

namespace big
{
	static uint32_t last_bits = 0;
	static float last_water_collistion_strength = 0;

	void looped::self_godmode()
	{
		if (g_local_player == nullptr)
		{
			return;
		}

		float* water_collision_ptr = nullptr;
		if (g_local_player->m_navigation != nullptr)
		{
			water_collision_ptr = water::get_water_collision_ptr(g_local_player->m_navigation);
		}

		uint32_t bits = g->self.proof_mask;
		uint32_t changed_bits = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = g_local_player->m_damage_bits & ~changed_or_enabled_bits;
			g_local_player->m_damage_bits = unchanged_bits | bits;
			last_bits = bits;


			if (changed_or_enabled_bits & (uint32_t)eEntityProofs::WATER)
			{
				water::reset_ped_oxygen_time(g_local_player);

				if (water_collision_ptr != nullptr && *water_collision_ptr != 0.f)
				{
					last_water_collistion_strength = *water_collision_ptr;
					*water_collision_ptr = 0;
				}

				return;
			}
		}

		if (last_water_collistion_strength != 0 && water_collision_ptr != nullptr)
		{
			*water_collision_ptr = last_water_collistion_strength;
			last_water_collistion_strength = 0;
		}
	}
}