#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"
#include "util/notify.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };
	static Entity ent;

	void looped::weapons_steal_vehicle_gun()
	{
		bool bStealVehicleGun = g.weapons.custom_weapon == CustomWeapon::STEAL_VEHICLE_GUN;

		if (bStealVehicleGun)
		{
			Ped player = PLAYER::PLAYER_PED_ID();

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					if (entity::raycast(&ent))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
						{
							Ped ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ent, -1, 0);
							TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);

							PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), ent, -1);
						}
					}
					else notify::above_map("No entity found.");
				}
			}
		}
	}
}