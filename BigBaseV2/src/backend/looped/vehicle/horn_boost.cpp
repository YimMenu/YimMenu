#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	static constexpr float hornBoostSpeedDefault = 10.f;
	static float hornBoostSpeed = hornBoostSpeedDefault;
	static constexpr float hostBoostSpeedMax = 200.f;

	void looped::vehicle_horn_boost()
	{
		if (!g->vehicle.horn_boost) return;
		
		const Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (veh == 0)
		{
			hornBoostSpeed = hornBoostSpeedDefault;

			return;
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
			hornBoostSpeed = ENTITY::GET_ENTITY_SPEED(veh);

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
		{
			if (hornBoostSpeed < hostBoostSpeedMax) hornBoostSpeed++;

			const auto velocity =
				ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, 0.f, hornBoostSpeed, 0.f) - ENTITY::GET_ENTITY_COORDS(veh, true);
			ENTITY::SET_ENTITY_VELOCITY(veh, velocity.x, velocity.y, velocity.z);
		}
		else if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_HORN))
			hornBoostSpeed = hornBoostSpeedDefault;
	}
}