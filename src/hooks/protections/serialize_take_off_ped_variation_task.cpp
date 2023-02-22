#include "hooking.hpp"
#include "util/notify.hpp"

#include <netsync/nodes/task/ClonedTakeOffPedVariationInfo.hpp>

namespace big
{
	void hooks::serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer)
	{
		g_hooking->get_original<hooks::serialize_take_off_ped_variation_task>()(info, serializer);
		if (info->m_prop_hash != 0 && info->m_variation_component == 5 && info->m_prop_hash != RAGE_JOAAT("p_parachute_s"))
		{
			notify::crash_blocked(g.m_syncing_player, "invalid parachute");
			info->m_prop_hash = 0;
		}
	}
}
