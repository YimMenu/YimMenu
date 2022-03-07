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
		static const char* get_mod_slot_name(int mod_slot, Vehicle vehicle);
		static const char* get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle);
		static void add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped);
		static void set_mp_parameters_for_vehicle(Vehicle vehicle);
		static Vehicle create_vehicle(Hash modelHash, float x, float y, float z, float heading);
	};
}