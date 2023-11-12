#include "hooking.hpp"
#include "network/Network.hpp"

#include <stats/CStatsSerializationContext.hpp>

namespace big
{
	void hooks::serialize_stats(CStatsSerializationContext* context, rage::joaat_t* stats, uint32_t stat_count)
	{
		g_hooking->get_original<hooks::serialize_stats>()(context, stats, stat_count);
	}
}