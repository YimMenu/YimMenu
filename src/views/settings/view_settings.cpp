#include "core/data/language_codes.hpp"
#include "pointers.hpp"
#include "thread_pool.hpp"
#include "views/view.hpp"

namespace big
{
	void view::settings()
	{
		const auto& language_entries = g_translation_service.available_translations();
		const auto& current_pack     = g_translation_service.current_language_pack();

		ImGui::SeparatorText("SETTINGS_LANGUAGES"_T.data());

		if (language_entries.contains(current_pack) && ImGui::BeginCombo("VIEW_SETTINGS_MENU_LANGUAGE"_T.data(), language_entries.at(current_pack).name.c_str()))
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

		if (ImGui::BeginCombo("VIEW_SETTINGS_GAME_LANGUAGE"_T.data(), languages[*g_pointers->m_gta.m_language].name))
		{
			for (auto& language : languages)
			{
				if (ImGui::Selectable(language.name, language.id == *g_pointers->m_gta.m_language))
				{
					*g_pointers->m_gta.m_language = language.id;

					g_fiber_pool->queue_job([] {
						g_pointers->m_gta.m_update_language(true);
					});
				}

				if (language.id == *g_pointers->m_gta.m_language)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		if (components::button("VIEW_SETTINGS_FORCE_UPDATE_LANGUAGES"_T))
		{
			g_thread_pool->push([] {
				g_translation_service.update_n_reload_language_packs();

				g_notification_service->push_success("LANGUAGE"_T.data(), "VIEW_SETTINGS_FINISHED_UPDATING_TRANSLATIONS"_T.data());
			});
		}

		ImGui::SeparatorText("SETTINGS_MISC"_T.data());
		ImGui::Checkbox("SETTINGS_MISC_DEV_DLC"_T.data(), &g.settings.dev_dlc);

		if (ImGui::Button("VIEW_SETTINGS_RESET"_T.data()))
		{
			g.write_default_config();
			g.load();
		}
	}
}