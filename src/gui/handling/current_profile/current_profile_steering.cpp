#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_steering()
	{
		if (ImGui::BeginTabItem("HANDLING_TAB_STEERING"_T.data()))
		{
			ImGui::Text("HANDLING_STEERING_LOCK_DEGREES"_T.data());
			ImGui::SliderAngle("##steering lock", &g_local_player->m_vehicle->m_handling_data->m_steering_lock, -90.f, 90.f);

			ImGui::EndTabItem();
		}
	}
}