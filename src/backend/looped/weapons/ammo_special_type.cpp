#include "backend/looped/looped.hpp"

namespace big
{
	static CWeaponInfo* p_modified_weapon          = nullptr;
	static eDamageType modified_weapon_damage_type = eDamageType::None;
	static CWeaponInfo::sExplosion modified_weapon_explosion{};
	static eAmmoSpecialType modified_weapon_ammo_type = eAmmoSpecialType::None;

	void looped::weapons_ammo_special_type()
	{
		if (g_local_player == nullptr || g_local_player->m_weapon_manager == nullptr || g_local_player->m_weapon_manager->m_weapon_info == nullptr
		    || g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info == nullptr)
		{
			return;
		}

		if (g.weapons.ammo_special.toggle)
		{
			CWeaponInfo* weapon_info = g_local_player->m_weapon_manager->m_weapon_info;

			// check if the player changed their weapon
			if (p_modified_weapon != weapon_info)
			{
				// apply the original bullet and impact type to the old weapon
				if (p_modified_weapon != nullptr)
				{
					p_modified_weapon->m_damage_type                    = modified_weapon_damage_type;
					p_modified_weapon->m_explosion                      = modified_weapon_explosion;
					p_modified_weapon->m_ammo_info->m_ammo_special_type = modified_weapon_ammo_type;
				}

				// backup the bullet and impact type of the new weapon
				p_modified_weapon           = weapon_info;
				modified_weapon_damage_type = weapon_info->m_damage_type;
				modified_weapon_explosion   = weapon_info->m_explosion;
				modified_weapon_ammo_type   = weapon_info->m_ammo_info->m_ammo_special_type;
			}

			// apply ammo type changes to the current weapon
			eDamageType damage_type     = eDamageType::None;
			eExplosionTag explosion_tag = g.weapons.ammo_special.explosion_tag;
			eAmmoSpecialType ammo_type  = eAmmoSpecialType::None;

			if (explosion_tag == eExplosionTag::DONTCARE)
			{
				damage_type = modified_weapon_damage_type;
				ammo_type   = g.weapons.ammo_special.type;
			}
			else
			{
				damage_type = eDamageType::Explosive;
				ammo_type   = modified_weapon_ammo_type;
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
		}
		else if (p_modified_weapon != nullptr)
		{
			// apply the original bullet and impact type to the weapon
			// when the ammo type feature is off
			p_modified_weapon->m_damage_type                    = modified_weapon_damage_type;
			p_modified_weapon->m_explosion                      = modified_weapon_explosion;
			p_modified_weapon->m_ammo_info->m_ammo_special_type = modified_weapon_ammo_type;
			p_modified_weapon                                   = nullptr;
		}
	}
}
