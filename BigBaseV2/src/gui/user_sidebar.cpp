#include "imgui.h"
#include "gui.hpp"
#include "features.hpp"

namespace big
{
	void gui::render_user_sidebar()
	{
		ImGui::SetNextWindowSize({ 350.f, (float)y }, ImGuiCond_Always);
		ImGui::SetNextWindowPos({ x - 350.f, 0.f }, ImGuiCond_Always);
		if (ImGui::Begin("###player_menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			auto vecButtonWidth = ImVec2(ImGui::GetWindowSize().x, 0.0f);

			ImGui::TextColored({ 255,255,255,255 }, "YOU:");

			if (ImGui::Button(g_players[g_playerId].name, vecButtonWidth))
			{
				g_selectedPlayer = g_playerId;
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Friends"))
			{
				bool friendInLobby = false;

				for (int i = 0; i < 32; i++)
				{
					player player = g_players[i];

					if (player.is_friend && player.is_online)
					{
						friendInLobby = true;

						if (ImGui::Button(player.name, vecButtonWidth))
						{
							g_selectedPlayer = i;
						}
					}
				}

				if (!friendInLobby)
				{
					ImGui::TextColored({ 180,180,180,255 }, "	No friends in current lobby.");
				}

				ImGui::TreePop();
				ImGui::Separator();
			}

			if (ImGui::TreeNode("Players"))
			{
				for (int i = 0; i < 32; i++)
				{
					player player = g_players[i];

					if (!player.is_friend && player.is_online && i != g_playerId)
					{
						if (ImGui::Button(player.name, vecButtonWidth))
						{
							g_selectedPlayer = i;
						}
					}
				}

				ImGui::TreePop();
			}

			ImGui::End();
		}

	}
}