#include "handling_tabs.hpp"

namespace big
{
	void tab_handling::tab_braking()
	{
		if (ImGui::BeginTabItem("Braking"))
		{
			ImGui::Text("Brake Force");
			ImGui::SliderFloat("##brake force", &g_local_player->m_vehicle->m_handling->m_brake_force, -50.f, 50.f);

			ImGui::Text("Brake Bias (1.0 = front, 0.0 = rear, 0.5 = balanced)");
			float fBrakeBias = g_local_player->m_vehicle->m_handling->m_brake_bias_front / 2;
			if (ImGui::SliderFloat("##brake bias front", &fBrakeBias, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling->m_brake_bias_front = fBrakeBias * 2;

			ImGui::Text("Hand Brake Force");
			ImGui::SliderFloat("##hand brake force", &g_local_player->m_vehicle->m_handling->m_handbrake_force, -50.f, 50.f);

			ImGui::EndTabItem();
		}
	}
}