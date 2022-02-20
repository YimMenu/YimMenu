#include "gui/window.hpp"
#include "imgui.h"
#include "services/player_service.hpp"

namespace big
{
	void window::users()
	{
		static const float height_correction = 28.f;
		static const float width = 170.f;

		ImGui::SetNextWindowSize({ width, (float)g.window.y - height_correction }, ImGuiCond_Always);
		ImGui::SetNextWindowPos({ g.window.x - width, height_correction }, ImGuiCond_Always);
		if (g.window.users && ImGui::Begin("###player_menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("Friends:");
			for (auto& item : g_player_service->m_players)
			{
				std::unique_ptr<player>& plyr = item.second;
				if (plyr->is_friend() && ImGui::Button(plyr->get_name(), { ImGui::GetWindowSize().x - 15.f, 0.f }))
				{
					g_player_service->set_selected(plyr.get());

					g.window.player = true;
				}
			}

			ImGui::Text("Players:");
			for (auto& item : g_player_service->m_players)
			{
				std::unique_ptr<player>& plyr = item.second;
				if (!plyr->is_friend() && ImGui::Button(plyr->get_name(), { ImGui::GetWindowSize().x - 15.f, 0.f }))
				{
					g_player_service->set_selected(plyr.get());

					g.window.player = true;
				}
			}

			ImGui::End();
		}
	}
}