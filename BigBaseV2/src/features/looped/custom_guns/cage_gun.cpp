#include "features/custom_guns.hpp"
#include "features/notify.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void custom_guns::cage_gun()
	{
		bool bCageGun = g_settings.options["custom_gun"]["type"] == 5;

		if (bCageGun)
		{
			Hash currWeapon;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), &currWeapon, 1);

			if (currWeapon != RAGE_JOAAT("weapon_pistol") && currWeapon != RAGE_JOAAT("weapon_pistol_mk2")) return;

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(g_player.id, true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					Entity entity;

					if (func::raycast_entity(&entity))
					{
						if (ENTITY::IS_ENTITY_A_PED(entity))
						{
							func::cage_ped(entity);
						}
					}
					else notify::above_map("No entity found.");
				}
			}
		}
	}
}