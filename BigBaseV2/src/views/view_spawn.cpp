#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/vehicle_preview_service.hpp"
#include "util/vehicle.hpp"

namespace big
{
	static char model[12] = "";

	bool does_search_match(std::string& input, const std::string& search)
	{
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		return input.find(search) != std::string::npos;
	}

	void view::spawn() {
		ImGui::Checkbox("Preview", &g->spawn.preview_vehicle);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn In", &g->spawn.spawn_inside);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn Maxed", &g->spawn.spawn_maxed);

		components::input_text_with_hint("Model Name", "Search", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, []
		{
			const auto location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 2.f, 2.f, 0.f);
			const Vehicle veh = vehicle::spawn(model, location, g_local_player->m_player_info->m_ped->m_navigation->m_heading + 90.f);

			if (g->spawn.spawn_inside)
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);

			if (g->spawn.spawn_maxed)
			{
				vehicle::max_vehicle(veh);
			}

		});
		if (ImGui::ListBoxHeader("###vehicles", { ImGui::GetWindowWidth(), ImGui::GetWindowHeight() }))
		{
			if (!g_vehicle_preview_service->get_vehicle_list().is_null())
			{
				for (auto& item : g_vehicle_preview_service->get_vehicle_list())
				{
					if (item["Name"].is_null() || item["DisplayName"].is_null())
						continue;

					std::string name = item["Name"];
					std::string display_name = item["DisplayName"];

					std::string manufacturer;
					std::string search = model;
					std::transform(search.begin(), search.end(), search.begin(), ::tolower);

					if (!item["ManufacturerDisplayName"].is_null())
						manufacturer = item["ManufacturerDisplayName"];

					if (search.empty() ||
						does_search_match(name, search) ||
						does_search_match(display_name, search) ||
						does_search_match(manufacturer, search))
					{
						components::selectable(item["DisplayName"], item["Name"] == search, [&item]
						{
							const auto location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
							const Vehicle veh = vehicle::spawn(item["Name"], location, 0.f);

							if (g->spawn.spawn_inside)
							{
								vehicle::telport_into_veh(veh);
							}

							if (g->spawn.spawn_maxed)
							{
								vehicle::max_vehicle(veh);
							}

						});

						if (g->spawn.preview_vehicle && ImGui::IsItemHovered())
							g_vehicle_preview_service->set_preview_vehicle(item);
					}
				}
			}
			else ImGui::Text("No vehicles in registry.");
		}
	}
}