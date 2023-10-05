#include "views/view.hpp"
#include "core/settings.hpp"

namespace big
{
	void view::esp_settings()
	{
		ImGui::Checkbox("ESP Enabled", &g.esp.enabled);

		if (g.esp.enabled)
		{
			ImGui::Text("Global Render Distance (min, max)");
			ImGui::SliderFloat2("###Global Render Distance", g.esp.global_render_distance, 0.f, 1500.f);

			ImGui::Checkbox("Show Player Distance", &g.esp.distance);

			static ImVec4 col_default    = ImGui::ColorConvertU32ToFloat4(g.esp.default_color);

			ImGui::Text("Default Color:");
			if (ImGui::ColorEdit4("###Default ESP Color##esp_picker", (float*)&col_default, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
			{
				g.esp.default_color = ImGui::ColorConvertFloat4ToU32(col_default);
			}
		}
	}
}
