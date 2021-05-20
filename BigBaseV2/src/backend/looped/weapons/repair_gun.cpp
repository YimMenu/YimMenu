#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"
#include "util/notify.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void looped::weapons_repair_gun()
	{
		bool bRepairGun = g.weapons.custom_weapon == CustomWeapon::REPAIR_GUN;

		if (bRepairGun)
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					Entity entity;

					if (entity::raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(entity))
						{
							VEHICLE::SET_VEHICLE_FIXED(entity);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(entity);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(entity, 0.f);
						}
						else
						{
							notify::above_map("Entity is not a vehicle.");
						}
					}
					else notify::above_map("No entity found.");
				}
			}
		}
	}
}