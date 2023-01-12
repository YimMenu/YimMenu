#include "views/view.hpp"
#include "renderer.hpp"

namespace big
{
	void view::gui_settings()
	{
		components::sub_title("SETTINGS_UI_SCALE");
		ImGui::SliderFloat("##gui-scale", &g.window.gui_scale, 1.f, 1.5f, "%.2f");
		ImGui::SameLine();
		if (ImGui::Button("APPLY"_T.data()))
			g_renderer->rescale(g.window.gui_scale);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("SETTINGS_UI_SCALE_DESCRIPTION"_T.data());

		components::sub_title("SETTINGS_UI_COLOR"_T);
		static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g.window.color);
		if (ImGui::ColorEdit4("SETTINGS_UI_COLOR_PICKER"_T.data(), (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g.window.color = ImGui::ColorConvertFloat4ToU32(col_gui);
		}
	}

}