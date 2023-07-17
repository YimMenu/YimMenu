#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::weapons_tp_gun()
	{
		if (g.weapons.custom_weapon == CustomWeapon::TP_GUN && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
			Vector3 c; entity::raycast(&c);

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					ENTITY::SET_ENTITY_COORDS(self::ped, c.x, c.y, c.z, 0, 0, 0, 0);
				}
			}
		}
	}
}