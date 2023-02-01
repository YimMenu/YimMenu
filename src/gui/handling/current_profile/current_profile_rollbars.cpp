#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_rollbars()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_ROLLBARS"_T.data()))
		{
			ImGui::Text("HANDLING_ANTI_ROLL_BAR_FORCE"_T.data());
			ImGui::SliderFloat("##anti rollbar force", &g_local_player->m_vehicle->m_handling_data->m_anti_rollbar_force, 0.f, 10.f);

			ImGui::Text("HANDLING_ANTI_ROLL_BAR_BIAS_FRONT"_T.data());
			float fAntiRollBarBiasFront = g_local_player->m_vehicle->m_handling_data->m_anti_rollbar_bias_front / 2;
			if (ImGui::SliderFloat("##anti rollbar bias", &fAntiRollBarBiasFront, 0.f, 1.f))
				g_local_player->m_vehicle->m_handling_data->m_anti_rollbar_bias_front = fAntiRollBarBiasFront * 2;

			ImGui::EndTabItem();
		}
	}
};