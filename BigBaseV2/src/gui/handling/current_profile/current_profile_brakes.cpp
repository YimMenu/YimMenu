#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_brakes()
	{
		if (ImGui::BeginTabItem("Brakes"))
		{
			ImGui::Text("Brake Force");
			ImGui::DragFloat("##brake force", &g_local_player->m_vehicle->m_handling->m_brake_force, .01f, 0.f, 10.f);

			ImGui::Text("Brake Bias (1.0 = front, 0.0 = rear, 0.5 = balanced)");
			float fBrakeBias = g_local_player->m_vehicle->m_handling->m_brake_bias_front / 2;
			if (ImGui::SliderFloat("##brake bias front", &fBrakeBias, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling->m_brake_bias_front = fBrakeBias * 2;

			ImGui::Text("Hand Brake Force");
			ImGui::DragFloat("##hand brake force", &g_local_player->m_vehicle->m_handling->m_handbrake_force, .01f, 0.f, 10.f);

			ImGui::EndTabItem();
		}
	}
}