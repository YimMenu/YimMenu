#include "backend/looped_command.hpp"

namespace big
{
	class custom_vehicle_weapon : looped_command
	{
		using looped_command::looped_command;
		using vehicle_ammo_setting = struct menu_settings::vehicle::vehicle_ammo_special;
		using CWeaponInfoFlags = std::bitset<192>;
		// mg
		CWeaponInfo* m_mg_weapon_info = nullptr;
		eDamageType m_mg_damage_type  = eDamageType::None;
		CWeaponInfo::sExplosion m_mg_explosion{};
		eAmmoSpecialType m_mg_ammo_type = eAmmoSpecialType::None;
		float m_mg_speed                = 0;
		float m_mg_time_between_shots   = 0;
		float m_mg_alternate_wait_time  = 0;
		float m_mg_range                = 0;
		// rocket
		CWeaponInfo* m_rocket_weapon_info  = nullptr;
		eDamageType m_rocket_damage_type       = eDamageType::Explosive;
		CWeaponInfoFlags m_rocket_weapon_flags = 0;
		float m_rocket_time_between_shots      = 0;
		float m_rocket_alternate_wait_time     = 0;
		float m_rocket_lock_on_range           = 0;
		float m_rocket_range                   = 0;
		float m_rocket_reload_time_mp          = 0;
		float m_rocket_reload_time_sp          = 0;
		// rocket ammo
		CAmmoRocketInfo::sExplosion m_rocket_explosion{};
		float m_rocket_lifetime           = 0;
		float m_rocket_launch_speed       = 0;
		float m_rocket_time_before_homing = 0;
		CHomingRocketParams m_rocket_homing_params{};

		virtual void on_tick() override
		{
			if (g_local_player == nullptr || g_local_player->m_weapon_manager == nullptr
			    || g_local_player->m_weapon_manager->m_vehicle_weapon_info == nullptr
			    || g_local_player->m_weapon_manager->m_vehicle_weapon_info->m_ammo_info == nullptr)
			{
				return;
			}

			CWeaponInfo* weapon_info = g_local_player->m_weapon_manager->m_vehicle_weapon_info;
			if (is_weapon_mg(weapon_info))
			{
				// check if the player changed their weapon
				if (m_mg_weapon_info != weapon_info)
				{
					// apply the original bullet and impact type to the old weapon
					restore_mg();

					// backup the bullet and impact type of the new weapon
					backup_mg(weapon_info);
				}

				// apply ammo type changes to the current weapon
				apply_mg(g.vehicle.vehicle_ammo_special);
			}
			else if (is_weapon_rocket(weapon_info))
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
			restore_mg();
			restore_rocket();
		}

		CWeaponInfoFlags& weapon_flags(CWeaponInfo* weapon_info)
		{
			return *((CWeaponInfoFlags*)((char*)weapon_info + 0x900));
		}

		bool is_weapon_mg(const CWeaponInfo* weapon_info)
		{
			return weapon_info->m_fire_type == eFireType::InstantHit || weapon_info->m_fire_type == eFireType::DelayedHit;
		}

		bool is_weapon_rocket(const CWeaponInfo* weapon_info)
		{
			if (weapon_info->m_fire_type != eFireType::ProjectTile)
				return false;
			// this is to differentiate missiles from turrets, mortars and barrage
			CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)weapon_info->m_ammo_info;
			uint32_t trail_hash          = rocket_info->m_m_trail_fx_hash;
			return (trail_hash == "proj_rpg_trail"_J || trail_hash == "proj_xm_thruster_rpg_trail"_J);
		}

		void restore_mg()
		{
			// apply the original bullet and impact type to the old weapon
			if (m_mg_weapon_info != nullptr)
			{
				m_mg_weapon_info->m_damage_type                    = m_mg_damage_type;
				m_mg_weapon_info->m_explosion                      = m_mg_explosion;
				m_mg_weapon_info->m_ammo_info->m_ammo_special_type = m_mg_ammo_type;
				m_mg_weapon_info->m_speed                          = m_mg_speed;
				m_mg_weapon_info->m_time_between_shots             = m_mg_time_between_shots;
				m_mg_weapon_info->m_alternate_wait_time            = m_mg_alternate_wait_time;
				m_mg_weapon_info->m_weapon_range                   = m_mg_range;
			}
		}

		void backup_mg(CWeaponInfo* weapon_info)
		{
			// backup the bullet and impact type of the new weapon
			m_mg_weapon_info         = weapon_info;
			m_mg_damage_type         = weapon_info->m_damage_type;
			m_mg_explosion           = weapon_info->m_explosion;
			m_mg_ammo_type           = weapon_info->m_ammo_info->m_ammo_special_type;
			m_mg_speed               = weapon_info->m_speed;
			m_mg_time_between_shots  = weapon_info->m_time_between_shots;
			m_mg_alternate_wait_time = weapon_info->m_alternate_wait_time;
			m_mg_range               = weapon_info->m_weapon_range;
		}

		void apply_mg(const vehicle_ammo_setting& g_vehicle_ammo_settings)
		{
			// apply ammo type changes to the current weapon
			eDamageType damage_type     = eDamageType::None;
			eExplosionTag explosion_tag = g_vehicle_ammo_settings.explosion_tag;
			eAmmoSpecialType ammo_type  = eAmmoSpecialType::None;

			if (explosion_tag == eExplosionTag::DONTCARE)
			{
				damage_type = m_mg_damage_type;
				ammo_type   = g_vehicle_ammo_settings.type;
			}
			else
			{
				damage_type = eDamageType::Explosive;
				ammo_type   = m_mg_ammo_type;
			}

			m_mg_weapon_info->m_damage_type = damage_type;

			CWeaponInfo::sExplosion explosion;
			explosion.m_default                                = explosion_tag;
			explosion.m_hit_bike                               = explosion_tag;
			explosion.m_hit_boat                               = explosion_tag;
			explosion.m_hit_car                                = explosion_tag;
			explosion.m_hit_plane                              = explosion_tag;
			explosion.m_hit_truck                              = explosion_tag;
			m_mg_weapon_info->m_explosion                      = explosion;
			m_mg_weapon_info->m_ammo_info->m_ammo_special_type = ammo_type;
			m_mg_weapon_info->m_speed                          = g_vehicle_ammo_settings.speed;
			m_mg_weapon_info->m_time_between_shots             = g_vehicle_ammo_settings.time_between_shots;
			m_mg_weapon_info->m_alternate_wait_time            = g_vehicle_ammo_settings.alternate_wait_time;
			m_mg_weapon_info->m_weapon_range                   = g_vehicle_ammo_settings.weapon_range;
		}

		void restore_rocket()
		{
			if (m_rocket_weapon_info != nullptr)
			{
				m_rocket_weapon_info->m_damage_type         = m_rocket_damage_type;
				m_rocket_weapon_info->m_time_between_shots  = m_rocket_time_between_shots;
				m_rocket_weapon_info->m_alternate_wait_time = m_rocket_alternate_wait_time;
				m_rocket_weapon_info->m_lock_on_range       = m_rocket_lock_on_range;
				m_rocket_weapon_info->m_weapon_range        = m_rocket_range;
				m_rocket_weapon_info->m_reload_time_mp      = m_rocket_reload_time_mp;
				m_rocket_weapon_info->m_reload_time_sp      = m_rocket_reload_time_sp;
				weapon_flags(m_rocket_weapon_info)          = m_rocket_weapon_flags;

				CAmmoRocketInfo* rocket_info        = (CAmmoRocketInfo*)m_rocket_weapon_info->m_ammo_info;
				rocket_info->m_explosion            = m_rocket_explosion;
				rocket_info->m_lifetime             = m_rocket_lifetime;
				rocket_info->m_launch_speed         = m_rocket_launch_speed;
				rocket_info->m_time_before_homing   = m_rocket_time_before_homing;
				rocket_info->m_homing_rocket_params = m_rocket_homing_params;
				m_rocket_weapon_info                = nullptr;
			}
		}

		void backup_rocket(CWeaponInfo* weapon_info)
		{
			m_rocket_weapon_info         = weapon_info;
			m_rocket_time_between_shots  = weapon_info->m_time_between_shots;
			m_rocket_alternate_wait_time = weapon_info->m_alternate_wait_time;
			m_rocket_lock_on_range       = weapon_info->m_lock_on_range;
			m_rocket_range               = weapon_info->m_weapon_range;
			m_rocket_reload_time_mp      = weapon_info->m_reload_time_mp;
			m_rocket_reload_time_sp      = weapon_info->m_reload_time_sp;
			m_rocket_weapon_flags        = weapon_flags(weapon_info);

			CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)weapon_info->m_ammo_info;
			m_rocket_explosion           = rocket_info->m_explosion;
			m_rocket_lifetime            = rocket_info->m_lifetime;
			m_rocket_launch_speed        = rocket_info->m_launch_speed;
			m_rocket_time_before_homing  = rocket_info->m_time_before_homing;
			m_rocket_homing_params       = rocket_info->m_homing_rocket_params;
		}

		void apply_rocket(const vehicle_ammo_setting& g_vehicle_ammo_settings)
		{
			m_rocket_weapon_info->m_damage_type         = eDamageType::Explosive;
			m_rocket_weapon_info->m_time_between_shots  = g_vehicle_ammo_settings.rocket_time_between_shots;
			m_rocket_weapon_info->m_alternate_wait_time = g_vehicle_ammo_settings.rocket_alternate_wait_time;
			m_rocket_weapon_info->m_weapon_range        = g_vehicle_ammo_settings.rocket_range;
			m_rocket_weapon_info->m_lock_on_range       = g_vehicle_ammo_settings.rocket_lock_on_range;
			m_rocket_weapon_info->m_reload_time_mp      = g_vehicle_ammo_settings.rocket_reload_time;
			m_rocket_weapon_info->m_reload_time_sp      = g_vehicle_ammo_settings.rocket_reload_time;

			CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)m_rocket_weapon_info->m_ammo_info;
			eExplosionTag explosion_tag  = g_vehicle_ammo_settings.rocket_explosion_tag;

			CAmmoRocketInfo::sExplosion explosion;
			explosion.m_default   = explosion_tag;
			explosion.m_hit_bike  = explosion_tag;
			explosion.m_hit_boat  = explosion_tag;
			explosion.m_hit_car   = explosion_tag;
			explosion.m_hit_plane = explosion_tag;
			explosion.m_hit_truck = explosion_tag;

			rocket_info->m_explosion          = explosion;
			rocket_info->m_lifetime           = g_vehicle_ammo_settings.rocket_lifetime;
			rocket_info->m_launch_speed       = g_vehicle_ammo_settings.rocket_launch_speed;
			rocket_info->m_time_before_homing = g_vehicle_ammo_settings.rocket_time_before_homing;

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
	custom_vehicle_weapon g_custom_vehicle_weapon("customvehweaps", "CUSTOM_VEH_WEAPONS", "CUSTOM_VEH_WEAPONS_DESC", g.vehicle.vehicle_ammo_special.enabled);
}
