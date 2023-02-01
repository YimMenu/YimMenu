#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_roll_centre_height()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_ROLL_CENTRE_HEIGHT"_T.data()))
		{
			ImGui::Text("HANDLING_ROLL_CENTRE_HEIGHT_DESCRIPTION"_T.data());

			ImGui::Separator();

			ImGui::Text("HANDLING_ROLL_CENTRE_HEIGHT_FRONT"_T.data());
			ImGui::SliderFloat("##roll centre height front", &g_local_player->m_vehicle->m_handling_data->m_roll_centre_height_front, -1.f, 1.f);

			ImGui::Text("HANDLING_ROLL_CENTRE_HEIGHT_BACK"_T.data());
			ImGui::SliderFloat("##roll centre height back", &g_local_player->m_vehicle->m_handling_data->m_roll_centre_height_rear, -1.f, 1.f);

			ImGui::EndTabItem();
		}
	}
};