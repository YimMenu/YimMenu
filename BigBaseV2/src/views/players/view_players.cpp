#include "views/view.hpp"
#include "services/gui_service.hpp"

namespace big
{
	void view::players()
	{
		if (ImGui::Begin("playerlist", nullptr, window_flags))
		{
			const auto player_count = g_player_service->m_players.size();
			if (ImGui::BeginListBox("##players", { 250.f - ImGui::GetStyle().WindowPadding.x * 2 , 500 })) {
				for (auto& item : g_player_service->m_players)
				{
					const auto& plyr = item.second;
					if (plyr->is_host())
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.45f, 0.69f, 1.f));
					if (ImGui::Button(plyr->get_name(), { ImGui::GetWindowSize().x - 15.f, 0.f }))
					{
						g_player_service->set_selected(plyr.get());
						g_gui_service->set_selected(tabs::PLAYER);
						g->window.switched_view = true;
					}
					if (plyr->is_host())
						ImGui::PopStyleColor();
				}

				ImGui::EndListBox();
			}
			ImGui::PopStyleColor(2);

			ImGui::End();
		}
	}
}
