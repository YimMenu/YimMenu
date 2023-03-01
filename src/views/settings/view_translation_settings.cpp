#include "views/view.hpp"

namespace big
{
	void view::translation_settings()
	{
		const auto& language_entries = g_translation_service.available_translations();
		const auto current_pack      = g_translation_service.current_language_pack();

		ImGui::Text("SETTINGS_LANGUAGES"_T.data());
		if (ImGui::BeginCombo("##combo-languages", language_entries.at(current_pack).name.c_str()))
		{
			for (auto& i : language_entries)
			{
				if (ImGui::Selectable(i.second.name.c_str(), i.first == current_pack))
					g_translation_service.select_language_pack(i.first);

				if (i.first == current_pack)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
}
