#include "api/api.hpp"
#include "fiber_pool.hpp"
#include "handling_tabs.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "thread_pool.hpp"

namespace big
{
	void tab_handling::tab_search()
	{
		if (ImGui::BeginTabItem("Search"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			}QUEUE_JOB_END_CLAUSE

			static char search[13];
			ImGui::InputTextWithHint("##search_share_code", "Search by share code", search, sizeof(search));
			ImGui::SameLine();
			if (ImGui::Button("Search"))
				g_thread_pool->push([&] { g_vehicle_service->get_by_share_code(search); });

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
					ImGui::SameLine();
					if (ImGui::Button("Save Profile"))
					{
						g_thread_pool->push([&]
						{
							api::vehicle::handling::save_profile(profile.share_code);

							g_vehicle_service->load_saved_profiles(true);
						});
					}

					ImGui::EndTable();
				}

				break;
			}

			ImGui::EndTabItem();
		}
	}
}