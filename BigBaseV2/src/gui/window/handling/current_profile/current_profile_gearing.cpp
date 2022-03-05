#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_gearing()
	{
		if (ImGui::BeginTabItem("Gearing"))
		{
			ImGui::Text("Initial Drive Gears");
			int initial_drive_gears = g_local_player->m_vehicle->m_handling->m_initial_drive_gears;
			if (ImGui::DragInt("###handling_drive_gears", &initial_drive_gears, .1f, 1, 16))
				g_local_player->m_vehicle->m_handling->m_initial_drive_gears = initial_drive_gears;

			ImGui::Text("Upshift Multiplier");
			ImGui::DragFloat("###handling_upshift", &g_local_player->m_vehicle->m_handling->m_upshift, .01f, 0.f, 10.f);

			ImGui::Text("Downshift Multiplier");
			ImGui::DragFloat("###handling_downshift", &g_local_player->m_vehicle->m_handling->m_downshift, .01f, 0.f, 10.f);

			ImGui::EndTabItem();
		}
	}
};