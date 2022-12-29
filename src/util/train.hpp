#pragma once
#include "gta/enums.hpp"
#include "services/players/player_service.hpp"
#include "script_global.hpp"
#include "pointers.hpp"
#include "natives.hpp"

namespace big::train
{
	inline auto get_all_vehicles = []() -> std::vector<Vehicle>
	{
		std::vector<Vehicle> result;
		Vehicle vehs[300 * 2 + 2];
		vehs[0] = 300;
		int nums = VEHICLE::GET_ALL_VEHICLES(vehs);
		for (int i = 1; result.size() < nums && i < sizeof(vehs) / sizeof(vehs[0]); i++)
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

		for (int i = 0; i < allVehicles.size(); i++)
		{
			if (ENTITY::GET_ENTITY_MODEL(allVehicles[i]) == 1030400667)
				return allVehicles[i];
		}
		return 0;
	}

	inline void hijack_train()
	{
		auto train = get_closest_train();

		if (train != 0)
		{
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), train, -1);
			g_notification_service->push_error("Hijack Train", train != 0 ? "Found a train nearby" : "No trains nearby");
		}
	}

	inline void delete_train()
	{
		int train = get_closest_train();

		if (train != 0)
		{
			VEHICLE::DELETE_ALL_TRAINS();
			g_notification_service->push_error("Hijack Train", train !=0 ? "Deleted the nearby train" : "There are no trains nearby to delete");
		}
	}

	inline void set_train_speed(float value)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			VEHICLE::SET_TRAIN_SPEED(get_closest_train(), value);
	}
}