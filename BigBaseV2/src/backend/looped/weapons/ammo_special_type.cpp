#include "backend/looped/looped.hpp"

namespace big
{
	static CWeaponInfo* pModifiedWeapon = nullptr;
	static eDamageType modifiedWeaponDamageType = eDamageType::None;
	static eImpactType modifiedWeaponImpactType = eImpactType::DEFAULT_BULLETS;
	static eAmmoSpecialType modifiedWeaponAmmoType = eAmmoSpecialType::None;

	void looped::weapons_ammo_special_type()
	{
		if (
			g_local_player == nullptr ||
			g_local_player->m_weapon_manager == nullptr ||
			g_local_player->m_weapon_manager->m_weapon_info == nullptr ||
			g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info == nullptr
		) {
			return;
		}

		if (g->weapons.ammo_special.toggle) {
			CWeaponInfo* pWeapon = g_local_player->m_weapon_manager->m_weapon_info;

			// check if the player changed their weapon
			if (pModifiedWeapon != pWeapon) {
				// apply the original bullet and impact type to the old weapon
				if (pModifiedWeapon != nullptr) {
					pModifiedWeapon->m_damage_type = modifiedWeaponDamageType;
					pModifiedWeapon->m_impact_type = modifiedWeaponImpactType;
					pModifiedWeapon->m_ammo_info->m_ammo_special_type = modifiedWeaponAmmoType;
				}

				// backup the bullet and impact type of the new weapon
				pModifiedWeapon = pWeapon;
				modifiedWeaponDamageType = pWeapon->m_damage_type;
				modifiedWeaponImpactType = pWeapon->m_impact_type;
				modifiedWeaponAmmoType = pWeapon->m_ammo_info->m_ammo_special_type;
			}

			// apply ammo type changes to the current weapon
			eDamageType damageType = eDamageType::None;
			eImpactType impactType = g->weapons.ammo_special.impactType;
			eAmmoSpecialType ammoType = eAmmoSpecialType::None;

			if (impactType == eImpactType::DEFAULT_BULLETS) {
				damageType = modifiedWeaponDamageType;
				ammoType = g->weapons.ammo_special.type;
			}
			else {
				damageType = eDamageType::Explosive;
				ammoType = modifiedWeaponAmmoType;
			}

			pWeapon->m_damage_type = damageType;
			pWeapon->m_impact_type = impactType;
			pWeapon->m_ammo_info->m_ammo_special_type = ammoType;
		} else if (pModifiedWeapon != nullptr) {
			// apply the original bullet and impact type to the weapon
			// when the ammo type feature is off
			pModifiedWeapon->m_damage_type = modifiedWeaponDamageType;
			pModifiedWeapon->m_impact_type = modifiedWeaponImpactType;
			pModifiedWeapon->m_ammo_info->m_ammo_special_type = modifiedWeaponAmmoType;
			pModifiedWeapon = nullptr;
		}
	}
}