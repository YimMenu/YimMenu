#include "fiber_pool.hpp"
#include "handling_tabs.hpp"

namespace big
{
	void tab_handling::tab_search()
	{
		if (ImGui::BeginTabItem("Search"))
		{
			static char search[13];
			ImGui::InputTextWithHint("##search_share_code", "Search by share code", search, sizeof(search));
			ImGui::SameLine();
			if (ImGui::Button("Search"))
				g_fiber_pool->queue_job([&] { g_vehicle_service->get_by_share_code(search); });

			switch (g_vehicle_service->m_search_status)
			{
			case SearchStatus::SEARCHING:
				ImGui::Text("Searching...");

				break;
			case SearchStatus::NO_RESULT:
				ImGui::Text("No results found for %s", search);

				break;
			case SearchStatus::FAILED:
				ImGui::Text("Search failed, host is down or response body is invalid...");

				break;
			case SearchStatus::FOUND:
				if (auto it = g_vehicle_service->m_handling_profiles.find(search); it != g_vehicle_service->m_handling_profiles.end())
				{
					auto& profile = it->second;
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
				}

				break;
			}

			ImGui::EndTabItem();
		}
	}
}