#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/mobile/mobile_service.hpp"
#include "services/model_preview/model_preview_service.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::pv()
	{
		ImGui::SetWindowSize({0.f, (float)*g_pointers->m_gta.m_resolution_y}, ImGuiCond_Always);

		if (ImGui::Checkbox("PREVIEW"_T.data(), &g.clone_pv.preview_vehicle))
		{
			if (!g.clone_pv.preview_vehicle)
			{
				g_model_preview_service->stop_preview();
			}
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("PREVIEW_DESC"_T.data());
		ImGui::SameLine();
		ImGui::Checkbox("SPAWN_IN"_T.data(), &g.clone_pv.spawn_inside);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("SPAWN_IN_DESC"_T.data());
		ImGui::SameLine();

		static char plate_buf[9] = {0};

		if (ImGui::Checkbox("SPAWN_CLONE"_T.data(), &g.clone_pv.spawn_clone))
		{
			g_mobile_service->refresh_garages();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("SPAWN_CLONE_DESC"_T.data());
		if (g.clone_pv.spawn_clone)
		{
			ImGui::Checkbox("SPAWN_MAXED"_T.data(), &g.clone_pv.spawn_maxed);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("SPAWN_MAXED_DESC"_T.data());

			ImGui::SameLine();
			ImGui::Checkbox("CLONE_PV_PLATE"_T.data(), &g.clone_pv.clone_plate);
			if (!g.clone_pv.clone_plate)
			{
				ImGui::SetNextItemWidth(300.f);

				strncpy(plate_buf, g.clone_pv.plate.c_str(), 9);
				components::input_text_with_hint("PLATE"_T, "PLATE_NUMBER"_T, plate_buf, sizeof(plate_buf), ImGuiInputTextFlags_None, [] {
					g.clone_pv.plate = plate_buf;
				});
			}
		}


		static int selected_class = -1;
		const auto& class_arr     = g_gta_data_service.vehicle_classes();

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::BeginCombo("VEHICLE_CLASS"_T.data(),
		        selected_class == -1 ? "ALL"_T.data() : class_arr[selected_class].c_str()))
		{
			if (ImGui::Selectable("ALL"_T.data(), selected_class == -1))
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
		std::string garage_display = g.clone_pv.garage.empty() ? "ALL"_T.data() : g.clone_pv.garage;
		if (ImGui::BeginCombo("GARAGE"_T.data(), garage_display.c_str()))
		{
			if (ImGui::Selectable("ALL"_T.data(), g.clone_pv.garage.empty()))
			{
				g.clone_pv.garage.clear();
			}
			for (auto garage : g_mobile_service->garages())
			{
				if (ImGui::Selectable(garage.c_str(), garage == g.clone_pv.garage))
				{
					g.clone_pv.garage = garage;
				}
				if (garage == g.clone_pv.garage)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		static char search[64];

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("MODEL_NAME"_T, "SEARCH"_T, search, sizeof(search), ImGuiInputTextFlags_None);

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
				const auto& item         = g_gta_data_service.vehicle_by_hash(personal_veh->get_hash());

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
				ImGui::Text("NO_PERSONAL_VEHICLES"_T.data());
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
							if (g.clone_pv.spawn_clone)
							{
								Vector3 spawn_location =
								    vehicle::get_spawn_location(g.spawn_vehicle.spawn_inside, personal_veh->get_hash());
								float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

								auto vehicle_idx = personal_veh->get_vehicle_idx();
								auto owned_mods  = vehicle::get_owned_mods_from_vehicle_idx(vehicle_idx);

								const char* spawn_plate_buf = plate_buf;
								if (g.clone_pv.clone_plate)
								{
									spawn_plate_buf = personal_veh->get_plate();
								}

								auto veh = vehicle::clone_from_owned_mods(owned_mods, spawn_location, spawn_heading);

								if (veh == 0)
								{
									g_notification_service.push_error("VEHICLE"_T.data(), "UNABLE_TO_SPAWN_VEHICLE"_T.data());
								}
								else
								{
									if (g.clone_pv.spawn_maxed)
									{
										vehicle::max_vehicle(veh);
									}

									vehicle::set_plate(veh, spawn_plate_buf);

									if (g.clone_pv.spawn_inside)
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

							g_model_preview_service->stop_preview();
						});
						ImGui::PopID();

						if (!g.clone_pv.preview_vehicle || (g.clone_pv.preview_vehicle && !ImGui::IsAnyItemHovered()))
						{
							g_model_preview_service->stop_preview();
						}
						else if (ImGui::IsItemHovered())
						{
							g_model_preview_service->show_vehicle(vehicle::get_owned_mods_from_vehicle_idx(personal_veh->get_vehicle_idx()),
							    g.clone_pv.spawn_maxed);
						}
					}
				}
			}

			ImGui::EndListBox();
		}
	}
}
