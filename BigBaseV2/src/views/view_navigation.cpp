#include "views/view.hpp"
#include "services/player_service.hpp"

namespace big
{
	void view::navigation() {
		ImGui::SetNextWindowPos({ 0.f, 0.f }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ (float)g->window.x * 0.15f, (float)g->window.y }, ImGuiCond_Always);

		if (ImGui::Begin("navigation", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			components::title("Yim");
			ImGui::SameLine(0, 0);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.172f, 0.380f, 0.909f, 1.f));
			components::title("Menu");
			ImGui::PopStyleColor();
			
			components::small_text(fmt::format("Welcome {}", g_local_player == nullptr || g_local_player->m_player_info == nullptr ? "unknown" : g_local_player->m_player_info->m_net_player_data.m_name).c_str());

			for (auto& navItem : nav) {
				const bool curTab = navItem.tab == current_tab->tab;
				if (curTab)
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.29f, 0.45f, 0.69f, 1.f));

				if (components::nav_button(navItem.name)) {
					current_tab = &navItem;
					g->window.switched_view = true;
				}

				if (curTab)
					ImGui::PopStyleColor();
			}

			static navigation_struct playerPage = { tabs::PLAYER, "Player", view::view_player };

			if (ImGui::BeginListBox("players", {(float)g->window.x * 0.15f - 30, (float)g->window.y * 0.3f})) {
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
			}

			
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
			if (components::nav_button("Unload"))
			{
				g_running = false;
			}

			if (components::nav_button("Rage Quit (hard crash)"))
			{
				g_running = false;

				TerminateProcess(GetCurrentProcess(), 0);
			}

			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}