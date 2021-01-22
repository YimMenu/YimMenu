#include "gui/tab_bar.hpp"
#include "features/functions.hpp"

namespace big
{
	void tabbar::handling_transmission()
	{
		if (ImGui::BeginTabItem("Transmission"))
		{
			ImGui::Text("Acceleration Multiplier");
			ImGui::SliderFloat("##acceleration", &g_vehicle->m_handling->m_acceleration, 0.f, 50.f);

			ImGui::Text("Drive Bias (1.0 = front, 0.0 = rear, 0.5 = balanced 4WD)");
			float fDriveBiasFront = g_vehicle->m_handling->m_drive_bias_front / 2;
			if (ImGui::SliderFloat("##drive_bias_front", &fDriveBiasFront, 0.f, 1.0f))
				g_vehicle->m_handling->m_drive_bias_front = fDriveBiasFront * 2;

			ImGui::Text("Steering Lock (degrees)");
			ImGui::SliderAngle("##steering lock", &g_vehicle->m_handling->m_steering_lock, 0.f, 90.f);

			ImGui::Text("Gears");
			int nInitialDriveGears = g_vehicle->m_handling->m_initial_drive_gears;
			if (ImGui::SliderInt("##initial_gears", &nInitialDriveGears, 1, 12))
				g_vehicle->m_handling->m_initial_drive_gears = nInitialDriveGears;

			ImGui::Text("Upshift Rate");
			ImGui::SliderFloat("##upshift", &g_vehicle->m_handling->m_upshift, 0.f, 10.f);

			ImGui::Text("Downshift Rate");
			ImGui::SliderFloat("##downshift", &g_vehicle->m_handling->m_downshift, 0.f, 10.f);

			ImGui::Text("Transmission Output (force)");
			ImGui::SliderFloat("##initial drive force", &g_vehicle->m_handling->m_initial_drive_force, 0.01f, 2.f);

			ImGui::Text("Max Velocity (broken)");
			//ImGui::SliderFloat("##initial drive max flat vel", );

			ImGui::EndTabItem();
		}
	}
}