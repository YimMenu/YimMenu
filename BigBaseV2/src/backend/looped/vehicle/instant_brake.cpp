#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{

	void looped::vehicle_instant_brake()
	{
		if (!g->vehicle.instant_brake) return;

		if (self::veh == 0 || ENTITY::GET_ENTITY_SPEED_VECTOR(self::veh, true).y < 1.f)
		{
			return;
		}

		if (PAD::IS_CONTROL_PRESSED(0, 33))
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0);
	}
}
