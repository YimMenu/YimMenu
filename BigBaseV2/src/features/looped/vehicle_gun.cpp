#include "features.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void features::vehicle_gun()
	{
		bool bVehicleGun = g_settings.options["custom_gun"]["type"] == 3;

		if (bVehicleGun)
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

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0.f, 10.f, 0.f);
					Vehicle veh = functions::spawn_vehicle(
						"bus",
						location,
						ENTITY::GET_ENTITY_HEADING(player)
					);

					script::get_current()->yield();

					ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0.f, 150.f, 0.f, 0.f, 0.f, 0.f, 0, 1, 1, 1, 0, 1);
				}
			}
		}
	}
}