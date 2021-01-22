#include "gui/tab_bar.hpp"

namespace big
{
	void tabbar::handling_traction()
	{
		if (ImGui::BeginTabItem("Traction"))
		{
			ImGui::Text("Acceleration/Braking Grip");
			ImGui::SliderFloat("##traction curve min", &g_vehicle->m_handling->m_traction_curve_min, 0.f, 7.f);

			ImGui::Text("Cornering Grip");
			ImGui::SliderFloat("##traction curve max", &g_vehicle->m_handling->m_traction_curve_max, 0.f, 7.f);

			ImGui::Text("Traction Spring Delta Max (distance from ground => grip)");
			ImGui::SliderFloat("##traction spring delta max", &g_vehicle->m_handling->m_traction_spring_delta_max, 0.f, 2.f);

			ImGui::Text("Burnout Multiplier");
			ImGui::SliderFloat("##low speed traction loss mult", &g_vehicle->m_handling->m_low_speed_traction_loss_mult, 0.f, 2.f);

			ImGui::Text("Camber Stiffness (grip when drifting)");
			ImGui::SliderFloat("##camber stiffness", &g_vehicle->m_handling->m_camber_stiffness, -1.f, 1.f);

			ImGui::Text("Traction Bias (1.0 = front, 0.0 = rear, 0.5 = balanced)");
			float fTractionBiasFront = g_vehicle->m_handling->m_traction_bias_front / 2;
			if (ImGui::SliderFloat("##traction bias front", &fTractionBiasFront, 0.01f, .99f))
				g_vehicle->m_handling->m_traction_bias_front = fTractionBiasFront * 2;

			ImGui::Text("Off-Road Traction Loss (1.0 = normal, lower = better)");
			ImGui::SliderFloat("##traction loss mult", &g_vehicle->m_handling->m_traction_loss_mult, 0.f, 5.f);

			ImGui::EndTabItem();
		}
	}
}