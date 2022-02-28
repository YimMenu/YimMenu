#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_roll_centre_height()
	{
		if (ImGui::BeginTabItem("Roll Centre Height"))
		{
			ImGui::Text("The point in the transverse vertical plane through any pair of wheel centres\nat which lateral forces apply to the sprung mass without producing suspension roll.");

			ImGui::Separator();

			ImGui::Text("Roll Centre Height Front");
			ImGui::SliderFloat("##roll centre height front", &g_local_player->m_vehicle->m_handling->m_roll_centre_height_front, -1.f, 1.f);

			ImGui::Text("Roll Centre Height Back");
			ImGui::SliderFloat("##roll centre height back", &g_local_player->m_vehicle->m_handling->m_roll_centre_height_rear, -1.f, 1.f);

			ImGui::EndTabItem();
		}
	}
};