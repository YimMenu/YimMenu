#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastInfiniteMag = false;

	void looped::weapons_infinite_mag()
	{
		bool bInfiniteMag = g->weapons.infinite_mag;

		if (bInfiniteMag || (!bInfiniteMag && bInfiniteMag != bLastInfiniteMag))
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, g->weapons.infinite_mag);

			bLastInfiniteMag = g->weapons.infinite_mag;
		}
	}
}