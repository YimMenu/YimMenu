#include "views/view.hpp"

namespace big
{
	void view::context_menu_settings()
	{
		ImGui::Checkbox("Context Menu Enabled", &g->context_menu.enabled);

		static ImVec4 selected_option_color = ImGui::ColorConvertU32ToFloat4(g->context_menu.selected_option_color);
		ImGui::Text("Selected Option Color:");
		if (ImGui::ColorEdit4("###BSelected Option Color##cm_picker", (float*)&selected_option_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g->context_menu.selected_option_color = ImGui::ColorConvertFloat4ToU32(selected_option_color);
		}

		ImGui::Checkbox("Bounding Box Enabled", &g->context_menu.bounding_box_enabled);

		if (g->context_menu.bounding_box_enabled)
		{
			static ImVec4 bounding_box_color = ImGui::ColorConvertU32ToFloat4(g->context_menu.bounding_box_color);
			ImGui::Text("Bounding Box Color:");
			if (ImGui::ColorEdit4("###Bounding Box Color##cm_picker", (float*)&bounding_box_color, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
			{
				g->context_menu.bounding_box_color = ImGui::ColorConvertFloat4ToU32(bounding_box_color);
			}
		}
	}
}
