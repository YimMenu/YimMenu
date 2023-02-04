#include "views/view.hpp"

namespace big
{
	void view::fonts_settings()
	{
		const auto& font_entries = g_fonts_service.available_fonts();
		const auto& language_entries = g_translation_service.available_translations();
		const auto current_pack = g_translation_service.current_language_pack();

		ImGui::Text("SETTINGS_FONTS"_T.data());
		if (ImGui::BeginCombo("##combo-languages", language_entries.at(current_pack).name.c_str()))
		{
			for (auto& i : font_entries)
			{
				if (ImGui::Selectable(i.first.c_str()))
					g_fonts_service.select_font(i.first);
			}
			ImGui::EndCombo();
		}
	}
}