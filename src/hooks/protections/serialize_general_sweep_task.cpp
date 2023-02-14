#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	uint64_t hooks::serialize_general_sweep_task(uint64_t a1, rage::CSyncDataBase* serializer)
	{
		auto result = g_hooking->get_original<&serialize_general_sweep_task>()(a1, serializer);
		switch (*(rage::joaat_t*)(a1 + 100))
		{
		case RAGE_JOAAT("rcmpaparazzo1ig_2"): //TASK_SWEEP_AIM_POSITION
		case RAGE_JOAAT("random@paparazzi@pap_anims"): //TASK_SWEEP_AIM_ENTITY
		{
			if (*(rage::joaat_t*)(a1 + 88) != RAGE_JOAAT("sweep_low") || *(rage::joaat_t*)(a1 + 88 + 4) != RAGE_JOAAT("sweep_med") || *(rage::joaat_t*)(a1 + 88 + 8) != RAGE_JOAAT("sweep_high"))
			{
				notify::crash_blocked(g.m_syncing_player, "invalid sweep anim");
				*(rage::joaat_t*)(a1 + 88) = RAGE_JOAAT("sweep_low");
				*(rage::joaat_t*)(a1 + 88 + 4) = RAGE_JOAAT("sweep_med");
				*(rage::joaat_t*)(a1 + 88 + 8) = RAGE_JOAAT("sweep_high");
			}
			break;
		}
		case RAGE_JOAAT("missCarsteal2"): //TASK_SWEEP_AIM_ENTITY
		{
			if (*(rage::joaat_t*)(a1 + 88) != RAGE_JOAAT("sweep_high") || *(rage::joaat_t*)(a1 + 88 + 4) != RAGE_JOAAT("sweep_high") || *(rage::joaat_t*)(a1 + 88 + 8) != RAGE_JOAAT("sweep_high"))
			{
				notify::crash_blocked(g.m_syncing_player, "invalid sweep anim");
				*(rage::joaat_t*)(a1 + 88) = RAGE_JOAAT("sweep_high");
				*(rage::joaat_t*)(a1 + 88 + 4) = RAGE_JOAAT("sweep_high");
				*(rage::joaat_t*)(a1 + 88 + 8) = RAGE_JOAAT("sweep_high");
			}
			break;
		}
		default:
		{
			notify::crash_blocked(g.m_syncing_player, "invalid sweep anim");
			*(rage::joaat_t*)(a1 + 100) = RAGE_JOAAT("rcmpaparazzo1ig_2");
			*(rage::joaat_t*)(a1 + 88) = RAGE_JOAAT("sweep_low");
			*(rage::joaat_t*)(a1 + 88 + 4) = RAGE_JOAAT("sweep_med");
			*(rage::joaat_t*)(a1 + 88 + 8) = RAGE_JOAAT("sweep_high");
			break;
		}
		}
		return result;
	}
}
