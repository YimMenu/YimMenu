#include "views/view.hpp"
#include "services/gui_service.hpp"

namespace big
{
	static void player_button(const player_ptr& plyr)
	{
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

	void view::players()
	{
		float window_pos = 110.f + g_gui_service->nav_ctr * ImGui::CalcTextSize("W").y + g_gui_service->nav_ctr * ImGui::GetStyle().ItemSpacing.y + g_gui_service->nav_ctr * ImGui::GetStyle().ItemInnerSpacing.y + ImGui::GetStyle().WindowPadding.y;

		ImGui::SetNextWindowSize({ 250.f, 0.f });
		ImGui::SetNextWindowPos({ 10.f, window_pos });
		if (ImGui::Begin("playerlist", nullptr, window_flags))
		{
			const auto player_count = g_player_service->m_players.size();

			// https://github.com/ocornut/imgui/issues/4399
			float window_height = 1.f;

			window_height += (ImGui::CalcTextSize("A").y + ImGui::GetStyle().ItemInnerSpacing.y * 2 + 6.5f) * player_count;
			window_height += window_pos > (float)*g_pointers->m_resolution_y - 10.f ? (float)*g_pointers->m_resolution_y - (window_pos + 40.f) : 0;

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, { 0.f, 0.f, 0.f, 0.f });

			if (ImGui::BeginListBox("##players", { 250.f - ImGui::GetStyle().WindowPadding.x * 2 , window_height })) {
				const auto& self = g_player_service->get_self();
				if (self)
					player_button(self);

				ImGui::Separator();

				for (const auto& item : g_player_service->m_players)
				{
					if (item.second != self) {
						player_button(item.second);
					}
				}

				ImGui::EndListBox();
			}
			ImGui::PopStyleColor(2);

			ImGui::End();
		}
	}
}
