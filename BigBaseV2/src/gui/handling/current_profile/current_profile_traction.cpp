#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_traction()
	{
		if (ImGui::BeginTabItem("Traction"))
		{
			ImGui::Text("Minimum Traction");
			ImGui::SliderFloat("##traction curve min", &g_local_player->m_vehicle->m_handling->m_traction_curve_min, 0.f, 7.f);

			ImGui::Text("Peak Traction before grip is lost");
			ImGui::SliderFloat("##traction curve max", &g_local_player->m_vehicle->m_handling->m_traction_curve_max, 0.f, 7.f);

			ImGui::Text("Traction Curve (point of grip loss)");
			ImGui::SliderAngle("##traction curve lateral", &g_local_player->m_vehicle->m_handling->m_traction_curve_lateral);

			ImGui::Text("Traction Height Loss (distance ground and tires)");
			ImGui::SliderFloat("##traction spring delta max", &g_local_player->m_vehicle->m_handling->m_traction_spring_delta_max, 0.f, 2.f);

			ImGui::Text("Burnout Multiplier");
			ImGui::SliderFloat("##low speed traction loss mult", &g_local_player->m_vehicle->m_handling->m_low_speed_traction_loss_mult, 0.f, 10.f);

			//ImGui::Text("Camber Stiffness (grip when drifting)");
			//ImGui::SliderFloat("##camber stiffness", &g_local_player->m_vehicle->m_handling->m_camber_stiffness, -1.f, 1.f);

			ImGui::Text("Traction Bias (1.0 = front, 0.0 = rear, 0.5 = balanced)");
			float fTractionBiasFront = g_local_player->m_vehicle->m_handling->m_traction_bias_front / 2;
			if (ImGui::SliderFloat("##traction bias front", &fTractionBiasFront, 0.01f, .99f))
				g_local_player->m_vehicle->m_handling->m_traction_bias_front = fTractionBiasFront * 2;

			ImGui::Text("Off-Road Traction Loss (1.0 = normal, lower = better)");
			ImGui::SliderFloat("##traction loss mult", &g_local_player->m_vehicle->m_handling->m_traction_loss_mult, 0.f, 5.f);

			ImGui::EndTabItem();
		}
	}
}