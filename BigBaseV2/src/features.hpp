#pragma once
#include "common.hpp"

namespace big::features
{
	void run_tick();
	void script_func();
	//Bools
	extern float max_vehicle_torque;
	extern float max_vehicle_engine;

	Vehicle ClonePedVehicle(Ped ped);
	extern void BoostStats(Vehicle vehicle);
}
