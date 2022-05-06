#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{

	void looped::vehicle_instant_brake()
	{
		if (!g->vehicle.instant_brake) return;

		const Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (veh == 0 || ENTITY::GET_ENTITY_SPEED_VECTOR(veh, true).y < 1.f)
		{
			return;
		}

		if (PAD::IS_CONTROL_PRESSED(0, 33))
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0);
	}
}
