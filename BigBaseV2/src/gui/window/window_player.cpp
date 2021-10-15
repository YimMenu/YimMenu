#include "player/player_tabs.hpp"
#include "gui/window.hpp"
#include "imgui.h"

namespace big
{
	void window::player()
	{
		if (!g.selected_player.is_online)
		{
			g.window.player = false;

			return;
		}

		char title[64];
		strcpy(title, "Player Options: ");
		strcat(title, g.selected_player.name);
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
	}
}