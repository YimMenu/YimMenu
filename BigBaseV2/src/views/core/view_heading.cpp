#include "views/view.hpp"

namespace big
{
	void view::heading()
	{
		ImGui::SetNextWindowSize({ 250.f, 80.f });
		ImGui::SetNextWindowPos({ 10.f, 10.f });
		if (ImGui::Begin("menu_heading", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::BeginGroup();
			ImGui::Text("Welcome");
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.172f, 0.380f, 0.909f, 1.f));
			ImGui::Text(g_local_player == nullptr || g_local_player->m_player_info == nullptr ? "unknown" : g_local_player->m_player_info->m_net_player_data.m_name);
			ImGui::PopStyleColor();
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::SetCursorPos({ 250.f - ImGui::CalcTextSize("Unload").x - ImGui::GetStyle().ItemSpacing.x, ImGui::GetStyle().WindowPadding.y / 2 + ImGui::GetStyle().ItemSpacing.y + (ImGui::CalcTextSize("W").y / 2) });
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
			if (components::nav_button("Unload"))
			{
				g_running = false;
			}
			ImGui::PopStyleColor();
		}
	}
}
