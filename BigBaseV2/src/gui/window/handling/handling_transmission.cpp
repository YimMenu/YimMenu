#include "handling_tabs.hpp"

namespace big
{
	void tab_handling::tab_transmission()
	{
		if (ImGui::BeginTabItem("Transmission"))
		{
			ImGui::Text("Drive Bias (1.0 = front, 0.0 = rear, 0.5 = balanced 4WD)");
			float fDriveBiasFront = g_local_player->m_vehicle->m_handling->m_drive_bias_front / 2;
			if (ImGui::SliderFloat("##drive_bias_front", &fDriveBiasFront, 0.f, 1.0f))
				g_local_player->m_vehicle->m_handling->m_drive_bias_front = fDriveBiasFront * 2;

			ImGui::Text("Drive Bias (1.0 = rear, 0.0 = front, 0.5 = balanced 4WD)");
			float fDriveBiasRear = g_local_player->m_vehicle->m_handling->m_drive_bias_rear / 2;
			if (ImGui::SliderFloat("##drive_bias_rear", &fDriveBiasRear, 0.f, 1.0f))
				g_local_player->m_vehicle->m_handling->m_drive_bias_rear = fDriveBiasRear * 2;

			ImGui::Text("Gears");
			int nInitialDriveGears = g_local_player->m_vehicle->m_handling->m_initial_drive_gears;
			if (ImGui::SliderInt("##initial_gears", &nInitialDriveGears, 1, 12))
				g_local_player->m_vehicle->m_handling->m_initial_drive_gears = nInitialDriveGears;

			ImGui::Text("Upshift Rate");
			ImGui::SliderFloat("##upshift", &g_local_player->m_vehicle->m_handling->m_upshift, 0.f, 10.f);

			ImGui::Text("Downshift Rate");
			ImGui::SliderFloat("##downshift", &g_local_player->m_vehicle->m_handling->m_downshift, 0.f, 10.f);

			ImGui::Text("Transmission Output (force)");
			ImGui::SliderFloat("##initial drive force", &g_local_player->m_vehicle->m_handling->m_initial_drive_force, 0.01f, 2.f);

			ImGui::EndTabItem();
		}
	}
}