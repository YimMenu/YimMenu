#include "backend/bool_command.hpp"
#include "pointers.hpp"

namespace big
{
	bool_command g_veh_unlimited_weapons("vehallweapons", "VEHICLE_ALL_WEAPONS", "VEHICLE_ALL_WEAPONS_DESC",
	    g.vehicle.unlimited_weapons);
}
