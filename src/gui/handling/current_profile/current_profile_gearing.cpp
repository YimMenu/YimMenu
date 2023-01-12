#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_gearing()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_GEARING"_T.data()))
		{
			ImGui::Text("HANDLING_INITIAL_DRIVE_GEARS"_T.data());
			int initial_drive_gears = g_local_player->m_vehicle->m_handling_data->m_initial_drive_gears;
			if (ImGui::DragInt("###handling_drive_gears", &initial_drive_gears, .1f, 1, 16))
				g_local_player->m_vehicle->m_handling_data->m_initial_drive_gears = initial_drive_gears;

			ImGui::Text("HANDLING_UPSHIFT_MULTIPLIER"_T.data());
			ImGui::DragFloat("###handling_upshift", &g_local_player->m_vehicle->m_handling_data->m_upshift, .01f, 0.f, 10.f);

			ImGui::Text("HANDLING_DOWNSHIFT_MULTIPLIER"_T.data());
			ImGui::DragFloat("###handling_downshift", &g_local_player->m_vehicle->m_handling_data->m_downshift, .01f, 0.f, 10.f);

			ImGui::EndTabItem();
		}
	}
};