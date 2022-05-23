#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastInfiniteAmmo = false;

	void looped::weapons_infinite_ammo()
	{
		bool bInfiniteAmmo = g->weapons.infinite_ammo;

		if (bInfiniteAmmo || (!bInfiniteAmmo && bInfiniteAmmo != bLastInfiniteAmmo))
		{
			WEAPON::SET_PED_INFINITE_AMMO(self::ped, g->weapons.infinite_ammo, NULL);

			bLastInfiniteAmmo = g->weapons.infinite_ammo;
		}
	}
}