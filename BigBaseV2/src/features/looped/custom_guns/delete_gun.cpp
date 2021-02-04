#include "features.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void features::delete_gun()
	{
		bool bDeleteGun = g_settings.options["custom_gun"]["type"] == 1;

		if (bDeleteGun)
		{
			Hash currWeapon;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), &currWeapon, 1);

			if (currWeapon != RAGE_JOAAT("weapon_pistol") && currWeapon != RAGE_JOAAT("weapon_pistol_mk2")) return;

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(g_playerId, true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					Entity entity;

					if (func::raycast_entity(&entity))
					{
						if (ENTITY::IS_ENTITY_A_PED(entity) && PED::IS_PED_A_PLAYER(entity))
						{
							notify::above_map("You can't delete player entities!");
						}
						else
						{
							Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), true);
							Vector3 entLoc = ENTITY::GET_ENTITY_COORDS(entity, true);
							double dist = func::distance_between_vectors(player, entLoc);

							if (dist > 500)
							{
								notify::above_map("Entity is too far.");
							}
							else
							{
								if (func::take_control_of_entity(entity))
								{
									func::delete_entity(entity);
								}
								else notify::above_map("~r~Failed to take control of entity.");
							}
						}
					}
					else features::notify::above_map("No entity found.");
				}
			}
		}
	}
}