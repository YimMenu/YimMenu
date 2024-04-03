#include "gui.hpp"
#include "pointers.hpp"
#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"

namespace big
{
	void select_language()
	{
		ImGui::SeparatorText("ONBOARDING_SET_LANGUAGE"_T.data());

		const auto& language_entries = g_translation_service.available_translations();
		const auto& current_pack     = g_translation_service.current_language_pack();
		if (language_entries.contains(current_pack)
		    && ImGui::BeginCombo("VIEW_SETTINGS_MENU_LANGUAGE"_T.data(), language_entries.at(current_pack).name.c_str()))
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

	void select_menu_open_key()
	{
		ImGui::SeparatorText("ONBOARDING_SET_MENU_OPEN_KEY"_T.data());
		if (ImGui::Hotkey("VIEW_HOTKEY_SETTINGS_MENU_TOGGLE"_T.data(), &g.settings.hotkeys.menu_toggle))
		{
			g_notification_service.push("ONBOARDING_NOTIFICATION_TITLE"_T.data(), "ONBOARDING_NOTIFICATION_OPEN_KEY"_T.data());
		}
	}

	void developer_console()
	{
		ImGui::SeparatorText("ONBOARDING_ENABLE_DEVELOPER_CONSOLE"_T.data());
		components::command_checkbox<"external_console">();
	}

	void view::onboarding()
	{
		static bool onboarding_open = false;
		if (g.settings.onboarding_complete)
		{
			return;
		}

		if (!onboarding_open)
		{
			g_gui->toggle(true);
			ImGui::OpenPopup("ONBOARDING_WELCOME_TITLE"_T.data());
			onboarding_open = true;
		}

		const auto window_size     = ImVec2{600, 400};
		const auto window_position = ImVec2{(*g_pointers->m_gta.m_resolution_x - window_size.x) / 2,
		    (*g_pointers->m_gta.m_resolution_y - window_size.y) / 2};

		ImGui::SetNextWindowSize(window_size, ImGuiCond_Always);
		ImGui::SetNextWindowPos(window_position, ImGuiCond_Always);

		if (ImGui::BeginPopupModal("ONBOARDING_WELCOME_TITLE"_T.data()))
		{
			select_language();
			select_menu_open_key();
			developer_console();

			if (ImGui::Button("CLOSE"_T.data()))
			{
				g.settings.onboarding_complete = true;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}
