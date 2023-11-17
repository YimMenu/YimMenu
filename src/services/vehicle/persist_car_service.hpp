#pragma once
#include "natives.hpp"

namespace big
{
	class persist_car_service
	{
	public:
		static constexpr auto vehicle_model_hash_key = "vehicle_model_hash";

		static std::vector<std::string> list_files(std::string folder_name = "");
		static std::vector<std::string> list_sub_folders();

		static Vehicle clone_ped_car(Vehicle vehicle);
		static void save_vehicle(Vehicle vehicle, std::string_view file_name, std::string folder_name);
		static nlohmann::json load_vehicle_json(std::string_view file_name, std::string folder_name);
		static Vehicle load_vehicle(std::string_view file_name, std::string folder_name = "", const std::optional<Vector3>& = std::nullopt);
		static void delete_vehicle(std::string_view file_name, std::string folder_name);
		static Vehicle spawn_vehicle_full(nlohmann::json vehicle_json, const std::optional<Vector3>& spawn_coords = std::nullopt, bool is_networked = true);

	private:
		static constexpr auto plate_text_key             = "plate_text";
		static constexpr auto plate_text_index_key       = "plate_text_index";
		static constexpr auto vehicle_extras_key         = "vehicle_extras";
		static constexpr auto vehicle_livery_key         = "vehicle_livery";
		static constexpr auto wheel_type_key             = "wheel_type";
		static constexpr auto wheel_color_key            = "wheel_color";
		static constexpr auto tire_smoke_color_key       = "tire_smoke_color";
		static constexpr auto tire_can_burst             = "tire_can_burst";
		static constexpr auto drift_tires                = "drift_tires";
		static constexpr auto vehicle_window_tint_key    = "vehicle_window_tint";
		static constexpr auto neon_lights_key            = "neon_lights";
		static constexpr auto neon_color_key             = "neon_color";
		static constexpr auto primary_color_key          = "primary_color";
		static constexpr auto custom_primary_color_key   = "custom_primary_color";
		static constexpr auto secondary_color_key        = "secondary_color";
		static constexpr auto custom_secondary_color_key = "custom_secondary_color";
		static constexpr auto pearlescent_color_key      = "pearlescent_color";
		static constexpr auto headlight_color_key        = "headlight_color";
		static constexpr auto interior_color_key         = "interior_color";
		static constexpr auto dash_color_key             = "dash_color";

		static nlohmann::json get_vehicle_json(Vehicle vehicle);
		static big::folder check_vehicle_folder(std::string folder_name = "");
	};
}