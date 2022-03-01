#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void looped::weapons_repair_gun()
	{
		bool bRepairGun = g->weapons.custom_weapon == CustomWeapon::REPAIR_GUN;

		if (bRepairGun)
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::GET_PLAYER_INDEX(), true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
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
					else g_notification_service->push_warning("Weapons", "No entity found.");
				}
			}
		}
	}
}