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

			ImGui::Text("Player ID: %d", g_player_service->get_selected()->id());

			ImGui::Text("Session Host: %s", g_player_service->get_selected()->is_host() ? "Yes" : "No");
					
			ImGui::Separator();

			if (CPlayerInfo* player_info = g_player_service->get_selected()->get_player_info(); player_info != nullptr)
			{
				ImGui::Text("Wanted Level: %d", player_info->m_wanted_level);
			}

			if (CPed* ped = g_player_service->get_selected()->get_ped(); ped != nullptr)
			{
				ImGui::Text("Player God Mode: %s",
					misc::has_bit_set((int*)&ped->m_damage_bits, 8) ? "Yes" : "No"
				);
			}

			CAutomobile* vehicle = g_player_service->get_selected()->get_current_vehicle();
			ImGui::Text("Vehicle God Mode: %s",
				vehicle == nullptr ? "No vehicle detected" :
				misc::has_bit_set((int*)&vehicle->m_damage_bits, 8) ? "Yes" : "No"
			);

			ImGui::Separator();

			if (rage::netPlayerData* net_player_data = g_player_service->get_selected()->get_net_data(); net_player_data != nullptr)
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