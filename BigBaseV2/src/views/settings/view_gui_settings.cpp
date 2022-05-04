#include "views/view.hpp"

namespace big
{
	void view::gui_settings()
	{
		static ImVec4 col_gui = ImGui::ColorConvertU32ToFloat4(g->window.color);
		if (ImGui::ColorEdit4("Gui Color##gui_picker", (float*)&col_gui, ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoSidePreview))
		{
			g->window.color = ImGui::ColorConvertFloat4ToU32(col_gui);
		}
	}

}