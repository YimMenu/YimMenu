#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "util/teleport.hpp"

namespace big
{
	void looped::weapons_tp_gun()
	{
		if (g.weapons.custom_weapon == CustomWeapon::TP_GUN && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Vector3 c;
					entity::raycast(&c);
					teleport::to_coords(c);
				}
			}
		}
	}
}