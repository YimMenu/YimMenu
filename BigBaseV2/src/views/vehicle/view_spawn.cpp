#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/vehicle_preview/vehicle_preview_service.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::spawn()
	{
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		ImGui::Checkbox("Preview", &g->spawn.preview_vehicle);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn In", &g->spawn.spawn_inside);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn Maxed", &g->spawn.spawn_maxed);

		static char plate[9] = { 0 };
		strncpy(plate, g->spawn.plate.c_str(), 9);

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Plate", "Plate Number", plate, sizeof(plate), ImGuiInputTextFlags_None, [] {
			g->spawn.plate = plate;
		});


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

		// arbitrary subtraction this looked nice so idc, works for all resolutions as well
		if (ImGui::ListBoxHeader("###vehicles", { 300, static_cast<float>(*g_pointers->m_resolution_y - 184 - 38 * 4) }))
		{

			auto item_arr = g_gta_data_service->get_vehicle_arr();

			if (item_arr.size() > 0)
			{
				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				for (auto& item : item_arr) {
					std::string display_name = item.display_name;
					std::string display_manufacturer = item.display_manufacturer;
					std::string clazz = item.clazz;

					std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
					std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

					if ((
						selected_class == -1 || class_arr[selected_class] == clazz
					) && (
						display_name.find(lower_search) != std::string::npos ||
						display_manufacturer.find(lower_search) != std::string::npos
					)) {
						ImGui::PushID(item.hash);
						components::selectable(item.display_name, false, [item] {

							float y_offset = 0;

							if (self::veh != 0)
							{
								y_offset = 10.f;
							}
							else if (!g->spawn.spawn_inside)
							{
								y_offset = 5.f;
							}

							Vector3 spawn_location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, y_offset, 0.f);
							float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

							const Vehicle veh = vehicle::spawn(item.hash, spawn_location, spawn_heading);

							if (g->spawn.spawn_maxed)
							{
								vehicle::max_vehicle(veh);
							}

							vehicle::set_plate(veh, plate);

							if (g->spawn.spawn_inside)
							{
								vehicle::teleport_into_vehicle(veh);
							}

							g_vehicle_preview_service->stop_preview();
						});
						ImGui::PopID();

						if (g->spawn.preview_vehicle && ImGui::IsItemHovered())
						{
							g_vehicle_preview_service->set_preview_vehicle(item);
						}
						else if (g->spawn.preview_vehicle && !ImGui::IsAnyItemHovered())
						{
							g_vehicle_preview_service->stop_preview();
						}
					}
				}
			}
			else
			{
				ImGui::Text("No vehicles in registry.");
			}
			ImGui::ListBoxFooter();
		}
	}
}