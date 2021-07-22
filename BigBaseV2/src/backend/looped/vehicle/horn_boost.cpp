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

			Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(veh) * 1.05f;

			ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z - 0.5f);
		}
	}
}