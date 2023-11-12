#include "core/data/clone_pv.hpp"
#include "core/data/spawn_vehicle.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/mobile/mobile_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::pv()
	{
		ImGui::SetWindowSize({0.f, (float)*g_pointers->m_gta.m_resolution_y}, ImGuiCond_Always);

		ImGui::Checkbox("Spawn Inside", &g_clone_pv.spawn_inside);
		ImGui::SameLine();

		if (ImGui::Checkbox("Spawn Clone", &g_clone_pv.spawn_clone))
			g_mobile_service->refresh_garages();

		static int selected_class = -1;
		const auto& class_arr     = g_gta_data_service->vehicle_classes();

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::BeginCombo("Vehicle Class", selected_class == -1 ? "All" : class_arr[selected_class].c_str()))
		{
			if (ImGui::Selectable("All", selected_class == -1))
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

		ImGui::SetNextItemWidth(300.f);
		std::string garage_display = g_clone_pv.garage.empty() ? "All" : g_clone_pv.garage;
		if (ImGui::BeginCombo("Garage", garage_display.c_str()))
		{
			if (ImGui::Selectable("All", g_clone_pv.garage.empty()))
			{
				g_clone_pv.garage.clear();
			}
			for (auto garage : g_mobile_service->garages())
			{
				if (ImGui::Selectable(garage.c_str(), garage == g_clone_pv.garage))
				{
					g_clone_pv.garage = garage;
				}
				if (garage == g_clone_pv.garage)
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

		auto num_of_rows = 0;

		std::set<int> indexes_to_use;

		if (!g_mobile_service->personal_vehicles().empty())
		{
			std::string lower_search = search;
			std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

			for (const auto& it : g_mobile_service->personal_vehicles())
			{
				const auto& label        = it.first;
				const auto& personal_veh = it.second;
				const auto& item         = g_gta_data_service->vehicle_by_hash(personal_veh->get_hash());

				std::string vehicle_class        = item.m_vehicle_class;
				std::string display_name         = label;
				std::string display_manufacturer = item.m_display_manufacturer;
				std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
				std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

				if ((selected_class == -1 || class_arr[selected_class] == vehicle_class)
				    && (display_name.find(lower_search) != std::string::npos || display_manufacturer.find(lower_search) != std::string::npos))
				{
					if (personal_veh->is_blacklisted_vehicle() || !personal_veh->is_in_selected_garage())
					{
						continue;
					}
					indexes_to_use.insert(personal_veh->get_id());
				}
			}
			num_of_rows = indexes_to_use.size();
		}
		else
		{
			num_of_rows = 2;
		}

		static const auto over_30 = (30 * ImGui::GetTextLineHeightWithSpacing() + 2);
		const auto box_height = num_of_rows <= 30 ? (num_of_rows * ImGui::GetTextLineHeightWithSpacing() + 2) : over_30;
		if (ImGui::BeginListBox("###personal_veh_list", {300, box_height}))
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
					const auto& personal_veh = it.second;

					if (indexes_to_use.contains(personal_veh->get_id()))
					{
						const auto& label = it.first;

						ImGui::PushID('v' << 24 & personal_veh->get_id());
						components::selectable(label, false, [&personal_veh] {
							if (g_clone_pv.spawn_clone)
							{
								Vector3 spawn_location =
								    vehicle::get_spawn_location(g_spawn_vehicle.spawn_inside, personal_veh->get_hash());
								float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

								auto vehicle_idx = personal_veh->get_vehicle_idx();
								auto owned_mods  = vehicle::get_owned_mods_from_vehicle_idx(vehicle_idx);

								auto veh = vehicle::clone_from_owned_mods(owned_mods, spawn_location, spawn_heading);

								if (veh == 0)
								{
									g_notification_service->push_error("Vehicle", "Unable to spawn vehicle");
								}
								else
								{
									if (g_clone_pv.spawn_inside)
									{
										vehicle::teleport_into_vehicle(veh);
									}
								}
								// cleanup clones
								ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&veh);
							}
							else
							{
								strcpy(search, "");
								personal_veh->summon();
							}
						});
						ImGui::PopID();
					}
				}
			}

			ImGui::EndListBox();
		}
	}
}
