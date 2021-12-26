#pragma once
#include "common.hpp"

namespace big::features
{
	void run_tick();
	void script_func();
	//Bools
	extern bool unlimited_ammo_bool;
	extern bool always_jackpot;
	extern float max_vehicle_torque;
	extern float max_vehicle_engine;
	extern bool aimbot_player;

	//VOIDS
	void unlimited_ammo();
	Vehicle ClonePedVehicle(Ped ped);
	extern void BoostStats(Vehicle vehicle);
	extern void Aimbot();
}
