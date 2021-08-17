#include "fiber_pool.hpp"
#include "gui/window.hpp"
#include "handling/handling_tabs.hpp"
#include "imgui.h"

namespace big
{
	void window::handling()
	{
		ImGui::SetNextWindowSize({ 500, 250 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_FirstUseEver);
		if (g.window.handling && ImGui::Begin("Handling", &g.window.handling))
		{
			if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_in_vehicle == 0x10)
			{
				ImGui::Text("Please enter a vehicle.");

				return;
			}
			g_vehicle_service->attempt_save();

			ImGui::BeginTabBar("handling_profiles");
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
				tab_handling::tab_general();
				tab_handling::tab_other();
				tab_handling::tab_brakes();
				tab_handling::tab_gearing();
				tab_handling::tab_traction();
				tab_handling::tab_steering();
				tab_handling::tab_suspension();
				tab_handling::tab_rollbars();
				tab_handling::tab_roll_centre_height();
				ImGui::EndTabBar();

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("My Profiles"))
			{
				if (!g_vehicle_service->update_mine())
					ImGui::Text("Loading profiles...");
				else
				{
					if (g_vehicle_service->m_my_profiles.size() == 0)
						ImGui::Text("You have no profiles available for this vehicle.");
					for (auto &key : g_vehicle_service->m_my_profiles)
					{
						if (auto it = g_vehicle_service->m_handling_profiles.find(key); it != g_vehicle_service->m_handling_profiles.end())
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
							{
								*g_local_player->m_vehicle->m_handling = profile.data;
							}

							ImGui::EndGroup();

							ImGui::Separator();
						}
					}
				}

				ImGui::EndTabItem();
			}
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
						{
							*g_local_player->m_vehicle->m_handling = profile.data;
						}

						ImGui::EndGroup();
					}
					
					break;
				}

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();

			ImGui::End();
		}
	}
}