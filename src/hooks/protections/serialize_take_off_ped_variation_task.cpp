#include "hooking.hpp"
#include "util/notify.hpp"
#include <datanodes/task/ClonedTakeOffPedVariationInfo.hpp>

namespace big
{
	void hooks::serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer)
	{
		g_hooking->get_original<hooks::serialize_take_off_ped_variation_task>()(info, serializer);
		if (info->m_prop_hash != 0 &&
			info->m_prop_hash != RAGE_JOAAT("p_parachute_s") ||
			info->m_prop_hash != 0xB0A40E1 ||
			info->m_prop_hash != 0x9464EAE ||
			info->m_prop_hash != 0xC002B75 ||
			info->m_prop_hash != 0x857E060
			)
		{
			notify::crash_blocked(g->m_syncing_player, "invalid parachute");
			info->m_prop_hash = 0;
		}
	}
}