#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"

namespace big
{
	static Entity ent;

	void looped::weapons_steal_vehicle_gun()
	{
		if (const bool bStealVehicleGun = g.weapons.custom_weapon == CustomWeapon::STEAL_VEHICLE_GUN; bStealVehicleGun)
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					if (entity::raycast(&ent))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
						{
							for (size_t i = 0; i < 8 && !VEHICLE::IS_VEHICLE_SEAT_FREE(ent, -1, 0); i++)
							{
								const auto ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ent, -1, 0);
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);

								script::get_current()->yield(100ms);
							}

							PED::SET_PED_INTO_VEHICLE(self::ped, ent, -1);
						}
						else
							g_notification_service->push_warning("Weapons", "Entity is not a vehicle.");
					}
					else
						g_notification_service->push_warning("Weapons", "No entity found.");
				}
			}
		}
	}
}
