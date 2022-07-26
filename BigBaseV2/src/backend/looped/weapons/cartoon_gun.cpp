#include "backend/looped/looped.hpp"
#include "util/ptfx.hpp"

namespace big
{
	void looped::weapons_cartoon_gun()
	{
		bool bCartoonGun = g->weapons.custom_weapon == CustomWeapon::CARTOON_GUN;

		if (bCartoonGun)
		{
			if (PED::IS_PED_SHOOTING(self::ped))
			{
				ptfx::cartoongun();
			}
		}
	}
}
