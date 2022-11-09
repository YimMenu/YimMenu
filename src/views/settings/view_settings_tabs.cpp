#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::settings_tabs() {
		if (ImGui::BeginTabBar("settings_tabbar"))
		{
			if (ImGui::BeginTabItem("Settings"))
			{
				view::settings();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Context Menu"))
			{
				view::context_menu_settings();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("ESP"))
			{
				view::esp_settings();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("GUI"))
			{
				view::gui_settings();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Notifications"))
			{
				view::notification_settings();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Protection"))
			{
				view::protection_settings();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
}
