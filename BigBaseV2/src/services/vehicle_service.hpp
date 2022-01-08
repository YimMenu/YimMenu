#pragma once

namespace big
{
	enum class PublishStatus {
		NONE = -2,
		IDLE = -1,
		SAVING,
		SAVED,
		FAILED
	};

	enum class SearchStatus {
		NONE = -2,
		IDLE = -1,
		SEARCHING,
		FOUND,
		NO_RESULT,
		FAILED
	};

	class vehicle_service
	{
	private:

		class HandlingProfile
		{
		public:
			HandlingProfile(nlohmann::json &in, CHandlingData *handling_data)
			{
				this->handling_hash = in["handling_hash"];
				this->share_code = in["share_code"];
				
				this->name = in["name"];
				this->description = in["description"];

				nlohmann::json& data = in["data"];

				// Make sure we copy the values that we don't modify to prevent corrupting the handling
				this->data = *handling_data;

				this->data.m_centre_of_mass.x = data["centre_of_mass"]["x"];
				this->data.m_centre_of_mass.y = data["centre_of_mass"]["y"];
				this->data.m_centre_of_mass.z = data["centre_of_mass"]["z"];

				this->data.m_inertia_mult.x = data["inertia_mult"]["x"];
				this->data.m_inertia_mult.y = data["inertia_mult"]["y"];
				this->data.m_inertia_mult.z = data["inertia_mult"]["z"];

				this->data.m_mass = data["mass"];
				this->data.m_downforce_multiplier = data["downforce_mult"];
				this->data.m_buoyancy = data["buoyancy"];

				this->data.m_drive_bias_rear = data["drive_bias_rear"];
				this->data.m_drive_bias_front = data["drive_bias_front"];

				this->data.m_acceleration = data["acceleration_mult"];

				this->data.m_initial_drive_gears = data["initial_drive_gears"];
				this->data.m_upshift = data["upshift"];
				this->data.m_downshift = data["downshift"];

				this->data.m_drive_inertia = data["drive_inertia"];

				this->data.m_drive_max_flat_velocity = data["drive_max_flat_vel"];

				this->data.m_brake_force = data["brake_force"];
				this->data.m_brake_bias_front = data["brake_bias_front"];
				this->data.m_brake_bias_rear = data["brake_bias_rear"];
				this->data.m_handbrake_force = data["handbrake_force"];

				this->data.m_steering_lock = data["steering_lock"];
				this->data.m_steering_lock_ratio = data["steering_lock_ratio"];

				this->data.m_traction_curve_max = data["traction_curve_max"];
				this->data.m_traction_curve_lateral = data["traction_curve_lateral"];
				this->data.m_traction_curve_min = data["traction_curve_min"];
				this->data.m_traction_curve_ratio = data["traction_curve_ratio"];

				this->data.m_curve_lateral = data["curve_lateral"];
				this->data.m_curve_lateral_ratio = data["curve_lateral_ratio"];

				this->data.m_traction_spring_delta_max = data["traction_spring_delta_max"];
				this->data.m_traction_spring_delta_max_ratio = data["traction_spring_delta_max_ratio"];

				this->data.m_low_speed_traction_loss_mult = data["low_speed_traction_loss_mult"];
				this->data.m_camber_stiffness = data["camber_stiffness"];

				this->data.m_suspension_force = data["suspension_force"];
				this->data.m_suspension_comp_damp = data["suspension_comp_damp"];
				this->data.m_suspension_rebound_damp = data["suspension_rebound_damp"];
				this->data.m_suspension_upper_limit = data["suspension_upper_limit"];
				this->data.m_suspension_lower_limit = data["suspension_lower_limit"];
				this->data.m_suspension_raise = data["suspension_raise"];
				this->data.m_suspension_bias_front = data["suspension_bias_front"];
				this->data.m_suspension_bias_rear = data["suspension_bias_rear"];

				this->data.m_anti_rollbar_force = data["anti_rollbar_force"];
				this->data.m_anti_rollbar_bias_front = data["anti_rollbar_bias_front"];
				this->data.m_anti_rollbar_bias_rear = data["anti_rollbar_bias_rear"];

				this->data.m_roll_centre_height_front = data["roll_centre_height_front"];
				this->data.m_roll_centre_height_rear = data["roll_centre_height_rear"];
			}

			CHandlingData data;

			uint32_t handling_hash;
			std::string share_code;

			std::string name;
			std::string description;
		};

	public:
		vehicle_service();
		~vehicle_service();

		int attempt_save();
		std::string get_active_profile(std::uint32_t hash);
		bool get_by_share_code(const char* share_code);
		bool handling_data_to_json(CHandlingData& handling_data, nlohmann::json& out);
		bool load_saved_profiles(bool force_update = false);
		bool publish_profile(const char* name, const char* description, std::string share_code = "");
		PublishStatus publish_status(PublishStatus new_status = PublishStatus::NONE);
		bool restore_vehicle();
		void set_active_profile(std::uint32_t hash, std::string share_code);
		void set_handling_profile(HandlingProfile& profile);
		bool update_mine(bool force_update = false);

		inline static std::unordered_map<std::uint32_t, std::string> m_active_profiles;
		inline static std::vector<std::string> m_my_profiles;
		inline static std::vector<std::string> m_saved_profiles;
		inline static std::unordered_map<std::string, HandlingProfile> m_handling_profiles;

		SearchStatus m_search_status = SearchStatus::IDLE;
	private:
		PublishStatus m_publish_status = PublishStatus::IDLE;

		inline static std::unordered_map<Hash, CHandlingData> m_handling_backup;
	};

	inline vehicle_service* g_vehicle_service;
}