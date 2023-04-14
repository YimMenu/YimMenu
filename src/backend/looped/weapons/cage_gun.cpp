#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::weapons_cage_gun()
	{
		bool bCageGun = g.weapons.custom_weapon == CustomWeapon::CAGE_GUN;

		if (bCageGun)
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
						g_notification_service->push_error("Weapons", "No entity found.");
				}
			}
		}
	}
}
