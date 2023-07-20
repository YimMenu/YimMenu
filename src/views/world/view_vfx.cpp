#include "views/view.hpp"

#include <imgui_internal.h>


namespace big
{
	void view::vfx()
	{
		ImGui::Checkbox("Enable Custom Sky Color", &g.vfx.enable_custom_sky_color);

		ImGui::ColorEdit4("VFX_AZIMUTH_EAST"_T.data(), (float*)&g.vfx.azimuth_east);
		ImGui::ColorEdit4("VFX_AZIMUTH_WEST"_T.data(), (float*)&g.vfx.azimuth_west);
		ImGui::ColorEdit4("VFX_AZIMUTH_TRANSITION"_T.data(), (float*)&g.vfx.azimuth_transition);
		ImGui::ColorEdit4("VFX_ZENITH"_T.data(), (float*)&g.vfx.zenith);

		ImGui::Separator();

		ImGui::SliderFloat("VFX_STARS_INTENSITY"_T.data(), &g.vfx.stars_intensity, 0, 20);
	}
}