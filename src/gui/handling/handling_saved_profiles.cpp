#include "services/vehicle/handling_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::handling_saved_profiles()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
		{
			ImGui::Text("HANDLING_ENTER_VEHICLE"_T.data());
			return;
		}
		g_handling_service->backup_vehicle();

		if (components::button("HANDLING_RELOAD_PROFILES"_T))
		{
			g_handling_service->load_files();
		}

		if (ImGui::ListBoxHeader("##handling_profiles"))
		{
			for (auto& [name, profile] : g_handling_service->profiles())
			{
				if (components::selectable(name, &profile == g_handling_service->active_profile()))
				{
					g_handling_service->apply_profile(&profile);
				}
			}
			ImGui::EndListBox();
		}
	}
}
