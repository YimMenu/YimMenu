#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_remove_speed_limit()
	{
		if (g->vehicle.remove_speed_limit)
		{
			ENTITY::SET_ENTITY_MAX_SPEED(self::veh, 2147483647);
		}
	}
}
