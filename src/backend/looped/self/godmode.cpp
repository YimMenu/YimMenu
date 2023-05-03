#include "godmode.hpp"

#include "natives.hpp"

namespace big
{
	void godmode_internal::on_tick()
	{
		if (g_local_player == nullptr)
		{
			return;
		}

		uint32_t bits                    = g.self.proof_mask;
		uint32_t changed_bits            = bits ^ last_bits;
		uint32_t changed_or_enabled_bits = bits | changed_bits;

		if (changed_or_enabled_bits)
		{
			uint32_t unchanged_bits       = g_local_player->m_damage_bits & ~changed_or_enabled_bits;
			g_local_player->m_damage_bits = unchanged_bits | bits;
			last_bits                     = bits;
		}
	}

	void godmode_internal::on_disable()
	{
		g_local_player->m_damage_bits = 0;
	}
}
