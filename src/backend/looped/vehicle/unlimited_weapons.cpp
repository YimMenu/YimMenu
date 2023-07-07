#include "backend/looped_command.hpp"
#include "pointers.hpp"

namespace big
{
	bool_command g_veh_unlimited_weapons("vehallweapons", "Allow Weapons In Vehicle", "Allows you to use all weapons in vehicle",
	    g.vehicle.unlimited_weapons);
}
