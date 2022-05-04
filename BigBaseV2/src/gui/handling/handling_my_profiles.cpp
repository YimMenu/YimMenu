#include "services/vehicle_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::handling_my_profiles()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
		{
			ImGui::Text("Please enter a vehicle.");
			return;
		}

		if (!g_vehicle_service->update_mine())
			ImGui::Text("Loading profiles...");
		else
		{
			if (g_vehicle_service->m_my_profiles.size() == 0)
				ImGui::Text("You have no profiles available for this vehicle.");
			for (auto& key : g_vehicle_service->m_my_profiles)
			{
				if (auto it = g_vehicle_service->m_handling_profiles.find(key); it != g_vehicle_service->m_handling_profiles.end())
				{
					auto& profile = it->second;

					if (profile.share_code == g_vehicle_service->get_active_profile(profile.handling_hash))
						ImGui::TextColored({ 0.1254f,0.8039f,0.3137f,1.f }, "Active");

					ImGui::BeginTable("table", 3, ImGuiTableFlags_SizingStretchProp);

					ImGui::TableNextRow();

					ImGui::TableNextColumn();
					ImGui::Text("Name:");
					ImGui::TableNextColumn();
					ImGui::Text(profile.name.c_str());
					ImGui::TableNextColumn();
					ImGui::Text("Share Code: %s", profile.share_code.c_str());

					ImGui::TableNextRow();

					ImGui::TableNextColumn();
					ImGui::Text("Description:");
					ImGui::TableNextColumn();
					ImGui::TextWrapped(profile.description.c_str());
					ImGui::TableNextColumn();
					if (ImGui::Button("Load Profile"))
						g_vehicle_service->set_handling_profile(profile);

					ImGui::EndTable();

					ImGui::Separator();
				}
			}
		}
			
	}
}
