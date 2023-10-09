#include "backend/looped_command.hpp"
#include "core/settings.hpp"

#include <bitset>
#include <weapon/CAmmoInfo.hpp>
#include <weapon/CAmmoRocketInfo.hpp>
#include <weapon/CWeaponInfo.hpp>

namespace big
{
	class custom_vehicle_weapon : looped_command
	{
		using looped_command::looped_command;
		using vehicle_ammo_setting = struct menu_settings::vehicle::vehicle_ammo_special;
		using CWeaponInfoFlags     = std::bitset<192>;

		// rocket

		CWeaponInfo* m_rocket_weapon_info = nullptr;

		float m_rocket_reload_time_mp          = 0;
		float m_rocket_reload_time_sp          = 0;
		float m_rocket_launch_speed            = 0;
		float m_rocket_range                   = 0;
		float m_rocket_lock_on_range           = 0;
		float m_rocket_time_before_homing      = 0;
		float m_rocket_time_between_shots      = 0;
		float m_rocket_alternate_wait_time     = 0;
		float m_rocket_lifetime                = 0;
		CWeaponInfoFlags m_rocket_weapon_flags = 0;
		CHomingRocketParams m_rocket_homing_params{};

		virtual void on_tick() override
		{
			if (g_local_player == nullptr || g_local_player->m_weapon_manager == nullptr
			    || g_local_player->m_weapon_manager->m_vehicle_weapon_info == nullptr
			    || g_local_player->m_weapon_manager->m_vehicle_weapon_info->m_ammo_info == nullptr)
				return;

			CWeaponInfo* weapon_info = g_local_player->m_weapon_manager->m_vehicle_weapon_info;

			if (is_weapon_rocket(weapon_info))
			{
				if (m_rocket_weapon_info != weapon_info)
				{
					restore_rocket();
					backup_rocket(weapon_info);
				}
				apply_rocket(g.vehicle.vehicle_ammo_special);
			}
		}

		virtual void on_disable() override
		{
			restore_rocket();
		}

		CWeaponInfoFlags& weapon_flags(CWeaponInfo* weapon_info)
		{
			return *((CWeaponInfoFlags*)((char*)weapon_info + 0x900));
		}

		bool is_weapon_rocket(const CWeaponInfo* weapon_info)
		{
			if (weapon_info->m_fire_type != eFireType::ProjectTile)
				return false;
			// this is to differentiate missiles from turrets, mortars and barrage
			CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)weapon_info->m_ammo_info;
			uint32_t trail_hash          = rocket_info->m_m_trail_fx_hash;
			return (trail_hash == RAGE_JOAAT("proj_rpg_trail") || trail_hash == RAGE_JOAAT("proj_xm_thruster_rpg_trail"));
		}

		void restore_rocket()
		{
			if (m_rocket_weapon_info != nullptr)
			{
				m_rocket_weapon_info->m_reload_time_mp      = m_rocket_reload_time_mp;
				m_rocket_weapon_info->m_reload_time_sp      = m_rocket_reload_time_sp;
				m_rocket_weapon_info->m_weapon_range        = m_rocket_range;
				m_rocket_weapon_info->m_lock_on_range       = m_rocket_lock_on_range;
				m_rocket_weapon_info->m_time_between_shots  = m_rocket_time_between_shots;
				m_rocket_weapon_info->m_alternate_wait_time = m_rocket_alternate_wait_time;

				weapon_flags(m_rocket_weapon_info) = m_rocket_weapon_flags;

				CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)m_rocket_weapon_info->m_ammo_info;

				rocket_info->m_launch_speed       = m_rocket_launch_speed;
				rocket_info->m_time_before_homing = m_rocket_time_before_homing;
				rocket_info->m_lifetime           = m_rocket_lifetime;

				rocket_info->m_homing_rocket_params = m_rocket_homing_params;

				m_rocket_weapon_info = nullptr;
			}
		}

		void backup_rocket(CWeaponInfo* weapon_info)
		{
			m_rocket_weapon_info = weapon_info;

			m_rocket_reload_time_mp      = weapon_info->m_reload_time_mp;
			m_rocket_reload_time_sp      = weapon_info->m_reload_time_sp;
			m_rocket_range               = weapon_info->m_weapon_range;
			m_rocket_lock_on_range       = weapon_info->m_lock_on_range;
			m_rocket_time_between_shots  = weapon_info->m_time_between_shots;
			m_rocket_alternate_wait_time = weapon_info->m_alternate_wait_time;

			m_rocket_weapon_flags = weapon_flags(weapon_info);

			CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)weapon_info->m_ammo_info;

			m_rocket_launch_speed       = rocket_info->m_launch_speed;
			m_rocket_time_before_homing = rocket_info->m_time_before_homing;
			m_rocket_lifetime           = rocket_info->m_lifetime;

			m_rocket_homing_params = rocket_info->m_homing_rocket_params;
		}

		void apply_rocket(const vehicle_ammo_setting& g_vehicle_ammo_settings)
		{
			m_rocket_weapon_info->m_reload_time_mp      = g_vehicle_ammo_settings.rocket_reload_time;
			m_rocket_weapon_info->m_reload_time_sp      = g_vehicle_ammo_settings.rocket_reload_time;
			m_rocket_weapon_info->m_weapon_range        = g_vehicle_ammo_settings.rocket_range;
			m_rocket_weapon_info->m_lock_on_range       = g_vehicle_ammo_settings.rocket_lock_on_range;
			m_rocket_weapon_info->m_time_between_shots  = g_vehicle_ammo_settings.rocket_time_between_shots;
			m_rocket_weapon_info->m_alternate_wait_time = g_vehicle_ammo_settings.rocket_alternate_wait_time;

			CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)m_rocket_weapon_info->m_ammo_info;

			rocket_info->m_launch_speed       = g_vehicle_ammo_settings.rocket_launch_speed;
			rocket_info->m_time_before_homing = g_vehicle_ammo_settings.rocket_time_before_homing;
			rocket_info->m_lifetime           = g_vehicle_ammo_settings.rocket_lifetime;

			if (g_vehicle_ammo_settings.rocket_improve_tracking)
			{
				rocket_info->m_homing_rocket_params.m_should_use_homing_params_from_info              = true;
				rocket_info->m_homing_rocket_params.m_turn_rate_modifier                              = 4.0;
				rocket_info->m_homing_rocket_params.m_pitch_yaw_roll_clamp                            = 8.5;
				rocket_info->m_homing_rocket_params.m_default_homing_rocket_break_lock_angle          = 0.2;
				rocket_info->m_homing_rocket_params.m_default_homing_rocket_break_lock_angle_close    = 0.6;
				rocket_info->m_homing_rocket_params.m_default_homing_rocket_break_lock_close_distance = 20.0;
				rocket_info->m_homing_rocket_params.m_time_before_starting_homing                     = 0.15;
				weapon_flags(m_rocket_weapon_info)[152]                                               = 1;
			}
			else
			{
				rocket_info->m_homing_rocket_params = m_rocket_homing_params;
				weapon_flags(m_rocket_weapon_info)  = m_rocket_weapon_flags;
			}
		}
	};
	custom_vehicle_weapon g_custom_vehicle_weapon("customvehweaps", "Custom Vehicle Weapons", "Replaces the current vehicle weapons with custom ones.",
	    g.vehicle.vehicle_ammo_special.enabled);
}
