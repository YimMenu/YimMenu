#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"

namespace big
{
	static Entity ent = 0;
	static Vector3 location;
	static Vector3 other;
	static float dist;

	static const int scroll = 0;

	void looped::weapons_gravity_gun()
	{
		bool is_gravity_gun_selected = g.weapons.custom_weapon == CustomWeapon::GRAVITY_GUN;
		constexpr double multiplier = 3.0;

		auto is_zoomed_in = is_gravity_gun_selected && PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);
		if (is_zoomed_in)
		{
			location = self::pos;

			auto is_attack_released = PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && ent == 0;
			if (is_attack_released)
			{
				if (entity::raycast(&ent))
				{
					if (ENTITY::IS_ENTITY_A_PED(ent) && PED::IS_PED_A_PLAYER(ent))
					{
						ent = 0;

						g_notification_service->push_warning("Weapons", "You can't move player entities!");
					}
					else
					{
						other = ENTITY::GET_ENTITY_COORDS(ent, true);
						dist = (float)math::distance_between_vectors(location, other);

						if (dist > 500)
						{
							ent = 0;

							g_notification_service->push_warning("Weapons", "Entity is too far.");
						}
						else
						{
							if (entity::take_control_of(ent) && ENTITY::IS_ENTITY_A_PED(ent) && !PED::IS_PED_RAGDOLL(ent))
							{
								TASK::SET_HIGH_FALL_TASK(ent, 0, 0, 0);

								g_notification_service->push_warning("Weapons", "Selected entity at crosshair.");
							}
						}
					}
				}
				else
				{
					ent = 0;

					g_notification_service->push_warning("Weapons", "No entity found.");
				}
			}

			if (ENTITY::DOES_ENTITY_EXIST(ent))
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
					dist -= 5;
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
					dist += 5;

				if (!entity::take_control_of(ent))
				{
					ent = 0;

					return g_notification_service->push_warning("Weapons", "Failed to take control of entity.");
				}

				ENTITY::SET_ENTITY_COLLISION(ent, false, false);

				other = ENTITY::GET_ENTITY_COORDS(ent, true);

				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
				float pitch = math::deg_to_rad(rot.x); // vertical
				// float roll = rot.y;
				float yaw = math::deg_to_rad(rot.z + 90); // horizontal

				Vector3 velocity;

				velocity.x = location.x + (dist * cos(pitch) * cos(yaw)) - other.x;
				velocity.y = location.y + (dist * sin(yaw) * cos(pitch)) - other.y;
				velocity.z = location.z + (dist * sin(pitch)) - other.z;

				ENTITY::SET_ENTITY_VELOCITY(ent, velocity.x * (float)multiplier, velocity.y * (float)multiplier, velocity.z * (float)multiplier);
				ENTITY::SET_ENTITY_ALPHA(ent, 105, 0);
			}
		}
		else if (ent != 0 && entity::take_control_of(ent))
		{
			ENTITY::SET_ENTITY_COLLISION(ent, true, true);
			ENTITY::RESET_ENTITY_ALPHA(ent);

			ent = 0;

			g_notification_service->push("Weapons", "Released entity.");
		}
	}
}
