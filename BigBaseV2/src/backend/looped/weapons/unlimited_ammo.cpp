#include "backend/looped/looped.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::self_unlimited_ammo()
	{
		bool bUnlimitedammo = g.weapons.unlimited_ammo;
		if (!bUnlimitedammo)
			return;

		Hash weaponHash;
		auto const ped = PLAYER::PLAYER_PED_ID();

		WEAPON::GET_CURRENT_PED_WEAPON(ped, &weaponHash, 1);
		if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED")) {
			WEAPON::GIVE_WEAPON_TO_PED(ped, weaponHash, 9999, false, false);
		}

	Hash cur;
	if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &cur, 1))
	{
		if (WEAPON::IS_WEAPON_VALID(cur))
		{
			int maxAmmo;
			if (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), cur, &maxAmmo))
			{
				WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), cur, maxAmmo, true);

				maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, 1);
				if (maxAmmo > 0)
					WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), cur, maxAmmo);
			}
		}
	}
	}
}