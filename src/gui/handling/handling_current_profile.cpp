#include "current_profile/current_profile_tabs.hpp"
#include "services/vehicle/handling_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::handling_current_profile()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
		{
			ImGui::Text("HANDLING_ENTER_VEHICLE"_T.data());
			return;
		}
		g_handling_service->backup_vehicle();

		if (components::button("HANDLING_SAVE_PROFILE"_T))
		{
			ImGui::OpenPopup("HANDLING_SAVE_HANDLING"_T.data());
		}

		modal_handling::modal_save_handling();
		ImGui::SameLine();
		if (components::button("HANDLING_RESTORE_HANDLING"_T))
			g_handling_service->restore_vehicle();

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