#pragma once
#include "entity.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"

namespace big::train
{
	inline auto get_all_vehicles()
	{
		std::vector<Vehicle> result;
		rage::CReplayInterface* CReplayInterface_var = *g_pointers->m_replay_interface;
		for (int i = 0; i < 300; i++)
		{
			auto vehicle_ptr = CReplayInterface_var->m_vehicle_interface->get_vehicle(i);
			if (vehicle_ptr)
			{
				Vehicle vehicle_handle = g_pointers->m_ptr_to_handle(vehicle_ptr);

				result.push_back(vehicle_handle);
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
			entity::take_control_of(train);
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), train, -1);

			g_notification_service->push_error("HIJACK_TRAIN"_T.data(), "HIJACK_TRAIN_FOUND_TRAIN"_T.data());
		}
	}

	inline void delete_train()
	{
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) && get_closest_train() != 0)
		{
			VEHICLE::DELETE_ALL_TRAINS();
			g_notification_service->push_error("HIJACK_TRAIN"_T.data(), "HIJACK_TRAIN_DELETED_TRAIN"_T.data());
		}
	}

	inline void exit_train()
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
	}

	inline void set_train_speed(float value)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			VEHICLE::SET_TRAIN_CRUISE_SPEED(get_closest_train(), value);
	}
}