#include "vehicle.hpp"

#include "blip.hpp"
#include "entity.hpp"
#include "gta/vehicle_values.hpp"
#include "ped.hpp"
#include "services/notifications/notification_service.hpp"

namespace big::vehicle
{
	Vector3 get_spawn_location(Hash hash, Ped ped)
	{
		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		Vector3 min, max, result;
		MISC::GET_MODEL_DIMENSIONS(hash, &min, &max);

		return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.f, (max - min).y, 0.f);
	}

	std::optional<Vector3> get_waypoint_location()
	{
		Vector3 location;

		if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint, -1))
			return std::nullopt;

		entity::load_ground_at_3dcoord(location);
		return location;
	}

	void set_mp_bitset(Vehicle veh, int net_id)
	{
		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
		VEHICLE::SET_VEHICLE_IS_STOLEN(veh, FALSE);
	}

	void bring(Vehicle veh, Vector3 location, bool put_in, int seatIdx)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
			return g_notification_service->push_error("Vehicle", "Vehicle is not a valid one.");

		auto vecVehicleLocation = ENTITY::GET_ENTITY_COORDS(veh, true);
		entity::load_ground_at_3dcoord(vecVehicleLocation);

		if (!entity::take_control_of(veh))
			return g_notification_service->push_warning("Vehicle", "Failed to take control of remote vehicle.");

		if (auto driver_ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, false); driver_ped != 0)
			clear_all_peds(veh);

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(self::ped));

		if (put_in)
		{
			for (size_t i = 0; i < 100 && math::distance_between_vectors(location, ENTITY::GET_ENTITY_COORDS(veh, true)) > 10; i++)
				script::get_current()->yield();

			PED::SET_PED_INTO_VEHICLE(self::ped, veh, seatIdx);
		}
	}

	void set_plate(Vehicle veh, const char* plate)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh))
			return;

		if (plate != nullptr && plate[0] != 0)
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, plate);
	}

	void repair(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh))
			return;

		VEHICLE::SET_VEHICLE_FIXED(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
	}

	Vehicle spawn(Hash hash, Vector3 location, float heading, bool is_networked, bool script_veh)
	{
		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return 0;
		}

		if (!heading)
			heading = ENTITY::GET_ENTITY_HEADING(self::ped) + 90;

		auto veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, script_veh, false);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		if (is_networked)
		{
			auto net_id = NETWORK::VEH_TO_NET(veh);

			self::spawned_vehicles[net_id] = veh;

			if (*g_pointers->m_gta.m_is_session_started)
				set_mp_bitset(veh, net_id);
		}

		return veh;
	}

	std::map<int, int32_t> get_owned_mods_from_vehicle_idx(script_global vehicle_idx)
	{
		std::map<int, int32_t> owned_mods;

		for (int i = MOD_SECONDARY_CUSTOM; i <= MOD_MODEL_HASH; i++)
		{
			owned_mods[i] = 0;
		}

		int32_t val_32  = *vehicle_idx.at(32).as<int32_t*>();
		int32_t val_77  = *vehicle_idx.at(77).as<int32_t*>();
		int32_t val_102 = *vehicle_idx.at(102).as<int32_t*>();
		int32_t val_103 = *vehicle_idx.at(103).as<int32_t*>();

		owned_mods[MOD_MODEL_HASH] = *vehicle_idx.at(66).as<int32_t*>();

		owned_mods[MOD_PLATE_STYLE] = *vehicle_idx.at(0).as<int32_t*>();
		owned_mods[MOD_WINDOW_TINT] = *vehicle_idx.at(65).as<int32_t*>();
		owned_mods[MOD_WHEEL_TYPE]  = *vehicle_idx.at(69).as<int32_t*>();


		owned_mods[MOD_PRIMARY_COL]     = *vehicle_idx.at(5).as<int32_t*>();
		owned_mods[MOD_SECONDARY_COL]   = *vehicle_idx.at(6).as<int32_t*>();
		owned_mods[MOD_PEARLESCENT_COL] = *vehicle_idx.at(7).as<int32_t*>();
		owned_mods[MOD_WHEEL_COL]       = *vehicle_idx.at(8).as<int32_t*>();
		owned_mods[MOD_INTERIOR_COL]    = *vehicle_idx.at(97).as<int32_t*>();
		owned_mods[MOD_DASHBOARD_COL]   = *vehicle_idx.at(99).as<int32_t*>();


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
		owned_mods[MOD_TYRE_SMOKE] = !(owned_mods[MOD_TIRESMOKE_COL_R] == 255 && owned_mods[MOD_TIRESMOKE_COL_G] == 255 && owned_mods[MOD_TIRESMOKE_COL_B] == 255);


		// XENON
		if (val_32 > 0)
		{
			owned_mods[MOD_XENON_LIGHTS] = 1;
			owned_mods[MOD_XENON_COL]    = val_32 - 2;
		}
		else
		{
			owned_mods[MOD_XENON_LIGHTS] = 0;
		}


		// NEON
		owned_mods[MOD_NEON_LEFT_ON]  = (val_77 & (1 << 30)) != 0;
		owned_mods[MOD_NEON_RIGHT_ON] = (val_77 & (1 << 31)) != 0;
		owned_mods[MOD_NEON_FRONT_ON] = (val_77 & (1 << 28)) != 0;
		owned_mods[MOD_NEON_BACK_ON]  = (val_77 & (1 << 29)) != 0;
		owned_mods[MOD_NEON_COL_R]    = *vehicle_idx.at(74).as<int32_t*>();
		owned_mods[MOD_NEON_COL_G]    = *vehicle_idx.at(75).as<int32_t*>();
		owned_mods[MOD_NEON_COL_B]    = *vehicle_idx.at(76).as<int32_t*>();

		// TIRE OPTIONS
		if (val_102 != 0) //Hal's Tyres
		{
			owned_mods[MOD_TIRE_CAN_BURST] = val_102 > 1;
			owned_mods[MOD_DRIFT_TIRE]     = val_102 == 3;
		}
		else
		{
			owned_mods[MOD_TIRE_CAN_BURST] = (val_77 & (1 << 9)) == 0;
		}


		owned_mods[MOD_TURBO] = *vehicle_idx.at(28).as<int32_t*>() != 0;

		owned_mods[MOD_FRONTWHEEL_VAR] = *vehicle_idx.at(60).as<int32_t*>() != 0;
		owned_mods[MOD_REARWHEEL_VAR]  = *vehicle_idx.at(61).as<int32_t*>() != 0;


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
		for (int extra = MOD_EXTRA_11; extra <= MOD_EXTRA_0; extra++)
		{
			int gta_extra_id  = (extra - MOD_EXTRA_0) * -1;
			owned_mods[extra] = val_77 >> (gta_extra_id - 1) & 1;
		}

		return owned_mods;
	}

	Vehicle clone_from_owned_mods(std::map<int, int32_t> owned_mods, Vector3 location, bool is_networked)
	{
		auto vehicle = spawn(owned_mods[MOD_MODEL_HASH], location, 0, is_networked);
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
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, owned_mods[MOD_PRIMARY_COL_R], owned_mods[MOD_PRIMARY_COL_G], owned_mods[MOD_PRIMARY_COL_B]);
		}

		if (owned_mods[MOD_SECONDARY_CUSTOM])
		{
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, owned_mods[MOD_SECONDARY_COL_R], owned_mods[MOD_SECONDARY_COL_G], owned_mods[MOD_SECONDARY_COL_B]);
		}

		if (owned_mods[MOD_TYRE_SMOKE])
		{
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, owned_mods[MOD_TIRESMOKE_COL_R], owned_mods[MOD_TIRESMOKE_COL_G], owned_mods[MOD_TIRESMOKE_COL_B]);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TYRE_SMOKE, owned_mods[MOD_TYRE_SMOKE]);
		}

		if (owned_mods[MOD_XENON_LIGHTS])
		{
			VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle, owned_mods[MOD_XENON_COL]);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENON_LIGHTS, owned_mods[MOD_XENON_LIGHTS]);
		}

		VEHICLE::SET_VEHICLE_NEON_COLOUR(vehicle, owned_mods[MOD_NEON_COL_R], owned_mods[MOD_NEON_COL_G], owned_mods[MOD_NEON_COL_B]);
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

		for (int extra = MOD_EXTRA_11; extra <= MOD_EXTRA_0; extra++)
		{
			int gta_extra_id = (extra - MOD_EXTRA_0) * -1;
			if (owned_mods.count(extra) && VEHICLE::DOES_EXTRA_EXIST(vehicle, gta_extra_id))
			{
				VEHICLE::SET_VEHICLE_EXTRA(vehicle, gta_extra_id, owned_mods[extra] == 0);
			}
		}

		return vehicle;
	}

	std::map<int, int32_t> get_owned_mods_from_vehicle(Vehicle vehicle)
	{
		std::map<int, int32_t> owned_mods;

		for (int i = MOD_SECONDARY_CUSTOM; i <= MOD_MODEL_HASH; i++)
		{
			owned_mods[i] = 0;
		}

		owned_mods[MOD_MODEL_HASH] = ENTITY::GET_ENTITY_MODEL(vehicle);

		owned_mods[MOD_PLATE_STYLE] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
		owned_mods[MOD_WINDOW_TINT] = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		owned_mods[MOD_WHEEL_TYPE]  = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);

		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &owned_mods[MOD_PRIMARY_COL], &owned_mods[MOD_SECONDARY_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &owned_mods[MOD_PEARLESCENT_COL], &owned_mods[MOD_WHEEL_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(vehicle, &owned_mods[MOD_INTERIOR_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(vehicle, &owned_mods[MOD_DASHBOARD_COL]);

		owned_mods[MOD_PRIMARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle);
		if (owned_mods[MOD_PRIMARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &owned_mods[MOD_PRIMARY_COL_R], &owned_mods[MOD_PRIMARY_COL_G], &owned_mods[MOD_PRIMARY_COL_B]);
		}

		owned_mods[MOD_SECONDARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle);
		if (owned_mods[MOD_SECONDARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &owned_mods[MOD_SECONDARY_COL_R], &owned_mods[MOD_SECONDARY_COL_G], &owned_mods[MOD_SECONDARY_COL_B]);
		}

		owned_mods[MOD_TYRE_SMOKE] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_TYRE_SMOKE);
		if (owned_mods[MOD_TYRE_SMOKE])
		{
			VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &owned_mods[MOD_TIRESMOKE_COL_R], &owned_mods[MOD_TIRESMOKE_COL_G], &owned_mods[MOD_TIRESMOKE_COL_B]);
		}

		owned_mods[MOD_XENON_LIGHTS] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_XENON_LIGHTS);
		if (owned_mods[MOD_XENON_LIGHTS])
		{
			owned_mods[MOD_XENON_COL] = (int8_t)VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle);
		}

		owned_mods[MOD_NEON_LEFT_ON]  = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_LEFT);
		owned_mods[MOD_NEON_RIGHT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_RIGHT);
		owned_mods[MOD_NEON_FRONT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_FRONT);
		owned_mods[MOD_NEON_BACK_ON]  = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, NEON_BACK);
		VEHICLE::GET_VEHICLE_NEON_COLOUR(vehicle, &owned_mods[MOD_NEON_COL_R], &owned_mods[MOD_NEON_COL_G], &owned_mods[MOD_NEON_COL_B]);

		owned_mods[MOD_TIRE_CAN_BURST] = VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle);
		owned_mods[MOD_DRIFT_TIRE]     = VEHICLE::GET_DRIFT_TYRES_SET(vehicle);
		owned_mods[MOD_TURBO]          = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, MOD_TURBO);

		owned_mods[MOD_FRONTWHEEL_VAR] = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, MOD_FRONTWHEEL);
		owned_mods[MOD_REARWHEEL_VAR]  = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, MOD_REARWHEEL);

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

		for (int extra = MOD_EXTRA_11; extra <= MOD_EXTRA_0; extra++)
		{
			int gta_extra_id = (extra - MOD_EXTRA_0) * -1;
			if (VEHICLE::DOES_EXTRA_EXIST(vehicle, gta_extra_id))
			{
				owned_mods[extra] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, gta_extra_id);
			}
		}

		return owned_mods;
	}

	void teleport_into_vehicle(Vehicle veh)
	{
		PED::SET_PED_INTO_VEHICLE(self::ped, veh, -1);
	}

	void max_vehicle(Vehicle veh)
	{
		Hash model = ENTITY::GET_ENTITY_MODEL(veh);

		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TURBO, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TYRE_SMOKE, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_XENON_LIGHTS, TRUE);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);

		for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
		{
			if (slot == MOD_LIVERY)
			{
				continue;
			}

			int count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, slot);
			if (count > 0)
			{
				int selected_mod = -1;

				for (int mod = count - 1; mod >= -1; mod--)
				{
					if (VEHICLE::IS_VEHICLE_MOD_GEN9_EXCLUSIVE(veh, slot, mod))
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

	void max_vehicle_performance(Vehicle veh)
	{
		if (entity::take_control_of(veh))
		{
			VehicleModType perfomance_mods[] = {MOD_ENGINE, MOD_BRAKES, MOD_TRANSMISSION, MOD_SUSPENSION, MOD_ARMOR, MOD_NITROUS, MOD_TURBO};
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (auto mod_slot : perfomance_mods)
			{
				if (mod_slot != MOD_NITROUS && mod_slot != MOD_TURBO)
					VEHICLE::SET_VEHICLE_MOD(veh, mod_slot, VEHICLE::GET_NUM_VEHICLE_MODS(veh, mod_slot) - 1, true);
				else
					VEHICLE::TOGGLE_VEHICLE_MOD(veh, mod_slot, true);
			}
		}
	}

	void clear_all_peds(Vehicle vehicle)
	{
		if (entity::take_control_of(vehicle))
			VEHICLE::BRING_VEHICLE_TO_HALT(vehicle, 1, 5, true);

		if (auto passengers = VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(vehicle, 1, 0))
		{
			eject_player(vehicle, -1); // if driver is player eject it

			if (passengers > 1) // if passengers > 1, check if other passengers are players and eject them too
				for (int i = 0; i < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle); ++i) // get max passengers capacity except driver
					eject_player(vehicle, i);

			// peds
			for (int i = -1; i < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle); ++i)
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, i, 0));

			// wait for passengers to leave
			for (int i = 0; i < 100 && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(vehicle, 1, 0) != 0; ++i)
				script::get_current()->yield(25ms);
		}
	}

	/*
	* Set 'open' to false to close the door.
	* Set doorId to eDoorId::VEH_EXT_DOOR_INVALID_ID or simply -1 to apply to all doors.
	*/
	void operate_vehicle_door(Vehicle veh, eDoorId doorId, bool open)
	{
		for (int i = 0; i < 6; i++)
			if ((doorId == eDoorId::VEH_EXT_DOOR_INVALID_ID || (int)doorId == i) && VEHICLE::GET_IS_DOOR_VALID(veh, i))
				if (open)
					VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, i, false, false);
				else
					VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, i, false);
	}
}
