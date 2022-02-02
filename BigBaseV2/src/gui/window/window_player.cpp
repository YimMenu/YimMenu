#include "player/player_tabs.hpp"
#include "gui/window.hpp"
#include "imgui.h"

namespace big
{
	void window::w_player()
	{
		char title[64];
		strcpy(title, "Player Options: ");
		strcat(title, g_player_service->get_selected()->get_name());
		strcat(title, "###player_options");

		ImGui::SetNextWindowSize({ 350.f, 300.f }, ImGuiCond_FirstUseEver);
		if (g.window.player && g_player_service->get_selected()->is_valid() && ImGui::Begin(title, &g.window.player))
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