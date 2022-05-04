#include "api/api.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "services/vehicle_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::handling_search()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT)
		{
			ImGui::Text("Please enter a vehicle.");
			return;
		}

		static char search[13];
		components::input_text_with_hint("##search_share_code", "Search by share code", search, sizeof(search), ImGuiInputTextFlags_EnterReturnsTrue, []
		{
			g_thread_pool->push([&] { g_vehicle_service->get_by_share_code(search); });
		});
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
	}
}
