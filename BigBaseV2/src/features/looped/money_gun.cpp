#include "features.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	static bool busy = false;
	static Entity entity = 0;

	void features::money_gun()
	{
		bool bMoneyGun = g_settings.options["custom_gun"]["type"] == 3;

		if (bMoneyGun)
		{
			Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);

			Hash currWeapon;
			WEAPON::GET_CURRENT_PED_WEAPON(player, &currWeapon, 1);

			if (currWeapon != RAGE_JOAAT("weapon_pistol") && currWeapon != RAGE_JOAAT("weapon_pistol_mk2")) return;

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(g_playerId, true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 24) && !busy)
				{
					busy = true;

					QUEUE_JOB_BEGIN_CLAUSE(&)
					{
						if (functions::raycast_entity(&entity))
						{
							if (!ENTITY::IS_ENTITY_A_PED(entity) || !PED::IS_PED_A_PLAYER(entity))
							{
								busy = false;

								return;
							}

							Vector3 location = ENTITY::GET_ENTITY_COORDS(entity, true);

							features::functions::create_ambient_money(location, rand() % 500 + 2000);

							script::get_current()->yield(33ms);

							busy = false;
						}
					}QUEUE_JOB_END_CLAUSE
				}
			}
		}
	}
}