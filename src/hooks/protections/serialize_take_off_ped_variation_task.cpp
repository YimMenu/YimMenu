#include "hooking.hpp"
#include "util/notify.hpp"
#include <datanodes/task/ClonedTakeOffPedVariationInfo.hpp>

namespace big
{
	void hooks::serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer)
	{
		g_hooking->get_original<hooks::serialize_take_off_ped_variation_task>()(info, serializer);
		if (info->m_parachute_override_model_hash != 0 && info->m_parachute_override_model_hash != RAGE_JOAAT("p_parachute_s"))
		{
			notify::crash_blocked(g->m_syncing_player, "invalid parachute");
			info->m_parachute_override_model_hash = 0;
		}
	}
}