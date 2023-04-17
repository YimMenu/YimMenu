#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_general()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_GENERAL"_T.data()))
		{
			ImGui::Text("HANDLING_GRAVITY"_T.data());
			ImGui::SliderFloat("##Gravity", &g_local_player->m_vehicle->m_gravity, -50.f, 50.f);

			ImGui::Text("HANDLING_MASS"_T.data());
			ImGui::SliderFloat("##Mass", &g_local_player->m_vehicle->m_handling_data->m_mass, 0.f, 50000.f);

			ImGui::Text("HANDLING_CENTRE_OF_MASS"_T.data());
			float fCenterOfMass[3]{g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.x,
			    g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.y,
			    g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.z};
			if (ImGui::SliderFloat3("##centre_of_mass", fCenterOfMass, -10.f, 10.f))
			{
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.x = fCenterOfMass[0];
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.y = fCenterOfMass[1];
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.z = fCenterOfMass[2];
			}

			ImGui::Text("HANDLING_BUOYANCY"_T.data());
			ImGui::SliderFloat("##buoyancy", &g_local_player->m_vehicle->m_handling_data->m_buoyancy, .01f, 99.f);

			ImGui::EndTabItem();
		}
	}
}