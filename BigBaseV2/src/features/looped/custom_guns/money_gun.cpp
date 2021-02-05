#include "features/custom_guns.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	static bool busy = false;
	static Entity entity = 0;

	void custom_guns::money_gun()
	{
		bool bMoneyGun = g_settings.options["custom_gun"]["type"] == 3;

		if (bMoneyGun)
		{
			Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

			Hash currWeapon;
			WEAPON::GET_CURRENT_PED_WEAPON(player, &currWeapon, 1);

			if (currWeapon != RAGE_JOAAT("weapon_pistol") && currWeapon != RAGE_JOAAT("weapon_pistol_mk2")) return;

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(g_player.id, true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 24) && !busy)
				{
					busy = true;

					g_fiber_pool->queue_job([&]
					{
						if (func::raycast_entity(&entity))
						{
							if (!ENTITY::IS_ENTITY_A_PED(entity) || !PED::IS_PED_A_PLAYER(entity))
							{
								busy = false;

								return;
							}

							Vector3 location = ENTITY::GET_ENTITY_COORDS(entity, true);

							func::create_ambient_money(location, rand() % 500 + 2000);

							script::get_current()->yield(33ms);

							busy = false;
						}
					});	
				}
			}
		}
	}
}