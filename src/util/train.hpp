#pragma once
#include "gta/enums.hpp"
#include "services/players/player_service.hpp"
#include "script_global.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big::train
{
	auto get_all_vehicles = []() -> std::vector<Vehicle>
	{
		std::vector<Vehicle> result;
		Vehicle vehs[300 * 2 + 2];
		vehs[0] = 300;
		int nums = VEHICLE::GET_ALL_VEHICLES(vehs);
		for (int i = 2; result.size() < nums && i < sizeof(vehs) / sizeof(vehs[0]); i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(vehs[i]) && !ENTITY::IS_ENTITY_DEAD(vehs[i], false))
			{
				result.push_back(vehs[i]);
			}
		}
		return result;
	};

	inline int get_closest_train()
	{	
		auto allVehicles = get_all_vehicles();

		for (int i = 0; sizeof(allVehicles); i++)
		{
			if (ENTITY::GET_ENTITY_MODEL(allVehicles[i]) == 1030400667)
				return allVehicles[i];
		}
	}

	inline void hijack_train()
	{
		int train = get_closest_train();

		if (train != 0)
		{
			PED::DELETE_PED((Ped*)VEHICLE::GET_PED_IN_VEHICLE_SEAT(train, -1, false));
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), train, -1);
		}
		else
			g_notification_service->push_error("Hijack Train", "There are no trains nearby");
	}
}