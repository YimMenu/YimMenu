#include "features.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void features::vehicle_gun()
	{
		bool bVehicleGun = g_settings.options["custom_gun"]["type"] == 4;

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
					Vehicle veh = func::spawn_vehicle(
						"bus",
						location,
						ENTITY::GET_ENTITY_HEADING(player)
					);

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					float pitch = func::deg_to_rad(rot.x); // vertical
					//float roll = rot.y;
					float yaw = func::deg_to_rad(rot.z + 90); // horizontal

					Vector3 velocity;
					float dist = 150.f;

					velocity.x = dist * cos(pitch) * cos(yaw);
					velocity.y = dist * sin(yaw) * cos(pitch);
					velocity.z = dist * sin(pitch);

					script::get_current()->yield();

					ENTITY::SET_ENTITY_ROTATION(veh, rot.x, rot.y, rot.z, 2, 1);
					ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);
				}
			}
		}
	}
}