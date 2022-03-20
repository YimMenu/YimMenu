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

			/*static navigation_struct playerPage = { tabs::PLAYER, "Player", view::view_player };

			if (ImGui::BeginListBox("players", {(float)*g_pointers->m_resolution_x * 0.15f - 30, (float)*g_pointers->m_resolution_y * 0.3f})) {
				for (auto& item : g_player_service->m_players)
				{
					std::unique_ptr<player>& plyr = item.second;
					if (plyr->is_host())
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.45f, 0.69f, 1.f));
					if (ImGui::Button(plyr->get_name(), { ImGui::GetWindowSize().x - 15.f, 0.f }))
					{
						g_player_service->set_selected(plyr.get());
						current_tab = &playerPage;
						g->window.switched_view = true;
					}
					if (plyr->is_host())
						ImGui::PopStyleColor();
				}

				ImGui::EndListBox();
			}*/
			ImGui::End();
		}
	}
}