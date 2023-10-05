#include "fiber_pool.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

namespace big
{
	static void save_vehicle(char* vehicle_file_name_input, const char* folder_name)
	{
		if (ENTITY::DOES_ENTITY_EXIST(self::veh))
		{
			const auto vehicle_file_name = std::string(vehicle_file_name_input).append(".json");
			persist_car_service::save_vehicle(self::veh, vehicle_file_name, folder_name);
			ZeroMemory(vehicle_file_name_input, sizeof(vehicle_file_name_input));
		}
	}

	static void load_vehicle(std::string& selected_vehicle_file)
	{
		if (!selected_vehicle_file.empty())
		{
			const auto vehicle = persist_car_service::load_vehicle(selected_vehicle_file, g.persist_car.persist_vehicle_sub_folder);
			if (!vehicle)
			{
				g_notification_service->push_warning("Persist Car", "Vehicle failed to spawn, there is most likely too many spawned vehicles in the area");
			}
			else if (g.persist_car.spawn_inside)
			{
				teleport::into_vehicle(vehicle);
			}

			selected_vehicle_file.clear();
		}
		else
		{
			g_notification_service->push_warning("Persist Car", "Select a file first");
		}
	}

	inline void save_vehicle_button(char* vehicle_file_name_input, const char* save_folder)
	{
		components::button("Save Vehicle", [vehicle_file_name_input, save_folder] {
			if (!self::veh)
				return g_notification_service->push_warning("Persist Car", "You must be in a vehicle. Please enter a vehicle before using load.");
			save_vehicle(vehicle_file_name_input, save_folder);
		});
	}

	void view::persist_car()
	{
		static std::string selected_vehicle_file;

		const auto vehicle_folders = persist_car_service::list_sub_folders();
		const auto vehicle_files   = persist_car_service::list_files(g.persist_car.persist_vehicle_sub_folder);

		ImGui::Checkbox("Spawn Inside", &g.persist_car.spawn_inside);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Controls whether the player should be set inside the vehicle after it spawns");

		ImGui::SetNextItemWidth(300.f);
		auto folder_display = g.persist_car.persist_vehicle_sub_folder.empty() ?
		    "Root" :
		    g.persist_car.persist_vehicle_sub_folder.c_str();
		if (ImGui::BeginCombo("Folder", folder_display))
		{
			if (ImGui::Selectable("Root", g.persist_car.persist_vehicle_sub_folder == ""))
				g.persist_car.persist_vehicle_sub_folder.clear();

			for (std::string folder_name : vehicle_folders)
			{
				if (ImGui::Selectable(folder_name.c_str(), g.persist_car.persist_vehicle_sub_folder == folder_name))
					g.persist_car.persist_vehicle_sub_folder = folder_name;
			}

			ImGui::EndCombo();
		}

		static char search[64];
		ImGui::SetNextItemWidth(300.f);
		components::input_text_with_hint("File Name", "Search", search, sizeof(search), ImGuiInputTextFlags_None);
		std::string lower_search = search;
		std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

		ImGui::SetNextItemWidth(250);
		ImGui::Text("Saved Vehicles");

		static const auto over_30 = (30 * ImGui::GetTextLineHeightWithSpacing() + 2);
		const auto box_height = vehicle_files.size() <= 30 ? (vehicle_files.size() * ImGui::GetTextLineHeightWithSpacing() + 2) : over_30;
		if (ImGui::BeginListBox("##empty", ImVec2(300, box_height)))
		{
			for (const auto& pair : vehicle_files)
			{
				std::string pair_lower = pair;
				std::transform(pair_lower.begin(), pair_lower.end(), pair_lower.begin(), tolower);
				if (pair_lower.contains(lower_search))
				{
					if (ImGui::Selectable(pair.c_str(), selected_vehicle_file == pair))
					{
						selected_vehicle_file = pair;
						g_fiber_pool->queue_job([] {
							load_vehicle(selected_vehicle_file);
						});
					}
				}
			}

			ImGui::EndListBox();
		}

		ImGui::SameLine();

		ImGui::BeginGroup();
		static char vehicle_file_name_input[50]{};

		components::small_text("Vehicle File Name");
		ImGui::SetNextItemWidth(250);
		ImGui::InputText("##vehiclefilename", vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));
		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Ex: My Cool Car");

		if (g.persist_car.persist_vehicle_sub_folder.empty())
		{
			static char save_folder[50]{};
			components::small_text("Vehicle Folder Name");
			ImGui::SetNextItemWidth(250);
			ImGui::InputText("##foldername", save_folder, IM_ARRAYSIZE(save_folder));
			if (ImGui::IsItemActive())
				g.self.hud.typing = TYPING_TICKS;
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Ex: My Cool Car Collection (Leave this blank for Root)");

			save_vehicle_button(vehicle_file_name_input, save_folder);
		}
		else
		{
			save_vehicle_button(vehicle_file_name_input, g.persist_car.persist_vehicle_sub_folder.c_str());
		}

		ImGui::EndGroup();
	}
}
