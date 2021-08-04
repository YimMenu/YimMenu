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

			if (g.selected_player.net_player)
			{
				ImGui::Text("Session Host: %s", g.selected_player.net_player->is_host() ? "Yes" : "No");

				rage::netPlayerData* net_data = g.selected_player.net_player->get_net_data();

				ImGui::Text("Rockstar ID: %d", net_data->m_rockstar_id);
				ImGui::Text("IP Address: %d.%d.%d.%d:%d", net_data->m_online_ip.m_field1, net_data->m_online_ip.m_field2, net_data->m_online_ip.m_field3, net_data->m_online_ip.m_field4, net_data->m_online_port);
			}

			ImGui::EndTabItem();
		}
	}
}