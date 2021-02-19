#include "gui/tab_bar.hpp"

namespace big
{
	void tabbar::handling_suspension()
	{
		if (ImGui::BeginTabItem("Suspension"))
		{
			ImGui::Text("Suspension Strength");
			ImGui::SliderFloat("##suspension force", &g_vehicle->m_handling->m_suspension_force, 0.f, 5.f);

			ImGui::Text("Suspension Compression (higher = stiffer)");
			ImGui::SliderFloat("##suspension comp", &g_vehicle->m_handling->m_suspension_comp_damp, 0.f, 5.f);

			ImGui::Text("Suspension Rebound (higher = stiffer)");
			ImGui::SliderFloat("##suspension rebound", &g_vehicle->m_handling->m_suspension_rebound_damp, 0.f, 5.f);

			ImGui::Text("Suspension Upper Limit");
			ImGui::SliderFloat("##suspension upper", &g_vehicle->m_handling->m_suspension_upper_limit, -1.f, 1.f);

			ImGui::Text("Suspension Lower Limit");
			ImGui::SliderFloat("##suspension lower", &g_vehicle->m_handling->m_suspension_lower_limit, -1.f, 1.f);

			ImGui::Text("Suspension Raise");
			ImGui::SliderFloat("##suspension raise", &g_vehicle->m_handling->m_suspension_raise, -1.f, 1.f);

			ImGui::Text("Suspension Bias (0.0 = front stiffer, 1.0 = rear stiffer");
			float fSuspensionBiasFront = g_vehicle->m_handling->m_suspension_bias_front / 2;
			if (ImGui::SliderFloat("##suspension bias", &fSuspensionBiasFront, 0.f, 1.f))
				g_vehicle->m_handling->m_suspension_bias_front = fSuspensionBiasFront * 2;

			ImGui::Text("Anti Rollbar Force (large = less body roll)");
			ImGui::SliderFloat("##anti rollbar force", &g_vehicle->m_handling->m_anti_rollbar_force, 0.f, 10.f);

			ImGui::Text("Anti Rollbar Bias (0 = front, 1 = rear)");
			float fAntiRollBarBiasFront = g_vehicle->m_handling->m_anti_rollbar_bias_front / 2;
			if (ImGui::SliderFloat("##anti rollbar bias", &fAntiRollBarBiasFront, 0.f, 1.f))
				g_vehicle->m_handling->m_anti_rollbar_bias_front = fAntiRollBarBiasFront * 2;

			ImGui::Text("Roll Centre Height Front");
			ImGui::SliderFloat("##roll centre height front", &g_vehicle->m_handling->m_roll_centre_height_front, -1.f, 1.f);

			ImGui::Text("Roll Centre Height Back");
			ImGui::SliderFloat("##roll centre height back", &g_vehicle->m_handling->m_roll_centre_height_rear, -1.f, 1.f);

			ImGui::EndTabItem();
		}
	}
}