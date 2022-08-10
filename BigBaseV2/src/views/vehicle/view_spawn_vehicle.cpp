#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/model_preview/model_preview_service.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::spawn_vehicle()
	{
		ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		if (ImGui::Checkbox("Preview", &g->spawn_vehicle.preview_vehicle))
		{
			if (!g->spawn_vehicle.preview_vehicle)
			{
				g_model_preview_service->stop_preview();
			}
		}
		ImGui::SameLine();
		ImGui::Checkbox("Spawn In", &g->spawn_vehicle.spawn_inside);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn Maxed", &g->spawn_vehicle.spawn_maxed);

		static char plate_buf[9] = { 0 };
		strncpy(plate_buf, g->spawn_vehicle.plate.c_str(), 9);

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Plate", "Plate Number", plate_buf, sizeof(plate_buf), ImGuiInputTextFlags_None, [] {
			g->spawn_vehicle.plate = plate_buf;
		});


		static int selected_class = -1;
		auto class_arr = g_gta_data_service->get_vehicle_class_arr();

		ImGui::SetNextItemWidth(300.f);
		if (ImGui::BeginCombo("Vehicle Class", selected_class == -1 ? "ALL" : class_arr[selected_class]))
		{
			if (ImGui::Selectable("ALL", selected_class == -1))
			{
				selected_class = -1;
			}

			for (int i = 0; i < class_arr.size(); i++)
			{
				if (ImGui::Selectable(class_arr[i], selected_class == i))
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


		if (ImGui::ListBoxHeader("###vehicles", { 300, static_cast<float>(*g_pointers->m_resolution_y - 188 - 38 * 4) }))
		{
			if (self::veh)
			{
				static auto veh_hash = 0;
				
				g_fiber_pool->queue_job([] {
					veh_hash = ENTITY::GET_ENTITY_MODEL(self::veh);
				});

				if (veh_hash)
				{
					auto item = g_gta_data_service->find_vehicle_by_hash(veh_hash);

					components::selectable("Current Vehicle [" + std::string(item.name) + "]", false, [] {
						if (self::veh)
						{
							Vector3 spawn_location = vehicle::get_spawn_location(g->spawn_vehicle.spawn_inside);
							float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

							auto owned_mods = vehicle::get_owned_mods_from_vehicle(self::veh);

							auto veh = vehicle::clone_from_owned_mods(owned_mods, spawn_location, spawn_heading);

							if (veh == 0)
							{
								g_notification_service->push_error("Vehicle", "Unable to spawn vehicle");
							}
							else
							{
								if (g->spawn_vehicle.spawn_maxed)
								{
									vehicle::max_vehicle(veh);
								}

								vehicle::set_plate(veh, plate_buf);

								if (g->spawn_vehicle.spawn_inside)
								{
									vehicle::teleport_into_vehicle(veh);
								}
							}
						}

						g_model_preview_service->stop_preview();
					});

					if (!g->spawn_vehicle.preview_vehicle || (g->spawn_vehicle.preview_vehicle && !ImGui::IsAnyItemHovered()))
					{
						g_model_preview_service->stop_preview();
					}
					else if (ImGui::IsItemHovered())
					{
						g_fiber_pool->queue_job([] {
							g_model_preview_service->show_vehicle(
								vehicle::get_owned_mods_from_vehicle(self::veh),
								g->spawn_vehicle.spawn_maxed
							);
						});
					}
				}
			}

			auto vehicle_arr = g_gta_data_service->get_vehicle_arr();

			if (vehicle_arr.size() > 0)
			{
				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				for (auto& vehicle : vehicle_arr) {
					if (!vehicle.hash)
					{
						continue;
					}

					std::string name = vehicle.name;
					std::string manufacturer = vehicle.get_manufacturer();
					std::string clazz = vehicle.get_class();

					std::transform(name.begin(), name.end(), name.begin(), ::tolower);
					std::transform(manufacturer.begin(), manufacturer.end(), manufacturer.begin(), ::tolower);

					if ((
						selected_class == -1 || class_arr[selected_class] == clazz
					) && (
						name.find(lower_search) != std::string::npos ||
						manufacturer.find(lower_search) != std::string::npos
					)) {
						ImGui::PushID(vehicle.hash);
						components::selectable(vehicle.name, false, [vehicle] {

							Vector3 spawn_location = vehicle::get_spawn_location(g->spawn_vehicle.spawn_inside);
							float spawn_heading = ENTITY::GET_ENTITY_HEADING(self::ped);

							const Vehicle veh = vehicle::spawn(vehicle.hash, spawn_location, spawn_heading);

							if (veh == 0)
							{
								g_notification_service->push_error("Vehicle", "Unable to spawn vehicle");
							}
							else
							{
								if (g->spawn_vehicle.spawn_maxed)
								{
									vehicle::max_vehicle(veh);
								}

								vehicle::set_plate(veh, plate_buf);

								if (g->spawn_vehicle.spawn_inside)
								{
									vehicle::teleport_into_vehicle(veh);
								}
							}

							g_model_preview_service->stop_preview();
						});
						ImGui::PopID();

						if (!g->spawn_vehicle.preview_vehicle || (g->spawn_vehicle.preview_vehicle && !ImGui::IsAnyItemHovered()))
						{
							g_model_preview_service->stop_preview();
						}
						else if (ImGui::IsItemHovered())
						{
							g_model_preview_service->show_vehicle(vehicle.hash, g->spawn_vehicle.spawn_maxed);
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