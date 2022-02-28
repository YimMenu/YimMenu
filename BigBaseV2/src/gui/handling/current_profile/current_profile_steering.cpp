#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_steering()
	{
		if (ImGui::BeginTabItem("Steering"))
		{
			ImGui::Text("Steering Lock (degrees)");
			ImGui::SliderAngle("##steering lock", &g_local_player->m_vehicle->m_handling->m_steering_lock, -90.f, 90.f);

			ImGui::EndTabItem();
		}
	}
}