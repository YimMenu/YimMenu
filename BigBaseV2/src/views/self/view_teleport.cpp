#include "fiber_pool.hpp"
#include "views/view.hpp"
#include "util/globals.hpp"
#include "util/mobile.hpp"
#include "util/ped.hpp"
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

				if (update_ticks > 1200)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##property_list", { 350, 400 }))
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
			static bool bring = false;
			static bool teleport_into = false;
			static bool take_driver_seat = false;

			if (g->world.mission_veh_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->world.mission_veh_list_updated = false;
				}

				update_ticks++;

				if (update_ticks > 600)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##mission_vehicles", { 350, 400 }))
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
								vehicle::put_in(self::ped, veh, false, take_driver_seat ? -1 : 0);
							}
						});
						ImGui::PopID();
					}
				}

				ImGui::ListBoxFooter();
			}

			ImGui::Checkbox("Bring Vehicle", &bring);
			ImGui::Checkbox("Teleport into Vehicle", &teleport_into);
			if (teleport_into)
			{
				ImGui::Checkbox("Take driver seat", &take_driver_seat);
			}

			ImGui::EndTabItem();
		}
	}

	void mission_ped_list_tab()
	{
		if (ImGui::BeginTabItem("Mission Peds"))
		{
			static int update_ticks = 0;
			static bool kill = false;
			static bool bring = false;

			if (g->world.mission_ped_list_updated == true)
			{
				if (update_ticks == 0)
				{
					g->world.mission_ped_list_updated = false;
				}

				update_ticks++;

				if (update_ticks > 600)
				{
					update_ticks = 0;
				}
			}

			if (ImGui::ListBoxHeader("##mission_peds", { 350, 400 }))
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
							if (bring)
							{
								ped::bring(ped);
							}
							else
							{
								teleport::to_entity(ped);
							}

							if (kill)
							{
								script::get_current()->yield(100ms);
								const Vector3 destination = PED::GET_PED_BONE_COORDS(ped, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
								Vector3 origin = PED::GET_PED_BONE_COORDS(ped, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 1.0f);
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 10000, true, RAGE_JOAAT("WEAPON_SNIPERRIFLE"), self::ped, false, false, 10000);
							}
						});
						ImGui::PopID();
					}
				}

				ImGui::ListBoxFooter();
			}

			ImGui::Checkbox("Bring Ped", &bring);
			ImGui::Checkbox("Kill Ped", &kill);
			if (ImGui::Button("Kill Attackers"))
			{
				for (auto& it : g->world.mission_ped_list)
				{
					const auto& ped = it.first;
					const auto& model = it.second;

					g_fiber_pool->queue_job([ped] {

						bool is_in_combat = PED::IS_PED_IN_COMBAT(ped, self::ped);

						if (is_in_combat || PED::GET_RELATIONSHIP_BETWEEN_PEDS(self::ped, ped) > 4)
						{
							if (bring)
							{
								ped::bring(ped);
								script::get_current()->yield(100ms);
							}

							const Vector3 destination = PED::GET_PED_BONE_COORDS(ped, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
							Vector3 origin = PED::GET_PED_BONE_COORDS(ped, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 1.0f);
							MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 10000, true, RAGE_JOAAT("WEAPON_SNIPERRIFLE"), self::ped, false, false, 10000);
						}
					});
				}
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
