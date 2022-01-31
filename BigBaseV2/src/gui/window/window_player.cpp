#include "player/player_tabs.hpp"
#include "gui/window.hpp"
#include "imgui.h"

namespace big
{
	void window::w_player()
	{
		if (g_player_service->m_selected_player == nullptr || !g_player_service->m_selected_player->is_valid())
		{
			g.window.player = false;

			return;
		}
		else g.window.player = true;

		char title[64];
		strcpy(title, "Player Options: ");
		strcat(title, g_player_service->m_selected_player->get_name());
		strcat(title, "###player_options");

		ImGui::SetNextWindowSize({ 350.f, 300.f }, ImGuiCond_FirstUseEver);
		if (g.window.player && ImGui::Begin(title, &g.window.player))
		{
			ImGui::BeginTabBar("tabbar_player");
			tab_player::tab_info();
			tab_player::tab_teleport();
			tab_player::tab_toxic();
			ImGui::EndTabBar();

			ImGui::End();
		}

		if (!g.window.player)
			g_player_service->m_selected_player = nullptr;
	}
}