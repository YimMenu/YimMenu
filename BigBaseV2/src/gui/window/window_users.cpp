#include <algorithm>
#include <iterator>
#include "gui/window.hpp"
#include "imgui.h"

namespace big
{
	void window::users()
	{
		static const float height_correction = 28.f;
		static const float width = 170.f;

		ImGui::SetNextWindowSize({ width, (float)g.window.y - height_correction }, ImGuiCond_Always);
		ImGui::SetNextWindowPos({ g.window.x - width, height_correction }, ImGuiCond_Always);
		if (ImGui::Begin("###player_menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			auto vecButtonWidth = ImVec2(ImGui::GetWindowSize().x - 15.f, 0.0f);

			//ImGui::TextColored({ 255,255,255,255 }, "YOU:");

			//if (ImGui::Button(g_player.name, vecButtonWidth))
			//{
			//	g_selectedPlayer = g_player;
			//	g_temp.windows.player = true;
			//}

			//ImGui::Separator();

			CPlayer players[32];
			std::copy(std::begin(g.players), std::end(g.players), std::begin(players));
			std::sort(std::begin(players), std::end(players));

			char title[64];
			sprintf(title, "Friends (%d)###friend_lists", g.friend_count);
			if (ImGui::TreeNode(title))
			{
				ImGui::Unindent();

				bool friendInLobby = false;

				for (auto& player : players)
				{
					if (player.is_friend && player.is_online)
					{
						friendInLobby = true;

						if (ImGui::Button(player.name, vecButtonWidth))
						{
							g.selected_player = player;
							g.window.player = true;
						}
					}
				}

				if (!friendInLobby)
				{
					ImGui::TextColored({ 180,180,180,255 }, "No friends in\ncurrent lobby.");
				}

				ImGui::Indent();
				ImGui::TreePop();
				ImGui::Separator();
			}

			sprintf(title, "Players (%d)###player_lists", g.player_count);
			if (ImGui::TreeNode(title))
			{
				ImGui::Unindent();

				for (auto& player : players)
				{
					if (!player.is_friend && player.is_online)
					{
						if (ImGui::Button(player.name, vecButtonWidth))
						{
							g.selected_player = player;
							g.window.player = true;
						}
					}
				}

				ImGui::Indent();
				ImGui::TreePop();
			}

			ImGui::End();
		}
	}
}