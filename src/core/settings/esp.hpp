#pragma once
#include <imgui.h>

namespace big
{
	inline struct g_esp_t
	{
		bool enabled                    = true;
		float global_render_distance[2] = {0.f, 600.f};
		bool name                       = true;
		bool distance                   = true;
		ImU32 default_color             = 4285713522;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_esp_t, enabled, global_render_distance, name, distance, default_color)
	} g_esp{};
}