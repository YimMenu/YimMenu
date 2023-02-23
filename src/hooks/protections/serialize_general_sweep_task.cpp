#include "hooking.hpp"
#include "util/notify.hpp"
#include <datanodes/task/CClonedGeneralSweepInfo.hpp>

namespace big
{
	uint64_t hooks::serialize_general_sweep_task(CClonedGeneralSweepInfo* info, rage::CSyncDataBase* serializer)
	{
		auto result = g_hooking->get_original<&serialize_general_sweep_task>()(info, serializer);
		switch (info->m_clip_set_id)
		{
		case RAGE_JOAAT("rcmpaparazzo1ig_2"): //TASK_SWEEP_AIM_POSITION
		case RAGE_JOAAT("random@paparazzi@pap_anims"): //TASK_SWEEP_AIM_ENTITY
		{
			if (info->m_low_clip != RAGE_JOAAT("sweep_low") || info->m_med_clip != RAGE_JOAAT("sweep_med") || info->m_high_clip != RAGE_JOAAT("sweep_high"))
			{
				notify::crash_blocked(g.m_syncing_player, "invalid sweep anim");
				info->m_low_clip = RAGE_JOAAT("sweep_low");
				info->m_med_clip = RAGE_JOAAT("sweep_med");
				info->m_high_clip = RAGE_JOAAT("sweep_high");
			}
			break;
		}
		case RAGE_JOAAT("missCarsteal2"): //TASK_SWEEP_AIM_ENTITY
		{
			if (info->m_low_clip != RAGE_JOAAT("sweep_high") || info->m_med_clip != RAGE_JOAAT("sweep_high") || info->m_high_clip != RAGE_JOAAT("sweep_high"))
			{
				notify::crash_blocked(g.m_syncing_player, "invalid sweep anim");
				info->m_low_clip = RAGE_JOAAT("sweep_high");
				info->m_med_clip = RAGE_JOAAT("sweep_high");
				info->m_high_clip = RAGE_JOAAT("sweep_high");
			}
			break;
		}
		default:
		{
			notify::crash_blocked(g.m_syncing_player, "invalid sweep anim");
			info->m_clip_set_id = RAGE_JOAAT("rcmpaparazzo1ig_2");
			info->m_low_clip = RAGE_JOAAT("sweep_low");
			info->m_med_clip = RAGE_JOAAT("sweep_med");
			info->m_high_clip = RAGE_JOAAT("sweep_high");
			break;
		}
		}
		return result;
	}
}
