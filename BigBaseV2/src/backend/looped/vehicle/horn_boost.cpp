#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	void looped::vehicle_horn_boost()
	{
		if (!g.vehicle.horn_boost) return;

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			if (veh == 0) return;

			Vector3 rot = ENTITY::GET_ENTITY_ROTATION(veh, 2);
			float pitch = math::deg_to_rad(rot.x); // vertical
			//float roll = rot.y;
			float yaw = math::deg_to_rad(rot.z + 90); // horizontal

			Vector3 velocity;
			const float dist = 50.f;
			velocity.x = dist * cos(pitch) * cos(yaw);
			velocity.y = dist * sin(yaw) * cos(pitch);
			velocity.z = dist * sin(pitch);

			ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);
		}
	}
}