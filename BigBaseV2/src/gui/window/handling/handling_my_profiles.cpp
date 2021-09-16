#include "handling_tabs.hpp"

namespace big
{
	void tab_handling::tab_my_profiles()
	{
		if (ImGui::BeginTabItem("My Profiles"))
		{
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

						ImGui::BeginGroup();

						ImGui::Text("Name:");
						ImGui::Text("Description:");

						ImGui::EndGroup();
						ImGui::SameLine();
						ImGui::BeginGroup();

						ImGui::Text(profile.name.c_str());
						ImGui::TextWrapped(profile.description.c_str());

						ImGui::EndGroup();
						ImGui::SameLine();
						ImGui::BeginGroup();

						ImGui::Text("Share Code: %s", profile.share_code.c_str());
						if (ImGui::Button("Load Profile"))
							g_vehicle_service->set_handling_profile(profile);

						ImGui::EndGroup();

						ImGui::Separator();
					}
				}
			}

			ImGui::EndTabItem();
		}
	}
}