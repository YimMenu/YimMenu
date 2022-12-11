#include "views/view.hpp"
#include "renderer.hpp"

namespace big
{
	void view::gui_settings()
	{
		components::sub_title("UI Scale");
		ImGui::SliderFloat("##gui-scale", &g->window.gui_scale, 1.f, 1.5f, "%.2f");
		ImGui::SameLine();
		if (ImGui::Button("Apply##gui-scale"))
			g_renderer->rescale(g->window.gui_scale);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Changing the UI scale may break rendering and require you to unload and inject YimMenu again.");

		components::sub_title("Colors");
		static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g->window.color);
		if (ImGui::ColorEdit4("Gui Color##gui_picker", (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g->window.color = ImGui::ColorConvertFloat4ToU32(col_gui);
		}
	}

}