#include "fiber_pool.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "services/model_preview/model_preview_service.hpp"
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
				g_notification_service.push_warning("PERSIST_CAR"_T.data(), "PERSIST_CAR_TO_MANY_SPAWNED"_T.data());
			}
			else if (g.persist_car.spawn_inside && self::veh != vehicle)
			{
				teleport::into_vehicle(vehicle);
			}

			selected_vehicle_file.clear();
		}
		else
		{
			g_notification_service.push_warning("PERSIST_CAR"_T.data(), "SELECT_FILE_FIRST"_T.data());
		}
	}

	void view::persist_car()
	{
		static std::string selected_vehicle_file;

		const auto vehicle_folders = persist_car_service::list_sub_folders();
		const auto vehicle_files   = persist_car_service::list_files(g.persist_car.persist_vehicle_sub_folder);
		static std::string file_name_to_delete{};

		if (!file_name_to_delete.empty())
			ImGui::OpenPopup("##deletepersistcar");

		if (ImGui::BeginPopupModal("##deletepersistcar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("VIEW_SELF_ANIMATIONS_ARE_YOU_SURE_DELETE"_T.data(), file_name_to_delete.c_str());

			ImGui::Spacing();

			if (ImGui::Button("YES"_T.data()))
			{
				persist_car_service::delete_vehicle(file_name_to_delete, g.persist_car.persist_vehicle_sub_folder);
				file_name_to_delete.clear();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("NO"_T.data()))
			{
				file_name_to_delete.clear();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		if (ImGui::Checkbox("PREVIEW"_T.data(), &g.persist_car.preview_vehicle))
		{
			if (!g.persist_car.preview_vehicle)
			{
				g_model_preview_service->stop_preview();
			}
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("PREVIEW_DESC"_T.data());
		ImGui::SameLine();
		ImGui::Checkbox("SPAWN_IN"_T.data(), &g.persist_car.spawn_inside);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("SPAWN_IN_DESC"_T.data());

		ImGui::SetNextItemWidth(300.f);
		auto folder_display = g.persist_car.persist_vehicle_sub_folder.empty() ?
		    "ROOT"_T.data() :
		    g.persist_car.persist_vehicle_sub_folder.c_str();
		if (ImGui::BeginCombo("FOLDER"_T.data(), folder_display))
		{
			if (ImGui::Selectable("ROOT"_T.data(), g.persist_car.persist_vehicle_sub_folder == ""))
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
		components::input_text_with_hint("FILE_NAME"_T, "SEARCH"_T, search, sizeof(search), ImGuiInputTextFlags_None);
		std::string lower_search = search;
		std::transform(lower_search.begin(), lower_search.end(), lower_search.begin(), tolower);

		ImGui::SetNextItemWidth(250);
		ImGui::Text("SAVED_VEHICLES"_T.data());

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
						g_fiber_pool->queue_job([] {
							load_vehicle(selected_vehicle_file);
						});
						g_model_preview_service->stop_preview();
					}

					if (!g.persist_car.preview_vehicle || (g.persist_car.preview_vehicle && !ImGui::IsAnyItemHovered()))
					{
						g_model_preview_service->stop_preview();
					}
					else if (ImGui::IsItemHovered())
					{
						g_model_preview_service->show_vehicle_persisted(pair);
					}

					ImGui::SameLine();
					ImGui::PushID(file_name);
					if (ImGui::SmallButton("X"))
					{
						file_name_to_delete = pair;
					}
					ImGui::PopID();
				}
			}

			ImGui::EndListBox();
		}

		ImGui::SameLine();

		ImGui::BeginGroup();
		static char vehicle_file_name_input[50]{};

		components::small_text("VEHICLE_FILE_NAME"_T);
		ImGui::SetNextItemWidth(250);
		ImGui::InputText("##vehiclefilename", vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));
		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("VEHICLE_FILE_NAME_EXAMPLE"_T.data());

		if (g.persist_car.persist_vehicle_sub_folder.empty())
		{
			static char save_folder[50]{};
			components::small_text("VEHICLE_FOLDER_NAME"_T);
			ImGui::SetNextItemWidth(250);
			ImGui::InputText("##foldername", save_folder, IM_ARRAYSIZE(save_folder));
			if (ImGui::IsItemActive())
				g.self.hud.typing = TYPING_TICKS;
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("VEHICLE_FOLDER_NAME_EXAMPLE"_T.data());

			components::button("SAVE_VEHICLE"_T, [] {
				if (vehicle_file_name_input[0] == '\0')
					return;

				if (!self::veh)
					return g_notification_service.push_warning("PERSIST_CAR"_T.data(), "PERSIST_CAR_NOT_IN_VEHICLE"_T.data());

				save_vehicle(vehicle_file_name_input, save_folder);
			});
		}
		else
		{
			components::button("SAVE_VEHICLE"_T, [] {
				if (vehicle_file_name_input[0] == '\0')
					return;

				if (!self::veh)
					return g_notification_service.push_warning("PERSIST_CAR"_T.data(), "PERSIST_CAR_NOT_IN_VEHICLE"_T.data());

				save_vehicle(vehicle_file_name_input, g.persist_car.persist_vehicle_sub_folder.c_str());
			});
		}

		ImGui::EndGroup();
	}
}
