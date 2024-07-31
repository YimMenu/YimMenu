#include "hooking/hooking.hpp"

#include <stats/CStatsSerializationContext.hpp>

namespace big
{
	void hooks::serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, uint32_t stat_count)
	{
		g_hooking->get_original<hooks::serialize_stats>()(context, stats, stat_count);

		// variable length array so we can't iterate it directly. Looks ugly but should work
		uint32_t* data = reinterpret_cast<uint32_t*>(context->m_entries);

		for (int i = 0; i < context->m_size / 4; i++)
		{
			CStatSerializationEntry* entry = reinterpret_cast<CStatSerializationEntry*>(&data[i]);

			if (g.spoofing.spoof_rank && (entry->m_hash == "MP0_CHAR_RANK_FM"_J || entry->m_hash == "MP1_CHAR_RANK_FM"_J))
			{
				entry->m_int_value = g.spoofing.rank;
			}

			if (g.spoofing.spoof_bad_sport && entry->m_hash == "MPPLY_OVERALL_BADSPORT"_J)
			{
				switch (g.spoofing.badsport_type)
				{
				case 0: entry->m_float_value = 0.0f; break;
				case 1: entry->m_float_value = 46.0f; break;
				case 2: entry->m_float_value = 1000.0f; break;
				}
			}

			if (g.spoofing.spoof_kd_ratio)
			{
				if (entry->m_hash == "MPPLY_KILLS_PLAYERS"_J)
					entry->m_int_value = g.spoofing.kd_ratio;// TODO precision loss

				if (entry->m_hash == "MPPLY_DEATHS_PLAYER"_J)
					entry->m_int_value = 1;

				if (entry->m_hash == "MPPLY_DEATHS_PLAYER_SUICIDE"_J)
					entry->m_int_value = 0;
			}
		}
	}
}
