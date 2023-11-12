#include "core/settings/esp.hpp"
#include "views/view.hpp"

namespace big
{
	void view::esp_settings()
	{
		ImGui::Checkbox("ESP Enabled", &g_esp.enabled);

		if (g_esp.enabled)
		{
			ImGui::Text("Global Render Distance (min, max)");
			ImGui::SliderFloat2("###Global Render Distance", g_esp.global_render_distance, 0.f, 1500.f);

			ImGui::Checkbox("Player full name", &g_esp.name);
			ImGui::Checkbox("Player Distance", &g_esp.distance);

			static ImVec4 col_default = ImGui::ColorConvertU32ToFloat4(g_esp.default_color);

			ImGui::Text("Default Color:");
			if (ImGui::ColorEdit4("###Default ESP Color##esp_picker", (float*)&col_default, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
				g_esp.default_color = ImGui::ColorConvertFloat4ToU32(col_default);
		}
	}
}
