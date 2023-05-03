#include "instant_brake.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void instant_brake::on_tick()
	{
		if (self::veh == 0 || ENTITY::GET_ENTITY_SPEED_VECTOR(self::veh, true).y < 1.f || !VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(self::veh))
			return;

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0);
	}
}
