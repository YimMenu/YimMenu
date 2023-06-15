#include "backend/looped/looped.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::vehicle_keep_engine_running()
	{
		if (!g.vehicle.keep_engine_running && !g.vehicle.disable_engine_auto_start)
			return;

		if (g.vehicle.keep_engine_running)
			vehicle::keep_engine_running(self::veh, true);
		else
			vehicle::keep_engine_running(self::veh, false);
	}
}