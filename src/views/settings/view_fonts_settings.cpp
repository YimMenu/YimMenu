#include "views/view.hpp"

namespace big
{
	void view::fonts_settings()
	{
		const auto& font_entries = g_fonts_service->available_fonts();

		ImGui::Text("SETTINGS_FONTS"_T.data());
		if (ImGui::BeginCombo("##combo", "fonts")
		{
			for (auto& i : font_entries)
			{
				if (ImGui::Selectable(i.first.c_str()))
					g_fonts_service->select_font(i.first);
			}
			ImGui::EndCombo();
		}
	}
}