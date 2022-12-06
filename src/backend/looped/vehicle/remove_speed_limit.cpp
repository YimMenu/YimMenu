#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_remove_speed_limit()
	{
		if (g->vehicle.remove_speed_limit)
		{
			if(self::veh != 0)
				ENTITY::SET_ENTITY_MAX_SPEED(self::veh, INT32_MAX);
			else
				ENTITY::SET_ENTITY_MAX_SPEED(self::id, INT32_MAX);
		}
	}
}
