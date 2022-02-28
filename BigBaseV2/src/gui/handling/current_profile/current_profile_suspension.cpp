#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_suspension()
	{
		if (ImGui::BeginTabItem("Suspension"))
		{
			ImGui::Text("Suspension Force (General Suspension Strength)");
			ImGui::SliderFloat("##suspension force", &g_local_player->m_vehicle->m_handling->m_suspension_force, 0.f, 5.f);

			ImGui::Text("Suspension Compression Damp (Higher = Less Compression)");
			ImGui::SliderFloat("##suspension comp", &g_local_player->m_vehicle->m_handling->m_suspension_comp_damp, 0.f, 5.f);

			ImGui::Text("Suspension Rebound Damp (Higher = Less Decompression)");
			ImGui::SliderFloat("##suspension rebound", &g_local_player->m_vehicle->m_handling->m_suspension_rebound_damp, 0.f, 5.f);

			ImGui::Text("Suspension Upper Limit (mostly visual)");
			ImGui::SliderFloat("##suspension upper", &g_local_player->m_vehicle->m_handling->m_suspension_upper_limit, -1.f, 1.f);

			ImGui::Text("Suspension Lower Limit (mostly visual)");
			ImGui::SliderFloat("##suspension lower", &g_local_player->m_vehicle->m_handling->m_suspension_lower_limit, -1.f, 1.f);

			ImGui::Text("Suspension Raise (Ride Height)");
			ImGui::SliderFloat("##suspension raise", &g_local_player->m_vehicle->m_handling->m_suspension_raise, -1.f, 1.f);

			ImGui::Text("Suspension Bias Front (Strength Bias, 1 = front, 0 = rear)");
			float fSuspensionBiasFront = g_local_player->m_vehicle->m_handling->m_suspension_bias_front / 2;
			if (ImGui::SliderFloat("##suspension bias", &fSuspensionBiasFront, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling->m_suspension_bias_front = fSuspensionBiasFront * 2;

			ImGui::EndTabItem();
		}
	}
}