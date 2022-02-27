#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/math.hpp"
#include "util/vehicle.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void looped::weapons_vehicle_gun()
	{
		bool bVehicleGun = g->weapons.custom_weapon == CustomWeapon::VEHICLE_GUN;

		if (bVehicleGun)
		{
			Ped player = PLAYER::PLAYER_PED_ID();

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::GET_PLAYER_INDEX(), true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					Vector3 location = ENTITY::GET_ENTITY_COORDS(player, true);

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					float pitch = math::deg_to_rad(rot.x); // vertical
					//float roll = rot.y;
					float yaw = math::deg_to_rad(rot.z + 90); // horizontal

					float dist = 10.f;
					location.x += dist * cos(pitch) * cos(yaw);
					location.y += dist * sin(yaw) * cos(pitch);
					location.z += dist * sin(pitch);
					Vehicle veh = vehicle::spawn(
						(const char*)g->weapons.vehicle_gun_model,
						location,
						ENTITY::GET_ENTITY_HEADING(player)
					);

					Vector3 velocity;
					dist = 150.f;
					velocity.x = dist * cos(pitch) * cos(yaw);
					velocity.y = dist * sin(yaw) * cos(pitch);
					velocity.z = dist * sin(pitch);

					ENTITY::SET_ENTITY_ROTATION(veh, rot.x, rot.y, rot.z, 2, 1);
					ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);
				}
			}
		}
	}
}