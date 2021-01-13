#include "features.hpp"

namespace big
{
	static Entity entity = -1;
	static Vector3 location;
	static Vector3 other;
	static double dist;

	static const int scroll = 2;
	static const int controls[] = { 14, 15, 24 };

	void features::gravity_gun()
	{
		bool bGravityGun = g_settings.options["gravity_gun"]["enabled"];
		double multiplier = g_settings.options["gravity_gun"]["multiplier"];

		Hash currWeapon;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), &currWeapon, 1);

		if (bGravityGun && currWeapon == RAGE_JOAAT("weapon_pistol"))
		{
			// ZOOMED IN
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(g_playerId, true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				location = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), true);

				// Attack RELEASED
				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, 24))
				{
					if (functions::raycast_entity(&entity))
					{
						other = ENTITY::GET_ENTITY_COORDS(entity, true);
						dist = functions::distance_between_vectors(location, other);

						if (dist > 50)
						{
							entity = 0;

							notify::above_map("Entity is too far.");
						}
						else
						{
							functions::take_control_of_entity(entity);

							features::notify::above_map("Selected entity at crosshair.");
						}
					}
					else
					{
						entity = 0;

						features::notify::above_map("No entity found.");
					}
				}

				if (ENTITY::DOES_ENTITY_EXIST(entity))
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 14))
						dist -= 5;
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 15))
						dist += 5;

					functions::take_control_of_entity(entity);

					ENTITY::SET_ENTITY_COLLISION(entity, false, false);

					other = ENTITY::GET_ENTITY_COORDS(entity, true);

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					float pitch = functions::deg_to_rad(rot.x); // vertical
					// float roll = rot.y;
					float yaw = functions::deg_to_rad(rot.z + 90); // horizontal

					Vector3 zRot;

					zRot.x = location.x + (dist * cos(pitch) * cos(yaw));
					zRot.y = location.y + (dist * sin(yaw) * cos(pitch));
					zRot.z = location.z + (dist * sin(pitch));

					ENTITY::SET_ENTITY_VELOCITY(entity, (zRot.x - other.x) * multiplier, (zRot.y - other.y) * multiplier, (zRot.z - other.z) * multiplier);
				}
			}
			else if (entity != -1)
			{
				ENTITY::SET_ENTITY_COLLISION(entity, true, true);

				entity = -1;

				features::notify::above_map("Released entity.");
			}
		}
	}

	float deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}
}