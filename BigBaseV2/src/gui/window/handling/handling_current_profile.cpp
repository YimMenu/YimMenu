#include "handling_tabs.hpp"

namespace big
{
	void tab_handling::tab_current_profile()
	{
		if (ImGui::BeginTabItem("Current Profile"))
		{
			if (ImGui::Button("Save Profile"))
			{
				ImGui::OpenPopup("Save Handling");
			}

			modal_handling::modal_save_handling();
			ImGui::SameLine();
			if (ImGui::Button("Restore Handling"))
			{
				g_vehicle_service->restore_vehicle();
			}

			ImGui::Separator();

			ImGui::BeginTabBar("handling_tabbar");
			tab_current_profile::tab_general();
			tab_current_profile::tab_other();
			tab_current_profile::tab_brakes();
			tab_current_profile::tab_gearing();
			tab_current_profile::tab_traction();
			tab_current_profile::tab_steering();
			tab_current_profile::tab_suspension();
			tab_current_profile::tab_rollbars();
			tab_current_profile::tab_roll_centre_height();
			ImGui::EndTabBar();

			ImGui::EndTabItem();
		}
	}
}