#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_rollbars()
	{
		if (ImGui::BeginTabItem("Rollbars"))
		{
			ImGui::Text("Anti-Roll Bar force");
			ImGui::SliderFloat("##anti rollbar force", &g_local_player->m_vehicle->m_handling->m_anti_rollbar_force, 0.f, 10.f);

			ImGui::Text("Anti-Roll Bar Bias front (0 = front, 1 = rear)");
			float fAntiRollBarBiasFront = g_local_player->m_vehicle->m_handling->m_anti_rollbar_bias_front / 2;
			if (ImGui::SliderFloat("##anti rollbar bias", &fAntiRollBarBiasFront, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling->m_anti_rollbar_bias_front = fAntiRollBarBiasFront * 2;

			ImGui::EndTabItem();
		}
	}
};