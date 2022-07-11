#pragma once
#include "entity.hpp"
#include "gta/joaat.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "teleport.hpp"
#include "script_global.hpp"
#include "gta\VehicleValues.h"

namespace big::vehicle
{
	inline auto spawn_global = script_global(2725269);

	inline void go_into_personal_vehicle()
	{
		*script_global(2671447).at(8).as<int*>() = 1;
	}

	inline void bring(Vehicle veh, Vector3 location, bool put_in = true, int seatIdx = -1)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh)) return g_notification_service->push_error("Vehicle", "Invalid handle");

		auto vecVehicleLocation = ENTITY::GET_ENTITY_COORDS(veh, true);
		teleport::load_ground_at_3dcoord(vecVehicleLocation);

		if (!entity::take_control_of(veh))
			return g_notification_service->push_warning("Vehicle", "Failed to take control of remote vehicle.");
		auto ped = self::ped;

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(ped));

		if (put_in)
		{
			for (size_t i = 0; i < 100 && math::distance_between_vectors(location, ENTITY::GET_ENTITY_COORDS(veh, true)) > 10; i++)
				script::get_current()->yield();

			auto driver_ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, false);

			if (driver_ped != 0)
			{
				if (PED::GET_PED_TYPE(driver_ped) == ePedType::PED_TYPE_NETWORK_PLAYER)
				{
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(driver_ped);
				}
				else
				{
					entity::delete_entity(driver_ped);
				}
			}

			PED::SET_PED_INTO_VEHICLE(ped, veh, seatIdx);
		}
	}

	inline Vehicle get_closest_to_location(Vector3 location, float range)
	{
		if (const auto replay = *g_pointers->m_replay_interface; replay)
		{
			if (const auto veh_interface = replay->m_vehicle_interface; veh_interface)
			{
				const auto veh_interface_size = veh_interface->m_max_vehicles;

				float min_dist = FLT_MAX;
				int32_t m_handle = 0;

				for (int32_t i = 0; i < veh_interface_size; i++)
				{
					auto veh_entity = veh_interface->m_vehicle_list->m_vehicles[i];
					auto veh_ptr = veh_entity.m_entity_ptr;

					if (!veh_ptr || !veh_ptr->m_navigation)
					{
						continue;
					}

					auto veh_pos_arr = veh_ptr->m_navigation->m_position;
					Vector3 veh_pos(veh_pos_arr.x, veh_pos_arr.y, veh_pos_arr.z);

					float dist = math::distance_between_vectors(veh_pos, location);

					if (dist < min_dist)
					{
						int32_t tmp_handle = g_pointers->m_ptr_to_handle(veh_ptr);

						if (entity::take_control_of(tmp_handle))
						{
							min_dist = dist;
							m_handle = tmp_handle;
						}
					}
				}

				return m_handle;
			}
		}

		return 0;
	}

	inline bool set_plate(Vehicle veh, const char* plate)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh))
		{
			return false;
		}

		if (plate != nullptr && plate[0] != 0)
		{
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, plate);
		}

		return true;
	}

	inline bool repair(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh))
		{
			return false;
		}

		VEHICLE::SET_VEHICLE_FIXED(veh);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);

		return true;
	}

	inline int spawn(Hash hash, Vector3 location, float heading, bool is_networked = true)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);

			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			g_notification_service->push_warning("Spawn", "Failed to spawn model, did you give an incorrect model?");

			return -1;
		}

		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
		auto veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, false, false);
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

		script::get_current()->yield();

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		if (*g_pointers->m_is_session_started)
		{
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
			ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(veh, true);
			int networkId = NETWORK::VEH_TO_NET(veh);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
		}

		return veh;
	}

	inline Vehicle clone(std::map<int, int32_t>& data, Vector3 location, float heading)
	{
		Vector3 tmpLocation = { location.x, location.y, 1200.0f };
		if (location.z > 1000.0f && location.z < 1400.0)
		{
			tmpLocation.z = 800.0f;
		}

		// vehicle data
		for (const auto& [idx, val] : data)
		{
			if (idx >= 0 && idx < 142)
			{
				*spawn_global.at(27).at(idx).as<int32_t*>() = val;
			}
		}

		// permission fix
		*spawn_global.at(27).at(19).as<int32_t*>() = -1;
		*spawn_global.at(27).at(60).as<int32_t*>() = 1;
		*spawn_global.at(27).at(77).as<int32_t*>() = 4030726305;

		// personal car flag
		*spawn_global.at(27).at(94).as<int32_t*>() = 0;
		*spawn_global.at(27).at(95).as<int32_t*>() = 0;

		// mmi
		*spawn_global.at(27).at(103).as<int32_t*>() = 0;

		// spawn location
		*spawn_global.at(7).at(0).as<float*>() = tmpLocation.x;
		*spawn_global.at(7).at(1).as<float*>() = tmpLocation.y;
		*spawn_global.at(7).at(2).as<float*>() = tmpLocation.z;

		// spawn non pegasus
		*spawn_global.at(3).as<int*>() = 0;

		// spawn signal
		int* spawn_signal = spawn_global.at(2).as<int32_t*>();
		*spawn_global.at(5).as<int32_t*>() = 1;
		*spawn_signal = 1;

		// wait until the vehicle is spawned
		for (size_t retry = 0; *spawn_signal != 0 && retry < 200; retry++)
		{
			script::get_current()->yield(10ms);
		}

		if (*spawn_signal == 1)
		{
			g_notification_service->push_error("Vehicle", "Unable to clone vehicle");
			return 0;
		}

		auto veh = vehicle::get_closest_to_location(tmpLocation, 200);
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
		{
			g_notification_service->push_error("Vehicle", "Unable to clone vehicle");
			return 0;
		}

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEADING(veh, heading);

		return veh;
	}

	inline std::map<int, int32_t> get_vehicle_data_from_vehicle_idx(script_global vehicle_idx)
	{
		std::map<int, int32_t> veh_data;

		for (int i = 0; i < 142; i++)
		{
			veh_data[i] = *vehicle_idx.at(i).as<int32_t*>();
		}

		veh_data.erase(1); veh_data.erase(19); veh_data.erase(60); veh_data.erase(77);
		veh_data.erase(94); veh_data.erase(95); veh_data.erase(103);

		return veh_data;
	}

	inline void telport_into_veh(Vehicle veh)
	{
		PED::SET_PED_INTO_VEHICLE(self::ped, veh, -1);
	}

	inline void max_vehicle(Vehicle veh)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18 /* Turbo */, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20 /* Tire Smoke */, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 17 /* Xenon Headlights */, TRUE);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);

		for (int i = 0; i < 50; i++)
		{
			if (
				i != MOD_LIVERY
			) {
				VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, true);
			}
		}
	}

	static constexpr char const* rgb_types[] = { "Off", "Fade", "Spasm" };

	static constexpr int driving_styles[] = { 443, 524861 };
	static constexpr char const* driving_style_names[] = { "Law-Abiding", "The Road Is Yours" };
}
