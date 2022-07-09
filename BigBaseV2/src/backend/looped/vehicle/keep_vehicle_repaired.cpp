#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::vehicle_keep_vehicle_repaired()
	{
		if (g->vehicle.keep_vehicle_repaired) {
			vehicle::repair(self::veh);
		}
	}
}