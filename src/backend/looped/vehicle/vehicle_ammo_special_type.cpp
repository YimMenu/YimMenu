#include "backend/looped/looped.hpp"

namespace big
{
	static CWeaponInfo* p_modified_vehicle_weapon          = nullptr;
	static eDamageType modified_vehicle_weapon_damage_type = eDamageType::None;
	static CWeaponInfo::sExplosion modified_vehicle_weapon_explosion{};
	static eAmmoSpecialType modified_vehicle_weapon_ammo_type = eAmmoSpecialType::None;
	static float modified_vehicle_weapon_speed                = 2000;
	static float modified_vehicle_weapon_time_between_shots   = 0.02;
	static float modified_vehicle_weapon_alternate_wait_time  = -1;
	static float modified_vehicle_weapon_weapon_range         = 180;

	static CWeaponInfo* p_modified_rocket_weapon          = nullptr;
	static CAmmoRocketInfo* p_modified_rocket_ammo        = nullptr;
	static eDamageType modified_rocket_weapon_damage_type = eDamageType::Explosive;
	static float modified_rocket_time_between_shots       = 1.5;
	static float modified_rocket_alternate_wait_time      = 1.5;
	static float modified_rocket_lock_on_range            = 300;
	static float modified_rocket_weapon_range             = 300;
	static float modified_rocket_reload_time_mp           = -1;
	static float modified_rocket_reload_time_sp           = -1;
	static CAmmoRocketInfo::sExplosion modified_rocket_explosion{};
	static float modified_rocket_lifetime           = 5;
	static float modified_rocket_launch_speed       = 1250;
	static CHomingRocketParams modified_rocket_homing_params{};

	void looped::vehicle_ammo_special_type()
	{
		if (g_local_player == nullptr || g_local_player->m_weapon_manager == nullptr || g_local_player->m_weapon_manager->m_vehicle_weapon_info == nullptr
		    || g_local_player->m_weapon_manager->m_vehicle_weapon_info->m_ammo_info == nullptr)
		{
			return;
		}

		if (g.vehicle.vehicle_ammo_special.toggle)
		{
			CWeaponInfo* weapon_info = g_local_player->m_weapon_manager->m_vehicle_weapon_info;

			if (weapon_info->m_fire_type == eFireType::ProjectTile)
			{
				CAmmoRocketInfo* rocket_info = (CAmmoRocketInfo*)weapon_info->m_ammo_info;
				// check if the player changed their weapon
				if (p_modified_rocket_weapon != weapon_info)
				{
					// apply the original bullet and impact type to the old weapon
					if (p_modified_rocket_weapon != nullptr && p_modified_rocket_ammo != nullptr)
					{
						p_modified_rocket_weapon->m_damage_type         = modified_rocket_weapon_damage_type;
						p_modified_rocket_weapon->m_time_between_shots  = modified_rocket_time_between_shots;
						p_modified_rocket_weapon->m_alternate_wait_time = modified_rocket_alternate_wait_time;
						p_modified_rocket_weapon->m_lock_on_range       = modified_rocket_lock_on_range;
						p_modified_rocket_weapon->m_weapon_range        = modified_rocket_weapon_range;
						p_modified_rocket_weapon->m_reload_time_mp      = modified_rocket_reload_time_mp;
						p_modified_rocket_weapon->m_reload_time_sp      = modified_rocket_reload_time_sp;

						p_modified_rocket_ammo->m_explosion            = modified_rocket_explosion;
						p_modified_rocket_ammo->m_lifetime             = modified_rocket_lifetime;
						p_modified_rocket_ammo->m_launch_speed         = modified_rocket_launch_speed;
						p_modified_rocket_ammo->m_homing_rocket_params = modified_rocket_homing_params;
					}

					// backup the bullet and impact type of the new weapon
					p_modified_rocket_weapon            = weapon_info;
					modified_rocket_weapon_damage_type  = weapon_info->m_damage_type;
					modified_rocket_time_between_shots  = weapon_info->m_time_between_shots;
					modified_rocket_alternate_wait_time = weapon_info->m_alternate_wait_time;
					modified_rocket_lock_on_range       = weapon_info->m_lock_on_range;
					modified_rocket_weapon_range        = weapon_info->m_weapon_range;
					modified_rocket_reload_time_mp      = weapon_info->m_reload_time_mp;
					modified_rocket_reload_time_sp      = weapon_info->m_reload_time_sp;
					p_modified_rocket_ammo              = rocket_info;
					modified_rocket_explosion           = rocket_info->m_explosion;
					modified_rocket_lifetime            = rocket_info->m_lifetime;
					modified_rocket_launch_speed        = rocket_info->m_launch_speed;
					modified_rocket_homing_params       = rocket_info->m_homing_rocket_params;
				}

				// apply ammo type changes to the current weapon
				weapon_info->m_damage_type         = eDamageType::Explosive;
				weapon_info->m_time_between_shots  = g.vehicle.vehicle_ammo_special.rocket_time_between_shots;
				weapon_info->m_alternate_wait_time = g.vehicle.vehicle_ammo_special.rocket_alternate_wait_time;
				weapon_info->m_weapon_range        = g.vehicle.vehicle_ammo_special.rocket_lock_on_range;
				weapon_info->m_lock_on_range       = g.vehicle.vehicle_ammo_special.rocket_lock_on_range;
				weapon_info->m_reload_time_mp      = g.vehicle.vehicle_ammo_special.rocket_reload_time;
				weapon_info->m_reload_time_sp      = g.vehicle.vehicle_ammo_special.rocket_reload_time;

				eExplosionTag explosion_tag = g.vehicle.vehicle_ammo_special.rocket_explosion_tag;

				CAmmoRocketInfo::sExplosion explosion;
				explosion.m_default   = explosion_tag;
				explosion.m_hit_bike  = explosion_tag;
				explosion.m_hit_boat  = explosion_tag;
				explosion.m_hit_car   = explosion_tag;
				explosion.m_hit_plane = explosion_tag;
				explosion.m_hit_truck = explosion_tag;

				rocket_info->m_explosion    = explosion;
				rocket_info->m_lifetime     = g.vehicle.vehicle_ammo_special.rocket_lifetime;
				rocket_info->m_launch_speed = g.vehicle.vehicle_ammo_special.rocket_launch_speed;

				if (g.vehicle.vehicle_ammo_special.rocket_improve_tracking)
				{
					rocket_info->m_homing_rocket_params.m_should_use_homing_params_from_info              = true;
					rocket_info->m_homing_rocket_params.m_time_before_starting_homing                     = 0.1;
					rocket_info->m_homing_rocket_params.m_turn_rate_modifier                              = 4.0;
					rocket_info->m_homing_rocket_params.m_pitch_yaw_roll_clamp                            = 8.5;
					rocket_info->m_homing_rocket_params.m_default_homing_rocket_break_lock_angle          = 0.2;
					rocket_info->m_homing_rocket_params.m_default_homing_rocket_break_lock_angle_close    = 0.6;
					rocket_info->m_homing_rocket_params.m_default_homing_rocket_break_lock_close_distance = 20.0;
				}
				else
				{
					rocket_info->m_homing_rocket_params = modified_rocket_homing_params;
				}
			}
			else if (weapon_info->m_fire_type == eFireType::InstantHit || weapon_info->m_fire_type == eFireType::DelayedHit)
			{
				// check if the player changed their weapon
				if (p_modified_vehicle_weapon != weapon_info)
				{
					// apply the original bullet and impact type to the old weapon
					if (p_modified_vehicle_weapon != nullptr)
					{
						p_modified_vehicle_weapon->m_damage_type = modified_vehicle_weapon_damage_type;
						p_modified_vehicle_weapon->m_explosion   = modified_vehicle_weapon_explosion;
						p_modified_vehicle_weapon->m_ammo_info->m_ammo_special_type = modified_vehicle_weapon_ammo_type;
						p_modified_vehicle_weapon->m_speed                          = modified_vehicle_weapon_speed;
						p_modified_vehicle_weapon->m_time_between_shots  = modified_vehicle_weapon_time_between_shots;
						p_modified_vehicle_weapon->m_alternate_wait_time = modified_vehicle_weapon_alternate_wait_time;
						p_modified_vehicle_weapon->m_weapon_range        = modified_vehicle_weapon_weapon_range;
					}

					// backup the bullet and impact type of the new weapon
					p_modified_vehicle_weapon                   = weapon_info;
					modified_vehicle_weapon_damage_type         = weapon_info->m_damage_type;
					modified_vehicle_weapon_explosion           = weapon_info->m_explosion;
					modified_vehicle_weapon_ammo_type           = weapon_info->m_ammo_info->m_ammo_special_type;
					modified_vehicle_weapon_speed               = weapon_info->m_speed;
					modified_vehicle_weapon_time_between_shots  = weapon_info->m_time_between_shots;
					modified_vehicle_weapon_alternate_wait_time = weapon_info->m_alternate_wait_time;
					modified_vehicle_weapon_weapon_range        = weapon_info->m_weapon_range;
				}

				// apply ammo type changes to the current weapon
				eDamageType damage_type     = eDamageType::None;
				eExplosionTag explosion_tag = g.vehicle.vehicle_ammo_special.explosion_tag;
				eAmmoSpecialType ammo_type  = eAmmoSpecialType::None;

				if (explosion_tag == eExplosionTag::DONTCARE)
				{
					damage_type = modified_vehicle_weapon_damage_type;
					ammo_type   = g.vehicle.vehicle_ammo_special.type;
				}
				else
				{
					damage_type = eDamageType::Explosive;
					ammo_type   = modified_vehicle_weapon_ammo_type;
				}

				weapon_info->m_damage_type = damage_type;

				CWeaponInfo::sExplosion explosion;
				explosion.m_default      = explosion_tag;
				explosion.m_hit_bike     = explosion_tag;
				explosion.m_hit_boat     = explosion_tag;
				explosion.m_hit_car      = explosion_tag;
				explosion.m_hit_plane    = explosion_tag;
				explosion.m_hit_truck    = explosion_tag;
				weapon_info->m_explosion = explosion;

				weapon_info->m_ammo_info->m_ammo_special_type = ammo_type;
				weapon_info->m_speed                          = g.vehicle.vehicle_ammo_special.speed;
				weapon_info->m_time_between_shots             = g.vehicle.vehicle_ammo_special.time_between_shots;
				weapon_info->m_alternate_wait_time            = g.vehicle.vehicle_ammo_special.alternate_wait_time;
				weapon_info->m_weapon_range                   = g.vehicle.vehicle_ammo_special.weapon_range;
			}
		}
		else
		{
			// apply the original bullet and impact type to the weapon
			// when the ammo type feature is off
			if (p_modified_vehicle_weapon != nullptr)
			{
				p_modified_vehicle_weapon->m_damage_type                    = modified_vehicle_weapon_damage_type;
				p_modified_vehicle_weapon->m_explosion                      = modified_vehicle_weapon_explosion;
				p_modified_vehicle_weapon->m_ammo_info->m_ammo_special_type = modified_vehicle_weapon_ammo_type;
				p_modified_vehicle_weapon->m_speed                          = modified_vehicle_weapon_speed;
				p_modified_vehicle_weapon->m_time_between_shots  = modified_vehicle_weapon_time_between_shots;
				p_modified_vehicle_weapon->m_alternate_wait_time = modified_vehicle_weapon_alternate_wait_time;
				p_modified_vehicle_weapon->m_weapon_range        = modified_vehicle_weapon_weapon_range;
				p_modified_vehicle_weapon                        = nullptr;
			}
			if (p_modified_rocket_weapon != nullptr)
			{
				p_modified_rocket_weapon->m_damage_type         = modified_rocket_weapon_damage_type;
				p_modified_rocket_weapon->m_time_between_shots  = modified_rocket_time_between_shots;
				p_modified_rocket_weapon->m_alternate_wait_time = modified_rocket_alternate_wait_time;
				p_modified_rocket_weapon->m_lock_on_range       = modified_rocket_lock_on_range;
				p_modified_rocket_weapon->m_weapon_range        = modified_rocket_weapon_range;
				p_modified_rocket_weapon->m_reload_time_mp      = modified_rocket_reload_time_mp;
				p_modified_rocket_weapon->m_reload_time_sp      = modified_rocket_reload_time_sp;
				p_modified_rocket_weapon                        = nullptr;

				if (p_modified_rocket_ammo == nullptr)
					return;

				p_modified_rocket_ammo->m_explosion            = modified_rocket_explosion;
				p_modified_rocket_ammo->m_lifetime             = modified_rocket_lifetime;
				p_modified_rocket_ammo->m_launch_speed         = modified_rocket_launch_speed;
				p_modified_rocket_ammo->m_homing_rocket_params = modified_rocket_homing_params;
				p_modified_rocket_ammo = nullptr;
			}
		}
	}
}
