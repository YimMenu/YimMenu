#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_other()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_OTHER"_T.data()))
		{
			ImGui::Text("HANDLING_ACCELERATION_MULTIPLIER"_T.data());
			ImGui::SliderFloat("###handling_acceleration", &g_local_player->m_vehicle->m_handling_data->m_acceleration, .01f, 10.f);

			ImGui::Text("HANDLING_DOWNFORCE_MULTIPLIER"_T.data());
			ImGui::SliderFloat("###handling_downforce", &g_local_player->m_vehicle->m_handling_data->m_downforce_multiplier, .01f, 10.f);

			ImGui::Text("HANDLING_INERTIA_MULTIPLIER"_T.data());
			float fInertiaMult[3];
			fInertiaMult[0] = g_local_player->m_vehicle->m_handling_data->m_inertia_mult.x;
			fInertiaMult[1] = g_local_player->m_vehicle->m_handling_data->m_inertia_mult.y;
			fInertiaMult[2] = g_local_player->m_vehicle->m_handling_data->m_inertia_mult.z;
			if (ImGui::SliderFloat3("##inertia_multiplier", fInertiaMult, -10.f, 10.f))
			{
				g_local_player->m_vehicle->m_handling_data->m_inertia_mult.x = fInertiaMult[0];
				g_local_player->m_vehicle->m_handling_data->m_inertia_mult.y = fInertiaMult[1];
				g_local_player->m_vehicle->m_handling_data->m_inertia_mult.z = fInertiaMult[2];
			}

			ImGui::EndTabItem();
		}
	}
};
