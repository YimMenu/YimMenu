#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_brakes()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_BRAKES"_T.data()))
		{
			ImGui::Text("HANDLING_BRAKE_FORCE"_T.data());
			ImGui::SliderFloat("##brake force", &g_local_player->m_vehicle->m_handling_data->m_brake_force, .01f, 10.f);

			ImGui::Text("HANDLING_BRAKE_BIAS"_T.data());
			float fBrakeBias = g_local_player->m_vehicle->m_handling_data->m_brake_bias_front / 2;
			if (ImGui::SliderFloat("##brake bias front", &fBrakeBias, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling_data->m_brake_bias_front = fBrakeBias * 2;

			ImGui::Text("HANDLING_HAND_BRAKE_FORCE"_T.data());
			ImGui::SliderFloat("##hand brake force", &g_local_player->m_vehicle->m_handling_data->m_handbrake_force, .01f, 10.f);

			ImGui::EndTabItem();
		}
	}
}