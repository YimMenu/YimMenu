#include "services/gui_service.hpp"
#include "views/view.hpp"
#include "services/player_service.hpp"

namespace big
{
	void view::navigation() {
		ImGui::SetNextWindowPos({ 10.f, 100.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 250.f, 0.f }, ImGuiCond_Always);

		if (ImGui::Begin("navigation", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			g_gui_service->reset_nav_size();
			for (std::pair<tabs, navigation_struct> navItem : g_gui_service->get_navigation()) {
				if (navItem.first == tabs::PLAYER) continue;
				components::nav_item(navItem, 0);
			}

			ImGui::End();
		}
	}
}