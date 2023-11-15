#include "core/data/hud.hpp"
#include "core/data/persist_car.hpp"
#include "fiber_pool.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "services/vehicle_preview/vehicle_preview.hpp"
#include "util/strings.hpp"
#include "util/teleport.hpp"
#include "views/view.hpp"

namespace big
{
	static std::string persist_vehicle_sub_folder = "";

	static void save_vehicle(char* vehicle_file_name_input, const char* folder_name)
	{
		if (ENTITY::DOES_ENTITY_EXIST(self::veh))
		{
			const auto vehicle_file_name = std::string(vehicle_file_name_input).append(".json");
			persist_car_service::save_vehicle(self::veh, vehicle_file_name, folder_name);
			ZeroMemory(vehicle_file_name_input, sizeof(vehicle_file_name_input));
		}
	}

	static void load_vehicle(std::string& selected_vehicle_file, bool spawn_at_waypoint)
	{
		if (!selected_vehicle_file.empty())
		{
			std::optional<Vector3> waypoint_location;
			if (spawn_at_waypoint)
				waypoint_location = vehicle::get_waypoint_location();

			const auto vehicle = persist_car_service::load_vehicle(selected_vehicle_file, persist_vehicle_sub_folder, waypoint_location);

			if (!vehicle)
				g_notification_service->push_warning("Persist Car", "Vehicle failed to spawn, there is most likely too many spawned vehicles in the area");
			else if (g_persist_car.spawn_inside)
				teleport::into_vehicle(vehicle);

			selected_vehicle_file.clear();
		}
		else
			g_notification_service->push_warning("Persist Car", "Select a file first");
	}

	inline void save_vehicle_button(char* vehicle_file_name_input, const char* save_folder)
	{
		components::button("Save Vehicle", [vehicle_file_name_input, save_folder] {
			if (!trimString(vehicle_file_name_input).size())
				return g_notification_service->push_warning("Persist Car", "Filename empty!");

			if (!self::veh)
				return g_notification_service->push_warning("Persist Car", "You must be in a vehicle. Please enter a vehicle before using load.");

			save_vehicle(vehicle_file_name_input, save_folder);
		});
		ImGui::SameLine();
		components::button("Populate Name", [vehicle_file_name_input] {
			if (self::veh)
			{
				auto model = ENTITY::GET_ENTITY_MODEL(self::veh);
				auto name = std::format("{} {}", toLowercase(VEHICLE::GET_MAKE_NAME_FROM_VEHICLE_MODEL(model)), toLowercase(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model)));

				strcpy(vehicle_file_name_input, name.c_str());
			}
		});
	}

	void view::persist_car(bool spawn_at_waypoint)
	{
		static std::string selected_vehicle_file;

		const auto vehicle_folders = persist_car_service::list_sub_folders();
		const auto vehicle_files   = persist_car_service::list_files(persist_vehicle_sub_folder);
		static std::string file_name_to_delete{};

		if (!file_name_to_delete.empty())
			ImGui::OpenPopup("##deletepersistcar");

		if (ImGui::BeginPopupModal("##deletepersistcar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Are you sure you want to delete %s?", file_name_to_delete.c_str());

			ImGui::Spacing();

			if (ImGui::Button("Yes"))
			{
				persist_car_service::delete_vehicle(file_name_to_delete, persist_vehicle_sub_folder);
				file_name_to_delete.clear();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				file_name_to_delete.clear();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::Checkbox("Spawn Inside", &g_persist_car.spawn_inside);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Controls whether the player should be set inside the vehicle after it spawns");

		ImGui::SetNextItemWidth(300.f);
		auto folder_display = persist_vehicle_sub_folder.empty() ? "Root" : persist_vehicle_sub_folder.c_str();
		if (ImGui::BeginCombo("Folder", folder_display))
		{
			if (ImGui::Selectable("Root", persist_vehicle_sub_folder == ""))
				persist_vehicle_sub_folder.clear();

			for (std::string folder_name : vehicle_folders)
			{
				if (ImGui::Selectable(folder_name.c_str(), persist_vehicle_sub_folder == folder_name))
					persist_vehicle_sub_folder = folder_name;
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
					auto file_name = pair.c_str();
					if (ImGui::Selectable(file_name, selected_vehicle_file == pair, ImGuiSelectableFlags_AllowItemOverlap))
					{
						selected_vehicle_file = pair;
						g_fiber_pool->queue_job([spawn_at_waypoint] {
							load_vehicle(selected_vehicle_file, spawn_at_waypoint);
						});
						g_vehicle_preview.clear();
					}

					if (g_vehicle_preview.is_camera_prepared && !ImGui::IsAnyItemHovered())
						g_vehicle_preview.clear();
					else if (g_enable_vehicle_preview && ImGui::IsItemHovered())
						g_vehicle_preview.preview_persisted_veh(pair, persist_vehicle_sub_folder);

					ImGui::SameLine();
					ImGui::PushID(file_name);
					if (ImGui::SmallButton("X"))
						file_name_to_delete = pair;
					ImGui::PopID();
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
			g_hud.typing = TYPING_TICKS;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Ex: My Cool Car");

		if (persist_vehicle_sub_folder.empty())
		{
			static char save_folder[50]{};
			components::small_text("Vehicle Folder Name");
			ImGui::SetNextItemWidth(250);
			ImGui::InputText("##foldername", save_folder, IM_ARRAYSIZE(save_folder));
			if (ImGui::IsItemActive())
				g_hud.typing = TYPING_TICKS;
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Ex: My Cool Car Collection (Leave this blank for Root)");

			save_vehicle_button(vehicle_file_name_input, save_folder);
		}
		else
			save_vehicle_button(vehicle_file_name_input, persist_vehicle_sub_folder.c_str());

		ImGui::EndGroup();
	}
}
