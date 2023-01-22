#pragma once
#include "entity.hpp"
#include "gta/joaat.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "teleport.hpp"
#include "script_global.hpp"
#include "gta/vehicle_values.hpp"
#include "services/vehicle_helper/vehicle_helper.hpp"
#include "core/scr_globals.hpp"

namespace big::vehicle
{
	inline float mps_to_speed(float mps, SpeedUnit speed_unit)
	{
		switch (speed_unit)
		{
		case SpeedUnit::KMPH:
			return mps * 3.6f;
			break;
		case SpeedUnit::MIPH:
			return mps * 2.2369f;
			break;
		}

		return mps;
	}

	inline float speed_to_mps(float speed, SpeedUnit speed_unit)
	{
		switch (speed_unit)
		{
		case SpeedUnit::KMPH:
			return speed / 3.6f;
			break;
		case SpeedUnit::MIPH:
			return speed / 2.2369f;
			break;
		}

		return speed;
	}

	inline Vector3 get_spawn_location(bool spawn_inside, Ped ped = self::ped)
	{
		float y_offset = 0;

		if (self::veh != 0)
		{
			y_offset = 10.f;
		}
		else if (!spawn_inside)
		{
			y_offset = 5.f;
		}

		return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.f, y_offset, 0.f);
	}

	inline void set_mp_bitset(Vehicle veh)
	{
		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		auto networkId = NETWORK::VEH_TO_NET(veh);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		VEHICLE::SET_VEHICLE_IS_STOLEN(veh, FALSE);
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

					auto veh_pos_arr = *veh_ptr->m_navigation->get_position();
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

	inline Vehicle spawn(Hash hash, Vector3 location, float heading, bool is_networked = true, bool script_veh = false)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return 0;
		}

		auto veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, script_veh, false);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		if (*g_pointers->m_is_session_started)
		{
			set_mp_bitset(veh);
		}

		return veh;
	}

	inline Vehicle clone_from_vehicle_data(std::map<int, int32_t>& data, Vector3 location, float heading)
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
				*scr_globals::spawn_global.at(27).at(idx).as<int32_t*>() = val;
			}
		}

		// permission fix
		*scr_globals::spawn_global.at(27).at(1).as<int32_t*>() = 0;

		// personal car flag
		*scr_globals::spawn_global.at(27).at(94).as<int32_t*>() = 14;
		*scr_globals::spawn_global.at(27).at(95).as<int32_t*>() = 2;

		// mmi
		*scr_globals::spawn_global.at(27).at(103).as<int32_t*>() = 0;

		// spawn location
		*scr_globals::spawn_global.at(7).at(0).as<float*>() = tmpLocation.x;
		*scr_globals::spawn_global.at(7).at(1).as<float*>() = tmpLocation.y;
		*scr_globals::spawn_global.at(7).at(2).as<float*>() = tmpLocation.z;

		// spawn non pegasus
		*scr_globals::spawn_global.at(3).as<int*>() = 0;

		// spawn signal
		int* spawn_signal = scr_globals::spawn_global.at(2).as<int32_t*>();
		*scr_globals::spawn_global.at(5).as<int32_t*>() = 1;
		*spawn_signal = 1;

		// wait until the vehicle is spawned
		for (size_t retry = 0; *spawn_signal != 0 && retry < 200; retry++)
		{
			script::get_current()->yield(10ms);
		}

		if (*spawn_signal == 1)
		{
			return 0;
		}

		auto veh = vehicle::get_closest_to_location(tmpLocation, 200);
		if (veh == 0)
		{
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

		veh_data.erase(1); veh_data.erase(94); veh_data.erase(95); veh_data.erase(103);

		return veh_data;
	}

	inline std::map<int, int32_t> get_owned_mods_from_vehicle_idx(script_global vehicle_idx)
	{
		std::map<int, int32_t> owned_mods;

		for (int i = MOD_SECONDARY_CUSTOM; i <= MOD_MODEL_HASH; i++)
		{
			owned_mods[i] = 0;
		}

		int32_t val_32 = *vehicle_idx.at(32).as<int32_t*>();
		int32_t val_77 = *vehicle_idx.at(77).as<int32_t*>();
		int32_t val_102 = *vehicle_idx.at(102).as<int32_t*>();


		owned_mods[MOD_MODEL_HASH] = *vehicle_idx.at(66).as<int32_t*>();

		owned_mods[MOD_PLATE_STYLE] = *vehicle_idx.at(0).as<int32_t*>();
		owned_mods[MOD_WINDOW_TINT] = *vehicle_idx.at(65).as<int32_t*>();
		owned_mods[MOD_WHEEL_TYPE] = *vehicle_idx.at(69).as<int32_t*>();


		owned_mods[MOD_PRIMARY_COL] = *vehicle_idx.at(5).as<int32_t*>();
		owned_mods[MOD_SECONDARY_COL] = *vehicle_idx.at(6).as<int32_t*>();
		owned_mods[MOD_PEARLESCENT_COL] = *vehicle_idx.at(7).as<int32_t*>();
		owned_mods[MOD_WHEEL_COL] = *vehicle_idx.at(8).as<int32_t*>();
		owned_mods[MOD_INTERIOR_COL] = *vehicle_idx.at(97).as<int32_t*>();
		owned_mods[MOD_DASHBOARD_COL] = *vehicle_idx.at(99).as<int32_t*>();


		//CUSTOM PRIMARY
		owned_mods[MOD_PRIMARY_CUSTOM] = (val_77 & (1 << 13)) != 0;
		if (owned_mods[MOD_PRIMARY_CUSTOM])
		{
			owned_mods[MOD_PRIMARY_COL_R] = *vehicle_idx.at(71).as<int32_t*>();
			owned_mods[MOD_PRIMARY_COL_G] = *vehicle_idx.at(72).as<int32_t*>();
			owned_mods[MOD_PRIMARY_COL_B] = *vehicle_idx.at(73).as<int32_t*>();
		}


		//CUSTOM SECONDARY
		owned_mods[MOD_SECONDARY_CUSTOM] = (val_77 & (1 << 12)) != 0;
		if (owned_mods[MOD_SECONDARY_CUSTOM])
		{
			owned_mods[MOD_SECONDARY_COL_R] = *vehicle_idx.at(71).as<int32_t*>();
			owned_mods[MOD_SECONDARY_COL_G] = *vehicle_idx.at(72).as<int32_t*>();
			owned_mods[MOD_SECONDARY_COL_B] = *vehicle_idx.at(73).as<int32_t*>();
		}


		// TIRE SMOKE
		owned_mods[MOD_TIRESMOKE_COL_R] = *vehicle_idx.at(62).as<int32_t*>();
		owned_mods[MOD_TIRESMOKE_COL_G] = *vehicle_idx.at(63).as<int32_t*>();
		owned_mods[MOD_TIRESMOKE_COL_B] = *vehicle_idx.at(64).as<int32_t*>();
		owned_mods[MOD_TYRE_SMOKE] = !(
			owned_mods[MOD_TIRESMOKE_COL_R] == 255 &&
			owned_mods[MOD_TIRESMOKE_COL_G] == 255 &&
			owned_mods[MOD_TIRESMOKE_COL_B] == 255
		);


		// XENON
		if (val_32 > 0)
		{
			owned_mods[MOD_XENON_LIGHTS] = 1;
			owned_mods[MOD_XENON_COL] = val_32 - 2;
		}
		else
		{
			owned_mods[MOD_XENON_LIGHTS] = 0;
		}


		// NEON
		owned_mods[MOD_NEON_LEFT_ON] = (val_77 & (1 << 30)) != 0;
		owned_mods[MOD_NEON_RIGHT_ON] = (val_77 & (1 << 31)) != 0;
		owned_mods[MOD_NEON_FRONT_ON] = (val_77 & (1 << 28)) != 0;
		owned_mods[MOD_NEON_BACK_ON] = (val_77 & (1 << 29)) != 0;
		owned_mods[MOD_NEON_COL_R] = *vehicle_idx.at(74).as<int32_t*>();
		owned_mods[MOD_NEON_COL_G] = *vehicle_idx.at(75).as<int32_t*>();
		owned_mods[MOD_NEON_COL_B] = *vehicle_idx.at(76).as<int32_t*>();

		// TIRE OPTIONS
		owned_mods[MOD_TIRE_CAN_BURST] = (val_77 & (1 << 9)) == 0;
		if ((val_102 & 0b11) == 0b11)
		{
			owned_mods[MOD_DRIFT_TIRE] = 1;
		}

		owned_mods[MOD_TURBO] = *vehicle_idx.at(28).as<int32_t*>() != 0;

		owned_mods[MOD_FRONTWHEEL_VAR] = *vehicle_idx.at(60).as<int32_t*>() != 0;
		owned_mods[MOD_REARWHEEL_VAR] = *vehicle_idx.at(61).as<int32_t*>() != 0;


		// OTHER MODS
		for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
		{
			if (slot == MOD_TURBO || slot == MOD_TYRE_SMOKE || slot == MOD_XENON_LIGHTS)
			{
				continue;
			}

			int32_t val = *vehicle_idx.at(10 + slot).as<int32_t*>() - 1;
			if (val != -1)
			{
				owned_mods[slot] = val;
			}
		}

		// EXTRA
		for (int extra = MOD_EXTRA_9; extra <= MOD_EXTRA_1; extra++)
		{
			int gta_extra_id = (extra - MOD_EXTRA_0) * -1;
			owned_mods[extra] = val_77 >> (gta_extra_id - 1) & 1;
		}

		return owned_mods;
	}


	inline Vehicle clone_from_owned_mods(std::map<int, int32_t> owned_mods, Vector3 location, float heading, bool is_networked = true)
	{
		auto vehicle = spawn(owned_mods[MOD_MODEL_HASH], location, heading, is_networked);
		if (vehicle == 0)
		{
			return 0;
		}

		for (int i = MOD_NEON_COL_B; i <= MOD_MODEL_HASH; i++)
		{
			if (owned_mods.count(i) == 0)
			{
				owned_mods[i] = 0;
			}
		}

		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		script::get_current()->yield(10ms);

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, owned_mods[MOD_PLATE_STYLE]);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, owned_mods[MOD_WINDOW_TINT]);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, owned_mods[MOD_WHEEL_TYPE]);
		script::get_current()->yield(10ms);

		VEHICLE::SET_VEHICLE_COLOURS(vehicle, owned_mods[MOD_PRIMARY_COL], owned_mods[MOD_SECONDARY_COL]);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, owned_mods[MOD_PEARLESCENT_COL], owned_mods[MOD_WHEEL_COL]);
		VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(vehicle, owned_mods[MOD_INTERIOR_COL]);
		VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(vehicle, owned_mods[MOD_DASHBOARD_COL]);

		if (owned_mods[MOD_PRIMARY_CUSTOM])
		{
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(
				vehicle, owned_mods[MOD_PRIMARY_COL_R],
				owned_mods[MOD_PRIMARY_COL_G], owned_mods[MOD_PRIMARY_COL_B]
			);
		}

		if (owned_mods[MOD_SECONDARY_CUSTOM])
		{
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(
				vehicle, owned_mods[MOD_SECONDARY_COL_R],
				owned_mods[MOD_SECONDARY_COL_G], owned_mods[MOD_SECONDARY_COL_B]
			);
		}

		if (owned_mods[MOD_TYRE_SMOKE])
		{
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(
				vehicle, owned_mods[MOD_TIRESMOKE_COL_R],
				owned_mods[MOD_TIRESMOKE_COL_G], owned_mods[MOD_TIRESMOKE_COL_B]
			);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TYRE_SMOKE, owned_mods[MOD_TYRE_SMOKE]);
		}

		if (owned_mods[MOD_XENON_LIGHTS])
		{
			VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle, owned_mods[MOD_XENON_COL]);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENON_LIGHTS, owned_mods[MOD_XENON_LIGHTS]);
		}

		VEHICLE::SET_VEHICLE_NEON_COLOUR(
			vehicle, owned_mods[MOD_NEON_COL_R],
			owned_mods[MOD_NEON_COL_G], owned_mods[MOD_NEON_COL_B]
		);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, NEON_LEFT, owned_mods[MOD_NEON_LEFT_ON]);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, NEON_RIGHT, owned_mods[MOD_NEON_RIGHT_ON]);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, NEON_FRONT, owned_mods[MOD_NEON_FRONT_ON]);
		VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, NEON_BACK, owned_mods[MOD_NEON_BACK_ON]);


		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, owned_mods[MOD_TIRE_CAN_BURST]);
		VEHICLE::SET_DRIFT_TYRES(vehicle, owned_mods[MOD_DRIFT_TIRE]);
		VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, owned_mods[MOD_TURBO]);

		for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
		{
			if (owned_mods.count(slot) && owned_mods[slot] != -1)
			{
				bool custom_tire = false;

				if (slot == MOD_FRONTWHEEL)
				{
					custom_tire = owned_mods[MOD_FRONTWHEEL_VAR];
				}
				else if (slot == MOD_REARWHEEL)
				{
					custom_tire = owned_mods[MOD_REARWHEEL_VAR];
				}

				VEHICLE::SET_VEHICLE_MOD(vehicle, slot, owned_mods[slot], custom_tire);
			}
		}

		for (int extra = MOD_EXTRA_14; extra <= MOD_EXTRA_1; extra++)
		{
			int gta_extra_id = (extra - MOD_EXTRA_0) * -1;
			if (owned_mods.count(extra) && VEHICLE::DOES_EXTRA_EXIST(vehicle, gta_extra_id))
			{
				VEHICLE::SET_VEHICLE_EXTRA(vehicle, gta_extra_id, owned_mods[extra] == 0);
			}
		}

		return vehicle;
	}

	inline std::map<int, int32_t> get_owned_mods_from_vehicle(Vehicle vehicle)
	{
		std::map<int, int32_t> owned_mods;

		for (int i = MOD_SECONDARY_CUSTOM; i <= MOD_MODEL_HASH; i++)
		{
			owned_mods[i] = 0;
		}

		owned_mods[MOD_MODEL_HASH] = ENTITY::GET_ENTITY_MODEL(vehicle);

		owned_mods[MOD_PLATE_STYLE] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
		owned_mods[MOD_WINDOW_TINT] = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		owned_mods[MOD_WHEEL_TYPE] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);

		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &owned_mods[MOD_PRIMARY_COL], &owned_mods[MOD_SECONDARY_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &owned_mods[MOD_PEARLESCENT_COL], &owned_mods[MOD_WHEEL_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(vehicle, &owned_mods[MOD_INTERIOR_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(vehicle, &owned_mods[MOD_DASHBOARD_COL]);

		owned_mods[MOD_PRIMARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle);
		if (owned_mods[MOD_PRIMARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(
				vehicle, &owned_mods[MOD_PRIMARY_COL_R],
				&owned_mods[MOD_PRIMARY_COL_G], &owned_mods[MOD_PRIMARY_COL_B]
			);
		}

		owned_mods[MOD_SECONDARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle);
		if (owned_mods[MOD_SECONDARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(
				vehicle, &owned_mods[MOD_SECONDARY_COL_R],
				&owned_mods[MOD_SECONDARY_COL_G], &owned_mods[MOD_SECONDARY_COL_B]
			);
		}

		owned_mods[MOD_TYRE_SMOKE] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_TYRE_SMOKE);
		if (owned_mods[MOD_TYRE_SMOKE])
		{
			VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(
				vehicle, &owned_mods[MOD_TIRESMOKE_COL_R],
				&owned_mods[MOD_TIRESMOKE_COL_G], &owned_mods[MOD_TIRESMOKE_COL_B]
			);
		}

		owned_mods[MOD_XENON_LIGHTS] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_XENON_LIGHTS);
		if (owned_mods[MOD_XENON_LIGHTS])
		{
			owned_mods[MOD_XENON_COL] = (int8_t)VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle);
		}

		owned_mods[MOD_NEON_LEFT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_LEFT);
		owned_mods[MOD_NEON_RIGHT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_RIGHT);
		owned_mods[MOD_NEON_FRONT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_FRONT);
		owned_mods[MOD_NEON_BACK_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_BACK);
		VEHICLE::GET_VEHICLE_NEON_COLOUR(
			vehicle, &owned_mods[MOD_NEON_COL_R],
			&owned_mods[MOD_NEON_COL_G], &owned_mods[MOD_NEON_COL_B]
		);

		owned_mods[MOD_TIRE_CAN_BURST] = VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle);
		owned_mods[MOD_DRIFT_TIRE] = VEHICLE::GET_DRIFT_TYRES_SET(vehicle);
		owned_mods[MOD_TURBO] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_TURBO);

		owned_mods[MOD_FRONTWHEEL_VAR] = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, MOD_FRONTWHEEL);
		owned_mods[MOD_REARWHEEL_VAR] = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, MOD_REARWHEEL);

		for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
		{
			int count = VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, slot);
			if (count > 0)
			{
				int32_t val = VEHICLE::GET_VEHICLE_MOD(vehicle, slot);

				if (val != -1)
				{
					owned_mods[slot] = val;
				}
			}
		}

		for (int extra = MOD_EXTRA_14; extra <= MOD_EXTRA_1; extra++)
		{
			int gta_extra_id = (extra - MOD_EXTRA_0) * -1;
			if (VEHICLE::DOES_EXTRA_EXIST(vehicle, gta_extra_id))
			{
				owned_mods[extra] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, gta_extra_id);
			}
		}

		return owned_mods;
	}

	inline void teleport_into_vehicle(Vehicle veh)
	{
		PED::SET_PED_INTO_VEHICLE(self::ped, veh, -1);
	}

	inline void max_vehicle(Vehicle veh)
	{
		Hash model = ENTITY::GET_ENTITY_MODEL(veh);

		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TURBO, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TYRE_SMOKE, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_XENON_LIGHTS, TRUE);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);

		for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
		{
			if (slot == MOD_LIVERY) {
				continue;
			}

			int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, slot);
			if (count > 0)
			{
				int selected_mod = -1;

				for (int mod = count - 1; mod >= -1; mod--)
				{

					if (vehicle_helper::check_mod_blacklist(model, slot, mod))
					{
						continue;
					}

					selected_mod = mod;
					break;
				}

				if (selected_mod != -1)
				{
					VEHICLE::SET_VEHICLE_MOD(veh, slot, selected_mod, true);
				}
			}
		}
	}

	inline void set_engine_state(Vehicle current_vehicle, bool state, bool immediately, bool disable_auto_start)
	{
		if (current_vehicle)
			VEHICLE::SET_VEHICLE_ENGINE_ON(current_vehicle, state, immediately, disable_auto_start);
		else
			return g_notification_service->push_warning("Vehicle", "Please be in a car first then try again.");
	}

	inline void downgrade_vehicle(Player player)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::REMOVE_VEHICLE_MOD(vehicle, i);
		}
		VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 18); //Remove turbo on vehicle
		VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 22); //Remove xeon headlights
	}	

inline void crush_vehicle(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, true, 0, 0, -40.0f, 0, 0, 0, true, true, true, true, false, true);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

inline void boost_player_vehicle(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 79);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

inline void flying_vehicle(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, 0.f, 0.f, 50000.f, 0.f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

inline void kill_vehicle_engine(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, -4000);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

inline void burst_tires(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
			entity::take_control_of(vehicle);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, true);
			static int tireID = 0;
			for (tireID = 0; tireID < 8; tireID++)
			{
				VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, tireID, true, 1000.0);
			}
		}
	}	

inline void smash_windows(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(ped));
			Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(ped, false);
			static int windowID = 0;
			for (windowID = 0; windowID < 10; windowID++)
			{
				VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, windowID);
			}
		}
	}	

inline void set_tint(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(ped));
			Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(ped, false);

			VEHICLE::SET_VEHICLE_WINDOW_TINT(UserVeh, WINDOWTINT_BLACK);
		}
	}	

inline void lock_doors(Player player)
	{
		int lockStatus = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player), 4);
		}
	}	

inline void unlock_doors(Player player)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player), 0);
		}
	}

inline void open_doors(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
			{
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 0, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 1, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 2, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 3, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 4, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 5, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 6, true, false);
				VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 7, true, false);
			}
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}

inline void close_doors(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

			if (entity::take_control_of(vehicle))
				VEHICLE::SET_VEHICLE_DOORS_SHUT(vehicle, false);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}	

inline void upgrade_vehicle(Player player)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), false);
		vehicle::max_vehicle(vehicle);
	}	

inline void gift_vehicle(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, TRUE, TRUE);
		DECORATOR::DECOR_REGISTER("PV_Slot", 3);
		DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
		DECORATOR::DECOR_SET_BOOL(vehicle, "IgnoredByQuickSave", FALSE);
		DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(player));
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
	}	

inline void clone_vehicle(Player player)
	{
		Vehicle pedVeh = NULL;
		Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		{
			pedVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
			if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
			{
				Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);


				Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(self::ped, FALSE); //playerPed
				Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, 0.f, true, false, false);
				PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
				int primaryColor, secondaryColor;
				VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
				if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
				{
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
					for (int i = 0; i <= 24; i++)
					{
						if (i > 16 && i < 23)
							VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
						else
							VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
					}
					int tireSmokeColor[3], pearlescentColor, wheelColor;
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
					{
						int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
						if (convertableState == 0 || convertableState == 3 || convertableState == 5)
							VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
						else
							VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
					}
					for (int i = 0; i <= 3; i++)
					{
						VEHICLE::SET_VEHICLE_NEON_ENABLED(playerVeh, i, VEHICLE::GET_VEHICLE_NEON_ENABLED(pedVeh, i));
					}
					for (int i = 0; i <= 11; i++)
					{
						if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
							VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, ~VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
					}
					if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
					{
						VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
					}
					int neonColor[3];
					VEHICLE::GET_VEHICLE_NEON_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
					VEHICLE::SET_VEHICLE_NEON_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
					VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
				}
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);

				if (*g_pointers->m_is_session_started)
				{
					vehicle::set_mp_bitset(vehicleModelHash);
				}
			}
		}
	}
	
	inline bool remote_control_vehicle(Vehicle veh)
	{
		if (!entity::take_control_of(veh, 4000))
		{
			g_notification_service->push_warning("Remote Control", "Failed to take control of remote vehicle");
			return false;
		}

		if (g.m_remote_controlled_vehicle == veh)
		{
			return false;
		}

		Hash model = ENTITY::GET_ENTITY_MODEL(veh);
		Vehicle spawned = vehicle::spawn(model, self::pos, 0.0f);

		ENTITY::SET_ENTITY_ALPHA(spawned, 0, FALSE);
		if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model))
			ENTITY::SET_ENTITY_VISIBLE(spawned, FALSE, FALSE);
		ENTITY::SET_ENTITY_INVINCIBLE(spawned, TRUE);

		float heading = ENTITY::GET_ENTITY_HEADING(veh);
		Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(veh, 2);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(veh, FALSE);
		Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(veh);

		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(spawned, coords.x, coords.y, coords.z, FALSE, FALSE, FALSE);
		ENTITY::SET_ENTITY_HEADING(spawned, heading);
		ENTITY::SET_ENTITY_ROTATION(spawned, rotation.x, rotation.y, rotation.z, 2, TRUE);

		ENTITY::SET_ENTITY_VISIBLE(veh, TRUE, FALSE);

		ENTITY::SET_ENTITY_COLLISION(veh, FALSE, FALSE);
		ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
		VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh, 4);
		VEHICLE::SET_VEHICLE_MAX_SPEED(veh, 0.0001f);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(veh, spawned, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, FALSE, FALSE, FALSE, FALSE, 0, TRUE, FALSE);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), spawned, -1);

		VEHICLE::SET_VEHICLE_ENGINE_ON(spawned, TRUE, TRUE, FALSE);
		ENTITY::SET_ENTITY_VELOCITY(spawned, velocity.x, velocity.y, velocity.z);
		VEHICLE::COPY_VEHICLE_DAMAGES(veh, spawned);

		g.m_remote_controller_vehicle = spawned;
		g.m_remote_controlled_vehicle = veh;
		return true;
	}
}
