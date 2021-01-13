#include "features.hpp"

namespace big
{
	static Entity entity = -1;
	static Vector3 location;
	static Vector3 other;
	static double dist;

	static const float multiplier = 3;
	static const int scroll = 2;
	static const int controls[] = { 14, 15, 24 };

	void features::gravity_gun()
	{
		bool bGravityGun = g_settings.options["gravity_gun"];

		if (bGravityGun)
		{
			// ZOOMED IN
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				location = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), true);

				// Attack RELEASED
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					if (functions::raycast_entity(&entity))
					{
						other = ENTITY::GET_ENTITY_COORDS(entity, true);
						dist = functions::distance_between_vectors(location, other);

						if (dist > 50)
						{
							entity = -1;

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
						entity = -1;

						features::notify::above_map("No entity found.");
					}
				}

				if (ENTITY::DOES_ENTITY_EXIST(entity))
				{
					// Scroll Away
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 14))
						dist -= 5;
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 15))
						dist += 5;

					functions::take_control_of_entity(entity);

					ENTITY::SET_ENTITY_COLLISION(entity, false, false);

					other = ENTITY::GET_ENTITY_COORDS(entity, true);

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					float pitch = functions::deg_to_rad(rot.x - 0); // vertical
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

	Vector3 rotation_to_direction(Vector3 rotation)
	{
		float x = deg_to_rad(rotation.x);
		float z = deg_to_rad(rotation.z);

		float num = abs(cos(x));

		return Vector3
		{
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}

	Vector3 screen_to_world(Vector3 position, Vector3 rotation, float mouseX, float mouseY, Vector3 &out)
	{
		Vector3 direction = rotation_to_direction(rotation);

		Vector3 rotUp = rotation;
		Vector3 rotDown = rotation;
		Vector3 rotLeft = rotation;
		Vector3 rotRight = rotation;

		rotUp.x += 1;
		rotDown.x -= 1;
		rotLeft.z -= 1;
		rotRight.z += 1;

		Vector3 camRight = rotation_to_direction(rotRight) - rotation_to_direction(rotLeft);
		Vector3 camUp = rotation_to_direction(rotUp) - rotation_to_direction(rotDown);

		float rollRad = -deg_to_rad(rotation.y);

		Vector3 camRightRoll = camRight * cos(rollRad) - camUp * sin(rollRad);
		Vector3 camUpRoll = camRight * sin(rollRad) + camUp * cos(rollRad);

		Vector3 point3d = position + direction * 1.f + camRightRoll + camUpRoll;
		float x, y;
		if (!GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(point3d.x, point3d.y, point3d.z, &x, &y))
		{
			out = direction;

			return position + direction * 1.f;
		}

		Vector3 point3d_zero = position + direction * 1.f;
		float x_zero, y_zero;
		if (!GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(point3d_zero.x, point3d_zero.y, point3d_zero.z, &x_zero, &y_zero))
		{
			out = direction;

			return position + direction * 1.f;
		}

		const double eps = .001;
		if (abs(x - x_zero) < eps || abs(y - y_zero) < eps)
		{
			out = direction;

			return position + direction * 1.f;
		}

		float scaleX = (mouseX - x_zero) / (x - x_zero);
		float scaleY = (mouseY - y_zero) / (y - y_zero);

		Vector3 point3d_ret = position + direction * 1.f + camRightRoll * scaleX + camUpRoll * scaleY;
		out = direction + camRightRoll * scaleX + camUpRoll * scaleY;
		return point3d_ret;
	}
}