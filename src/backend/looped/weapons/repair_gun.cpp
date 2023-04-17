#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::weapons_repair_gun()
	{
		if (g.weapons.custom_weapon == CustomWeapon::REPAIR_GUN && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Entity entity;

					if (entity::raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(entity))
						{
							vehicle::repair(entity);
						}
						else
						{
							g_notification_service->push_warning("Weapons", "Entity is not a vehicle.");
						}
					}
					else
						g_notification_service->push_warning("Weapons", "No entity found.");
				}
			}
		}
	}
}