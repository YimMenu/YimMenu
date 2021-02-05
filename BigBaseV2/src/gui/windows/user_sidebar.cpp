#include "gui/window.hpp"
#include "features.hpp"

namespace big
{
	void window::render_user_sidebar()
	{
		static const float height_correction = 28.f;
		static const float width = 170.f;

		ImGui::SetNextWindowSize({ width, (float)y - height_correction }, ImGuiCond_Always);
		ImGui::SetNextWindowPos({ x - width, height_correction }, ImGuiCond_Always);
		if (ImGui::Begin("###player_menu", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav))
		{
			auto vecButtonWidth = ImVec2(ImGui::GetWindowSize().x - 30.f, 0.0f);

			ImGui::TextColored({ 255,255,255,255 }, "YOU:");

			if (ImGui::Button(g_player.name, vecButtonWidth))
			{
				g_selectedPlayer = g_player;
				g_temp.windows.player = true;
			}

			ImGui::Separator();

			if (ImGui::TreeNode("Friends"))
			{
				ImGui::Unindent();

				bool friendInLobby = false;

				for (auto& pair : g_players)
				{
					player player = pair.second;

					if (player.is_friend && player.is_online)
					{
						friendInLobby = true;

						if (ImGui::Button(player.name, vecButtonWidth))
						{
							g_selectedPlayer = player;
							g_temp.windows.player = true;
						}
					}
				}

				if (!friendInLobby)
				{
					ImGui::TextColored({ 180,180,180,255 }, "	No friends in current lobby.");
				}

				ImGui::Indent();
				ImGui::TreePop();
				ImGui::Separator();
			}

			if (ImGui::TreeNode("Players"))
			{
				ImGui::Unindent();

				for (auto& pair : g_players)
				{
					player player = pair.second;

					if (!player.is_friend && player.is_online && player.id != g_player.id)
					{
						if (ImGui::Button(player.name, vecButtonWidth))
						{
							g_selectedPlayer = player;
							g_temp.windows.player = true;
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