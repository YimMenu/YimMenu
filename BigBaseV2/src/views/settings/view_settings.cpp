#include "views/view.hpp"
#include "widgets/imgui_hotkey.hpp"
#include "script_mgr.hpp"
#include "services/notification_service.hpp"

namespace big
{

	void scripts_popupmodal() {

		ImGui::BeginGroup();
		components::small_text("Scripts");
		ImGui::SameLine(ImGui::GetWindowWidth() - 100);
		if (ImGui::Button("Close")) ImGui::CloseCurrentPopup();
		ImGui::Spacing();
		components::small_text("These scripts are responsible for all looped features,\nOnly disable if you know what you are doing.");

		for (auto& s : g_script_mgr.get_scripts_data()) {
			if (ImGui::Checkbox(s->m_name, s->get_enabled_pointer())) g_notification_service->push(std::string(s->m_name).append(" script"), *s->get_enabled_pointer() ? "Resumed" : "Halted");
		}

		ImGui::EndGroup();


	}

	void view::settings() {
		components::small_text("Hotkeys");

		ImGui::PushItemWidth(350.f);

		if (ImGui::Hotkey("Menu Toggle", &g->settings.hotkeys.menu_toggle))
			g->settings.hotkeys.editing_menu_toggle = true; // make our menu reappear

		ImGui::Text("(Below hotkey is not implemented)");
		ImGui::Hotkey("Teleport to waypoint", &g->settings.hotkeys.teleport_waypoint);

		ImGui::PopItemWidth();

		
		ImGui::Separator();


		if (ImGui::Button("Manage scripts")) ImGui::OpenPopup("Scripts");

		ImGui::SetNextWindowSize({ 388,576 }, ImGuiCond_FirstUseEver); ImGui::SetNextWindowPos({ 780,228 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("Scripts")) {

			scripts_popupmodal();

			ImGui::EndPopup();
		}
		
	}
}