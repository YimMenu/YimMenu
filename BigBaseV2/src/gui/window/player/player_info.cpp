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

			ImGui::Text("Player ID: %d", g_player_service->m_selected_player->id());

			ImGui::Text("Session Host: %s", g_player_service->m_selected_player->is_host() ? "Yes" : "No");
					
			ImGui::Separator();

			if (CPlayerInfo* player_info = g_player_service->m_selected_player->get_player_info(); player_info != nullptr)
			{
				ImGui::Text("Wanted Level: %d", player_info->m_wanted_level);
				ImGui::Text("Player God Mode: %s", misc::has_bit_set((int*)&player_info->m_ped->m_damage_bits, 8) ? "Yes" : "No");
				ImGui::Text("Vehicle God Mode: %s",
					player_info->m_ped->m_vehicle == nullptr ? "No vehicle detected" :
					misc::has_bit_set((int*)&player_info->m_ped->m_vehicle->m_damage_bits, 8) ? "Yes" : "No"
				);
			}

			ImGui::Separator();

			if (rage::netPlayerData* net_player_data = g_player_service->m_selected_player->get_net_data(); net_player_data != nullptr)
			{
				ImGui::Text("Rockstar ID: %d", net_player_data->m_rockstar_id);
				ImGui::Text(
					"IP Address: %d.%d.%d.%d:%d",
					net_player_data->m_external_ip.m_field1,
					net_player_data->m_external_ip.m_field2,
					net_player_data->m_external_ip.m_field3,
					net_player_data->m_external_ip.m_field4,
					net_player_data->m_external_port
				);
			}

			ImGui::EndTabItem();
		}
	}
}