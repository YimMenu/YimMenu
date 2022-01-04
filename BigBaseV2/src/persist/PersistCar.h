#pragma once

#include "natives.hpp"
#include "services\VehicleHelper.h"
#include "pointers.hpp"
#include "ModelAttachment.h"

namespace big
{
	class persist_car
	{
	public:
		static void save_vehicle(Vehicle vehicle, std::string file_name);
		static Vehicle load_vehicle(std::string file_name);
		static std::vector<std::string> list_files();
		static Vehicle clone_ped_car(Ped ped, Vehicle vehicle);
		static void do_presentation_layer();
	private:
		static Vehicle spawn_vehicle_full(nlohmann::json vehicle_json, Ped ped);
		static Vehicle spawn_vehicle(nlohmann::json vehicle_json, Ped ped);
		static Vehicle spawn_vehicle_json(nlohmann::json vehicle_json, Ped ped);
		static nlohmann::json get_full_vehicle_json(Vehicle vehicle);
		static model_attachment::model_attachment get_model_attachment(Vehicle vehicle, Object object);
		static nlohmann::json get_model_attachments(Vehicle vehicle, bool is_towed_vehicle = false);
		static nlohmann::json get_vehicle_attachents(Vehicle vehicle);
		static nlohmann::json get_vehicle_json(Vehicle vehicle);
		static std::filesystem::path check_vehicle_folder();
		static void do_save_vehicle(char* vehicle_file_name_input);
		static void do_load_vehicle(std::string& selected_vehicle_file);
	};
}