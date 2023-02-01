#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_transmission()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_TRANSMISSION"_T.data()))
		{
			ImGui::Text("HANDLING_DRIVE_BIAS_FRONT"_T.data());
			float fDriveBiasFront = g_local_player->m_vehicle->m_handling_data->m_drive_bias_front / 2;
			if (ImGui::SliderFloat("##drive_bias_front", &fDriveBiasFront, 0.f, 1.0f))
				g_local_player->m_vehicle->m_handling_data->m_drive_bias_front = fDriveBiasFront * 2;

			ImGui::Text("HANDLING_DRIVE_BIAS_REAR"_T.data());
			float fDriveBiasRear = g_local_player->m_vehicle->m_handling_data->m_drive_bias_rear / 2;
			if (ImGui::SliderFloat("##drive_bias_rear", &fDriveBiasRear, 0.f, 1.0f))
				g_local_player->m_vehicle->m_handling_data->m_drive_bias_rear = fDriveBiasRear * 2;

			ImGui::Text("HANDLING_TRANSMISSION_OUTPUT"_T.data());
			ImGui::SliderFloat("##initial drive force", &g_local_player->m_vehicle->m_handling_data->m_initial_drive_force, 0.01f, 2.f);

			ImGui::EndTabItem();
		}
	}
}