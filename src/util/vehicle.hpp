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

namespace big::vehicle
{
	struct disable_collisions
	{
		inline static memory::byte_patch* m_patch;
	};

	inline float mps_to_miph(float mps) { return mps * 2.2369f; }
	inline float miph_to_mps(float miph) { return miph / 2.2369f; }
	Vector3 get_spawn_location(bool spawn_inside, Hash hash, Ped ped = self::ped);
	std::optional<Vector3> get_waypoint_location();
	void set_mp_bitset(Vehicle veh);
	void bring(Vehicle veh, Vector3 location, bool put_in = true, int seatIdx = -1);
	Vehicle get_closest_to_location(Vector3 location, float range);
	bool set_plate(Vehicle veh, const char* plate);
	bool repair(Vehicle veh);
	Vehicle spawn(Hash hash, Vector3 location, float heading, bool is_networked = true, bool script_veh = false);
	std::map<int, int32_t> get_owned_mods_from_vehicle_idx(script_global vehicle_idx);
	Vehicle clone_from_owned_mods(std::map<int, int32_t> owned_mods, Vector3 location, float heading, bool is_networked = true);
	std::map<int, int32_t> get_owned_mods_from_vehicle(Vehicle vehicle);
	void teleport_into_vehicle(Vehicle veh);
	void max_vehicle(Vehicle veh);
	void max_vehicle_performance(Vehicle veh);

	/*
	* Set 'open' to false to close the door.
	* Set doorId to eDoorId::VEH_EXT_DOOR_INVALID_ID or simply -1 to apply to all doors.
	*/
	void operate_vehicle_door(Vehicle veh, eDoorId doorId, bool open);
}
