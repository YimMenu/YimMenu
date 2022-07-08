#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/vehicle_preview/vehicle_preview_service.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::spawn() {
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		ImGui::Checkbox("Preview", &g->spawn.preview_vehicle);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn In", &g->spawn.spawn_inside);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn Maxed", &g->spawn.spawn_maxed);

		static char plate[9] = { 0 };
		strncpy(plate, g->spawn.plate.c_str(), 9);

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::InputTextWithHint("Plate", "Plate Number", plate, sizeof(plate))) {
			g->spawn.plate = plate;
		}

		static char search[64];
		static std::string lower_search;

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::InputTextWithHint("Model Name", "Search", search, sizeof(search))) {
			lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);
		}

		// arbitrary subtraction this looked nice so idc, works for all resolutions as well
		if (ImGui::ListBoxHeader("###vehicles", { 300, static_cast<float>(*g_pointers->m_resolution_y - 260)})) {
			if (g_vehicle_preview_service->get_vehicle_map().size() > 0) {

				for (auto& [hash, item] : g_vehicle_preview_service->get_vehicle_map()) {
					std::string display_name = item.dispaly_name;
					std::string display_manufacturer = item.display_manufacturer;

					std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
					std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

					if (
						display_name.find(lower_search) != std::string::npos ||
						display_manufacturer.find(lower_search) != std::string::npos
					) {
						std::string& item_name = item.name;

						components::selectable(item.dispaly_name + "##" + std::to_string(item.hash), false, [&item_name] {

							float y_offset = 0;

							if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, false)) {
								y_offset = 10.f;
							} else if (!g->spawn.spawn_inside) {
								y_offset = 5.f;
							}

							Vector3 spawn_location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, y_offset, 0.f);
							float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

							const Vehicle veh = vehicle::spawn(item_name, spawn_location, spawn_heading);

							if (g->spawn.spawn_inside) {
								vehicle::telport_into_veh(veh);
							}

							if (g->spawn.spawn_maxed) {
								vehicle::max_vehicle(veh);
							}

							vehicle::set_plate(veh, plate);

							g_vehicle_preview_service->stop_preview();
						});

						if (g->spawn.preview_vehicle && ImGui::IsItemHovered()) {
							g_vehicle_preview_service->set_preview_vehicle(item);
						} else if (g->spawn.preview_vehicle && !ImGui::IsAnyItemHovered()) {
							g_vehicle_preview_service->stop_preview();
						}
					}
				}
			}
			else ImGui::Text("No vehicles in registry.");
			ImGui::ListBoxFooter();
		}
	}
}