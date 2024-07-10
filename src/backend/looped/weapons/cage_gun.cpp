#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_cage_gun()
	{
		if (g.weapons.custom_weapon == CustomWeapon::CAGE_GUN && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Entity entity;

					if (entity::raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_A_PED(entity))
						{
							entity::cage_ped(entity);
						}
					}
					else
					{
						g_notification_service.push_error("CUSTOM_WEAPONS"_T.data(), "BACKEND_LOOPED_WEAPONS_CAGE_GUN_NO_ENTITY_FOUND"_T.data());
					}
				}
			}
		}
	}
}
