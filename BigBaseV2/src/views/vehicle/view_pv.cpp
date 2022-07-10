#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/mobile/mobile_service.hpp"
#include "services/vehicle_preview/vehicle_preview_service.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::pv() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		ImGui::Checkbox("Preview", &g->clone_pv.preview_vehicle);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn In", &g->clone_pv.spawn_inside);
		ImGui::SameLine();

		static char plate[9] = { 0 };
		int num_of_rows = 2;

		ImGui::Checkbox("Spawn Clone", &g->clone_pv.spawn_clone);
		if (g->clone_pv.spawn_clone)
		{
			num_of_rows = 4;

			ImGui::Checkbox("Spawn Maxed", &g->clone_pv.spawn_maxed);

			ImGui::SameLine();
			strncpy(plate, g->clone_pv.plate.c_str(), 9);
			ImGui::Checkbox("Clone PV Plate", &g->clone_pv.clone_plate);
			if (g->clone_pv.clone_plate)
			{
				num_of_rows = 3;
			}
			else
			{
				ImGui::SetNextItemWidth(300.f);

				components::input_text_with_hint("Plate", "Plate Number", plate, sizeof(plate), ImGuiInputTextFlags_None, [] {
					g->clone_pv.plate = plate;
				});
			}
		}

		static char search[64];
		static std::string lower_search;

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Model Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None, [] {
			lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
		});

		g_mobile_service->refresh_personal_vehicles();
		if (ImGui::ListBoxHeader("##personal_veh_list", { 300, static_cast<float>(*g_pointers->m_resolution_y - 184 - 38 * num_of_rows) }))
		{

			if (g_mobile_service->personal_vehicles().empty())
			{
				ImGui::Text("No personal vehicles found, \nare you online?");
			}
			else
			{

				for (const auto& it : g_mobile_service->personal_vehicles())
				{
					const auto& label = it.first;
					const auto& personal_veh = it.second;
					auto item = g_vehicle_preview_service->find_vehicle_item_by_hash(personal_veh->get_hash());

					std::string display_name = label;
					std::string display_manufacturer = item.display_manufacturer;
					std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
					std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

					if (
						display_name.find(lower_search) != std::string::npos ||
						display_manufacturer.find(lower_search) != std::string::npos
					) {
						ImGui::PushID(personal_veh->get_id());
						if (ImGui::Selectable(label.c_str(), false)) {

							if (g->clone_pv.spawn_clone)
							{
								g_fiber_pool->queue_job([&personal_veh] {
									auto vehicle_idx = personal_veh->get_vehicle_idx();
									auto veh_data = vehicle::get_vehicle_data_from_vehicle_idx(vehicle_idx);

									float y_offset = 0;

									if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, false))
									{
										y_offset = 10.f;
									}
									else if (!g->spawn.spawn_inside)
									{
										y_offset = 5.f;
									}

									auto spawn_location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, y_offset, 0.f);
									float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

									const char* spawn_plate = plate;
									if (g->clone_pv.clone_plate)
									{
										spawn_plate = personal_veh->get_plate();
									}

									auto veh = vehicle::clone(veh_data, spawn_location, spawn_heading);

									if (g->clone_pv.spawn_inside)
									{
										vehicle::telport_into_veh(veh);
									}

									if (g->clone_pv.spawn_maxed)
									{
										vehicle::max_vehicle(veh);
									}

									vehicle::set_plate(veh, spawn_plate);
								});
							}
							else
							{
								strcpy(search, "");
								lower_search = search;

								g_fiber_pool->queue_job([&personal_veh] {
									personal_veh->summon();
								});
							}
						}
						ImGui::PopID();

						if (g->clone_pv.preview_vehicle && ImGui::IsItemHovered())
						{
							g_vehicle_preview_service->set_preview_vehicle(item);
						}
						else if (g->clone_pv.preview_vehicle && !ImGui::IsAnyItemHovered())
						{
							g_vehicle_preview_service->stop_preview();
						}
					}
				}
			}

			ImGui::ListBoxFooter();
		}
	}
}