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

		if (ImGui::BeginCombo("Menu Language", language_entries.at(current_pack).name.c_str()))
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

		if (ImGui::BeginCombo("Game Language", languages[*g_pointers->m_gta.m_language].name))
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

		if (components::button("Force Update Languages"))
		{
			g_thread_pool->push([] {
				g_translation_service.update_language_packs();

				g_notification_service->push_success("Translations", "Finished updating translations.");
			});
		}

		ImGui::SeparatorText("Rainbow");
		ImGui::Checkbox("Spasm", &g.settings.rainbow.spasm);
		ImGui::Checkbox("Fade", &g.settings.rainbow.fade);
		ImGui::SliderInt("Speed", &g.settings.rainbow.speed, 0, 10); // TODO: THIS SPEED DOESNT MAKE SENSE

		ImGui::SeparatorText("SETTINGS_MISC"_T.data());
		ImGui::Checkbox("SETTINGS_MISC_DEV_DLC"_T.data(), &g.settings.dev_dlc);

		if (ImGui::Button("Reset Settings"))
		{
			g.write_default_config();
			g.load();
		}


	}
}