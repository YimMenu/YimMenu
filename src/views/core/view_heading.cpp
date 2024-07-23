#include "views/view.hpp"
#include "lua/lua_manager.hpp"

namespace big
{
	void view::heading()
	{
		ImGui::SetNextWindowSize({300.f * g.window.gui_scale, 80.f * g.window.gui_scale});
		ImGui::SetNextWindowPos({10.f, 10.f});
		if (ImGui::Begin("menu_heading", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::BeginGroup();
			ImGui::Text("HEADING_WELCOME"_T.data());
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.172f, 0.380f, 0.909f, 1.f));
			ImGui::Text(g_local_player == nullptr || g_local_player->m_player_info == nullptr ?
			        "UNKNOWN_USERNAME"_T.data() :
			        g_local_player->m_player_info->m_net_player_data.m_name);
			ImGui::PopStyleColor();
			ImGui::EndGroup();
#ifdef YIM_DEV
			ImGui::SameLine();
			ImGui::SetCursorPos(
			    {(300.f * g.window.gui_scale) - ImGui::CalcTextSize("UNLOAD"_T.data()).x - ImGui::GetStyle().ItemSpacing.x,
			        ImGui::GetStyle().WindowPadding.y / 2 + ImGui::GetStyle().ItemSpacing.y + (ImGui::CalcTextSize("W").y / 2)});
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
			if (components::nav_button("UNLOAD"_T))
			{
				g_lua_manager->trigger_event<menu_event::MenuUnloaded>();
				g_running = false;
			}
			ImGui::PopStyleColor();
#endif
		}
		ImGui::End();
	}
}
