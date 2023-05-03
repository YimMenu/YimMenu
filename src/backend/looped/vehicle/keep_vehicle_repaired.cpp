#include "keep_vehicle_repaired.hpp"

#include "natives.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void keep_vehicle_repaired::on_tick()
	{
		if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(self::veh))
			vehicle::repair(self::veh);
	}
}
