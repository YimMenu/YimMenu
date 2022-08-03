#include "views/view.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	void property_list_tab()
	{
		if (ImGui::BeginTabItem("Properties"))
		{
			static int update_ticks = 0;
			if (g->teleport.property_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->teleport.property_list_updated = false;
					LOG(WARNING) << "PU";
				}

				update_ticks++;

				if (update_ticks > 1600)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##property_list", { 300, 400 }))
			{
				for (auto& it : g->teleport.property_list)
				{
					const auto& name = it.first;
					const auto& location = it.second;

					components::selectable(name, false, [&location] {
						teleport::to_coords(location);
					});
				}

				ImGui::ListBoxFooter();
			}

			ImGui::EndTabItem();
		}
	}

	void mission_vehicle_list_tab()
	{
		if (ImGui::BeginTabItem("Mission Vehicles"))
		{
			static int update_ticks = 0;
			static bool teleport_into = false;

			if (g->teleport.mission_veh_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->teleport.mission_veh_list_updated = false;
					LOG(WARNING) << "VU";
				}

				update_ticks++;

				if (update_ticks > 800)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##mission_vehicles", { 300, 400 }))
			{
				for (auto& it : g->teleport.mission_veh_list)
				{
					const auto& veh = it.first;
					const auto& model = it.second;

					auto item = g_gta_data_service->find_vehicle_by_hash(model);

					if (item.hash)
					{
						components::selectable(item.display_name, false, [veh] {

							if (teleport_into)
							{
								teleport::into_vehicle(veh);
							}
							else
							{
								teleport::to_entity(veh);
							}
						});
					}
				}

				ImGui::ListBoxFooter();
			}

			ImGui::Checkbox("Teleport into Vehicle", &teleport_into);

			ImGui::EndTabItem();
		}
	}

	void view::teleport()
	{
		components::button("Waypoint", [] {
			teleport::to_waypoint();
		});

		ImGui::SameLine();

		components::button("Objective", [] {
			teleport::to_objective();
		});

		ImGui::Separator();

		ImGui::BeginTabBar("handling_tabbar");
		property_list_tab();
		mission_vehicle_list_tab();
		ImGui::EndTabBar();
	}
}
