#include "api/api.hpp"
#include "thread_pool.hpp"
#include "vehicle_service.hpp"

namespace big
{
	bool safe_to_modify()
	{
		return !(g_local_player == nullptr || g_local_player->m_vehicle == nullptr);
	}

	vehicle_service::vehicle_service()
	{
		g_vehicle_service = this;
	}

	vehicle_service::~vehicle_service()
	{
		g_vehicle_service = nullptr;
	}

	int vehicle_service::attempt_save()
	{
		if (g_local_player == nullptr || g_local_player->m_ped_task_flag & (int)ePedTask::TASK_FOOT || g_local_player->m_vehicle == nullptr)
			return -1;
		if (m_handling_backup.find(g_local_player->m_vehicle->m_handling->m_model_hash) != m_handling_backup.end())
			return 0;

		CHandlingData handling = *g_local_player->m_vehicle->m_handling;

		m_handling_backup.emplace(g_local_player->m_vehicle->m_handling->m_model_hash, handling);

		return 1;
	}

	std::string vehicle_service::get_active_profile(std::uint32_t hash)
	{
		if (auto it = this->m_active_profiles.find(hash); it != this->m_active_profiles.end())
			return it->second;
		return std::string("");
	}

	bool vehicle_service::get_by_share_code(const char* share_code)
	{
		static std::string up_to_date = "";

		if (m_search_status == SearchStatus::SEARCHING)
			return false;

		if (!safe_to_modify())
			return false;

		if (up_to_date == share_code)
			return true;
		m_search_status = SearchStatus::SEARCHING;

		nlohmann::json json;
		if (api::vehicle::handling::get_by_share_code(std::string(share_code), json))
		{
			if (json["data"].is_null())
				m_search_status = SearchStatus::NO_RESULT;
			else
			{
				auto& data = json["data"];

				HandlingProfile profile = HandlingProfile(data, g_local_player->m_vehicle->m_handling);

				if (auto it = m_handling_profiles.find(data["share_code"]); it != m_handling_profiles.end())
					it->second = profile;
				else m_handling_profiles.emplace(data["share_code"], profile);

				up_to_date = data["share_code"];
				m_search_status = SearchStatus::FOUND;
			}
		}
		else m_search_status = SearchStatus::FAILED;

		return true;
	}

	bool vehicle_service::handling_data_to_json(CHandlingData& handling_data, nlohmann::json& out)
	{
		out = {
			{ "centre_of_mass",
				{
					{ "x", handling_data.m_centre_of_mass.x },
					{ "y", handling_data.m_centre_of_mass.y },
					{ "z", handling_data.m_centre_of_mass.z }
				}
			},
			{ "inertia_mult",
				{
					{ "x", handling_data.m_inertia_mult.x },
					{ "y", handling_data.m_inertia_mult.y },
					{ "z", handling_data.m_inertia_mult.z }
				}
			},
			{ "mass", handling_data.m_mass },
			{ "downforce_mult", handling_data.m_downforce_multiplier },
			{ "buoyancy", handling_data.m_buoyancy },
			{ "drive_bias_rear", handling_data.m_drive_bias_rear },
			{ "drive_bias_front", handling_data.m_drive_bias_front },
			{ "acceleration_mult", handling_data.m_acceleration },
			{ "initial_drive_gears", handling_data.m_initial_drive_gears },
			{ "upshift", handling_data.m_upshift },
			{ "downshift", handling_data.m_downshift },
			{ "drive_inertia", handling_data.m_drive_inertia },
			{ "initial_drive_force", handling_data.m_initial_drive_force },
			{ "drive_max_flat_vel", handling_data.m_drive_max_flat_velocity },
			{ "brake_force", handling_data.m_brake_force },
			{ "brake_bias_front", handling_data.m_brake_bias_front },
			{ "brake_bias_rear", handling_data.m_brake_bias_rear },
			{ "handbrake_force", handling_data.m_handbrake_force },
			{ "steering_lock", handling_data.m_steering_lock },
			{ "steering_lock_ratio", handling_data.m_steering_lock_ratio },
			{ "traction_curve_max", handling_data.m_traction_curve_max },
			{ "traction_curve_lateral", handling_data.m_traction_curve_lateral },
			{ "traction_curve_min", handling_data.m_traction_curve_min },
			{ "traction_curve_ratio", handling_data.m_traction_curve_ratio },
			{ "traction_bias_front", handling_data.m_traction_bias_front },
			{ "traction_bias_rear", handling_data.m_traction_bias_rear },
			{ "traction_loss_mult", handling_data.m_traction_loss_mult },
			{ "curve_lateral", handling_data.m_curve_lateral },
			{ "curve_lateral_ratio", handling_data.m_curve_lateral_ratio },
			{ "traction_spring_delta_max", handling_data.m_traction_spring_delta_max },
			{ "traction_spring_delta_max_ratio", handling_data.m_traction_spring_delta_max_ratio },
			{ "low_speed_traction_loss_mult", handling_data.m_low_speed_traction_loss_mult },
			{ "camber_stiffness", handling_data.m_camber_stiffness },
			{ "suspension_force", handling_data.m_suspension_force },
			{ "suspension_comp_damp", handling_data.m_suspension_comp_damp },
			{ "suspension_rebound_damp", handling_data.m_suspension_rebound_damp },
			{ "suspension_upper_limit", handling_data.m_suspension_upper_limit },
			{ "suspension_lower_limit", handling_data.m_suspension_lower_limit },
			{ "suspension_raise", handling_data.m_suspension_raise },
			{ "suspension_bias_front", handling_data.m_suspension_bias_front },
			{ "suspension_bias_rear", handling_data.m_suspension_bias_rear },
			{ "anti_rollbar_force", handling_data.m_anti_rollbar_force },
			{ "anti_rollbar_bias_front", handling_data.m_anti_rollbar_bias_front },
			{ "anti_rollbar_bias_rear", handling_data.m_anti_rollbar_bias_rear },
			{ "roll_centre_height_front", handling_data.m_roll_centre_height_front },
			{ "roll_centre_height_rear", handling_data.m_roll_centre_height_rear }
		};

		return true;
	}

	bool vehicle_service::load_saved_profiles(bool force_update)
	{
		static bool busy = false;
		static uint32_t up_to_date = -1;

		if (busy)
			return false;

		if (!safe_to_modify())
			return false;
		
		if (!force_update && up_to_date == g_local_player->m_vehicle->m_handling->m_model_hash)
			return true;

		busy = true;

		g_thread_pool->push([&]()
		{
				nlohmann::json json;
				if (!api::vehicle::handling::get_saved_handling(g_local_player->m_vehicle->m_handling->m_model_hash, json) || json == nullptr)
				{
					busy = false;

					return;
				}

				this->m_saved_profiles.clear();
				for (auto& el : json["data"])
				{
					LOG(INFO) << "Registered profile '" << el["name"].get<std::string>().c_str() << "' with share code " << el["share_code"].get<std::string>().c_str();

					HandlingProfile profile = HandlingProfile(el, g_local_player->m_vehicle->m_handling);

					if (auto it = this->m_handling_profiles.find(el["share_code"]); it != this->m_handling_profiles.end())
						it->second = profile;
					else this->m_handling_profiles.emplace(el["share_code"], profile);
					this->m_saved_profiles.push_back(el["share_code"]);
				}

				busy = false;
				up_to_date = g_local_player->m_vehicle->m_handling->m_model_hash;
		});

		return false;
	}

	bool vehicle_service::publish_profile(const char* name, const char* description, std::string share_code)
	{
		if (this->m_publish_status == PublishStatus::SAVED)
			return true;
		if (this->m_publish_status == PublishStatus::SAVING)
			return false;

		if (!safe_to_modify()) return false;

		this->m_publish_status = PublishStatus::SAVING;

		CHandlingData handling_data = *g_local_player->m_vehicle->m_handling;
		uint32_t hash = handling_data.m_model_hash;

		nlohmann::json data;
		this->handling_data_to_json(handling_data, data);

		nlohmann::json json;
		if (!share_code.empty() && api::vehicle::handling::update(hash, name, description, share_code, data))
			m_publish_status = PublishStatus::SAVED;
		else if (api::vehicle::handling::create_profile(hash, name, description, data, json))
		{
			this->set_active_profile(hash, json["data"]["share_code"]);

			m_publish_status = PublishStatus::SAVED;
		}
		else m_publish_status = PublishStatus::FAILED;

		return false;
	}

	PublishStatus vehicle_service::publish_status(PublishStatus new_status)
	{
		if (new_status != PublishStatus::NONE)
			this->m_publish_status = new_status;

		return this->m_publish_status;
	}

	bool vehicle_service::restore_vehicle()
	{
		if (auto it = m_handling_backup.find(g_local_player->m_vehicle->m_handling->m_model_hash); it != m_handling_backup.end())
		{
			if (safe_to_modify())
				*g_local_player->m_vehicle->m_handling = it->second;
			this->m_active_profiles.erase(g_local_player->m_vehicle->m_handling->m_model_hash);

			return true;
		}

		return false;
	}

	void vehicle_service::set_active_profile(std::uint32_t hash, std::string share_code)
	{
		if (auto& it = this->m_active_profiles.find(hash); it != this->m_active_profiles.end())
			it->second = share_code;
		else
			this->m_active_profiles.emplace(hash, share_code);
	}

	void vehicle_service::set_handling_profile(HandlingProfile& profile)
	{
		if (!safe_to_modify())
			return;
		*g_local_player->m_vehicle->m_handling = profile.data;

		this->set_active_profile(profile.handling_hash, profile.share_code);
	}

	bool vehicle_service::update_mine(bool force_update)
	{
		static bool busy = false;
		static uint32_t up_to_date = 0;

		if (busy)
			return false;

		if (!safe_to_modify())
			return false;

		if (!force_update && up_to_date == g_local_player->m_vehicle->m_handling->m_model_hash)
			return true;

		busy = true;

		g_thread_pool->push([&] {
			nlohmann::json json;
			if (!api::vehicle::handling::get_my_handling(g_local_player->m_vehicle->m_handling->m_model_hash, json) || json == nullptr)
			{
				busy = false;

				return;
			}

			this->m_my_profiles.clear();
			for (auto& el : json["data"])
			{
				LOG(INFO) << "Registered profile '" << el["name"].get<std::string>().c_str() << "' with share code " << el["share_code"].get<std::string>().c_str();

				HandlingProfile profile = HandlingProfile(el, g_local_player->m_vehicle->m_handling);

				if (auto it = this->m_handling_profiles.find(el["share_code"]); it != this->m_handling_profiles.end())
					it->second = profile;
				else this->m_handling_profiles.emplace(el["share_code"], profile);
				this->m_my_profiles.push_back(el["share_code"]);
			}

			busy = false;
			up_to_date = g_local_player->m_vehicle->m_handling->m_model_hash;
		});

		return false;
	}
}