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
			if (g->world.property_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->world.property_list_updated = false;
				}

				update_ticks++;

				if (update_ticks > 1600)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##property_list", { 300, 400 }))
			{
				for (auto& it : g->world.property_list)
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
			static bool bring = false;

			if (g->world.mission_veh_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->world.mission_veh_list_updated = false;
				}

				update_ticks++;

				if (update_ticks > 800)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##mission_vehicles", { 300, 400 }))
			{
				for (auto& it : g->world.mission_veh_list)
				{
					const auto& veh = it.first;
					const auto& model = it.second;

					auto item = g_gta_data_service->find_vehicle_by_hash(model);

					if (item.hash)
					{
						ImGui::PushID(veh);
						components::selectable(item.display_name, false, [veh] {
							if (bring)
							{
								vehicle::bring(veh, self::pos);
							}
							else
							{
								teleport::to_entity(veh);
							}
							
							if (teleport_into)
							{
								vehicle::put_in(self::ped, veh);
							}
						});
						ImGui::PopID();
					}
				}

				ImGui::ListBoxFooter();
			}

			ImGui::Checkbox("Bring Vehicle", &bring);
			ImGui::Checkbox("Teleport into Vehicle", &teleport_into);

			ImGui::EndTabItem();
		}
	}

	void mission_ped_list_tab()
	{
		if (ImGui::BeginTabItem("Mission Peds"))
		{
			static int update_ticks = 0;

			if (g->world.mission_ped_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->world.mission_ped_list_updated = false;
				}

				update_ticks++;

				if (update_ticks > 800)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##mission_peds", { 300, 400 }))
			{
				for (auto& it : g->world.mission_ped_list)
				{
					const auto& ped = it.first;
					const auto& model = it.second;

					auto item = g_gta_data_service->find_ped_by_hash(model);

					if (item.hash)
					{
						ImGui::PushID(ped);
						components::selectable(item.name, false, [ped] {
							teleport::to_entity(ped);
						});
						ImGui::PopID();
					}
				}

				ImGui::ListBoxFooter();
			}

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
		mission_ped_list_tab();
		ImGui::EndTabBar();
	}
}
