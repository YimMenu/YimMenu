#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "core/enums.hpp"
#include "natives.hpp"
#include "hooking.hpp"
#include "gta_util.hpp"
#include <network/Network.hpp>

namespace big
{
	void looped::weapons_clown_gun()
	{
		bool bClownGun = g.weapons.custom_weapon == CustomWeapon::CLOWN_GUN;

		if (bClownGun)
		{
			if (g.weapons.clownshoot)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
						if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
						{
							Vector3 vec0, vec1;
							Entity indx = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self::ped, 0);
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY("muz_clown", indx, 3.5, 0.f, 0.f, 0.f, 180.f, 0.f, 1.f, true, true, true);

						}
					}
				}
			}
			if (g.weapons.clownhit)
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
						if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
						{
							Vector3 c;
							WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(self::ped, &c);
							GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
							GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("muz_clown", c.x, c.y, c.z, 0.f, 0.f, 180.f, 0.f, 1.f, true, true, true);

						}
					}
				}
			}
		}
	}
}
