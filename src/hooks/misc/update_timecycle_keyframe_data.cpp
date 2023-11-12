#include "hooking.hpp"

#include <misc/vfx/TimecycleKeyframeData.hpp>

namespace big
{
	void hooks::update_timecycle_keyframe_data(int64_t timecycleManager, TimecycleKeyframeData* timecycleKeyframeData)
	{
		g_hooking->get_original<update_timecycle_keyframe_data>()(timecycleManager, timecycleKeyframeData);
	}
}