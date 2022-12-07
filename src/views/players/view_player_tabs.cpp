#include "views/view.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void view::view_player_tabs() {

		if (!*g_pointers->m_is_session_started && !g_player_service->get_selected()->is_valid()) return;

		if (ImGui::Begin("Player", &g->window.player))
		{
			if (ImGui::BeginTabBar("player_tabbar"))
			{
				if (ImGui::BeginTabItem("Info"))
				{
					view::view_player_info();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Troll"))
				{
					view::view_player_troll();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc"))
				{
					view::view_player_misc();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Toxic"))
				{
					view::view_player_toxic();
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Kicks and Crashes"))
				{
					view::view_player_kicks_and_crashes();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}
}
