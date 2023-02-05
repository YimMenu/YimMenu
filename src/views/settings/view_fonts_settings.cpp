#include "views/view.hpp"

namespace big
{
	void view::fonts_settings()
	{


		const auto& font_entries = g_fonts_service->available_fonts();
		std::string current_font = g_fonts_service->current_font();
		if (current_font.empty())
		{
			current_font = "Default";
		}
		ImGui::Text("SETTINGS_FONTS"_T.data());
		if (ImGui::BeginCombo("##combo-fonts", current_font.c_str()))
		{
			for (auto& i : font_entries)
			{
				if (ImGui::Selectable(i.first.c_str()))
					g_fonts_service->select_font(i.first);
				if (i.first == current_font)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
}
