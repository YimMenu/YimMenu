#include "core/data/vehicle.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/vehicle_preview/vehicle_preview.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void render_spawn_new_vehicle()
	{
		static bool spawn_maxed;

		ImGui::Checkbox("Spawn Maxed", &spawn_maxed);

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

		static char search[64];

		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("Model Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None);

		vehicle_map calculated_map{};

		if (g_gta_data_service->vehicles().size() > 0)
		{
			for (auto& item : g_gta_data_service->vehicles())
			{
				const auto& vehicle = item.second;

				std::string display_name         = vehicle.m_display_name;
				std::string display_manufacturer = vehicle.m_display_manufacturer;
				std::string clazz                = vehicle.m_vehicle_class;

				std::transform(display_name.begin(), display_name.end(), display_name.begin(), ::tolower);
				std::transform(display_manufacturer.begin(), display_manufacturer.end(), display_manufacturer.begin(), ::tolower);

				std::string lower_search = search;
				std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

				if ((selected_class == -1 || class_arr[selected_class] == clazz)
				    && (display_name.find(lower_search) != std::string::npos || display_manufacturer.find(lower_search) != std::string::npos))
				{
					calculated_map.emplace(item);
				}
			}
		}

		static const auto over_30 = (30 * ImGui::GetTextLineHeightWithSpacing() + 2);
		auto calculated_size      = calculated_map.size();
		if (calculated_map.size() == 0)
		{
			calculated_size++;
		}
		if (self::veh)
		{
			calculated_size++;
		}
		const auto box_height = calculated_size <= 30 ? (calculated_size * ImGui::GetTextLineHeightWithSpacing() + 2) : over_30;
		if (ImGui::BeginListBox("###vehicles", {300, box_height}))
		{
			if (calculated_map.size() > 0)
			{
				for (auto& item : calculated_map)
				{
					const auto& vehicle = item.second;
					ImGui::PushID(vehicle.m_hash);
					components::selectable(vehicle.m_display_name, false, [&vehicle] {
						Vector3 spawn_location;
						std::optional<Vector3> waypoint_location;

						if (g_vehicle.spawn_at_waypoint && (waypoint_location = vehicle::get_waypoint_location()).has_value())
							spawn_location = waypoint_location.value();
						else
							spawn_location = vehicle::get_spawn_location(vehicle.m_hash);

						auto veh = vehicle::spawn(vehicle.m_hash, spawn_location);

						if (veh == 0)
							g_notification_service->push_error("Vehicle", "Unable to spawn vehicle");
						else
						{
							if (spawn_maxed)
								vehicle::max_vehicle(veh);
							if (g_vehicle.spawn_inside)
								vehicle::teleport_into_vehicle(veh);
						}

						g_vehicle_preview.clear();
						ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&veh);
					});
					ImGui::PopID();

					if (g_vehicle_preview.is_camera_prepared && !ImGui::IsAnyItemHovered())
						g_vehicle_preview.clear();
					else if (g_vehicle.preview_vehicle && ImGui::IsItemHovered())
						g_vehicle_preview.preview_veh(vehicle.m_hash);
				}
			}
			else
			{
				ImGui::Text("No vehicles in registry.");
			}
			ImGui::EndListBox();
		}
	}

	void view::spawn_vehicle()
	{
		static int spawn_vehicle_type;

		ImGui::RadioButton("New", &spawn_vehicle_type, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Personal", &spawn_vehicle_type, 1);
		ImGui::SameLine();
		ImGui::RadioButton("Persistent", &spawn_vehicle_type, 2);

		ImGui::Spacing();

		ImGui::Checkbox("Spawn at waypoint", &g_vehicle.spawn_at_waypoint);
		ImGui::SameLine();
		ImGui::Checkbox("Spawn Inside", &g_vehicle.spawn_inside);
		ImGui::SameLine();
		if (ImGui::Checkbox("Preview", &g_vehicle.preview_vehicle))
			if (!g_vehicle.preview_vehicle)
				g_vehicle_preview.clear();

		ImGui::Spacing();

		switch (spawn_vehicle_type)
		{
		case 0: render_spawn_new_vehicle(); break;
		case 1: view::pv(); break;
		case 2: view::persist_car(); break;
		}
	}
}
