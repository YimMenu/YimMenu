#include "hooking/hooking.hpp"

#include <misc/vfx/TimecycleKeyframeData.hpp>

namespace big
{
	inline rage::fvector4 float_to_vector(const float color[4])
	{
		return rage::fvector4(color[0], color[1], color[2], color[3]);
	}

	void hooks::update_timecycle_keyframe_data(int64_t timecycleManager, TimecycleKeyframeData* timecycleKeyframeData)
	{
		g_hooking->get_original<update_timecycle_keyframe_data>()(timecycleManager, timecycleKeyframeData);

		if (g.vfx.enable_custom_sky_color)
		{
			timecycleKeyframeData->m_azimuth_east       = float_to_vector(g.vfx.azimuth_east);
			timecycleKeyframeData->m_azimuth_west       = float_to_vector(g.vfx.azimuth_west);
			timecycleKeyframeData->m_azimuth_transition = float_to_vector(g.vfx.azimuth_transition);
			timecycleKeyframeData->m_zenith             = float_to_vector(g.vfx.zenith);

			timecycleKeyframeData->m_stars_iten = g.vfx.stars_intensity;
		}
	}
}