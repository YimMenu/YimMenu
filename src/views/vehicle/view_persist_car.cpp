#include "fiber_pool.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"
#include "util/mobile.hpp"
#include "core/data/speed_units.hpp"
#include "services/vehicle/persist_car_service.hpp"

namespace big
{
	static void save_vehicle(char* vehicle_file_name_input)
	{
		if (ENTITY::DOES_ENTITY_EXIST(self::veh))
		{
			const auto vehicle_file_name = std::string(vehicle_file_name_input).append(".json");
			persist_car_service::save_vehicle(self::veh, vehicle_file_name);
			ZeroMemory(vehicle_file_name_input, sizeof(vehicle_file_name_input));
		}
	}

	static void load_vehicle(std::string& selected_vehicle_file)
	{
		if (!selected_vehicle_file.empty())
		{
			const auto vehicle = persist_car_service::load_vehicle(selected_vehicle_file);
			if (!vehicle)
			{
				g_notification_service->push_warning("Persist Car", "Vehicle failed to spawn, there is most likely too many spawned vehicles in the area");
			}
			else if (g.spawn_vehicle.spawn_inside)
				teleport::into_vehicle(vehicle);

			selected_vehicle_file.clear();
		}
		else
		{
			g_notification_service->push_warning("Persist Car", "Select a file first");
		}
	}

	void view::persist_car()
	{
		static std::string selected_vehicle_file;

		const auto vehicle_files = persist_car_service::list_files();

		ImGui::PushItemWidth(250);
		ImGui::Text("Saved Vehicles");

		if (ImGui::ListBoxHeader("##empty", ImVec2(200, 200)))
		{
			for (const auto& pair : vehicle_files)
			{
				if (ImGui::Selectable(pair.c_str(), selected_vehicle_file == pair))
					selected_vehicle_file = pair;
			}

			ImGui::ListBoxFooter();
		}

		ImGui::SameLine();

		ImGui::BeginGroup();
		static char vehicle_file_name_input[50]{};

		ImGui::PushItemWidth(250);
		components::input_text_with_hint(
			"Vehicle File Name",
			"Ex: My Cool Car",
			vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));

		ImGui::SameLine();

		components::button("Save Vehicle", []
		{
			save_vehicle(vehicle_file_name_input);
		});

		components::button("Load Vehicle", []
		{
			load_vehicle(selected_vehicle_file);
		});

		ImGui::EndGroup();
	}
}
