#include "pointers.hpp"
#include "services/gui/gui_service.hpp"
#include "services/players/player_service.hpp"
#include "views/view.hpp"

namespace big
{
	static void player_button(const player_ptr& plyr)
	{
		if (plyr->is_host())
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.45f, 0.69f, 1.f));

		ImGui::PushID(plyr->id());
		if (ImGui::Button(plyr->get_name(), {ImGui::GetWindowSize().x - 15.f, 0.f}))
		{
			g_player_service->set_selected(plyr);
			g_gui_service->set_selected(tabs::PLAYER);
			g->window.switched_view = true;
		}
		ImGui::PopID();

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
			const auto player_count = g_player_service->players().size() + 1;

			float window_height = (ImGui::CalcTextSize("A").y + ImGui::GetStyle().ItemInnerSpacing.y * 2 + 8.5f) * player_count;
			window_height = window_height + window_pos > (float)*g_pointers->m_resolution_y - 10.f ? (float)*g_pointers->m_resolution_y - (window_pos + 40.f) : window_height;

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, { 0.f, 0.f, 0.f, 0.f });

			if (ImGui::BeginListBox("##players", { 250.f - ImGui::GetStyle().WindowPadding.x * 2 , window_height }))
			{
				player_button(g_player_service->get_self());

				ImGui::Separator();

				for (const auto& [_, player] : g_player_service->players())
					player_button(player);

				ImGui::EndListBox();
			}
			ImGui::PopStyleColor(2);
		}
		ImGui::End();
	}
}
