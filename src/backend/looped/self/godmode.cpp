#include "backend/looped/looped.hpp"

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

		uint32_t bits = g.self.proof_mask;
		uint32_t changed_bits = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits = g_local_player->m_damage_bits & ~changed_or_enabled_bits;
			g_local_player->m_damage_bits = unchanged_bits | bits;
			last_bits = bits;
		}
	}
}