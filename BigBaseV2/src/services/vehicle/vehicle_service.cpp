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
		if (m_handling_backup.find(g_local_player->m_vehicle->m_handling_data->m_model_hash) != m_handling_backup.end())
			return 0;

		CHandlingData handling = *g_local_player->m_vehicle->m_handling_data;

		m_handling_backup.emplace(g_local_player->m_vehicle->m_handling_data->m_model_hash, handling);

		return 1;
	}

	std::string vehicle_service::get_active_profile(std::uint32_t hash)
	{
		if (auto it = this->m_active_profiles.find(hash); it != this->m_active_profiles.end())
			return it->second;
		return std::string("");
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

	bool vehicle_service::restore_vehicle()
	{
		if (auto it = m_handling_backup.find(g_local_player->m_vehicle->m_handling_data->m_model_hash); it != m_handling_backup.end())
		{
			if (safe_to_modify())
				*g_local_player->m_vehicle->m_handling_data = it->second;
			this->m_active_profiles.erase(g_local_player->m_vehicle->m_handling_data->m_model_hash);

			return true;
		}

		return false;
	}
}