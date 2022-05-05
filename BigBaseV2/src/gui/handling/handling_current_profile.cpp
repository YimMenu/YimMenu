#include "current_profile/current_profile_tabs.hpp"
#include "services/vehicle_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::handling_current_profile()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
		{
			ImGui::Text("Please enter a vehicle.");
			return;
		}

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
		
	}
}