#include "player_tabs.hpp"
#include "util/misc.hpp"

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
				if (CPlayerInfo* player_info = net_player->m_player_info; player_info != nullptr)
				{
					rage::netPlayerData& netData = player_info->m_net_player_data;

					ImGui::Text("Session Host: %s", net_player->is_host() ? "Yes" : "No");
					
					ImGui::Separator();

					ImGui::Text("Wanted Level: %d", player_info->m_wanted_level);
					ImGui::Text("Player God Mode: %s", misc::has_bit_set((int*)&player_info->m_ped->m_damage_bits, 8) ? "Yes" : "No");
					ImGui::Text("Vehicle God Mode: %s",
						player_info->m_ped->m_vehicle == nullptr ? "No vehicle detected" :
						misc::has_bit_set((int*)&player_info->m_ped->m_vehicle->m_damage_bits, 8) ? "Yes" : "No"
					);

					ImGui::Separator();

					ImGui::Text("Rockstar ID: %d", netData.m_rockstar_id);
					ImGui::Text("IP Address: %d.%d.%d.%d:%d", netData.m_external_ip.m_field1, netData.m_external_ip.m_field2, netData.m_external_ip.m_field3, netData.m_external_ip.m_field4, netData.m_external_port);
				}
			}

			ImGui::EndTabItem();
		}
	}
}