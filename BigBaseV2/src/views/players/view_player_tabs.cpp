#include "views/view.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void view::view_player_tabs() {

		if (!*g_pointers->m_is_session_started) return;

		if (!g_player_service->get_selected()->is_valid()) return;

		if (ImGui::Begin("Player"))
		{
			if (ImGui::BeginTabBar("player_tabbar"))
			{
				if (ImGui::BeginTabItem("Info"))
				{
					view::view_player_info();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Ped"))
				{
					view::view_player_ped();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Teleport"))
				{
					view::view_player_teleport();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Toxic"))
				{
					view::view_player_toxic();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}
}
