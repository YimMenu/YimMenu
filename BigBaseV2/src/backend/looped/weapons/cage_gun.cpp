#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"
#include "util/notify.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void looped::weapons_cage_gun()
	{
		bool bCageGun = g.weapons.custom_weapon == CustomWeapon::CAGE_GUN;

		if (bCageGun)
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
						if (ENTITY::IS_ENTITY_A_PED(entity))
						{
							entity::cage_ped(entity);
						}
					}
					else notify::above_map("No entity found.");
				}
			}
		}
	}
}