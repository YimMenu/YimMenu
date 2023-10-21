#pragma once

#define ROCKET_LAUNCH_SPEED 1200
#define ROCKET_RANGE 1000
#define ROCKET_LOCK_ON_RANGE 500
#define ROCKET_TIME_BEFORE_HOMING 0.75
#define ROCKET_LIFETIME 15

namespace big
{
	inline struct g_vehicle_ammo_special
	{
		bool enabled                 = false;
		bool rocket_improve_tracking = true;

		float rocket_launch_speed       = ROCKET_LAUNCH_SPEED;
		float rocket_range              = ROCKET_RANGE;
		float rocket_lock_on_range      = ROCKET_LOCK_ON_RANGE;
		float rocket_time_before_homing = ROCKET_TIME_BEFORE_HOMING;
		float rocket_lifetime           = ROCKET_LIFETIME;

		float m_rocket_launch_speed       = 0;
		float m_rocket_range              = 0;
		float m_rocket_lock_on_range      = 0;
		float m_rocket_time_before_homing = 0;
		float m_rocket_lifetime           = 0;
	} g_vehicle_ammo_special{};
}