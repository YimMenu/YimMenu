#include "hooking.hpp"
#include "network/Network.hpp"

#pragma pack(push, 1)
class CStatsSerializationContext
{
public:
	bool m_compressed; //0x0000
	char pad_0001[7]; //0x0001
	class CStatSerializationEntry* m_entries; //0x0008
	uint16_t m_size; //0x0010
}; //Size: 0x0012
static_assert(sizeof(CStatsSerializationContext) == 0x12);

class CStatSerializationEntry
{
public:
	uint32_t m_hash; //0x0000
	union //0x0004
	{
		float m_float_value; //0x0000
		uint16_t m_short_value; //0x0000
		uint64_t m_int_value; //0x0000
	};
}; //Size: 0x000C
static_assert(sizeof(CStatSerializationEntry) == 0xC); // can be 0x8 or 0xC
#pragma pack(pop)

namespace big
{
	void hooks::serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, std::uint32_t stat_count)
	{
		g_hooking->get_original<hooks::serialize_stats>()(context, stats, stat_count);

		// variable length array so we can't iterate it directly. Looks ugly but should work
		std::uint32_t* data = reinterpret_cast<std::uint32_t*>(context->m_entries);

		for (int i = 0; i < context->m_size / 4; i++)
		{
			CStatSerializationEntry* entry = reinterpret_cast<CStatSerializationEntry*>(&data[i]);

			if (g.spoofing.spoof_rank && (entry->m_hash == RAGE_JOAAT("MP0_CHAR_RANK_FM") || entry->m_hash == RAGE_JOAAT("MP1_CHAR_RANK_FM")))
			{
				entry->m_int_value = g.spoofing.rank;
			}

			if (g.spoofing.spoof_bad_sport && entry->m_hash == RAGE_JOAAT("MPPLY_OVERALL_BADSPORT"))
			{
				switch (g.spoofing.badsport_type)
				{
					case 0:
						entry->m_float_value = 0.0f;
						break;
					case 1:
						entry->m_float_value = 46.0f;
						break;
					case 2:
						entry->m_float_value = 1000.0f;
						break;
				}
			}

			if (g.spoofing.spoof_kd_ratio)
			{
				if (entry->m_hash == RAGE_JOAAT("MPPLY_KILLS_PLAYERS"))
					entry->m_int_value = g.spoofing.kd_ratio; // TODO precision loss

				if (entry->m_hash == RAGE_JOAAT("MPPLY_DEATHS_PLAYER"))
					entry->m_int_value = 1;

				if (entry->m_hash == RAGE_JOAAT("MPPLY_DEATHS_PLAYER_SUICIDE"))
					entry->m_int_value = 0;
			}
		}
	}
}