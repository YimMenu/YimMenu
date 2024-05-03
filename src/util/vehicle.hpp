#pragma once
#include "core/scr_globals.hpp"
#include "entity.hpp"
#include "gta/enums.hpp"
#include "gta/joaat.hpp"
#include "gta/vehicle_values.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "script_global.hpp"
#include "services/vehicle_helper/vehicle_helper.hpp"

namespace big::vehicle
{
	struct disable_collisions
	{
		inline static memory::byte_patch* m_patch;
	};

	float mps_to_speed(float mps, SpeedUnit speed_unit);
	float speed_to_mps(float speed, SpeedUnit speed_unit);
	Vector3 get_spawn_location(bool spawn_inside, Hash hash, Ped ped = self::ped);
	void set_mp_bitset(Vehicle veh);
	void bring(Vehicle veh, Vector3 location, bool put_in = true, int seatIdx = -1);
	Vehicle get_closest_to_location(Vector3 location, float range);
	bool set_plate(Vehicle veh, const char* plate);
	void repair_engine_from_water(Vehicle veh);
	bool repair(Vehicle veh);
	Vehicle spawn(Hash hash, Vector3 location, float heading, bool is_networked = true, bool script_veh = false);
	Vehicle clone_from_vehicle_data(std::map<int, int32_t>& data, Vector3 location, float heading);
	std::map<int, int32_t> get_owned_mods_from_vehicle_idx(script_global vehicle_idx);
	Vehicle clone_from_owned_mods(std::map<int, int32_t> owned_mods, Vector3 location, float heading, bool is_networked = true, bool is_script_vehicle = false);
	std::map<int, int32_t> get_owned_mods_from_vehicle(Vehicle vehicle);
	void teleport_into_vehicle(Vehicle veh);
	void max_vehicle(Vehicle veh);
	void max_vehicle_performance(Vehicle veh);
	void set_engine_state(Vehicle current_vehicle, bool state, bool immediately, bool disable_auto_start);
	void downgrade(Vehicle vehicle);
	bool remote_control_vehicle(Vehicle veh);

	/*
	 Set doorId to eDoorId::VEH_EXT_DOOR_INVALID_ID or simply -1 to apply to all vehicle doors.
	*/
	bool change_vehicle_door_lock_state(Vehicle veh, eDoorId doorId, eVehicleLockState state);

	/*
	* Set 'open' to false to close the door.
	* Set doorId to eDoorId::VEH_EXT_DOOR_INVALID_ID or simply -1 to apply to all doors.
	*/
	bool operate_vehicle_door(Vehicle veh, eDoorId doorId, bool open);
	bool operate_vehicle_window(Vehicle veh, eWindowId windowId, bool open);

	bool operate_vehicle_headlights(Vehicle veh, bool lights, bool highbeams);

	/*
	* Input index -1 to apply to all neons.
	*/
	bool operate_vehicle_neons(Vehicle veh, int index, bool toggle);
}
