#include "player_tabs.hpp"

namespace big
{
	void tab_player::tab_info()
	{
		if (ImGui::BeginTabItem("Info"))
		{
			ImGui::Checkbox("Spectate", &g.player.spectating);

			ImGui::Separator();

			ImGui::Text("Player ID: %d", g.selected_player.id);

			if (g.selected_player.net_player != nullptr)
			{
				ImGui::Text("Session Host: %s", g.selected_player.net_player->is_host() ? "Yes" : "No");
				CPlayerInfo* player_info = g.selected_player.net_player->player_info;

				ImGui::Text("Rockstar ID: %d", player_info->m_rockstar_id);
				ImGui::Text("IP Address: %d.%d.%d.%d:%d", player_info->m_external_ip.m_field1, player_info->m_external_ip.m_field2, player_info->m_external_ip.m_field3, player_info->m_external_ip.m_field4, player_info->m_external_port);
			}

			ImGui::EndTabItem();
		}
	}
}