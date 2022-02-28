#include "handling_tabs.hpp"

namespace big
{
	void tab_handling::tab_current_profile()
	{
		if (ImGui::BeginTabItem("Current Profile"))
		{
			if (g_vehicle_service->get_active_profile(g_local_player->m_vehicle->m_handling->m_model_hash).empty())
			{
				if (ImGui::Button("Save Profile"))
				{
					ImGui::OpenPopup("Save Handling");
				}
			}
			else
			{
				if (ImGui::Button("Update Profile"))
				{
					ImGui::OpenPopup("Update Handling");
				}
			}

			modal_handling::modal_save_handling();
			modal_handling::modal_update_handling();
			ImGui::SameLine();
			if (ImGui::Button("Restore Handling"))
				g_vehicle_service->restore_vehicle();

			ImGui::Separator();

			ImGui::BeginTabBar("handling_tabbar");
			tab_current_profile::tab_general();
			tab_current_profile::tab_other();
			tab_current_profile::tab_brakes();
			tab_current_profile::tab_gearing();
			tab_current_profile::tab_traction();
			tab_current_profile::tab_transmission();
			tab_current_profile::tab_steering();
			tab_current_profile::tab_suspension();
			tab_current_profile::tab_rollbars();
			tab_current_profile::tab_roll_centre_height();
			ImGui::EndTabBar();

			ImGui::EndTabItem();
		}
	}
}