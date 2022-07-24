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
		int num_of_rows = 3;

		ImGui::Checkbox("Spawn Clone", &g->clone_pv.spawn_clone);
		if (g->clone_pv.spawn_clone)
		{
			num_of_rows = 5;

			ImGui::Checkbox("Spawn Maxed", &g->clone_pv.spawn_maxed);

			ImGui::SameLine();
			strncpy(plate, g->clone_pv.plate.c_str(), 9);
			ImGui::Checkbox("Clone PV Plate", &g->clone_pv.clone_plate);
			if (g->clone_pv.clone_plate)
			{
				num_of_rows = 4;
			}
			else
			{
				ImGui::SetNextItemWidth(300.f);

				components::input_text_with_hint("Plate", "Plate Number", plate, sizeof(plate), ImGuiInputTextFlags_None, [] {
					g->clone_pv.plate = plate;
				});
			}
		}


		static int selected_class = -1;
		auto class_arr = g_gta_data_service->get_vehicle_class_arr();

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::BeginCombo("Vehicle Class", selected_class == -1 ? "ALL" : class_arr[selected_class].c_str()))
		{
			if (ImGui::Selectable("ALL", selected_class == -1))
			{
				selected_class = -1;
			}

			for (int i = 0; i < class_arr.size(); i++)
			{
				if (ImGui::Selectable(class_arr[i].c_str(), selected_class == i))
				{
					selected_class = i;
				}

				if (selected_class == i)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}


		static char search[64];

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Model Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None);

		g_mobile_service->refresh_personal_vehicles();
		if (ImGui::ListBoxHeader("###personal_veh_list", { 300, static_cast<float>(*g_pointers->m_resolution_y - 184 - 38 * num_of_rows) }))
		{
			if (g_mobile_service->personal_vehicles().empty())
			{
				ImGui::Text("No personal vehicles found, \nare you online?");
			}
			else
			{
				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				for (const auto& it : g_mobile_service->personal_vehicles())
				{
					const auto& label = it.first;
					const auto& personal_veh = it.second;
					auto item = g_gta_data_service->find_vehicle_by_hash(personal_veh->get_hash());

					std::string clazz = item.clazz;
					std::string display_name = label;
					std::string display_manufacturer = item.display_manufacturer;
					std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
					std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

					if ((
						selected_class == -1 || class_arr[selected_class] == clazz
					) && (
						display_name.find(lower_search) != std::string::npos ||
						display_manufacturer.find(lower_search) != std::string::npos
					)) {
						ImGui::PushID('v' << 24 & personal_veh->get_id());

						components::selectable(label, false, [&personal_veh] {
							if (g->clone_pv.spawn_clone)
							{
								auto vehicle_idx = personal_veh->get_vehicle_idx();
								auto veh_data = vehicle::get_vehicle_data_from_vehicle_idx(vehicle_idx);

								float y_offset = 0;

								if (self::veh != 0)
								{
									y_offset = 10.f;
								}
								else if (!g->clone_pv.spawn_inside)
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

								auto veh = vehicle::clone_from_vehicle_data(veh_data, spawn_location, spawn_heading);

								if (g->clone_pv.spawn_maxed)
								{
									vehicle::max_vehicle(veh);
								}

								vehicle::set_plate(veh, spawn_plate);

								if (g->clone_pv.spawn_inside)
								{
									vehicle::teleport_into_vehicle(veh);
								}
							}
							else
							{
								strcpy(search, "");

								personal_veh->summon();
							}

							g_vehicle_preview_service->stop_preview();
						});
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