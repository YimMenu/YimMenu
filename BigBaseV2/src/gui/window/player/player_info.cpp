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

			
			if (CNetGamePlayer* net_player = g.selected_player.net_player; net_player != nullptr)
			{
				if (CPlayerInfo* player_info = net_player->player_info; player_info != nullptr)
				{
					netPlayerData& netData = player_info->m_net_player_data;

					ImGui::Text("Session Host: %s", net_player->is_host() ? "Yes" : "No");

					ImGui::Text("Rockstar ID: %d", netData.m_rockstar_id);
					ImGui::Text("IP Address: %d.%d.%d.%d:%d", netData.m_external_ip.m_field1, netData.m_external_ip.m_field2, netData.m_external_ip.m_field3, netData.m_external_ip.m_field4, netData.m_external_port);
				}
			}

			ImGui::EndTabItem();
		}
	}
}