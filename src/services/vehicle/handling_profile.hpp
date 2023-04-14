#pragma once
#include "vehicle/CVehicle.hpp"

// Register to_json/from_json for these GTA classes
namespace rage
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(rage::fvector3, x, y, z)
}
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CHandlingData, m_mass, m_initial_drag_coeff, m_downforce_multiplier, m_centre_of_mass, m_inertia_mult, m_buoyancy, m_drive_bias_rear, m_drive_bias_front, m_acceleration, m_initial_drive_gears, m_drive_inertia, m_upshift, m_downshift, m_initial_drive_force, m_drive_max_flat_velocity, m_initial_drive_max_flat_vel, m_brake_force, m_brake_bias_front, m_brake_bias_rear, m_handbrake_force, m_steering_lock, m_steering_lock_ratio, m_traction_curve_max, m_traction_curve_lateral, m_traction_curve_min, m_traction_curve_ratio, m_curve_lateral, m_curve_lateral_ratio, m_traction_spring_delta_max, m_traction_spring_delta_max_ratio, m_low_speed_traction_loss_mult, m_camber_stiffness, m_traction_bias_front, m_traction_bias_rear, m_traction_loss_mult, m_suspension_force, m_suspension_comp_damp, m_suspension_rebound_damp, m_suspension_upper_limit, m_suspension_lower_limit, m_suspension_raise, m_suspension_bias_front, m_suspension_bias_rear, m_anti_rollbar_force, m_anti_rollbar_bias_front, m_anti_rollbar_bias_rear, m_roll_centre_height_front, m_roll_centre_height_rear, m_collision_damage_mult)

namespace big
{
	class handling_profile final
	{
	public:
		handling_profile(CVehicle* vehicle);
		handling_profile() = default;

		void apply_to(CVehicle* vehicle, bool restore_hash = true) const;

	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(handling_profile, m_gravity, m_handling_data)

	private:
		float m_gravity;
		CHandlingData m_handling_data;
	};
}