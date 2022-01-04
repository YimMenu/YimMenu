#pragma once

#include "common.hpp"
#include "natives.hpp"
#include "gta\VehicleValues.h"
#include "pointers.hpp"

namespace big
{
	class vehicle_helper
	{
	public:
		static void add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped);
		static void set_mp_parameters_for_vehicle(Vehicle vehicle);
		static Vehicle create_vehicle(Hash modelHash, float x, float y, float z, float heading);
	};
}