#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static Vehicle LUA_NATIVE_VEHICLE_CREATE_VEHICLE(Hash modelHash, float x, float y, float z, float heading, bool isNetwork, bool bScriptHostVeh, bool p7)
	{
		auto retval = VEHICLE::CREATE_VEHICLE(modelHash, x, y, z, heading, isNetwork, bScriptHostVeh, p7);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_DELETE_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::DELETE_VEHICLE(&vehicle);
		return vehicle;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON(Vehicle vehicle, bool toggle, bool p2)
	{
		VEHICLE::SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON(vehicle, toggle, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(Vehicle vehicle, bool canBeLockedOn, bool p2)
	{
		VEHICLE::SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(vehicle, canBeLockedOn, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Vehicle veh, bool toggle)
	{
		VEHICLE::SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(veh, toggle);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_HOMING_LOCKON_STATE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_HOMING_LOCKON_STATE(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_HOMING_LOCKEDONTO_STATE(Any p0)
	{
		auto retval = VEHICLE::GET_VEHICLE_HOMING_LOCKEDONTO_STATE(p0);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HOMING_LOCKEDONTO_STATE(Any p0, Any p1)
	{
		VEHICLE::SET_VEHICLE_HOMING_LOCKEDONTO_STATE(p0, p1);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_MODEL(Vehicle vehicle, Hash model)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_MODEL(vehicle, model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(int vehicleGenerator)
	{
		auto retval = (bool)VEHICLE::DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(vehicleGenerator);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_CREATE_SCRIPT_VEHICLE_GENERATOR(float x, float y, float z, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16)
	{
		auto retval = VEHICLE::CREATE_SCRIPT_VEHICLE_GENERATOR(x, y, z, heading, p4, p5, modelHash, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_DELETE_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator)
	{
		VEHICLE::DELETE_SCRIPT_VEHICLE_GENERATOR(vehicleGenerator);
	}

	static void LUA_NATIVE_VEHICLE_SET_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator, bool enabled)
	{
		VEHICLE::SET_SCRIPT_VEHICLE_GENERATOR(vehicleGenerator, enabled);
	}

	static void LUA_NATIVE_VEHICLE_SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool toggle, bool p7)
	{
		VEHICLE::SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(x1, y1, z1, x2, y2, z2, toggle, p7);
	}

	static void LUA_NATIVE_VEHICLE_SET_ALL_VEHICLE_GENERATORS_ACTIVE()
	{
		VEHICLE::SET_ALL_VEHICLE_GENERATORS_ACTIVE();
	}

	static void LUA_NATIVE_VEHICLE_SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(bool active)
	{
		VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(active);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_GENERATOR_AREA_OF_INTEREST(float x, float y, float z, float radius)
	{
		VEHICLE::SET_VEHICLE_GENERATOR_AREA_OF_INTEREST(x, y, z, radius);
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST()
	{
		VEHICLE::CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST();
	}

	static bool LUA_NATIVE_VEHICLE_SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle vehicle, float p1)
	{
		auto retval = (bool)VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, p1);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION(Vehicle p0, bool p1, bool p2, bool p3)
	{
		auto retval = (bool)VEHICLE::SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION(p0, p1, p2, p3);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_STUCK_ON_ROOF(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_STUCK_ON_ROOF(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_ADD_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)
	{
		VEHICLE::ADD_VEHICLE_UPSIDEDOWN_CHECK(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle)
	{
		VEHICLE::REMOVE_VEHICLE_UPSIDEDOWN_CHECK(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_STOPPED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_STOPPED(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle vehicle, bool includeDriver, bool includeDeadOccupants)
	{
		auto retval = VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(vehicle, includeDriver, includeDeadOccupants);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_NUMBER_OF_SEATS(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(modelHash);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_SEAT_WARP_ONLY(Vehicle vehicle, int seatIndex)
	{
		auto retval = (bool)VEHICLE::IS_SEAT_WARP_ONLY(vehicle, seatIndex);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_TURRET_SEAT(Vehicle vehicle, int seatIndex)
	{
		auto retval = (bool)VEHICLE::IS_TURRET_SEAT(vehicle, seatIndex);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_DOES_VEHICLE_ALLOW_RAPPEL(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DOES_VEHICLE_ALLOW_RAPPEL(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)
	{
		VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)
	{
		VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier)
	{
		VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(bool toggle)
	{
		VEHICLE::SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(float value)
	{
		VEHICLE::SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(value);
	}

	static void LUA_NATIVE_VEHICLE_SET_FAR_DRAW_VEHICLES(bool toggle)
	{
		VEHICLE::SET_FAR_DRAW_VEHICLES(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_NUMBER_OF_PARKED_VEHICLES(int value)
	{
		VEHICLE::SET_NUMBER_OF_PARKED_VEHICLES(value);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED(Vehicle vehicle, int doorLockStatus)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED(vehicle, doorLockStatus);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED(Vehicle vehicle, int doorId, int doorLockStatus)
	{
		VEHICLE::SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED(vehicle, doorId, doorLockStatus);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_MUTED_SIRENS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_HAS_MUTED_SIRENS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(vehicle, player, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(vehicle, player);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Vehicle vehicle, int team, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(vehicle, team, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED(Vehicle vehicle)
	{
		VEHICLE::SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MAX_LAUNCH_ENGINE_REVS_(Vehicle vehicle, float modifier)
	{
		VEHICLE::_SET_VEHICLE_MAX_LAUNCH_ENGINE_REVS(vehicle, modifier);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_THROTTLE_(Vehicle vehicle)
	{
		auto retval = VEHICLE::_GET_VEHICLE_THROTTLE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible)
	{
		VEHICLE::EXPLODE_VEHICLE(vehicle, isAudible, isInvisible);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_OUT_OF_CONTROL(Vehicle vehicle, bool killDriver, bool explodeOnImpact)
	{
		VEHICLE::SET_VEHICLE_OUT_OF_CONTROL(vehicle, killDriver, explodeOnImpact);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TIMED_EXPLOSION(Vehicle vehicle, Ped ped, bool toggle)
	{
		VEHICLE::SET_VEHICLE_TIMED_EXPLOSION(vehicle, ped, toggle);
	}

	static void LUA_NATIVE_VEHICLE_ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE(Vehicle vehicle)
	{
		VEHICLE::ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE()
	{
		VEHICLE::CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE();
	}

	static bool LUA_NATIVE_VEHICLE_HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE()
	{
		auto retval = (bool)VEHICLE::HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE();
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE()
	{
		VEHICLE::DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE();
	}

	static bool LUA_NATIVE_VEHICLE_HAVE_VEHICLE_REAR_DOORS_BEEN_BLOWN_OPEN_BY_STICKYBOMB(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::HAVE_VEHICLE_REAR_DOORS_BEEN_BLOWN_OPEN_BY_STICKYBOMB(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_TAXI_LIGHTS(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_TAXI_LIGHTS(vehicle, state);
	}

	static bool LUA_NATIVE_VEHICLE_IS_TAXI_LIGHT_ON(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_TAXI_LIGHT_ON(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_IN_GARAGE_AREA(sol::stack_object garageName, Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_IN_GARAGE_AREA(garageName.is<const char*>() ? garageName.as<const char*>() : nullptr, vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary)
	{
		VEHICLE::SET_VEHICLE_COLOURS(vehicle, colorPrimary, colorSecondary);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FULLBEAM(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_FULLBEAM(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_RACING(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_IS_RACING(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b)
	{
		VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, r, g, b);
	}

	static std::tuple<int, int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle)
	{
		VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int r, int g, int b)
	{
		VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, r, g, b);
	}

	static std::tuple<int, int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle)
	{
		VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle, float fade)
	{
		VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, fade);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_ENVEFF_SCALE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_CAN_RESPRAY_VEHICLE(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_GOON_BOSS_VEHICLE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_GOON_BOSS_VEHICLE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_OPEN_REAR_DOORS_ON_EXPLOSION(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_OPEN_REAR_DOORS_ON_EXPLOSION(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_FORCE_SUBMARINE_SURFACE_MODE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::FORCE_SUBMARINE_SURFACE_MODE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_FORCE_SUBMARINE_NEURTAL_BUOYANCY(Any p0, Any p1)
	{
		VEHICLE::FORCE_SUBMARINE_NEURTAL_BUOYANCY(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_SUBMARINE_CRUSH_DEPTHS(Vehicle vehicle, bool p1, float depth1, float depth2, float depth3)
	{
		VEHICLE::SET_SUBMARINE_CRUSH_DEPTHS(vehicle, p1, depth1, depth2, depth3);
	}

	static bool LUA_NATIVE_VEHICLE_GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH(Vehicle submarine)
	{
		auto retval = (bool)VEHICLE::GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH(submarine);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_SUBMARINE_NUMBER_OF_AIR_LEAKS(Vehicle submarine)
	{
		auto retval = VEHICLE::GET_SUBMARINE_NUMBER_OF_AIR_LEAKS(submarine);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_IGNORE_LAND_PROBES(Any p0, Any p1)
	{
		VEHICLE::SET_BOAT_IGNORE_LAND_PROBES(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_BOUNDS_AFFECT_WATER_PROBES_(Vehicle vehicle, bool toggle)
	{
		VEHICLE::_SET_BOUNDS_AFFECT_WATER_PROBES(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_ANCHOR(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_BOAT_ANCHOR(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_CAN_ANCHOR_BOAT_HERE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::CAN_ANCHOR_BOAT_HERE(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_FORCE_LOW_LOD_ANCHOR_MODE(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_FORCE_LOW_LOD_ANCHOR_MODE(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_LOW_LOD_ANCHOR_DISTANCE(Vehicle vehicle, float value)
	{
		VEHICLE::SET_BOAT_LOW_LOD_ANCHOR_DISTANCE(vehicle, value);
	}

	static bool LUA_NATIVE_VEHICLE_IS_BOAT_ANCHORED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_BOAT_ANCHORED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_SINKS_WHEN_WRECKED(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_BOAT_SINKS_WHEN_WRECKED(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_WRECKED(Vehicle vehicle)
	{
		VEHICLE::SET_BOAT_WRECKED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_SIREN(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_SIREN(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_SIREN_ON(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_SIREN_ON(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_SIREN_AUDIO_ON(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_SIREN_AUDIO_ON(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_STRONG(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_STRONG(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_STUCK_CHECK(Vehicle vehicle)
	{
		VEHICLE::REMOVE_VEHICLE_STUCK_CHECK(vehicle);
	}

	static std::tuple<int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary)
	{
		std::tuple<int, int> return_values;
		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &colorPrimary, &colorSecondary);
		std::get<0>(return_values) = colorPrimary;
		std::get<1>(return_values) = colorSecondary;

		return return_values;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex, bool isTaskRunning)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, seatIndex, isTaskRunning);
		return retval;
	}

	static Ped LUA_NATIVE_VEHICLE_GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex, bool p2)
	{
		auto retval = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, seatIndex, p2);
		return retval;
	}

	static Ped LUA_NATIVE_VEHICLE_GET_LAST_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex)
	{
		auto retval = VEHICLE::GET_LAST_PED_IN_VEHICLE_SEAT(vehicle, seatIndex);
		return retval;
	}

	static std::tuple<bool, bool, bool> LUA_NATIVE_VEHICLE_GET_VEHICLE_LIGHTS_STATE(Vehicle vehicle, bool lightsOn, bool highbeamsOn)
	{
		std::tuple<bool, bool, bool> return_values;
		std::get<0>(return_values) = (bool)VEHICLE::GET_VEHICLE_LIGHTS_STATE(vehicle, (BOOL*)&lightsOn, (BOOL*)&highbeamsOn);
		std::get<1>(return_values) = lightsOn;
		std::get<2>(return_values) = highbeamsOn;

		return return_values;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, bool completely)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_TYRE_BURST(vehicle, wheelID, completely);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed)
	{
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, speed);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FORWARD_SPEED_XY(Vehicle vehicle, float speed)
	{
		VEHICLE::SET_VEHICLE_FORWARD_SPEED_XY(vehicle, speed);
	}

	static void LUA_NATIVE_VEHICLE_BRING_VEHICLE_TO_HALT(Vehicle vehicle, float distance, int duration, bool p3)
	{
		VEHICLE::BRING_VEHICLE_TO_HALT(vehicle, distance, duration, p3);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_STEER_FOR_BUILDINGS(Vehicle vehicle, Any p1)
	{
		VEHICLE::SET_VEHICLE_STEER_FOR_BUILDINGS(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAUSES_SWERVING(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAUSES_SWERVING(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_IGNORE_PLANES_SMALL_PITCH_CHANGE(Any p0, Any p1)
	{
		VEHICLE::SET_IGNORE_PLANES_SMALL_PITCH_CHANGE(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_STOP_BRINGING_VEHICLE_TO_HALT(Vehicle vehicle)
	{
		VEHICLE::STOP_BRINGING_VEHICLE_TO_HALT(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_BEING_BROUGHT_TO_HALT(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_BEING_BROUGHT_TO_HALT(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_LOWER_FORKLIFT_FORKS(Vehicle forklift)
	{
		VEHICLE::LOWER_FORKLIFT_FORKS(forklift);
	}

	static void LUA_NATIVE_VEHICLE_SET_FORKLIFT_FORK_HEIGHT(Vehicle vehicle, float height)
	{
		VEHICLE::SET_FORKLIFT_FORK_HEIGHT(vehicle, height);
	}

	static bool LUA_NATIVE_VEHICLE_IS_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle, Entity entity)
	{
		auto retval = (bool)VEHICLE::IS_ENTITY_ATTACHED_TO_HANDLER_FRAME(vehicle, entity);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME(vehicle);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO(Entity entity)
	{
		auto retval = VEHICLE::FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO(entity);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER(Vehicle vehicle, Entity entity)
	{
		auto retval = (bool)VEHICLE::IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER(vehicle, entity);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP(Vehicle vehicle, Entity entity)
	{
		VEHICLE::ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP(vehicle, entity);
	}

	static void LUA_NATIVE_VEHICLE_DETACH_CONTAINER_FROM_HANDLER_FRAME(Vehicle vehicle)
	{
		VEHICLE::DETACH_CONTAINER_FROM_HANDLER_FRAME(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_BOAT_DISABLE_AVOIDANCE(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_BOAT_DISABLE_AVOIDANCE(vehicle, p1);
	}

	static bool LUA_NATIVE_VEHICLE_IS_HELI_LANDING_AREA_BLOCKED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_HELI_LANDING_AREA_BLOCKED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_SHORT_SLOWDOWN_FOR_LANDING(Vehicle vehicle)
	{
		VEHICLE::SET_SHORT_SLOWDOWN_FOR_LANDING(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_TURBULENCE_SCALAR(Vehicle vehicle, float p1)
	{
		VEHICLE::SET_HELI_TURBULENCE_SCALAR(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CAR_BOOT_OPEN(Vehicle vehicle)
	{
		VEHICLE::SET_CAR_BOOT_OPEN(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRE_BURST(Vehicle vehicle, int index, bool onRim, float p3)
	{
		VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, index, onRim, p3);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, bool closeInstantly)
	{
		VEHICLE::SET_VEHICLE_DOORS_SHUT(vehicle, closeInstantly);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, bool enabled)
	{
		VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(vehicle, enabled);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorId, bool loose, bool openInstantly)
	{
		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, doorId, loose, openInstantly);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_AUTO_LOCK(Vehicle vehicle, int doorId, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DOOR_AUTO_LOCK(vehicle, doorId, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES(Any p0)
	{
		VEHICLE::SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES(p0);
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)
	{
		VEHICLE::REMOVE_VEHICLE_WINDOW(vehicle, windowIndex);
	}

	static void LUA_NATIVE_VEHICLE_ROLL_DOWN_WINDOWS(Vehicle vehicle)
	{
		VEHICLE::ROLL_DOWN_WINDOWS(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex)
	{
		VEHICLE::ROLL_DOWN_WINDOW(vehicle, windowIndex);
	}

	static void LUA_NATIVE_VEHICLE_ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex)
	{
		VEHICLE::ROLL_UP_WINDOW(vehicle, windowIndex);
	}

	static void LUA_NATIVE_VEHICLE_SMASH_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)
	{
		VEHICLE::SMASH_VEHICLE_WINDOW(vehicle, windowIndex);
	}

	static void LUA_NATIVE_VEHICLE_FIX_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex)
	{
		VEHICLE::FIX_VEHICLE_WINDOW(vehicle, windowIndex);
	}

	static void LUA_NATIVE_VEHICLE_POP_OUT_VEHICLE_WINDSCREEN(Vehicle vehicle)
	{
		VEHICLE::POP_OUT_VEHICLE_WINDSCREEN(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_POP_OFF_VEHICLE_ROOF_WITH_IMPULSE(Vehicle vehicle, float x, float y, float z)
	{
		VEHICLE::POP_OFF_VEHICLE_ROOF_WITH_IMPULSE(vehicle, x, y, z);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_LIGHTS(Vehicle vehicle, int state)
	{
		VEHICLE::SET_VEHICLE_LIGHTS(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HEADLIGHT_SHADOWS(Vehicle vehicle, int p1)
	{
		VEHICLE::SET_VEHICLE_HEADLIGHT_SHADOWS(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ALARM(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_VEHICLE_ALARM(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_START_VEHICLE_ALARM(Vehicle vehicle)
	{
		VEHICLE::START_VEHICLE_ALARM(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_INTERIORLIGHT(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FORCE_INTERIORLIGHT(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_FORCE_INTERIORLIGHT(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier)
	{
		VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(vehicle, multiplier);
	}

	static void LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float radius)
	{
		VEHICLE::ATTACH_VEHICLE_TO_TRAILER(vehicle, trailer, radius);
	}

	static void LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_ON_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float offsetX, float offsetY, float offsetZ, float coordsX, float coordsY, float coordsZ, float rotationX, float rotationY, float rotationZ, float disableCollisions)
	{
		VEHICLE::ATTACH_VEHICLE_ON_TO_TRAILER(vehicle, trailer, offsetX, offsetY, offsetZ, coordsX, coordsY, coordsZ, rotationX, rotationY, rotationZ, disableCollisions);
	}

	static void LUA_NATIVE_VEHICLE_STABILISE_ENTITY_ATTACHED_TO_HELI(Vehicle vehicle, Entity entity, float p2)
	{
		VEHICLE::STABILISE_ENTITY_ATTACHED_TO_HELI(vehicle, entity, p2);
	}

	static void LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_TRAILER(Vehicle vehicle)
	{
		VEHICLE::DETACH_VEHICLE_FROM_TRAILER(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_ATTACHED_TO_TRAILER(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAILER_INVERSE_MASS_SCALE(Vehicle vehicle, float p1)
	{
		VEHICLE::SET_TRAILER_INVERSE_MASS_SCALE(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAILER_LEGS_RAISED(Vehicle vehicle)
	{
		VEHICLE::SET_TRAILER_LEGS_RAISED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAILER_LEGS_LOWERED(Vehicle vehicle)
	{
		VEHICLE::SET_TRAILER_LEGS_LOWERED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex)
	{
		VEHICLE::SET_VEHICLE_TYRE_FIXED(vehicle, tyreIndex);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, sol::stack_object plateText)
	{
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, plateText.is<const char*>() ? plateText.as<const char*>() : nullptr);
	}

	static const char* LUA_NATIVE_VEHICLE_GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_NUMBER_OF_VEHICLE_NUMBER_PLATES()
	{
		auto retval = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int plateIndex)
	{
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, plateIndex);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_RANDOM_TRAINS(bool toggle)
	{
		VEHICLE::SET_RANDOM_TRAINS(toggle);
	}

	static Vehicle LUA_NATIVE_VEHICLE_CREATE_MISSION_TRAIN(int variation, float x, float y, float z, bool direction, Any p5, Any p6)
	{
		auto retval = VEHICLE::CREATE_MISSION_TRAIN(variation, x, y, z, direction, p5, p6);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SWITCH_TRAIN_TRACK(int trackId, bool state)
	{
		VEHICLE::SWITCH_TRAIN_TRACK(trackId, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAIN_TRACK_SPAWN_FREQUENCY(int trackIndex, int frequency)
	{
		VEHICLE::SET_TRAIN_TRACK_SPAWN_FREQUENCY(trackIndex, frequency);
	}

	static void LUA_NATIVE_VEHICLE_ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION(Any p0)
	{
		VEHICLE::ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION(p0);
	}

	static void LUA_NATIVE_VEHICLE_DELETE_ALL_TRAINS()
	{
		VEHICLE::DELETE_ALL_TRAINS();
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAIN_SPEED(Vehicle train, float speed)
	{
		VEHICLE::SET_TRAIN_SPEED(train, speed);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed)
	{
		VEHICLE::SET_TRAIN_CRUISE_SPEED(train, speed);
	}

	static void LUA_NATIVE_VEHICLE_SET_RANDOM_BOATS(bool toggle)
	{
		VEHICLE::SET_RANDOM_BOATS(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_RANDOM_BOATS_MP(bool toggle)
	{
		VEHICLE::SET_RANDOM_BOATS_MP(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_GARBAGE_TRUCKS(bool toggle)
	{
		VEHICLE::SET_GARBAGE_TRUCKS(toggle);
	}

	static bool LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_RECORDING_ID(int recording, sol::stack_object script)
	{
		auto retval = VEHICLE::GET_VEHICLE_RECORDING_ID(recording, script.is<const char*>() ? script.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_RECORDING(int recording, sol::stack_object script)
	{
		VEHICLE::REQUEST_VEHICLE_RECORDING(recording, script.is<const char*>() ? script.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_VEHICLE_HAS_VEHICLE_RECORDING_BEEN_LOADED(int recording, sol::stack_object script)
	{
		auto retval = (bool)VEHICLE::HAS_VEHICLE_RECORDING_BEEN_LOADED(recording, script.is<const char*>() ? script.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_RECORDING(int recording, sol::stack_object script)
	{
		VEHICLE::REMOVE_VEHICLE_RECORDING(recording, script.is<const char*>() ? script.as<const char*>() : nullptr);
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time)
	{
		auto retval = VEHICLE::GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME(id, time);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, sol::stack_object script)
	{
		auto retval = VEHICLE::GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(recording, time, script.is<const char*>() ? script.as<const char*>() : nullptr);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time)
	{
		auto retval = VEHICLE::GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME(id, time);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, sol::stack_object script)
	{
		auto retval = VEHICLE::GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(recording, time, script.is<const char*>() ? script.as<const char*>() : nullptr);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(int id)
	{
		auto retval = VEHICLE::GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(id);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(int recording, sol::stack_object script)
	{
		auto retval = VEHICLE::GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(recording, script.is<const char*>() ? script.as<const char*>() : nullptr);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_POSITION_IN_RECORDING(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_POSITION_IN_RECORDING(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_TIME_POSITION_IN_RECORDING(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_TIME_POSITION_IN_RECORDING(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_START_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, int recording, sol::stack_object script, bool p3)
	{
		VEHICLE::START_PLAYBACK_RECORDED_VEHICLE(vehicle, recording, script.is<const char*>() ? script.as<const char*>() : nullptr, p3);
	}

	static void LUA_NATIVE_VEHICLE_START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Vehicle vehicle, int recording, sol::stack_object script, int flags, int time, int drivingStyle)
	{
		VEHICLE::START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(vehicle, recording, script.is<const char*>() ? script.as<const char*>() : nullptr, flags, time, drivingStyle);
	}

	static void LUA_NATIVE_VEHICLE_FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE(Vehicle vehicle, bool p1)
	{
		VEHICLE::FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::STOP_PLAYBACK_RECORDED_VEHICLE(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_PAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::PAUSE_PLAYBACK_RECORDED_VEHICLE(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_UNPAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::UNPAUSE_PLAYBACK_RECORDED_VEHICLE(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_PLAYBACK_GOING_ON_FOR_VEHICLE(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_CURRENT_PLAYBACK_FOR_VEHICLE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_CURRENT_PLAYBACK_FOR_VEHICLE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_PLAYBACK_SPEED(Vehicle vehicle, float speed)
	{
		VEHICLE::SET_PLAYBACK_SPEED(vehicle, speed);
	}

	static void LUA_NATIVE_VEHICLE_START_PLAYBACK_RECORDED_VEHICLE_USING_AI(Vehicle vehicle, int recording, sol::stack_object script, float speed, int drivingStyle)
	{
		VEHICLE::START_PLAYBACK_RECORDED_VEHICLE_USING_AI(vehicle, recording, script.is<const char*>() ? script.as<const char*>() : nullptr, speed, drivingStyle);
	}

	static void LUA_NATIVE_VEHICLE_SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, float time)
	{
		VEHICLE::SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(vehicle, time);
	}

	static void LUA_NATIVE_VEHICLE_SET_PLAYBACK_TO_USE_AI(Vehicle vehicle, int drivingStyle)
	{
		VEHICLE::SET_PLAYBACK_TO_USE_AI(vehicle, drivingStyle);
	}

	static void LUA_NATIVE_VEHICLE_SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(Vehicle vehicle, int time, int drivingStyle, bool p3)
	{
		VEHICLE::SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(vehicle, time, drivingStyle, p3);
	}

	static void LUA_NATIVE_VEHICLE_SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z, Any p4)
	{
		VEHICLE::SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK(vehicle, x, y, z, p4);
	}

	static void LUA_NATIVE_VEHICLE_SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z)
	{
		VEHICLE::SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(vehicle, x, y, z);
	}

	static void LUA_NATIVE_VEHICLE_SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z)
	{
		VEHICLE::SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(vehicle, x, y, z);
	}

	static void LUA_NATIVE_VEHICLE_SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_EXPLODE_VEHICLE_IN_CUTSCENE(Vehicle vehicle, bool p1)
	{
		VEHICLE::EXPLODE_VEHICLE_IN_CUTSCENE(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_ADD_VEHICLE_STUCK_CHECK_WITH_WARP(Any p0, float p1, Any p2, bool p3, bool p4, bool p5, Any p6)
	{
		VEHICLE::ADD_VEHICLE_STUCK_CHECK_WITH_WARP(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MODEL_IS_SUPPRESSED(Hash model, bool suppressed)
	{
		VEHICLE::SET_VEHICLE_MODEL_IS_SUPPRESSED(model, suppressed);
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_IN_SPHERE(float x, float y, float z, float radius, Hash modelHash, int flags)
	{
		auto retval = VEHICLE::GET_RANDOM_VEHICLE_IN_SPHERE(x, y, z, radius, modelHash, flags);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)
	{
		auto retval = VEHICLE::GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(p0, p1, p2, p3, p4, p5, p6);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6)
	{
		auto retval = VEHICLE::GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(p0, p1, p2, p3, p4, p5, p6);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_CLOSEST_VEHICLE(float x, float y, float z, float radius, Hash modelHash, int flags)
	{
		auto retval = VEHICLE::GET_CLOSEST_VEHICLE(x, y, z, radius, modelHash, flags);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_TRAIN_CARRIAGE(Vehicle train, int trailerNumber)
	{
		auto retval = VEHICLE::GET_TRAIN_CARRIAGE(train, trailerNumber);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_MISSION_TRAIN(Vehicle train)
	{
		auto retval = (bool)VEHICLE::IS_MISSION_TRAIN(train);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_DELETE_MISSION_TRAIN(Vehicle train)
	{
		VEHICLE::DELETE_MISSION_TRAIN(&train);
		return train;
	}

	static Vehicle LUA_NATIVE_VEHICLE_SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Vehicle train, bool p1)
	{
		VEHICLE::SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(&train, p1);
		return train;
	}

	static void LUA_NATIVE_VEHICLE_SET_MISSION_TRAIN_COORDS(Vehicle train, float x, float y, float z)
	{
		VEHICLE::SET_MISSION_TRAIN_COORDS(train, x, y, z);
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_BOAT(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_BOAT(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_JETSKI(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_JETSKI(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_PLANE(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_PLANE(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_HELI(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_HELI(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_CAR(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_CAR(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_TRAIN(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_TRAIN(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_BIKE(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_BIKE(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_BICYCLE(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_BICYCLE(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_QUADBIKE(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_A_QUADBIKE(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(model);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE(Hash model)
	{
		auto retval = (bool)VEHICLE::IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE(model);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_BLADES_FULL_SPEED(Vehicle vehicle)
	{
		VEHICLE::SET_HELI_BLADES_FULL_SPEED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed)
	{
		VEHICLE::SET_HELI_BLADES_SPEED(vehicle, speed);
	}

	static void LUA_NATIVE_VEHICLE_FORCE_SUB_THROTTLE_FOR_TIME(Vehicle vehicle, float p1, float p2)
	{
		VEHICLE::FORCE_SUB_THROTTLE_FOR_TIME(vehicle, p1, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_VEHICLE_CAN_BE_TARGETTED(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED(Any p0, Any p1)
	{
		VEHICLE::SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED(p0, p1);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_DIRT_LEVEL(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float dirtLevel)
	{
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, dirtLevel);
	}

	static bool LUA_NATIVE_VEHICLE_GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorId)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_DOOR_FULLY_OPEN(vehicle, doorId);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ENGINE_ON(Vehicle vehicle, bool value, bool instantly, bool disableAutoStart)
	{
		VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, value, instantly, disableAutoStart);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_UNDRIVEABLE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_PROVIDES_COVER(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_PROVIDES_COVER(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_CONTROL(Vehicle vehicle, int doorId, int speed, float angle)
	{
		VEHICLE::SET_VEHICLE_DOOR_CONTROL(vehicle, doorId, speed, angle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_LATCHED(Vehicle vehicle, int doorId, bool p2, bool p3, bool p4)
	{
		VEHICLE::SET_VEHICLE_DOOR_LATCHED(vehicle, doorId, p2, p3, p4);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_DOOR_ANGLE_RATIO(Vehicle vehicle, int doorId)
	{
		auto retval = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(vehicle, doorId);
		return retval;
	}

	static Ped LUA_NATIVE_VEHICLE_GET_PED_USING_VEHICLE_DOOR(Vehicle vehicle, int doord)
	{
		auto retval = VEHICLE::GET_PED_USING_VEHICLE_DOOR(vehicle, doord);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorId, bool closeInstantly)
	{
		VEHICLE::SET_VEHICLE_DOOR_SHUT(vehicle, doorId, closeInstantly);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_BROKEN(Vehicle vehicle, int doorId, bool deleteDoor)
	{
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, doorId, deleteDoor);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BREAK(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DOES_VEHICLE_HAVE_ROOF(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION(Any p0)
	{
		VEHICLE::SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION(p0);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION(Any p0)
	{
		VEHICLE::SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION(p0);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARJACK_MISSION_REMOVAL_PARAMETERS(Any p0, Any p1)
	{
		VEHICLE::SET_CARJACK_MISSION_REMOVAL_PARAMETERS(p0, p1);
	}

	static bool LUA_NATIVE_VEHICLE_IS_BIG_VEHICLE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_BIG_VEHICLE(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_NUMBER_OF_VEHICLE_COLOURS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_NUMBER_OF_VEHICLE_COLOURS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle, int colorCombination)
	{
		VEHICLE::SET_VEHICLE_COLOUR_COMBINATION(vehicle, colorCombination);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_COLOUR_COMBINATION(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle, int colorIndex)
	{
		VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle, colorIndex);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS(vehicle, p1);
	}

	static std::tuple<Hash, int> LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(bool p0, Hash modelHash, int successIndicator)
	{
		std::tuple<Hash, int> return_values;
		VEHICLE::GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(p0, &modelHash, &successIndicator);
		std::get<0>(return_values) = modelHash;
		std::get<1>(return_values) = successIndicator;

		return return_values;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_DOOR_LOCK_STATUS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(Vehicle vehicle, int doorId)
	{
		auto retval = VEHICLE::GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(vehicle, doorId);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_DOOR_DAMAGED(veh, doorID);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(Vehicle vehicle, int doorId, bool isBreakable)
	{
		VEHICLE::SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(vehicle, doorId, isBreakable);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_BUMPER_BOUNCING(Vehicle vehicle, bool frontBumper)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_BUMPER_BOUNCING(vehicle, frontBumper);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_BUMPER_BROKEN_OFF(Vehicle vehicle, bool frontBumper)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_BUMPER_BROKEN_OFF(vehicle, frontBumper);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_COP_VEHICLE_IN_AREA_3D(float x1, float x2, float y1, float y2, float z1, float z2)
	{
		auto retval = (bool)VEHICLE::IS_COP_VEHICLE_IN_AREA_3D(x1, x2, y1, y2, z1, z2);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_VALUE(Hash vehicleModel)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_VALUE(vehicleModel);
		return retval;
	}

	static Hash LUA_NATIVE_VEHICLE_GET_VEHICLE_LAYOUT_HASH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_LAYOUT_HASH(vehicle);
		return retval;
	}

	static Hash LUA_NATIVE_VEHICLE_GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT(Vehicle vehicle, int p1)
	{
		auto retval = VEHICLE::GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT(vehicle, p1);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, bool toggle)
	{
		VEHICLE::SET_RENDER_TRAIN_AS_DERAILED(train, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor)
	{
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, pearlescentColor, wheelColor);
	}

	static std::tuple<int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor)
	{
		std::tuple<int, int> return_values;
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &pearlescentColor, &wheelColor);
		std::get<0>(return_values) = pearlescentColor;
		std::get<1>(return_values) = wheelColor;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int color)
	{
		VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(vehicle, color);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int color)
	{
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(vehicle, &color);
		return color;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int color)
	{
		VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(vehicle, color);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int color)
	{
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(vehicle, &color);
		return color;
	}

	static void LUA_NATIVE_VEHICLE_STOP_ALL_GARAGE_ACTIVITY()
	{
		VEHICLE::STOP_ALL_GARAGE_ACTIVITY();
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FIXED(Vehicle vehicle)
	{
		VEHICLE::SET_VEHICLE_FIXED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DEFORMATION_FIXED(Vehicle vehicle)
	{
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_ENGINE_MISSFIRE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_ENGINE_MISSFIRE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_LEAK_OIL(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_LEAK_OIL(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_LEAK_PETROL(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_LEAK_PETROL(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_ENGINE_FIRES(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_VEHICLE_ENGINE_FIRES(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_PRETEND_OCCUPANTS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_PRETEND_OCCUPANTS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Any p6)
	{
		VEHICLE::REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(x1, y1, z1, x2, y2, z2, p6);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value)
	{
		VEHICLE::SET_VEHICLE_STEER_BIAS(vehicle, value);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, int extraId)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, extraId);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA(Vehicle vehicle, int extraId, bool disable)
	{
		VEHICLE::SET_VEHICLE_EXTRA(vehicle, extraId, disable);
	}

	static bool LUA_NATIVE_VEHICLE_DOES_EXTRA_EXIST(Vehicle vehicle, int extraId)
	{
		auto retval = (bool)VEHICLE::DOES_EXTRA_EXIST(vehicle, extraId);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_EXTRA_BROKEN_OFF(Vehicle vehicle, int extraId)
	{
		auto retval = (bool)VEHICLE::IS_EXTRA_BROKEN_OFF(vehicle, extraId);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_CONVERTIBLE_ROOF(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_CONVERTIBLE_ROOF(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_LOWER_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyLower)
	{
		VEHICLE::LOWER_CONVERTIBLE_ROOF(vehicle, instantlyLower);
	}

	static void LUA_NATIVE_VEHICLE_RAISE_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyRaise)
	{
		VEHICLE::RAISE_CONVERTIBLE_ROOF(vehicle, instantlyRaise);
	}

	static int LUA_NATIVE_VEHICLE_GET_CONVERTIBLE_ROOF_STATE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_A_CONVERTIBLE(Vehicle vehicle, bool p1)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_A_CONVERTIBLE(vehicle, p1);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_TRANSFORM_TO_SUBMARINE(Vehicle vehicle, bool noAnimation)
	{
		auto retval = (bool)VEHICLE::TRANSFORM_TO_SUBMARINE(vehicle, noAnimation);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_TRANSFORM_TO_CAR(Vehicle vehicle, bool noAnimation)
	{
		VEHICLE::TRANSFORM_TO_CAR(vehicle, noAnimation);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_IN_SUBMARINE_MODE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_IN_SUBMARINE_MODE(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DAMAGE(Vehicle vehicle, float xOffset, float yOffset, float zOffset, float damage, float radius, bool focusOnModel)
	{
		VEHICLE::SET_VEHICLE_DAMAGE(vehicle, xOffset, yOffset, zOffset, damage, radius, focusOnModel);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE(vehicle, toggle);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_ENGINE_HEALTH(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health)
	{
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, health);
	}

	static void LUA_NATIVE_VEHICLE_SET_PLANE_ENGINE_HEALTH(Vehicle vehicle, float health)
	{
		VEHICLE::SET_PLANE_ENGINE_HEALTH(vehicle, health);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_PETROL_TANK_HEALTH(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health)
	{
		VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, health);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_STUCK_TIMER_UP(Vehicle vehicle, int p1, int ms)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_STUCK_TIMER_UP(vehicle, p1, ms);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_RESET_VEHICLE_STUCK_TIMER(Vehicle vehicle, int nullAttributes)
	{
		VEHICLE::RESET_VEHICLE_STUCK_TIMER(vehicle, nullAttributes);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_DRIVEABLE(Vehicle vehicle, bool isOnFireCheck)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_DRIVEABLE(vehicle, isOnFireCheck);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle vehicle, bool owned)
	{
		VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(vehicle, owned);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BLIP_THROTTLE_RANDOMLY(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_BLIP_THROTTLE_RANDOMLY(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_POLICE_FOCUS_WILL_TRACK_VEHICLE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_POLICE_FOCUS_WILL_TRACK_VEHICLE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_START_VEHICLE_HORN(Vehicle vehicle, int duration, Hash mode, bool forever)
	{
		VEHICLE::START_VEHICLE_HORN(vehicle, duration, mode, forever);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_IN_CAR_MOD_SHOP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_IN_CAR_MOD_SHOP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_STRONG_AXLES(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(vehicle, toggle);
	}

	static const char* LUA_NATIVE_VEHICLE_GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash modelHash)
	{
		auto retval = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(modelHash);
		return retval;
	}

	static const char* LUA_NATIVE_VEHICLE_GET_MAKE_NAME_FROM_VEHICLE_MODEL(Hash modelHash)
	{
		auto retval = VEHICLE::GET_MAKE_NAME_FROM_VEHICLE_MODEL(modelHash);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_VEHICLE_DEFORMATION_AT_POS(Vehicle vehicle, float offsetX, float offsetY, float offsetZ)
	{
		auto retval = VEHICLE::GET_VEHICLE_DEFORMATION_AT_POS(vehicle, offsetX, offsetY, offsetZ);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_LIVERY(Vehicle vehicle, int livery)
	{
		VEHICLE::SET_VEHICLE_LIVERY(vehicle, livery);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_LIVERY(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY_COUNT(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_LIVERY_COUNT(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_LIVERY2(Vehicle vehicle, int livery)
	{
		VEHICLE::SET_VEHICLE_LIVERY2(vehicle, livery);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY2(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_LIVERY2(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY2_COUNT(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_LIVERY2_COUNT(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_WINDOW_INTACT(Vehicle vehicle, int windowIndex)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_WINDOW_INTACT(vehicle, windowIndex);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_ARE_ALL_VEHICLE_WINDOWS_INTACT(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::ARE_ALL_VEHICLE_WINDOWS_INTACT(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_ARE_ANY_VEHICLE_SEATS_FREE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_RESET_VEHICLE_WHEELS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::RESET_VEHICLE_WHEELS(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_HELI_PART_BROKEN(Vehicle vehicle, bool p1, bool p2, bool p3)
	{
		auto retval = (bool)VEHICLE::IS_HELI_PART_BROKEN(vehicle, p1, p2, p3);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_HELI_MAIN_ROTOR_HEALTH(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_HELI_TAIL_ROTOR_HEALTH(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_HELI_TAIL_BOOM_HEALTH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_HELI_TAIL_BOOM_HEALTH(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle, float health)
	{
		VEHICLE::SET_HELI_MAIN_ROTOR_HEALTH(vehicle, health);
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle, float health)
	{
		VEHICLE::SET_HELI_TAIL_ROTOR_HEALTH(vehicle, health);
	}

	static bool LUA_NATIVE_VEHICLE_SET_HELI_TAIL_BOOM_CAN_BREAK_OFF(Vehicle vehicle, bool toggle)
	{
		auto retval = (bool)VEHICLE::SET_HELI_TAIL_BOOM_CAN_BREAK_OFF(vehicle, toggle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NAME_DEBUG(Vehicle vehicle, sol::stack_object name)
	{
		VEHICLE::SET_VEHICLE_NAME_DEBUG(vehicle, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DISABLE_TOWING(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DISABLE_TOWING(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_HAS_LANDING_GEAR(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_HAS_LANDING_GEAR(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_CONTROL_LANDING_GEAR(Vehicle vehicle, int state)
	{
		VEHICLE::CONTROL_LANDING_GEAR(vehicle, state);
	}

	static int LUA_NATIVE_VEHICLE_GET_LANDING_GEAR_STATE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_LANDING_GEAR_STATE(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_ANY_VEHICLE_NEAR_POINT(float x, float y, float z, float radius)
	{
		auto retval = (bool)VEHICLE::IS_ANY_VEHICLE_NEAR_POINT(x, y, z, radius);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)
	{
		VEHICLE::REQUEST_VEHICLE_HIGH_DETAIL_MODEL(vehicle);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_NUM_DRIVE_GEARS_(Hash vehicleModel)
	{
		auto retval = VEHICLE::_GET_VEHICLE_MODEL_NUM_DRIVE_GEARS(vehicleModel);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_DRIVE_GEAR_COUNT_(Vehicle vehicle)
	{
		auto retval = VEHICLE::_GET_VEHICLE_MAX_DRIVE_GEAR_COUNT(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_CURRENT_DRIVE_GEAR_(Vehicle vehicle)
	{
		auto retval = VEHICLE::_GET_VEHICLE_CURRENT_DRIVE_GEAR(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CURRENT_REV_RATIO_(Vehicle vehicle)
	{
		auto retval = VEHICLE::_GET_VEHICLE_CURRENT_REV_RATIO(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle)
	{
		VEHICLE::REMOVE_VEHICLE_HIGH_DETAIL_MODEL(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_HIGH_DETAIL(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_HIGH_DETAIL(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_ASSET(Hash vehicleHash, int vehicleAsset)
	{
		VEHICLE::REQUEST_VEHICLE_ASSET(vehicleHash, vehicleAsset);
	}

	static bool LUA_NATIVE_VEHICLE_HAS_VEHICLE_ASSET_LOADED(int vehicleAsset)
	{
		auto retval = (bool)VEHICLE::HAS_VEHICLE_ASSET_LOADED(vehicleAsset);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_ASSET(int vehicleAsset)
	{
		VEHICLE::REMOVE_VEHICLE_ASSET(vehicleAsset);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TOW_TRUCK_ARM_POSITION(Vehicle vehicle, float position)
	{
		VEHICLE::SET_VEHICLE_TOW_TRUCK_ARM_POSITION(vehicle, position);
	}

	static void LUA_NATIVE_VEHICLE_SET_ATTACHED_VEHICLE_TO_TOW_TRUCK_ARM_(Vehicle towTruck, Vehicle vehicle)
	{
		VEHICLE::_SET_ATTACHED_VEHICLE_TO_TOW_TRUCK_ARM(towTruck, vehicle);
	}

	static void LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle, bool rear, float hookOffsetX, float hookOffsetY, float hookOffsetZ)
	{
		VEHICLE::ATTACH_VEHICLE_TO_TOW_TRUCK(towTruck, vehicle, rear, hookOffsetX, hookOffsetY, hookOffsetZ);
	}

	static void LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)
	{
		VEHICLE::DETACH_VEHICLE_FROM_TOW_TRUCK(towTruck, vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(towTruck, vehicle);
		return retval;
	}

	static Entity LUA_NATIVE_VEHICLE_GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck)
	{
		auto retval = VEHICLE::GET_ENTITY_ATTACHED_TO_TOW_TRUCK(towTruck);
		return retval;
	}

	static Entity LUA_NATIVE_VEHICLE_SET_VEHICLE_AUTOMATICALLY_ATTACHES(Vehicle vehicle, bool p1, Any p2)
	{
		auto retval = VEHICLE::SET_VEHICLE_AUTOMATICALLY_ATTACHES(vehicle, p1, p2);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BULLDOZER_ARM_POSITION(Vehicle vehicle, float position, bool p2)
	{
		VEHICLE::SET_VEHICLE_BULLDOZER_ARM_POSITION(vehicle, position, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TANK_TURRET_POSITION(Vehicle vehicle, float position, bool p2)
	{
		VEHICLE::SET_VEHICLE_TANK_TURRET_POSITION(vehicle, position, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TURRET_TARGET(Vehicle vehicle, bool p1, float x, float y, float z, bool p5)
	{
		VEHICLE::SET_VEHICLE_TURRET_TARGET(vehicle, p1, x, y, z, p5);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TANK_STATIONARY(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_TANK_STATIONARY(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TURRET_SPEED_THIS_FRAME(Vehicle vehicle, float speed)
	{
		VEHICLE::SET_VEHICLE_TURRET_SPEED_THIS_FRAME(vehicle, speed);
	}

	static void LUA_NATIVE_VEHICLE_DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME(Vehicle vehicle)
	{
		VEHICLE::DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle vehicle, float angleRatio)
	{
		VEHICLE::SET_VEHICLE_FLIGHT_NOZZLE_POSITION(vehicle, angleRatio);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE(Vehicle vehicle, float angle)
	{
		VEHICLE::SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE(vehicle, angle);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle plane)
	{
		auto retval = VEHICLE::GET_VEHICLE_FLIGHT_NOZZLE_POSITION(plane);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION(vehicle, toggle);
	}

	static std::tuple<bool, Vector3, Vector3> LUA_NATIVE_VEHICLE_GENERATE_VEHICLE_CREATION_POS_FROM_PATHS(Vector3 outVec, Any p1, Vector3 outVec1, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8)
	{
		std::tuple<bool, Vector3, Vector3> return_values;
		std::get<0>(return_values) = (bool)VEHICLE::GENERATE_VEHICLE_CREATION_POS_FROM_PATHS(&outVec, p1, &outVec1, p3, p4, p5, p6, p7, p8);
		std::get<1>(return_values) = outVec;
		std::get<2>(return_values) = outVec1;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BURNOUT(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_BURNOUT(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_IN_BURNOUT(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_IN_BURNOUT(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_REDUCE_GRIP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_REDUCE_GRIP_LEVEL(Vehicle vehicle, int val)
	{
		VEHICLE::SET_VEHICLE_REDUCE_GRIP_LEVEL(vehicle, val);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, bool toggle)
	{
		VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(vehicle, turnSignal, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_BRAKE_LIGHTS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TAIL_LIGHTS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_TAIL_LIGHTS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HANDBRAKE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_HANDBRAKE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BRAKE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_BRAKE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_INSTANTLY_FILL_VEHICLE_POPULATION()
	{
		VEHICLE::INSTANTLY_FILL_VEHICLE_POPULATION();
	}

	static bool LUA_NATIVE_VEHICLE_HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED()
	{
		auto retval = (bool)VEHICLE::HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED();
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL(bool toggle)
	{
		VEHICLE::NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL(toggle);
	}

	static void LUA_NATIVE_VEHICLE_NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL(int p0)
	{
		VEHICLE::NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL(p0);
	}

	static std::tuple<bool, Vehicle> LUA_NATIVE_VEHICLE_GET_VEHICLE_TRAILER_VEHICLE(Vehicle vehicle, Vehicle trailer)
	{
		std::tuple<bool, Vehicle> return_values;
		std::get<0>(return_values) = (bool)VEHICLE::GET_VEHICLE_TRAILER_VEHICLE(vehicle, &trailer);
		std::get<1>(return_values) = trailer;

		return return_values;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_VEHICLE_TRAILER_PARENT_VEHICLE_(Vehicle trailer)
	{
		auto retval = VEHICLE::_GET_VEHICLE_TRAILER_PARENT_VEHICLE(trailer);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USES_LARGE_REAR_RAMP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_USES_LARGE_REAR_RAMP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_RUDDER_BROKEN(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_RUDDER_BROKEN(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_CONVERTIBLE_ROOF_LATCH_STATE(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_CONVERTIBLE_ROOF_LATCH_STATE(vehicle, state);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_ESTIMATED_MAX_SPEED(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_BRAKING(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_MAX_BRAKING(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_TRACTION(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_MAX_TRACTION(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_ACCELERATION(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_ACCELERATION(vehicle);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_MAX_BRAKING(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_MAX_TRACTION(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_MAX_TRACTION(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_ACCELERATION(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_ACCELERATION(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_FLYING_VEHICLE_MODEL_AGILITY(Hash modelHash)
	{
		auto retval = VEHICLE::GET_FLYING_VEHICLE_MODEL_AGILITY(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_BOAT_VEHICLE_MODEL_AGILITY(Hash modelHash)
	{
		auto retval = VEHICLE::GET_BOAT_VEHICLE_MODEL_AGILITY(modelHash);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED(int vehicleClass)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED(vehicleClass);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_TRACTION(int vehicleClass)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS_MAX_TRACTION(vehicleClass);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_AGILITY(int vehicleClass)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS_MAX_AGILITY(vehicleClass);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_ACCELERATION(int vehicleClass)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS_MAX_ACCELERATION(vehicleClass);
		return retval;
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_BRAKING(int vehicleClass)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS_MAX_BRAKING(vehicleClass);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_ADD_ROAD_NODE_SPEED_ZONE(float x, float y, float z, float radius, float speed, bool p5)
	{
		auto retval = VEHICLE::ADD_ROAD_NODE_SPEED_ZONE(x, y, z, radius, speed, p5);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_REMOVE_ROAD_NODE_SPEED_ZONE(int speedzone)
	{
		auto retval = (bool)VEHICLE::REMOVE_ROAD_NODE_SPEED_ZONE(speedzone);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_OPEN_BOMB_BAY_DOORS(Vehicle vehicle)
	{
		VEHICLE::OPEN_BOMB_BAY_DOORS(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_CLOSE_BOMB_BAY_DOORS(Vehicle vehicle)
	{
		VEHICLE::CLOSE_BOMB_BAY_DOORS(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_ARE_BOMB_BAY_DOORS_OPEN(Vehicle aircraft)
	{
		auto retval = (bool)VEHICLE::GET_ARE_BOMB_BAY_DOORS_OPEN(aircraft);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_SEARCHLIGHT_ON(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_SEARCHLIGHT(Vehicle heli, bool toggle, bool canBeUsedByAI)
	{
		VEHICLE::SET_VEHICLE_SEARCHLIGHT(heli, toggle, canBeUsedByAI);
	}

	static bool LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_SEARCHLIGHT(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DOES_VEHICLE_HAVE_SEARCHLIGHT(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_ENTRY_POINT_FOR_SEAT_CLEAR(Ped ped, Vehicle vehicle, int seatIndex, bool side, bool onEnter)
	{
		auto retval = (bool)VEHICLE::IS_ENTRY_POINT_FOR_SEAT_CLEAR(ped, vehicle, seatIndex, side, onEnter);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_ENTRY_POINT_POSITION(Vehicle vehicle, int doorId)
	{
		auto retval = VEHICLE::GET_ENTRY_POINT_POSITION(vehicle, doorId);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_CAN_SHUFFLE_SEAT(Vehicle vehicle, int seatIndex)
	{
		auto retval = (bool)VEHICLE::CAN_SHUFFLE_SEAT(vehicle, seatIndex);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_NUM_MOD_KITS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_NUM_MOD_KITS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD_KIT(Vehicle vehicle, int modKit)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, modKit);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_KIT(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_KIT(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_KIT_TYPE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_KIT_TYPE(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType)
	{
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, WheelType);
	}

	static int LUA_NATIVE_VEHICLE_GET_NUM_MOD_COLORS(int paintType, bool p1)
	{
		auto retval = VEHICLE::GET_NUM_MOD_COLORS(paintType, p1);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int pearlescentColor)
	{
		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle, paintType, color, pearlescentColor);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color)
	{
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle, paintType, color);
	}

	static std::tuple<int, int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int pearlescentColor)
	{
		std::tuple<int, int, int> return_values;
		VEHICLE::GET_VEHICLE_MOD_COLOR_1(vehicle, &paintType, &color, &pearlescentColor);
		std::get<0>(return_values) = paintType;
		std::get<1>(return_values) = color;
		std::get<2>(return_values) = pearlescentColor;

		return return_values;
	}

	static std::tuple<int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color)
	{
		std::tuple<int, int> return_values;
		VEHICLE::GET_VEHICLE_MOD_COLOR_2(vehicle, &paintType, &color);
		std::get<0>(return_values) = paintType;
		std::get<1>(return_values) = color;

		return return_values;
	}

	static const char* LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_1_NAME(Vehicle vehicle, bool p1)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_COLOR_1_NAME(vehicle, p1);
		return retval;
	}

	static const char* LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_2_NAME(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_COLOR_2_NAME(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_HAVE_VEHICLE_MODS_STREAMED_IN(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::HAVE_VEHICLE_MODS_STREAMED_IN(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_MOD_GEN9_EXCLUSIVE(Vehicle vehicle, int modType, int modIndex)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_MOD_GEN9_EXCLUSIVE(vehicle, modType, modIndex);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex, bool customTires)
	{
		VEHICLE::SET_VEHICLE_MOD(vehicle, modType, modIndex, customTires);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD(Vehicle vehicle, int modType)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD(vehicle, modType);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int modType)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, modType);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_NUM_VEHICLE_MODS(Vehicle vehicle, int modType)
	{
		auto retval = VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, modType);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_MOD(Vehicle vehicle, int modType)
	{
		VEHICLE::REMOVE_VEHICLE_MOD(vehicle, modType);
	}

	static void LUA_NATIVE_VEHICLE_TOGGLE_VEHICLE_MOD(Vehicle vehicle, int modType, bool toggle)
	{
		VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, modType, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_TOGGLE_MOD_ON(Vehicle vehicle, int modType)
	{
		auto retval = (bool)VEHICLE::IS_TOGGLE_MOD_ON(vehicle, modType);
		return retval;
	}

	static const char* LUA_NATIVE_VEHICLE_GET_MOD_TEXT_LABEL(Vehicle vehicle, int modType, int modValue)
	{
		auto retval = VEHICLE::GET_MOD_TEXT_LABEL(vehicle, modType, modValue);
		return retval;
	}

	static const char* LUA_NATIVE_VEHICLE_GET_MOD_SLOT_NAME(Vehicle vehicle, int modType)
	{
		auto retval = VEHICLE::GET_MOD_SLOT_NAME(vehicle, modType);
		return retval;
	}

	static const char* LUA_NATIVE_VEHICLE_GET_LIVERY_NAME(Vehicle vehicle, int liveryIndex)
	{
		auto retval = VEHICLE::GET_LIVERY_NAME(vehicle, liveryIndex);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_MODIFIER_VALUE(Vehicle vehicle, int modType, int modIndex)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_MODIFIER_VALUE(vehicle, modType, modIndex);
		return retval;
	}

	static Hash LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_IDENTIFIER_HASH(Vehicle vehicle, int modType, int modIndex)
	{
		auto retval = VEHICLE::GET_VEHICLE_MOD_IDENTIFIER_HASH(vehicle, modType, modIndex);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_PRELOAD_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex)
	{
		VEHICLE::PRELOAD_VEHICLE_MOD(vehicle, modType, modIndex);
	}

	static bool LUA_NATIVE_VEHICLE_HAS_PRELOAD_MODS_FINISHED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::HAS_PRELOAD_MODS_FINISHED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_RELEASE_PRELOAD_MODS(Vehicle vehicle)
	{
		VEHICLE::RELEASE_PRELOAD_MODS(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int r, int g, int b)
	{
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, r, g, b);
	}

	static std::tuple<int, int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int tint)
	{
		VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, tint);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_WINDOW_TINT(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_NUM_VEHICLE_WINDOW_TINTS()
	{
		auto retval = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
		return retval;
	}

	static std::tuple<int, int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOR(Vehicle vehicle, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		VEHICLE::GET_VEHICLE_COLOR(vehicle, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET(vehicle);
		return retval;
	}

	static Hash LUA_NATIVE_VEHICLE_GET_VEHICLE_CAUSE_OF_DESTRUCTION(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_CAUSE_OF_DESTRUCTION(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_OVERRIDE_PLANE_DAMAGE_THREHSOLD(Vehicle vehicle, float health)
	{
		VEHICLE::OVERRIDE_PLANE_DAMAGE_THREHSOLD(vehicle, health);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRANSMISSION_REDUCED_GEAR_RATIO_(Vehicle vehicle, bool toggle)
	{
		VEHICLE::_SET_TRANSMISSION_REDUCED_GEAR_RATIO(vehicle, toggle);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_DESIRED_DRIVE_GEAR_(Vehicle vehicle)
	{
		auto retval = VEHICLE::_GET_VEHICLE_DESIRED_DRIVE_GEAR(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_MODIFY_VEHICLE_TOP_SPEED(Vehicle vehicle, float value)
	{
		VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, value);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_MAX_SPEED(Vehicle vehicle, float speed)
	{
		VEHICLE::SET_VEHICLE_MAX_SPEED(vehicle, speed);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE(Vehicle vehicle, bool toggle, float p2)
	{
		VEHICLE::SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE(vehicle, toggle, p2);
	}

	static int LUA_NATIVE_VEHICLE_ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6)
	{
		auto retval = VEHICLE::ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA(p0, p1, p2, p3, p4, p5, p6);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA(int p0)
	{
		VEHICLE::REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA(p0);
	}

	static bool LUA_NATIVE_VEHICLE_IS_ANY_PED_RAPPELLING_FROM_HELI(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_ANY_PED_RAPPELLING_FROM_HELI(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CHEAT_POWER_INCREASE(Vehicle vehicle, float value)
	{
		VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(vehicle, value);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_INFLUENCES_WANTED_LEVEL(Any p0, bool p1)
	{
		VEHICLE::SET_VEHICLE_INFLUENCES_WANTED_LEVEL(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_WANTED(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_VEHICLE_IS_WANTED(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SWING_BOAT_BOOM_TO_RATIO(Vehicle vehicle, float ratio)
	{
		VEHICLE::SWING_BOAT_BOOM_TO_RATIO(vehicle, ratio);
	}

	static void LUA_NATIVE_VEHICLE_SWING_BOAT_BOOM_FREELY(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SWING_BOAT_BOOM_FREELY(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_ALLOW_BOAT_BOOM_TO_ANIMATE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::ALLOW_BOAT_BOOM_TO_ANIMATE(vehicle, toggle);
	}

	static float LUA_NATIVE_VEHICLE_GET_BOAT_BOOM_POSITION_RATIO(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_BOAT_BOOM_POSITION_RATIO(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_DISABLE_PLANE_AILERON(Vehicle vehicle, bool p1, bool p2)
	{
		VEHICLE::DISABLE_PLANE_AILERON(vehicle, p1, p2);
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_ENGINE_RUNNING(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_ALTERNATE_HANDLING(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_USE_ALTERNATE_HANDLING(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_BIKE_ON_STAND(Vehicle vehicle, float x, float y)
	{
		VEHICLE::SET_BIKE_ON_STAND(vehicle, x, y);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NOT_STEALABLE_AMBIENTLY(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_NOT_STEALABLE_AMBIENTLY(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_LOCK_DOORS_WHEN_NO_LONGER_NEEDED(Vehicle vehicle)
	{
		VEHICLE::LOCK_DOORS_WHEN_NO_LONGER_NEEDED(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_LAST_DRIVEN_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::SET_LAST_DRIVEN_VEHICLE(vehicle);
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_LAST_DRIVEN_VEHICLE()
	{
		auto retval = VEHICLE::GET_LAST_DRIVEN_VEHICLE();
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_LAST_DRIVEN_VEHICLE()
	{
		VEHICLE::CLEAR_LAST_DRIVEN_VEHICLE();
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN(Vehicle plane, int height)
	{
		VEHICLE::SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN(plane, height);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_LOD_MULTIPLIER(Vehicle vehicle, float multiplier)
	{
		VEHICLE::SET_VEHICLE_LOD_MULTIPLIER(vehicle, multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_SAVE_IN_GARAGE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_SAVE_IN_GARAGE(vehicle, toggle);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET(Any p0, bool p1)
	{
		VEHICLE::SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_COPY_VEHICLE_DAMAGES(Vehicle sourceVehicle, Vehicle targetVehicle)
	{
		VEHICLE::COPY_VEHICLE_DAMAGES(sourceVehicle, targetVehicle);
	}

	static void LUA_NATIVE_VEHICLE_DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS()
	{
		VEHICLE::DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS();
	}

	static void LUA_NATIVE_VEHICLE_SET_LIGHTS_CUTOFF_DISTANCE_TWEAK(float distance)
	{
		VEHICLE::SET_LIGHTS_CUTOFF_DISTANCE_TWEAK(distance);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_SHOOT_AT_TARGET(Ped driver, Entity entity, float xTarget, float yTarget, float zTarget)
	{
		VEHICLE::SET_VEHICLE_SHOOT_AT_TARGET(driver, entity, xTarget, yTarget, zTarget);
	}

	static std::tuple<bool, Entity> LUA_NATIVE_VEHICLE_GET_VEHICLE_LOCK_ON_TARGET(Vehicle vehicle, Entity entity)
	{
		std::tuple<bool, Entity> return_values;
		std::get<0>(return_values) = (bool)VEHICLE::GET_VEHICLE_LOCK_ON_TARGET(vehicle, &entity);
		std::get<1>(return_values) = entity;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_SET_FORCE_HD_VEHICLE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_FORCE_HD_VEHICLE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS(Vehicle vehicle, float p1)
	{
		VEHICLE::SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS(vehicle, p1);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_PLATE_TYPE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_PLATE_TYPE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_TRACK_VEHICLE_VISIBILITY(Vehicle vehicle)
	{
		VEHICLE::TRACK_VEHICLE_VISIBILITY(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_VISIBLE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_VISIBLE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_GRAVITY(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_GRAVITY(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_ENABLE_VEHICLE_SLIPSTREAMING(bool toggle)
	{
		VEHICLE::SET_ENABLE_VEHICLE_SLIPSTREAMING(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT(bool toggle)
	{
		VEHICLE::SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT(toggle);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_PRODUCING_SLIP_STREAM(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_PRODUCING_SLIP_STREAM(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_INACTIVE_DURING_PLAYBACK(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_INACTIVE_DURING_PLAYBACK(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ACTIVE_DURING_PLAYBACK(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_ACTIVE_DURING_PLAYBACK(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_SPRAYABLE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_SPRAYABLE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ENGINE_CAN_DEGRADE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle, int p1, int p2)
	{
		VEHICLE::DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES(vehicle, p1, p2);
	}

	static void LUA_NATIVE_VEHICLE_ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle)
	{
		VEHICLE::ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_PLANE_LANDING_GEAR_INTACT(Vehicle plane)
	{
		auto retval = (bool)VEHICLE::IS_PLANE_LANDING_GEAR_INTACT(plane);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_ARE_PLANE_PROPELLERS_INTACT(Vehicle plane)
	{
		auto retval = (bool)VEHICLE::ARE_PLANE_PROPELLERS_INTACT(plane);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_SET_PLANE_PROPELLER_HEALTH(Vehicle plane, float health)
	{
		auto retval = (bool)VEHICLE::SET_PLANE_PROPELLER_HEALTH(plane, health);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_DEFORM_WHEELS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_DEFORM_WHEELS(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_STOLEN(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_STOLEN(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_STOLEN(Vehicle vehicle, bool isStolen)
	{
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, isStolen);
	}

	static void LUA_NATIVE_VEHICLE_SET_PLANE_TURBULENCE_MULTIPLIER(Vehicle vehicle, float multiplier)
	{
		VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(vehicle, multiplier);
	}

	static bool LUA_NATIVE_VEHICLE_ARE_WINGS_OF_PLANE_INTACT(Vehicle plane)
	{
		auto retval = (bool)VEHICLE::ARE_WINGS_OF_PLANE_INTACT(plane);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS(Vehicle vehicle)
	{
		VEHICLE::ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_CARGOBOB(Vehicle vehicle, Vehicle cargobob)
	{
		VEHICLE::DETACH_VEHICLE_FROM_CARGOBOB(vehicle, cargobob);
	}

	static bool LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_ANY_CARGOBOB(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DETACH_VEHICLE_FROM_ANY_CARGOBOB(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_DETACH_ENTITY_FROM_CARGOBOB(Vehicle cargobob, Entity entity)
	{
		auto retval = (bool)VEHICLE::DETACH_ENTITY_FROM_CARGOBOB(cargobob, entity);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicleAttached)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_ATTACHED_TO_CARGOBOB(cargobob, vehicleAttached);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob)
	{
		auto retval = VEHICLE::GET_VEHICLE_ATTACHED_TO_CARGOBOB(cargobob);
		return retval;
	}

	static Entity LUA_NATIVE_VEHICLE_GET_ENTITY_ATTACHED_TO_CARGOBOB(Any p0)
	{
		auto retval = VEHICLE::GET_ENTITY_ATTACHED_TO_CARGOBOB(p0);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicle, int p2, float x, float y, float z)
	{
		VEHICLE::ATTACH_VEHICLE_TO_CARGOBOB(cargobob, vehicle, p2, x, y, z);
	}

	static void LUA_NATIVE_VEHICLE_ATTACH_ENTITY_TO_CARGOBOB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		VEHICLE::ATTACH_ENTITY_TO_CARGOBOB(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE(Vehicle cargobob, bool toggle)
	{
		VEHICLE::SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE(cargobob, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY(Any p0, Any p1)
	{
		VEHICLE::SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY(p0, p1);
	}

	static bool LUA_NATIVE_VEHICLE_CAN_CARGOBOB_PICK_UP_ENTITY(Any p0, Any p1)
	{
		auto retval = (bool)VEHICLE::CAN_CARGOBOB_PICK_UP_ENTITY(p0, p1);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_GET_ATTACHED_PICK_UP_HOOK_POSITION(Vehicle cargobob)
	{
		auto retval = VEHICLE::GET_ATTACHED_PICK_UP_HOOK_POSITION(cargobob);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_DOES_CARGOBOB_HAVE_PICK_UP_ROPE(Vehicle cargobob)
	{
		auto retval = (bool)VEHICLE::DOES_CARGOBOB_HAVE_PICK_UP_ROPE(cargobob);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_CREATE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob, int state)
	{
		VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(cargobob, state);
	}

	static void LUA_NATIVE_VEHICLE_REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob)
	{
		VEHICLE::REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(cargobob);
	}

	static void LUA_NATIVE_VEHICLE_SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB(Vehicle cargobob, float length1, float length2, bool p3)
	{
		VEHICLE::SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB(cargobob, length1, length2, p3);
	}

	static void LUA_NATIVE_VEHICLE_SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB(Any p0, Any p1, Any p2)
	{
		VEHICLE::SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB(p0, p1, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER(Any p0, Any p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_ROPE_TYPE(Any p0, Any p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_ROPE_TYPE(p0, p1);
	}

	static bool LUA_NATIVE_VEHICLE_DOES_CARGOBOB_HAVE_PICKUP_MAGNET(Vehicle cargobob)
	{
		auto retval = (bool)VEHICLE::DOES_CARGOBOB_HAVE_PICKUP_MAGNET(cargobob);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(Vehicle cargobob, bool isActive)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(cargobob, isActive);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(Vehicle cargobob, float strength)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(cargobob, strength);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_FALLOFF(Vehicle cargobob, float p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_FALLOFF(cargobob, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH(Vehicle cargobob, float p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH(cargobob, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF(Vehicle cargobob, float p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF(cargobob, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH(Vehicle cargobob, float p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH(cargobob, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH(Vehicle vehicle, float p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE(Vehicle vehicle, Vehicle cargobob)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE(vehicle, cargobob);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE(Vehicle vehicle, bool p1, bool p2)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE(vehicle, p1, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT(vehicle, p1);
	}

	static bool LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_DISABLE_VEHICLE_WEAPON(bool disabled, Hash weaponHash, Vehicle vehicle, Ped owner)
	{
		VEHICLE::DISABLE_VEHICLE_WEAPON(disabled, weaponHash, vehicle, owner);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_WEAPON_DISABLED(Hash weaponHash, Vehicle vehicle, Ped owner)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_WEAPON_DISABLED(weaponHash, vehicle, owner);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USED_FOR_PILOT_SCHOOL(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_USED_FOR_PILOT_SCHOOL(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION(vehicle, toggle);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS(vehicle);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_FROM_NAME(Hash modelHash)
	{
		auto retval = VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(modelHash);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle)
	{
		VEHICLE::SET_PLAYERS_LAST_VEHICLE(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR(Vehicle vehicle, float p1)
	{
		VEHICLE::SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_IMPATIENCE_TIMER(Vehicle vehicle, Any p1)
	{
		VEHICLE::SET_VEHICLE_IMPATIENCE_TIMER(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_HANDLING_OVERRIDE(Vehicle vehicle, Hash hash)
	{
		VEHICLE::SET_VEHICLE_HANDLING_OVERRIDE(vehicle, hash);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTENDED_REMOVAL_RANGE(Vehicle vehicle, int range)
	{
		VEHICLE::SET_VEHICLE_EXTENDED_REMOVAL_RANGE(vehicle, range);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_STEERING_BIAS_SCALAR(Any p0, float p1)
	{
		VEHICLE::SET_VEHICLE_STEERING_BIAS_SCALAR(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_CONTROL_LAGGING_RATE_SCALAR(Vehicle helicopter, float multiplier)
	{
		VEHICLE::SET_HELI_CONTROL_LAGGING_RATE_SCALAR(helicopter, multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FRICTION_OVERRIDE(Vehicle vehicle, float friction)
	{
		VEHICLE::SET_VEHICLE_FRICTION_OVERRIDE(vehicle, friction);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_ARE_PLANE_CONTROL_PANELS_INTACT(Vehicle vehicle, bool p1)
	{
		auto retval = (bool)VEHICLE::ARE_PLANE_CONTROL_PANELS_INTACT(vehicle, p1);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_CEILING_HEIGHT(Vehicle vehicle, float height)
	{
		VEHICLE::SET_VEHICLE_CEILING_HEIGHT(vehicle, height);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_ROUTE_HISTORY(Vehicle vehicle)
	{
		VEHICLE::CLEAR_VEHICLE_ROUTE_HISTORY(vehicle);
	}

	static Vehicle LUA_NATIVE_VEHICLE_DOES_VEHICLE_EXIST_WITH_DECORATOR(sol::stack_object decorator)
	{
		auto retval = VEHICLE::DOES_VEHICLE_EXIST_WITH_DECORATOR(decorator.is<const char*>() ? decorator.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_EXCLUSIVE_DRIVER(Vehicle vehicle, Ped ped, int index)
	{
		VEHICLE::SET_VEHICLE_EXCLUSIVE_DRIVER(vehicle, ped, index);
	}

	static std::tuple<bool, int> LUA_NATIVE_VEHICLE_IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE(Ped ped, Vehicle vehicle, int outIndex)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)VEHICLE::IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE(ped, vehicle, &outIndex);
		std::get<1>(return_values) = outIndex;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_DISABLE_INDIVIDUAL_PLANE_PROPELLER(Vehicle vehicle, int propeller)
	{
		VEHICLE::DISABLE_INDIVIDUAL_PLANE_PROPELLER(vehicle, propeller);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_FORCE_AFTERBURNER(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_FORCE_AFTERBURNER(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DONT_PROCESS_VEHICLE_GLASS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DONT_PROCESS_VEHICLE_GLASS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_WANTED_CONES_RESPONSE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_WANTED_CONES_RESPONSE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK(Vehicle vehicle, float p1)
	{
		VEHICLE::SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_READY_FOR_CLEANUP(Any p0)
	{
		VEHICLE::SET_VEHICLE_READY_FOR_CLEANUP(p0);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISTANT_CARS_ENABLED(bool toggle)
	{
		VEHICLE::SET_DISTANT_CARS_ENABLED(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int r, int g, int b)
	{
		VEHICLE::SET_VEHICLE_NEON_COLOUR(vehicle, r, g, b);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NEON_INDEX_COLOUR(Vehicle vehicle, int index)
	{
		VEHICLE::SET_VEHICLE_NEON_INDEX_COLOUR(vehicle, index);
	}

	static std::tuple<int, int, int> LUA_NATIVE_VEHICLE_GET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int r, int g, int b)
	{
		std::tuple<int, int, int> return_values;
		VEHICLE::GET_VEHICLE_NEON_COLOUR(vehicle, &r, &g, &b);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;

		return return_values;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index, bool toggle)
	{
		VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, index, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, index);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_AMBIENT_VEHICLE_NEON_ENABLED(bool p0)
	{
		VEHICLE::SET_AMBIENT_VEHICLE_NEON_ENABLED(p0);
	}

	static void LUA_NATIVE_VEHICLE_SUPPRESS_NEONS_ON_VEHICLE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SUPPRESS_NEONS_ON_VEHICLE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_SUPERDUMMY(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_DISABLE_SUPERDUMMY(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_DIAL(Vehicle vehicle)
	{
		VEHICLE::REQUEST_VEHICLE_DIAL(vehicle);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_BODY_HEALTH(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_BODY_HEALTH(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BODY_HEALTH(Vehicle vehicle, float value)
	{
		VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, value);
	}

	static std::tuple<Vector3, Vector3> LUA_NATIVE_VEHICLE_GET_VEHICLE_SIZE(Vehicle vehicle, Vector3 out1, Vector3 out2)
	{
		std::tuple<Vector3, Vector3> return_values;
		VEHICLE::GET_VEHICLE_SIZE(vehicle, &out1, &out2);
		std::get<0>(return_values) = out1;
		std::get<1>(return_values) = out2;

		return return_values;
	}

	static float LUA_NATIVE_VEHICLE_GET_FAKE_SUSPENSION_LOWERING_AMOUNT(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_FAKE_SUSPENSION_LOWERING_AMOUNT(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(float multiplier)
	{
		VEHICLE::SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(multiplier);
	}

	static int LUA_NATIVE_VEHICLE_GET_NUMBER_OF_VEHICLE_DOORS(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_HYDRAULICS_CONTROL(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_HYDRAULICS_CONTROL(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_CAN_ADJUST_GROUND_CLEARANCE(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_CAN_ADJUST_GROUND_CLEARANCE(vehicle, p1);
	}

	static float LUA_NATIVE_VEHICLE_GET_VEHICLE_HEALTH_PERCENTAGE(Vehicle vehicle, float maxEngineHealth, float maxPetrolTankHealth, float maxBodyHealth, float maxMainRotorHealth, float maxTailRotorHealth, float maxUnkHealth)
	{
		auto retval = VEHICLE::GET_VEHICLE_HEALTH_PERCENTAGE(vehicle, maxEngineHealth, maxPetrolTankHealth, maxBodyHealth, maxMainRotorHealth, maxTailRotorHealth, maxUnkHealth);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_IS_MERCENARY(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_IS_MERCENARY(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_KERS_ALLOWED(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_KERS_ALLOWED(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_HAS_KERS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_HAS_KERS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_PLANE_RESIST_TO_EXPLOSION(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_PLANE_RESIST_TO_EXPLOSION(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_RESIST_TO_EXPLOSION(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_HELI_RESIST_TO_EXPLOSION(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_BMX_EXTRA_TRICK_FORCES(Any p0)
	{
		VEHICLE::SET_DISABLE_BMX_EXTRA_TRICK_FORCES(p0);
	}

	static void LUA_NATIVE_VEHICLE_SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId, float value)
	{
		VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(vehicle, wheelId, value);
	}

	static float LUA_NATIVE_VEHICLE_GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId)
	{
		auto retval = VEHICLE::GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(vehicle, wheelId);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_CAN_USE_HYDRAULICS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_CAN_USE_HYDRAULICS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_HYDRAULIC_VEHICLE_STATE(Vehicle vehicle, int state)
	{
		VEHICLE::SET_HYDRAULIC_VEHICLE_STATE(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_HYDRAULIC_WHEEL_STATE(Vehicle vehicle, int wheelId, int state, float value, Any p4)
	{
		VEHICLE::SET_HYDRAULIC_WHEEL_STATE(vehicle, wheelId, state, value, p4);
	}

	static bool LUA_NATIVE_VEHICLE_HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY(Any p0, Any p1)
	{
		auto retval = (bool)VEHICLE::HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT(Vehicle vehicle)
	{
		VEHICLE::CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BOBBLEHEAD_VELOCITY(float x, float y, float p2)
	{
		VEHICLE::SET_VEHICLE_BOBBLEHEAD_VELOCITY(x, y, p2);
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_IS_DUMMY(Any p0)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_IS_DUMMY(p0);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_SET_VEHICLE_DAMAGE_SCALE(Vehicle vehicle, float p1)
	{
		auto retval = (bool)VEHICLE::SET_VEHICLE_DAMAGE_SCALE(vehicle, p1);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_SET_VEHICLE_WEAPON_DAMAGE_SCALE(Vehicle vehicle, float multiplier)
	{
		auto retval = (bool)VEHICLE::SET_VEHICLE_WEAPON_DAMAGE_SCALE(vehicle, multiplier);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY(Any p0, Any p1)
	{
		auto retval = (bool)VEHICLE::SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER(Any p0, Any p1)
	{
		VEHICLE::SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_BIKE_EASY_TO_LAND(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_BIKE_EASY_TO_LAND(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_INVERT_VEHICLE_CONTROLS(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_INVERT_VEHICLE_CONTROLS(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_SPEED_BOOST_EFFECT_DISABLED(bool disabled)
	{
		VEHICLE::SET_SPEED_BOOST_EFFECT_DISABLED(disabled);
	}

	static void LUA_NATIVE_VEHICLE_SET_SLOW_DOWN_EFFECT_DISABLED(bool disabled)
	{
		VEHICLE::SET_SLOW_DOWN_EFFECT_DISABLED(disabled);
	}

	static void LUA_NATIVE_VEHICLE_SET_FORMATION_LEADER(Vehicle vehicle, float x, float y, float z, float p4)
	{
		VEHICLE::SET_FORMATION_LEADER(vehicle, x, y, z, p4);
	}

	static void LUA_NATIVE_VEHICLE_RESET_FORMATION_LEADER()
	{
		VEHICLE::RESET_FORMATION_LEADER();
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_BOAT_CAPSIZED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_BOAT_CAPSIZED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_ALLOW_RAMMING_SOOP_OR_RAMP(Any p0, Any p1)
	{
		VEHICLE::SET_ALLOW_RAMMING_SOOP_OR_RAMP(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_SCRIPT_RAMP_IMPULSE_SCALE(Vehicle vehicle, float impulseScale)
	{
		VEHICLE::SET_SCRIPT_RAMP_IMPULSE_SCALE(vehicle, impulseScale);
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_DOOR_VALID(Vehicle vehicle, int doorId)
	{
		auto retval = (bool)VEHICLE::GET_IS_DOOR_VALID(vehicle, doorId);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(Vehicle vehicle, float seconds)
	{
		VEHICLE::SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(vehicle, seconds);
	}

	static bool LUA_NATIVE_VEHICLE_GET_HAS_ROCKET_BOOST(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_HAS_ROCKET_BOOST(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_ROCKET_BOOST_ACTIVE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_ROCKET_BOOST_ACTIVE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_ROCKET_BOOST_ACTIVE(Vehicle vehicle, bool active)
	{
		VEHICLE::SET_ROCKET_BOOST_ACTIVE(vehicle, active);
	}

	static bool LUA_NATIVE_VEHICLE_GET_HAS_RETRACTABLE_WHEELS(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_HAS_RETRACTABLE_WHEELS(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_WHEELS_RETRACTED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_WHEELS_RETRACTED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_WHEELS_EXTENDED_INSTANTLY(Vehicle vehicle)
	{
		VEHICLE::SET_WHEELS_EXTENDED_INSTANTLY(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_WHEELS_RETRACTED_INSTANTLY(Vehicle vehicle)
	{
		VEHICLE::SET_WHEELS_RETRACTED_INSTANTLY(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_CAR_HAS_JUMP(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_CAR_HAS_JUMP(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_USE_HIGHER_CAR_JUMP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_USE_HIGHER_CAR_JUMP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex, int capacity)
	{
		VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(vehicle, weaponIndex, capacity);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex)
	{
		auto retval = VEHICLE::GET_VEHICLE_WEAPON_RESTRICTED_AMMO(vehicle, weaponIndex);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_HAS_PARACHUTE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_HAS_PARACHUTE(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_VEHICLE_CAN_DEPLOY_PARACHUTE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_VEHICLE_CAN_DEPLOY_PARACHUTE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_START_PARACHUTING(Vehicle vehicle, bool active)
	{
		VEHICLE::VEHICLE_START_PARACHUTING(vehicle, active);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_PARACHUTE_DEPLOYED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_VEHICLE_PARACHUTE_DEPLOYED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(Any p0, Any p1)
	{
		VEHICLE::VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(Any p0, Any p1)
	{
		VEHICLE::VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_SET_JET_WASH_FORCE_ENABLED(Any p0)
	{
		VEHICLE::VEHICLE_SET_JET_WASH_FORCE_ENABLED(p0);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT(bool toggle)
	{
		VEHICLE::SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_HORN_BUTTON_FOR_NITROUS_(bool toggle)
	{
		VEHICLE::_SET_VEHICLE_USE_HORN_BUTTON_FOR_NITROUS(toggle);
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(Vehicle vehicle, Hash modelHash)
	{
		VEHICLE::VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(vehicle, modelHash);
	}

	static void LUA_NATIVE_VEHICLE_VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX(Vehicle vehicle, int textureVariation)
	{
		VEHICLE::VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX(vehicle, textureVariation);
	}

	static int LUA_NATIVE_VEHICLE_VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO(Any p0, Any p1)
	{
		auto retval = VEHICLE::VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO(Any p0, Any p1)
	{
		auto retval = VEHICLE::VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_VEHICLE_SET_OVERRIDE_SIDE_RATIO(Any p0, Any p1)
	{
		auto retval = VEHICLE::VEHICLE_SET_OVERRIDE_SIDE_RATIO(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_ALL_VEHICLES(uintptr_t vehsStruct)
	{
		auto retval = VEHICLE::GET_ALL_VEHICLES((Any*)vehsStruct);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_CARGOBOB_EXTA_PICKUP_RANGE(Any p0, Any p1)
	{
		VEHICLE::SET_CARGOBOB_EXTA_PICKUP_RANGE(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_OVERRIDE_VEHICLE_DOOR_TORQUE(Any p0, Any p1, Any p2)
	{
		VEHICLE::SET_OVERRIDE_VEHICLE_DOOR_TORQUE(p0, p1, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_WHEELIE_ENABLED(Vehicle vehicle, bool enabled)
	{
		VEHICLE::SET_WHEELIE_ENABLED(vehicle, enabled);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE(Any p0, Any p1)
	{
		VEHICLE::SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION(Vehicle vehicle, float value)
	{
		VEHICLE::SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION(vehicle, value);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRAILER_ATTACHMENT_ENABLED(Any p0, Any p1)
	{
		VEHICLE::SET_TRAILER_ATTACHMENT_ENABLED(p0, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_ROCKET_BOOST_FILL(Vehicle vehicle, float percentage)
	{
		VEHICLE::SET_ROCKET_BOOST_FILL(vehicle, percentage);
	}

	static void LUA_NATIVE_VEHICLE_SET_GLIDER_ACTIVE(Vehicle vehicle, bool state)
	{
		VEHICLE::SET_GLIDER_ACTIVE(vehicle, state);
	}

	static void LUA_NATIVE_VEHICLE_SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS(Vehicle vehicle, bool shouldReset)
	{
		VEHICLE::SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS(vehicle, shouldReset);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION(Vehicle vehicle, bool disable)
	{
		VEHICLE::SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION(vehicle, disable);
	}

	static void LUA_NATIVE_VEHICLE_SET_GROUND_EFFECT_REDUCES_DRAG(bool toggle)
	{
		VEHICLE::SET_GROUND_EFFECT_REDUCES_DRAG(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_MAP_COLLISION(Vehicle vehicle)
	{
		VEHICLE::SET_DISABLE_MAP_COLLISION(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_PED_STAND_ON_TOP(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_PED_STAND_ON_TOP(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DAMAGE_SCALES(Vehicle vehicle, Any p1, Any p2, Any p3, Any p4)
	{
		VEHICLE::SET_VEHICLE_DAMAGE_SCALES(vehicle, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_VEHICLE_SET_PLANE_SECTION_DAMAGE_SCALE(Vehicle vehicle, Any p1, Any p2)
	{
		VEHICLE::SET_PLANE_SECTION_DAMAGE_SCALE(vehicle, p1, p2);
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_BOMB_AMMO(Vehicle vehicle, int bombCount)
	{
		VEHICLE::SET_VEHICLE_BOMB_AMMO(vehicle, bombCount);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_BOMB_AMMO(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_BOMB_AMMO(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle, int counterMeasureCount)
	{
		VEHICLE::SET_VEHICLE_COUNTERMEASURE_AMMO(vehicle, counterMeasureCount);
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_VEHICLE_COUNTERMEASURE_AMMO(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_HELI_COMBAT_OFFSET(Vehicle vehicle, float x, float y, float z)
	{
		VEHICLE::SET_HELI_COMBAT_OFFSET(vehicle, x, y, z);
	}

	static bool LUA_NATIVE_VEHICLE_GET_CAN_VEHICLE_BE_PLACED_HERE(Vehicle vehicle, float x, float y, float z, float rotX, float rotY, float rotZ, int p7, Any p8)
	{
		auto retval = (bool)VEHICLE::GET_CAN_VEHICLE_BE_PLACED_HERE(vehicle, x, y, z, rotX, rotY, rotZ, p7, p8);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_AUTOMATIC_CRASH_TASK(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_AUTOMATIC_CRASH_TASK(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_SPECIAL_FLIGHT_MODE_RATIO(Vehicle vehicle, float ratio)
	{
		VEHICLE::SET_SPECIAL_FLIGHT_MODE_RATIO(vehicle, ratio);
	}

	static void LUA_NATIVE_VEHICLE_SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(Vehicle vehicle, float targetRatio)
	{
		VEHICLE::SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(vehicle, targetRatio);
	}

	static void LUA_NATIVE_VEHICLE_SET_SPECIAL_FLIGHT_MODE_ALLOWED(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_SPECIAL_FLIGHT_MODE_ALLOWED(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_HOVER_MODE_FLIGHT(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DISABLE_HOVER_MODE_FLIGHT(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_OUTRIGGERS_DEPLOYED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_OUTRIGGERS_DEPLOYED(vehicle);
		return retval;
	}

	static Vector3 LUA_NATIVE_VEHICLE_FIND_SPAWN_COORDINATES_FOR_HELI(Ped ped)
	{
		auto retval = VEHICLE::FIND_SPAWN_COORDINATES_FOR_HELI(ped);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DEPLOY_FOLDING_WINGS(Vehicle vehicle, bool deploy, bool p2)
	{
		VEHICLE::SET_DEPLOY_FOLDING_WINGS(vehicle, deploy, p2);
	}

	static bool LUA_NATIVE_VEHICLE_ARE_FOLDING_WINGS_DEPLOYED(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::ARE_FOLDING_WINGS_DEPLOYED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DEPLOY_MISSILE_BAYS_(Vehicle vehicle, bool deploy)
	{
		VEHICLE::_SET_DEPLOY_MISSILE_BAYS(vehicle, deploy);
	}

	static bool LUA_NATIVE_VEHICLE_ARE_MISSILE_BAYS_DEPLOYED_(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::_ARE_MISSILE_BAYS_DEPLOYED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_TURRET_HIDDEN(Vehicle vehicle, int index, bool toggle)
	{
		VEHICLE::SET_TURRET_HIDDEN(vehicle, index, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_HOVER_MODE_WING_RATIO(Vehicle vehicle, float ratio)
	{
		VEHICLE::SET_HOVER_MODE_WING_RATIO(vehicle, ratio);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_TURRET_MOVEMENT(Vehicle vehicle, int turretId)
	{
		VEHICLE::SET_DISABLE_TURRET_MOVEMENT(vehicle, turretId);
	}

	static void LUA_NATIVE_VEHICLE_SET_FORCE_FIX_LINK_MATRICES(Vehicle vehicle)
	{
		VEHICLE::SET_FORCE_FIX_LINK_MATRICES(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRANSFORM_RATE_FOR_ANIMATION(Vehicle vehicle, float transformRate)
	{
		VEHICLE::SET_TRANSFORM_RATE_FOR_ANIMATION(vehicle, transformRate);
	}

	static void LUA_NATIVE_VEHICLE_SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_COMBAT_MODE(bool toggle)
	{
		VEHICLE::SET_VEHICLE_COMBAT_MODE(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_DETONATION_MODE(bool toggle)
	{
		VEHICLE::SET_VEHICLE_DETONATION_MODE(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_VEHICLE_SHUNT_ON_STICK(bool toggle)
	{
		VEHICLE::SET_VEHICLE_SHUNT_ON_STICK(toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_SHUNTING(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_VEHICLE_SHUNTING(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT(vehicle);
		return retval;
	}

	static Vehicle LUA_NATIVE_VEHICLE_GET_LAST_SHUNT_VEHICLE(Vehicle vehicle)
	{
		auto retval = VEHICLE::GET_LAST_SHUNT_VEHICLE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE(bool toggle)
	{
		VEHICLE::SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_OVERRIDE_NITROUS_LEVEL(Vehicle vehicle, bool toggle, float level, float power, float rechargeTime, bool disableSound)
	{
		VEHICLE::SET_OVERRIDE_NITROUS_LEVEL(vehicle, toggle, level, power, rechargeTime, disableSound);
	}

	static void LUA_NATIVE_VEHICLE_SET_NITROUS_IS_ACTIVE(Vehicle vehicle, bool enabled)
	{
		VEHICLE::SET_NITROUS_IS_ACTIVE(vehicle, enabled);
	}

	static void LUA_NATIVE_VEHICLE_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER_(Vehicle vehicle, float modifier)
	{
		VEHICLE::_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER(vehicle, modifier);
	}

	static void LUA_NATIVE_VEHICLE_SET_DRIFT_SLIP_ANGLE_LIMITS_(Vehicle vehicle, float durationScalar, float amplitudeScalar, float slipAngleLimit)
	{
		VEHICLE::_SET_DRIFT_SLIP_ANGLE_LIMITS(vehicle, durationScalar, amplitudeScalar, slipAngleLimit);
	}

	static void LUA_NATIVE_VEHICLE_SET_MINIMUM_TIME_BETWEEN_GEAR_SHIFTS_(Vehicle vehicle, int time)
	{
		VEHICLE::_SET_MINIMUM_TIME_BETWEEN_GEAR_SHIFTS(vehicle, time);
	}

	static void LUA_NATIVE_VEHICLE_FULLY_CHARGE_NITROUS(Vehicle vehicle)
	{
		VEHICLE::FULLY_CHARGE_NITROUS(vehicle);
	}

	static float LUA_NATIVE_VEHICLE_GET_REMAINING_NITROUS_DURATION_(Vehicle vehicle)
	{
		auto retval = VEHICLE::_GET_REMAINING_NITROUS_DURATION(vehicle);
		return retval;
	}

	static bool LUA_NATIVE_VEHICLE_IS_NITROUS_ACTIVE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::IS_NITROUS_ACTIVE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_CLEAR_NITROUS(Vehicle vehicle)
	{
		VEHICLE::CLEAR_NITROUS(vehicle);
	}

	static void LUA_NATIVE_VEHICLE_SET_INCREASE_WHEEL_CRUSH_DAMAGE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_INCREASE_WHEEL_CRUSH_DAMAGE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_WEAPON_BLADE_FORCES(bool toggle)
	{
		VEHICLE::SET_DISABLE_WEAPON_BLADE_FORCES(toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP(bool toggle)
	{
		VEHICLE::SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP(toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_DOES_VEHICLE_HAVE_TOMBSTONE(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_DOES_VEHICLE_HAVE_TOMBSTONE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_HIDE_TOMBSTONE(Vehicle vehicle, bool toggle)
	{
		VEHICLE::HIDE_TOMBSTONE(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_APPLY_EMP_EFFECT(Vehicle vehicle)
	{
		VEHICLE::APPLY_EMP_EFFECT(vehicle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_DISABLED_BY_EMP(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_IS_VEHICLE_DISABLED_BY_EMP(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_DISABLE_RETRACTING_WEAPON_BLADES(bool toggle)
	{
		VEHICLE::SET_DISABLE_RETRACTING_WEAPON_BLADES(toggle);
	}

	static float LUA_NATIVE_VEHICLE_GET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex)
	{
		auto retval = VEHICLE::GET_TYRE_HEALTH(vehicle, wheelIndex);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex, float health)
	{
		VEHICLE::SET_TYRE_HEALTH(vehicle, wheelIndex, health);
	}

	static float LUA_NATIVE_VEHICLE_GET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex)
	{
		auto retval = VEHICLE::GET_TYRE_WEAR_RATE(vehicle, wheelIndex);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_SET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier)
	{
		VEHICLE::SET_TYRE_WEAR_RATE(vehicle, wheelIndex, multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_TYRE_WEAR_RATE_SCALE(Vehicle vehicle, int wheelIndex, float multiplier)
	{
		VEHICLE::SET_TYRE_WEAR_RATE_SCALE(vehicle, wheelIndex, multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier)
	{
		VEHICLE::SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE(vehicle, wheelIndex, multiplier);
	}

	static void LUA_NATIVE_VEHICLE_SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION(Vehicle vehicle, int p1)
	{
		VEHICLE::SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_REDUCED_SUSPENSION_FORCE(Vehicle vehicle, bool enable)
	{
		VEHICLE::SET_REDUCED_SUSPENSION_FORCE(vehicle, enable);
	}

	static void LUA_NATIVE_VEHICLE_SET_DRIFT_TYRES(Vehicle vehicle, bool toggle)
	{
		VEHICLE::SET_DRIFT_TYRES(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_GET_DRIFT_TYRES_SET(Vehicle vehicle)
	{
		auto retval = (bool)VEHICLE::GET_DRIFT_TYRES_SET(vehicle);
		return retval;
	}

	static void LUA_NATIVE_VEHICLE_NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING(Vehicle vehicle, bool toggle)
	{
		VEHICLE::NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING(vehicle, toggle);
	}

	static void LUA_NATIVE_VEHICLE_SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED(Vehicle vehicle, bool p1)
	{
		VEHICLE::SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED(vehicle, p1);
	}

	static void LUA_NATIVE_VEHICLE_SET_ALLOW_COLLISION_WHEN_IN_VEHICLE_(Vehicle vehicle, bool toggle)
	{
		VEHICLE::_SET_ALLOW_COLLISION_WHEN_IN_VEHICLE(vehicle, toggle);
	}

	static bool LUA_NATIVE_VEHICLE_IS_VEHICLE_GEN9_EXCLUSIVE_MODEL_(Hash vehicleModel)
	{
		auto retval = (bool)VEHICLE::_IS_VEHICLE_GEN9_EXCLUSIVE_MODEL(vehicleModel);
		return retval;
	}

	static int LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_EXHAUST_BONE_COUNT_()
	{
		auto retval = VEHICLE::_GET_VEHICLE_MAX_EXHAUST_BONE_COUNT();
		return retval;
	}

	static std::tuple<bool, int, bool> LUA_NATIVE_VEHICLE_GET_VEHICLE_EXHAUST_BONE_(Vehicle vehicle, int index, int boneIndex, bool axisX)
	{
		std::tuple<bool, int, bool> return_values;
		std::get<0>(return_values) = (bool)VEHICLE::_GET_VEHICLE_EXHAUST_BONE(vehicle, index, &boneIndex, (BOOL*)&axisX);
		std::get<1>(return_values) = boneIndex;
		std::get<2>(return_values) = axisX;

		return return_values;
	}

	void init_native_binding_VEHICLE(sol::state& L)
	{
		auto VEHICLE = L["VEHICLE"].get_or_create<sol::table>();
		VEHICLE.set_function("CREATE_VEHICLE", LUA_NATIVE_VEHICLE_CREATE_VEHICLE);
		VEHICLE.set_function("DELETE_VEHICLE", LUA_NATIVE_VEHICLE_DELETE_VEHICLE);
		VEHICLE.set_function("SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON", LUA_NATIVE_VEHICLE_SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON);
		VEHICLE.set_function("SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED", LUA_NATIVE_VEHICLE_SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED);
		VEHICLE.set_function("SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON", LUA_NATIVE_VEHICLE_SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON);
		VEHICLE.set_function("GET_VEHICLE_HOMING_LOCKON_STATE", LUA_NATIVE_VEHICLE_GET_VEHICLE_HOMING_LOCKON_STATE);
		VEHICLE.set_function("GET_VEHICLE_HOMING_LOCKEDONTO_STATE", LUA_NATIVE_VEHICLE_GET_VEHICLE_HOMING_LOCKEDONTO_STATE);
		VEHICLE.set_function("SET_VEHICLE_HOMING_LOCKEDONTO_STATE", LUA_NATIVE_VEHICLE_SET_VEHICLE_HOMING_LOCKEDONTO_STATE);
		VEHICLE.set_function("IS_VEHICLE_MODEL", LUA_NATIVE_VEHICLE_IS_VEHICLE_MODEL);
		VEHICLE.set_function("DOES_SCRIPT_VEHICLE_GENERATOR_EXIST", LUA_NATIVE_VEHICLE_DOES_SCRIPT_VEHICLE_GENERATOR_EXIST);
		VEHICLE.set_function("CREATE_SCRIPT_VEHICLE_GENERATOR", LUA_NATIVE_VEHICLE_CREATE_SCRIPT_VEHICLE_GENERATOR);
		VEHICLE.set_function("DELETE_SCRIPT_VEHICLE_GENERATOR", LUA_NATIVE_VEHICLE_DELETE_SCRIPT_VEHICLE_GENERATOR);
		VEHICLE.set_function("SET_SCRIPT_VEHICLE_GENERATOR", LUA_NATIVE_VEHICLE_SET_SCRIPT_VEHICLE_GENERATOR);
		VEHICLE.set_function("SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA", LUA_NATIVE_VEHICLE_SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA);
		VEHICLE.set_function("SET_ALL_VEHICLE_GENERATORS_ACTIVE", LUA_NATIVE_VEHICLE_SET_ALL_VEHICLE_GENERATORS_ACTIVE);
		VEHICLE.set_function("SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE", LUA_NATIVE_VEHICLE_SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE);
		VEHICLE.set_function("SET_VEHICLE_GENERATOR_AREA_OF_INTEREST", LUA_NATIVE_VEHICLE_SET_VEHICLE_GENERATOR_AREA_OF_INTEREST);
		VEHICLE.set_function("CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST", LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST);
		VEHICLE.set_function("SET_VEHICLE_ON_GROUND_PROPERLY", LUA_NATIVE_VEHICLE_SET_VEHICLE_ON_GROUND_PROPERLY);
		VEHICLE.set_function("SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION", LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION);
		VEHICLE.set_function("IS_VEHICLE_STUCK_ON_ROOF", LUA_NATIVE_VEHICLE_IS_VEHICLE_STUCK_ON_ROOF);
		VEHICLE.set_function("ADD_VEHICLE_UPSIDEDOWN_CHECK", LUA_NATIVE_VEHICLE_ADD_VEHICLE_UPSIDEDOWN_CHECK);
		VEHICLE.set_function("REMOVE_VEHICLE_UPSIDEDOWN_CHECK", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_UPSIDEDOWN_CHECK);
		VEHICLE.set_function("IS_VEHICLE_STOPPED", LUA_NATIVE_VEHICLE_IS_VEHICLE_STOPPED);
		VEHICLE.set_function("GET_VEHICLE_NUMBER_OF_PASSENGERS", LUA_NATIVE_VEHICLE_GET_VEHICLE_NUMBER_OF_PASSENGERS);
		VEHICLE.set_function("GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS", LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS);
		VEHICLE.set_function("GET_VEHICLE_MODEL_NUMBER_OF_SEATS", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_NUMBER_OF_SEATS);
		VEHICLE.set_function("IS_SEAT_WARP_ONLY", LUA_NATIVE_VEHICLE_IS_SEAT_WARP_ONLY);
		VEHICLE.set_function("IS_TURRET_SEAT", LUA_NATIVE_VEHICLE_IS_TURRET_SEAT);
		VEHICLE.set_function("DOES_VEHICLE_ALLOW_RAPPEL", LUA_NATIVE_VEHICLE_DOES_VEHICLE_ALLOW_RAPPEL);
		VEHICLE.set_function("SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME", LUA_NATIVE_VEHICLE_SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME);
		VEHICLE.set_function("SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME", LUA_NATIVE_VEHICLE_SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME);
		VEHICLE.set_function("SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME", LUA_NATIVE_VEHICLE_SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME);
		VEHICLE.set_function("SET_DISABLE_RANDOM_TRAINS_THIS_FRAME", LUA_NATIVE_VEHICLE_SET_DISABLE_RANDOM_TRAINS_THIS_FRAME);
		VEHICLE.set_function("SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME", LUA_NATIVE_VEHICLE_SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME);
		VEHICLE.set_function("SET_FAR_DRAW_VEHICLES", LUA_NATIVE_VEHICLE_SET_FAR_DRAW_VEHICLES);
		VEHICLE.set_function("SET_NUMBER_OF_PARKED_VEHICLES", LUA_NATIVE_VEHICLE_SET_NUMBER_OF_PARKED_VEHICLES);
		VEHICLE.set_function("SET_VEHICLE_DOORS_LOCKED", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED);
		VEHICLE.set_function("SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED", LUA_NATIVE_VEHICLE_SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED);
		VEHICLE.set_function("SET_VEHICLE_HAS_MUTED_SIRENS", LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_MUTED_SIRENS);
		VEHICLE.set_function("SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER);
		VEHICLE.set_function("GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER", LUA_NATIVE_VEHICLE_GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER);
		VEHICLE.set_function("SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS);
		VEHICLE.set_function("SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS);
		VEHICLE.set_function("SET_VEHICLE_DOORS_LOCKED_FOR_TEAM", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_TEAM);
		VEHICLE.set_function("SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS);
		VEHICLE.set_function("SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED", LUA_NATIVE_VEHICLE_SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED);
		VEHICLE.set_function("SET_VEHICLE_MAX_LAUNCH_ENGINE_REVS_", LUA_NATIVE_VEHICLE_SET_VEHICLE_MAX_LAUNCH_ENGINE_REVS_);
		VEHICLE.set_function("GET_VEHICLE_THROTTLE_", LUA_NATIVE_VEHICLE_GET_VEHICLE_THROTTLE_);
		VEHICLE.set_function("EXPLODE_VEHICLE", LUA_NATIVE_VEHICLE_EXPLODE_VEHICLE);
		VEHICLE.set_function("SET_VEHICLE_OUT_OF_CONTROL", LUA_NATIVE_VEHICLE_SET_VEHICLE_OUT_OF_CONTROL);
		VEHICLE.set_function("SET_VEHICLE_TIMED_EXPLOSION", LUA_NATIVE_VEHICLE_SET_VEHICLE_TIMED_EXPLOSION);
		VEHICLE.set_function("ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE", LUA_NATIVE_VEHICLE_ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE);
		VEHICLE.set_function("CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE", LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE);
		VEHICLE.set_function("HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE", LUA_NATIVE_VEHICLE_HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE);
		VEHICLE.set_function("DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE", LUA_NATIVE_VEHICLE_DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE);
		VEHICLE.set_function("HAVE_VEHICLE_REAR_DOORS_BEEN_BLOWN_OPEN_BY_STICKYBOMB", LUA_NATIVE_VEHICLE_HAVE_VEHICLE_REAR_DOORS_BEEN_BLOWN_OPEN_BY_STICKYBOMB);
		VEHICLE.set_function("SET_TAXI_LIGHTS", LUA_NATIVE_VEHICLE_SET_TAXI_LIGHTS);
		VEHICLE.set_function("IS_TAXI_LIGHT_ON", LUA_NATIVE_VEHICLE_IS_TAXI_LIGHT_ON);
		VEHICLE.set_function("IS_VEHICLE_IN_GARAGE_AREA", LUA_NATIVE_VEHICLE_IS_VEHICLE_IN_GARAGE_AREA);
		VEHICLE.set_function("SET_VEHICLE_COLOURS", LUA_NATIVE_VEHICLE_SET_VEHICLE_COLOURS);
		VEHICLE.set_function("SET_VEHICLE_FULLBEAM", LUA_NATIVE_VEHICLE_SET_VEHICLE_FULLBEAM);
		VEHICLE.set_function("SET_VEHICLE_IS_RACING", LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_RACING);
		VEHICLE.set_function("SET_VEHICLE_CUSTOM_PRIMARY_COLOUR", LUA_NATIVE_VEHICLE_SET_VEHICLE_CUSTOM_PRIMARY_COLOUR);
		VEHICLE.set_function("GET_VEHICLE_CUSTOM_PRIMARY_COLOUR", LUA_NATIVE_VEHICLE_GET_VEHICLE_CUSTOM_PRIMARY_COLOUR);
		VEHICLE.set_function("CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR", LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR);
		VEHICLE.set_function("GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM", LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM);
		VEHICLE.set_function("SET_VEHICLE_CUSTOM_SECONDARY_COLOUR", LUA_NATIVE_VEHICLE_SET_VEHICLE_CUSTOM_SECONDARY_COLOUR);
		VEHICLE.set_function("GET_VEHICLE_CUSTOM_SECONDARY_COLOUR", LUA_NATIVE_VEHICLE_GET_VEHICLE_CUSTOM_SECONDARY_COLOUR);
		VEHICLE.set_function("CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR", LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR);
		VEHICLE.set_function("GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM", LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM);
		VEHICLE.set_function("SET_VEHICLE_ENVEFF_SCALE", LUA_NATIVE_VEHICLE_SET_VEHICLE_ENVEFF_SCALE);
		VEHICLE.set_function("GET_VEHICLE_ENVEFF_SCALE", LUA_NATIVE_VEHICLE_GET_VEHICLE_ENVEFF_SCALE);
		VEHICLE.set_function("SET_CAN_RESPRAY_VEHICLE", LUA_NATIVE_VEHICLE_SET_CAN_RESPRAY_VEHICLE);
		VEHICLE.set_function("SET_GOON_BOSS_VEHICLE", LUA_NATIVE_VEHICLE_SET_GOON_BOSS_VEHICLE);
		VEHICLE.set_function("SET_OPEN_REAR_DOORS_ON_EXPLOSION", LUA_NATIVE_VEHICLE_SET_OPEN_REAR_DOORS_ON_EXPLOSION);
		VEHICLE.set_function("FORCE_SUBMARINE_SURFACE_MODE", LUA_NATIVE_VEHICLE_FORCE_SUBMARINE_SURFACE_MODE);
		VEHICLE.set_function("FORCE_SUBMARINE_NEURTAL_BUOYANCY", LUA_NATIVE_VEHICLE_FORCE_SUBMARINE_NEURTAL_BUOYANCY);
		VEHICLE.set_function("SET_SUBMARINE_CRUSH_DEPTHS", LUA_NATIVE_VEHICLE_SET_SUBMARINE_CRUSH_DEPTHS);
		VEHICLE.set_function("GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH", LUA_NATIVE_VEHICLE_GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH);
		VEHICLE.set_function("GET_SUBMARINE_NUMBER_OF_AIR_LEAKS", LUA_NATIVE_VEHICLE_GET_SUBMARINE_NUMBER_OF_AIR_LEAKS);
		VEHICLE.set_function("SET_BOAT_IGNORE_LAND_PROBES", LUA_NATIVE_VEHICLE_SET_BOAT_IGNORE_LAND_PROBES);
		VEHICLE.set_function("SET_BOUNDS_AFFECT_WATER_PROBES_", LUA_NATIVE_VEHICLE_SET_BOUNDS_AFFECT_WATER_PROBES_);
		VEHICLE.set_function("SET_BOAT_ANCHOR", LUA_NATIVE_VEHICLE_SET_BOAT_ANCHOR);
		VEHICLE.set_function("CAN_ANCHOR_BOAT_HERE", LUA_NATIVE_VEHICLE_CAN_ANCHOR_BOAT_HERE);
		VEHICLE.set_function("CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS", LUA_NATIVE_VEHICLE_CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS);
		VEHICLE.set_function("SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER", LUA_NATIVE_VEHICLE_SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER);
		VEHICLE.set_function("SET_FORCE_LOW_LOD_ANCHOR_MODE", LUA_NATIVE_VEHICLE_SET_FORCE_LOW_LOD_ANCHOR_MODE);
		VEHICLE.set_function("SET_BOAT_LOW_LOD_ANCHOR_DISTANCE", LUA_NATIVE_VEHICLE_SET_BOAT_LOW_LOD_ANCHOR_DISTANCE);
		VEHICLE.set_function("IS_BOAT_ANCHORED", LUA_NATIVE_VEHICLE_IS_BOAT_ANCHORED);
		VEHICLE.set_function("SET_BOAT_SINKS_WHEN_WRECKED", LUA_NATIVE_VEHICLE_SET_BOAT_SINKS_WHEN_WRECKED);
		VEHICLE.set_function("SET_BOAT_WRECKED", LUA_NATIVE_VEHICLE_SET_BOAT_WRECKED);
		VEHICLE.set_function("SET_VEHICLE_SIREN", LUA_NATIVE_VEHICLE_SET_VEHICLE_SIREN);
		VEHICLE.set_function("IS_VEHICLE_SIREN_ON", LUA_NATIVE_VEHICLE_IS_VEHICLE_SIREN_ON);
		VEHICLE.set_function("IS_VEHICLE_SIREN_AUDIO_ON", LUA_NATIVE_VEHICLE_IS_VEHICLE_SIREN_AUDIO_ON);
		VEHICLE.set_function("SET_VEHICLE_STRONG", LUA_NATIVE_VEHICLE_SET_VEHICLE_STRONG);
		VEHICLE.set_function("REMOVE_VEHICLE_STUCK_CHECK", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_STUCK_CHECK);
		VEHICLE.set_function("GET_VEHICLE_COLOURS", LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOURS);
		VEHICLE.set_function("IS_VEHICLE_SEAT_FREE", LUA_NATIVE_VEHICLE_IS_VEHICLE_SEAT_FREE);
		VEHICLE.set_function("GET_PED_IN_VEHICLE_SEAT", LUA_NATIVE_VEHICLE_GET_PED_IN_VEHICLE_SEAT);
		VEHICLE.set_function("GET_LAST_PED_IN_VEHICLE_SEAT", LUA_NATIVE_VEHICLE_GET_LAST_PED_IN_VEHICLE_SEAT);
		VEHICLE.set_function("GET_VEHICLE_LIGHTS_STATE", LUA_NATIVE_VEHICLE_GET_VEHICLE_LIGHTS_STATE);
		VEHICLE.set_function("IS_VEHICLE_TYRE_BURST", LUA_NATIVE_VEHICLE_IS_VEHICLE_TYRE_BURST);
		VEHICLE.set_function("SET_VEHICLE_FORWARD_SPEED", LUA_NATIVE_VEHICLE_SET_VEHICLE_FORWARD_SPEED);
		VEHICLE.set_function("SET_VEHICLE_FORWARD_SPEED_XY", LUA_NATIVE_VEHICLE_SET_VEHICLE_FORWARD_SPEED_XY);
		VEHICLE.set_function("BRING_VEHICLE_TO_HALT", LUA_NATIVE_VEHICLE_BRING_VEHICLE_TO_HALT);
		VEHICLE.set_function("SET_VEHICLE_STEER_FOR_BUILDINGS", LUA_NATIVE_VEHICLE_SET_VEHICLE_STEER_FOR_BUILDINGS);
		VEHICLE.set_function("SET_VEHICLE_CAUSES_SWERVING", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAUSES_SWERVING);
		VEHICLE.set_function("SET_IGNORE_PLANES_SMALL_PITCH_CHANGE", LUA_NATIVE_VEHICLE_SET_IGNORE_PLANES_SMALL_PITCH_CHANGE);
		VEHICLE.set_function("STOP_BRINGING_VEHICLE_TO_HALT", LUA_NATIVE_VEHICLE_STOP_BRINGING_VEHICLE_TO_HALT);
		VEHICLE.set_function("IS_VEHICLE_BEING_BROUGHT_TO_HALT", LUA_NATIVE_VEHICLE_IS_VEHICLE_BEING_BROUGHT_TO_HALT);
		VEHICLE.set_function("LOWER_FORKLIFT_FORKS", LUA_NATIVE_VEHICLE_LOWER_FORKLIFT_FORKS);
		VEHICLE.set_function("SET_FORKLIFT_FORK_HEIGHT", LUA_NATIVE_VEHICLE_SET_FORKLIFT_FORK_HEIGHT);
		VEHICLE.set_function("IS_ENTITY_ATTACHED_TO_HANDLER_FRAME", LUA_NATIVE_VEHICLE_IS_ENTITY_ATTACHED_TO_HANDLER_FRAME);
		VEHICLE.set_function("IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME", LUA_NATIVE_VEHICLE_IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME);
		VEHICLE.set_function("FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO", LUA_NATIVE_VEHICLE_FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO);
		VEHICLE.set_function("IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER", LUA_NATIVE_VEHICLE_IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER);
		VEHICLE.set_function("ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP", LUA_NATIVE_VEHICLE_ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP);
		VEHICLE.set_function("DETACH_CONTAINER_FROM_HANDLER_FRAME", LUA_NATIVE_VEHICLE_DETACH_CONTAINER_FROM_HANDLER_FRAME);
		VEHICLE.set_function("SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE", LUA_NATIVE_VEHICLE_SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE);
		VEHICLE.set_function("SET_BOAT_DISABLE_AVOIDANCE", LUA_NATIVE_VEHICLE_SET_BOAT_DISABLE_AVOIDANCE);
		VEHICLE.set_function("IS_HELI_LANDING_AREA_BLOCKED", LUA_NATIVE_VEHICLE_IS_HELI_LANDING_AREA_BLOCKED);
		VEHICLE.set_function("SET_SHORT_SLOWDOWN_FOR_LANDING", LUA_NATIVE_VEHICLE_SET_SHORT_SLOWDOWN_FOR_LANDING);
		VEHICLE.set_function("SET_HELI_TURBULENCE_SCALAR", LUA_NATIVE_VEHICLE_SET_HELI_TURBULENCE_SCALAR);
		VEHICLE.set_function("SET_CAR_BOOT_OPEN", LUA_NATIVE_VEHICLE_SET_CAR_BOOT_OPEN);
		VEHICLE.set_function("SET_VEHICLE_TYRE_BURST", LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRE_BURST);
		VEHICLE.set_function("SET_VEHICLE_DOORS_SHUT", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOORS_SHUT);
		VEHICLE.set_function("SET_VEHICLE_TYRES_CAN_BURST", LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRES_CAN_BURST);
		VEHICLE.set_function("GET_VEHICLE_TYRES_CAN_BURST", LUA_NATIVE_VEHICLE_GET_VEHICLE_TYRES_CAN_BURST);
		VEHICLE.set_function("SET_VEHICLE_WHEELS_CAN_BREAK", LUA_NATIVE_VEHICLE_SET_VEHICLE_WHEELS_CAN_BREAK);
		VEHICLE.set_function("SET_VEHICLE_DOOR_OPEN", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_OPEN);
		VEHICLE.set_function("SET_VEHICLE_DOOR_AUTO_LOCK", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_AUTO_LOCK);
		VEHICLE.set_function("SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES", LUA_NATIVE_VEHICLE_SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES);
		VEHICLE.set_function("REMOVE_VEHICLE_WINDOW", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_WINDOW);
		VEHICLE.set_function("ROLL_DOWN_WINDOWS", LUA_NATIVE_VEHICLE_ROLL_DOWN_WINDOWS);
		VEHICLE.set_function("ROLL_DOWN_WINDOW", LUA_NATIVE_VEHICLE_ROLL_DOWN_WINDOW);
		VEHICLE.set_function("ROLL_UP_WINDOW", LUA_NATIVE_VEHICLE_ROLL_UP_WINDOW);
		VEHICLE.set_function("SMASH_VEHICLE_WINDOW", LUA_NATIVE_VEHICLE_SMASH_VEHICLE_WINDOW);
		VEHICLE.set_function("FIX_VEHICLE_WINDOW", LUA_NATIVE_VEHICLE_FIX_VEHICLE_WINDOW);
		VEHICLE.set_function("POP_OUT_VEHICLE_WINDSCREEN", LUA_NATIVE_VEHICLE_POP_OUT_VEHICLE_WINDSCREEN);
		VEHICLE.set_function("POP_OFF_VEHICLE_ROOF_WITH_IMPULSE", LUA_NATIVE_VEHICLE_POP_OFF_VEHICLE_ROOF_WITH_IMPULSE);
		VEHICLE.set_function("SET_VEHICLE_LIGHTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_LIGHTS);
		VEHICLE.set_function("SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS", LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS);
		VEHICLE.set_function("SET_VEHICLE_HEADLIGHT_SHADOWS", LUA_NATIVE_VEHICLE_SET_VEHICLE_HEADLIGHT_SHADOWS);
		VEHICLE.set_function("SET_VEHICLE_ALARM", LUA_NATIVE_VEHICLE_SET_VEHICLE_ALARM);
		VEHICLE.set_function("START_VEHICLE_ALARM", LUA_NATIVE_VEHICLE_START_VEHICLE_ALARM);
		VEHICLE.set_function("IS_VEHICLE_ALARM_ACTIVATED", LUA_NATIVE_VEHICLE_IS_VEHICLE_ALARM_ACTIVATED);
		VEHICLE.set_function("SET_VEHICLE_INTERIORLIGHT", LUA_NATIVE_VEHICLE_SET_VEHICLE_INTERIORLIGHT);
		VEHICLE.set_function("SET_VEHICLE_FORCE_INTERIORLIGHT", LUA_NATIVE_VEHICLE_SET_VEHICLE_FORCE_INTERIORLIGHT);
		VEHICLE.set_function("SET_VEHICLE_LIGHT_MULTIPLIER", LUA_NATIVE_VEHICLE_SET_VEHICLE_LIGHT_MULTIPLIER);
		VEHICLE.set_function("ATTACH_VEHICLE_TO_TRAILER", LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_TO_TRAILER);
		VEHICLE.set_function("ATTACH_VEHICLE_ON_TO_TRAILER", LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_ON_TO_TRAILER);
		VEHICLE.set_function("STABILISE_ENTITY_ATTACHED_TO_HELI", LUA_NATIVE_VEHICLE_STABILISE_ENTITY_ATTACHED_TO_HELI);
		VEHICLE.set_function("DETACH_VEHICLE_FROM_TRAILER", LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_TRAILER);
		VEHICLE.set_function("IS_VEHICLE_ATTACHED_TO_TRAILER", LUA_NATIVE_VEHICLE_IS_VEHICLE_ATTACHED_TO_TRAILER);
		VEHICLE.set_function("SET_TRAILER_INVERSE_MASS_SCALE", LUA_NATIVE_VEHICLE_SET_TRAILER_INVERSE_MASS_SCALE);
		VEHICLE.set_function("SET_TRAILER_LEGS_RAISED", LUA_NATIVE_VEHICLE_SET_TRAILER_LEGS_RAISED);
		VEHICLE.set_function("SET_TRAILER_LEGS_LOWERED", LUA_NATIVE_VEHICLE_SET_TRAILER_LEGS_LOWERED);
		VEHICLE.set_function("SET_VEHICLE_TYRE_FIXED", LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRE_FIXED);
		VEHICLE.set_function("SET_VEHICLE_NUMBER_PLATE_TEXT", LUA_NATIVE_VEHICLE_SET_VEHICLE_NUMBER_PLATE_TEXT);
		VEHICLE.set_function("GET_VEHICLE_NUMBER_PLATE_TEXT", LUA_NATIVE_VEHICLE_GET_VEHICLE_NUMBER_PLATE_TEXT);
		VEHICLE.set_function("GET_NUMBER_OF_VEHICLE_NUMBER_PLATES", LUA_NATIVE_VEHICLE_GET_NUMBER_OF_VEHICLE_NUMBER_PLATES);
		VEHICLE.set_function("SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX", LUA_NATIVE_VEHICLE_SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX);
		VEHICLE.set_function("GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX", LUA_NATIVE_VEHICLE_GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX);
		VEHICLE.set_function("SET_RANDOM_TRAINS", LUA_NATIVE_VEHICLE_SET_RANDOM_TRAINS);
		VEHICLE.set_function("CREATE_MISSION_TRAIN", LUA_NATIVE_VEHICLE_CREATE_MISSION_TRAIN);
		VEHICLE.set_function("SWITCH_TRAIN_TRACK", LUA_NATIVE_VEHICLE_SWITCH_TRAIN_TRACK);
		VEHICLE.set_function("SET_TRAIN_TRACK_SPAWN_FREQUENCY", LUA_NATIVE_VEHICLE_SET_TRAIN_TRACK_SPAWN_FREQUENCY);
		VEHICLE.set_function("ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION", LUA_NATIVE_VEHICLE_ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION);
		VEHICLE.set_function("DELETE_ALL_TRAINS", LUA_NATIVE_VEHICLE_DELETE_ALL_TRAINS);
		VEHICLE.set_function("SET_TRAIN_SPEED", LUA_NATIVE_VEHICLE_SET_TRAIN_SPEED);
		VEHICLE.set_function("SET_TRAIN_CRUISE_SPEED", LUA_NATIVE_VEHICLE_SET_TRAIN_CRUISE_SPEED);
		VEHICLE.set_function("SET_RANDOM_BOATS", LUA_NATIVE_VEHICLE_SET_RANDOM_BOATS);
		VEHICLE.set_function("SET_RANDOM_BOATS_MP", LUA_NATIVE_VEHICLE_SET_RANDOM_BOATS_MP);
		VEHICLE.set_function("SET_GARBAGE_TRUCKS", LUA_NATIVE_VEHICLE_SET_GARBAGE_TRUCKS);
		VEHICLE.set_function("DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK", LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK);
		VEHICLE.set_function("GET_VEHICLE_RECORDING_ID", LUA_NATIVE_VEHICLE_GET_VEHICLE_RECORDING_ID);
		VEHICLE.set_function("REQUEST_VEHICLE_RECORDING", LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_RECORDING);
		VEHICLE.set_function("HAS_VEHICLE_RECORDING_BEEN_LOADED", LUA_NATIVE_VEHICLE_HAS_VEHICLE_RECORDING_BEEN_LOADED);
		VEHICLE.set_function("REMOVE_VEHICLE_RECORDING", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_RECORDING);
		VEHICLE.set_function("GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME", LUA_NATIVE_VEHICLE_GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME);
		VEHICLE.set_function("GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME", LUA_NATIVE_VEHICLE_GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME);
		VEHICLE.set_function("GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME", LUA_NATIVE_VEHICLE_GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME);
		VEHICLE.set_function("GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME", LUA_NATIVE_VEHICLE_GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME);
		VEHICLE.set_function("GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID", LUA_NATIVE_VEHICLE_GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID);
		VEHICLE.set_function("GET_TOTAL_DURATION_OF_VEHICLE_RECORDING", LUA_NATIVE_VEHICLE_GET_TOTAL_DURATION_OF_VEHICLE_RECORDING);
		VEHICLE.set_function("GET_POSITION_IN_RECORDING", LUA_NATIVE_VEHICLE_GET_POSITION_IN_RECORDING);
		VEHICLE.set_function("GET_TIME_POSITION_IN_RECORDING", LUA_NATIVE_VEHICLE_GET_TIME_POSITION_IN_RECORDING);
		VEHICLE.set_function("START_PLAYBACK_RECORDED_VEHICLE", LUA_NATIVE_VEHICLE_START_PLAYBACK_RECORDED_VEHICLE);
		VEHICLE.set_function("START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS", LUA_NATIVE_VEHICLE_START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS);
		VEHICLE.set_function("FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE", LUA_NATIVE_VEHICLE_FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE);
		VEHICLE.set_function("STOP_PLAYBACK_RECORDED_VEHICLE", LUA_NATIVE_VEHICLE_STOP_PLAYBACK_RECORDED_VEHICLE);
		VEHICLE.set_function("PAUSE_PLAYBACK_RECORDED_VEHICLE", LUA_NATIVE_VEHICLE_PAUSE_PLAYBACK_RECORDED_VEHICLE);
		VEHICLE.set_function("UNPAUSE_PLAYBACK_RECORDED_VEHICLE", LUA_NATIVE_VEHICLE_UNPAUSE_PLAYBACK_RECORDED_VEHICLE);
		VEHICLE.set_function("IS_PLAYBACK_GOING_ON_FOR_VEHICLE", LUA_NATIVE_VEHICLE_IS_PLAYBACK_GOING_ON_FOR_VEHICLE);
		VEHICLE.set_function("IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE", LUA_NATIVE_VEHICLE_IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE);
		VEHICLE.set_function("GET_CURRENT_PLAYBACK_FOR_VEHICLE", LUA_NATIVE_VEHICLE_GET_CURRENT_PLAYBACK_FOR_VEHICLE);
		VEHICLE.set_function("SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE", LUA_NATIVE_VEHICLE_SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE);
		VEHICLE.set_function("SET_PLAYBACK_SPEED", LUA_NATIVE_VEHICLE_SET_PLAYBACK_SPEED);
		VEHICLE.set_function("START_PLAYBACK_RECORDED_VEHICLE_USING_AI", LUA_NATIVE_VEHICLE_START_PLAYBACK_RECORDED_VEHICLE_USING_AI);
		VEHICLE.set_function("SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE", LUA_NATIVE_VEHICLE_SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE);
		VEHICLE.set_function("SET_PLAYBACK_TO_USE_AI", LUA_NATIVE_VEHICLE_SET_PLAYBACK_TO_USE_AI);
		VEHICLE.set_function("SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER", LUA_NATIVE_VEHICLE_SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER);
		VEHICLE.set_function("SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK", LUA_NATIVE_VEHICLE_SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK);
		VEHICLE.set_function("SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK", LUA_NATIVE_VEHICLE_SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK);
		VEHICLE.set_function("SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK", LUA_NATIVE_VEHICLE_SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK);
		VEHICLE.set_function("SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING", LUA_NATIVE_VEHICLE_SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING);
		VEHICLE.set_function("EXPLODE_VEHICLE_IN_CUTSCENE", LUA_NATIVE_VEHICLE_EXPLODE_VEHICLE_IN_CUTSCENE);
		VEHICLE.set_function("ADD_VEHICLE_STUCK_CHECK_WITH_WARP", LUA_NATIVE_VEHICLE_ADD_VEHICLE_STUCK_CHECK_WITH_WARP);
		VEHICLE.set_function("SET_VEHICLE_MODEL_IS_SUPPRESSED", LUA_NATIVE_VEHICLE_SET_VEHICLE_MODEL_IS_SUPPRESSED);
		VEHICLE.set_function("GET_RANDOM_VEHICLE_IN_SPHERE", LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_IN_SPHERE);
		VEHICLE.set_function("GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE", LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE);
		VEHICLE.set_function("GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE", LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE);
		VEHICLE.set_function("GET_CLOSEST_VEHICLE", LUA_NATIVE_VEHICLE_GET_CLOSEST_VEHICLE);
		VEHICLE.set_function("GET_TRAIN_CARRIAGE", LUA_NATIVE_VEHICLE_GET_TRAIN_CARRIAGE);
		VEHICLE.set_function("IS_MISSION_TRAIN", LUA_NATIVE_VEHICLE_IS_MISSION_TRAIN);
		VEHICLE.set_function("DELETE_MISSION_TRAIN", LUA_NATIVE_VEHICLE_DELETE_MISSION_TRAIN);
		VEHICLE.set_function("SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED", LUA_NATIVE_VEHICLE_SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED);
		VEHICLE.set_function("SET_MISSION_TRAIN_COORDS", LUA_NATIVE_VEHICLE_SET_MISSION_TRAIN_COORDS);
		VEHICLE.set_function("IS_THIS_MODEL_A_BOAT", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_BOAT);
		VEHICLE.set_function("IS_THIS_MODEL_A_JETSKI", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_JETSKI);
		VEHICLE.set_function("IS_THIS_MODEL_A_PLANE", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_PLANE);
		VEHICLE.set_function("IS_THIS_MODEL_A_HELI", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_HELI);
		VEHICLE.set_function("IS_THIS_MODEL_A_CAR", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_CAR);
		VEHICLE.set_function("IS_THIS_MODEL_A_TRAIN", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_TRAIN);
		VEHICLE.set_function("IS_THIS_MODEL_A_BIKE", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_BIKE);
		VEHICLE.set_function("IS_THIS_MODEL_A_BICYCLE", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_BICYCLE);
		VEHICLE.set_function("IS_THIS_MODEL_A_QUADBIKE", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_A_QUADBIKE);
		VEHICLE.set_function("IS_THIS_MODEL_AN_AMPHIBIOUS_CAR", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_AN_AMPHIBIOUS_CAR);
		VEHICLE.set_function("IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE", LUA_NATIVE_VEHICLE_IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE);
		VEHICLE.set_function("SET_HELI_BLADES_FULL_SPEED", LUA_NATIVE_VEHICLE_SET_HELI_BLADES_FULL_SPEED);
		VEHICLE.set_function("SET_HELI_BLADES_SPEED", LUA_NATIVE_VEHICLE_SET_HELI_BLADES_SPEED);
		VEHICLE.set_function("FORCE_SUB_THROTTLE_FOR_TIME", LUA_NATIVE_VEHICLE_FORCE_SUB_THROTTLE_FOR_TIME);
		VEHICLE.set_function("SET_VEHICLE_CAN_BE_TARGETTED", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BE_TARGETTED);
		VEHICLE.set_function("SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER", LUA_NATIVE_VEHICLE_SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER);
		VEHICLE.set_function("SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED);
		VEHICLE.set_function("SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS);
		VEHICLE.set_function("SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER", LUA_NATIVE_VEHICLE_SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER);
		VEHICLE.set_function("SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED);
		VEHICLE.set_function("GET_VEHICLE_DIRT_LEVEL", LUA_NATIVE_VEHICLE_GET_VEHICLE_DIRT_LEVEL);
		VEHICLE.set_function("SET_VEHICLE_DIRT_LEVEL", LUA_NATIVE_VEHICLE_SET_VEHICLE_DIRT_LEVEL);
		VEHICLE.set_function("GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS", LUA_NATIVE_VEHICLE_GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS);
		VEHICLE.set_function("IS_VEHICLE_DOOR_FULLY_OPEN", LUA_NATIVE_VEHICLE_IS_VEHICLE_DOOR_FULLY_OPEN);
		VEHICLE.set_function("SET_VEHICLE_ENGINE_ON", LUA_NATIVE_VEHICLE_SET_VEHICLE_ENGINE_ON);
		VEHICLE.set_function("SET_VEHICLE_UNDRIVEABLE", LUA_NATIVE_VEHICLE_SET_VEHICLE_UNDRIVEABLE);
		VEHICLE.set_function("SET_VEHICLE_PROVIDES_COVER", LUA_NATIVE_VEHICLE_SET_VEHICLE_PROVIDES_COVER);
		VEHICLE.set_function("SET_VEHICLE_DOOR_CONTROL", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_CONTROL);
		VEHICLE.set_function("SET_VEHICLE_DOOR_LATCHED", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_LATCHED);
		VEHICLE.set_function("GET_VEHICLE_DOOR_ANGLE_RATIO", LUA_NATIVE_VEHICLE_GET_VEHICLE_DOOR_ANGLE_RATIO);
		VEHICLE.set_function("GET_PED_USING_VEHICLE_DOOR", LUA_NATIVE_VEHICLE_GET_PED_USING_VEHICLE_DOOR);
		VEHICLE.set_function("SET_VEHICLE_DOOR_SHUT", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_SHUT);
		VEHICLE.set_function("SET_VEHICLE_DOOR_BROKEN", LUA_NATIVE_VEHICLE_SET_VEHICLE_DOOR_BROKEN);
		VEHICLE.set_function("SET_VEHICLE_CAN_BREAK", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BREAK);
		VEHICLE.set_function("DOES_VEHICLE_HAVE_ROOF", LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_ROOF);
		VEHICLE.set_function("SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION", LUA_NATIVE_VEHICLE_SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION);
		VEHICLE.set_function("SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION", LUA_NATIVE_VEHICLE_SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION);
		VEHICLE.set_function("SET_CARJACK_MISSION_REMOVAL_PARAMETERS", LUA_NATIVE_VEHICLE_SET_CARJACK_MISSION_REMOVAL_PARAMETERS);
		VEHICLE.set_function("IS_BIG_VEHICLE", LUA_NATIVE_VEHICLE_IS_BIG_VEHICLE);
		VEHICLE.set_function("GET_NUMBER_OF_VEHICLE_COLOURS", LUA_NATIVE_VEHICLE_GET_NUMBER_OF_VEHICLE_COLOURS);
		VEHICLE.set_function("SET_VEHICLE_COLOUR_COMBINATION", LUA_NATIVE_VEHICLE_SET_VEHICLE_COLOUR_COMBINATION);
		VEHICLE.set_function("GET_VEHICLE_COLOUR_COMBINATION", LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOUR_COMBINATION);
		VEHICLE.set_function("SET_VEHICLE_XENON_LIGHT_COLOR_INDEX", LUA_NATIVE_VEHICLE_SET_VEHICLE_XENON_LIGHT_COLOR_INDEX);
		VEHICLE.set_function("GET_VEHICLE_XENON_LIGHT_COLOR_INDEX", LUA_NATIVE_VEHICLE_GET_VEHICLE_XENON_LIGHT_COLOR_INDEX);
		VEHICLE.set_function("SET_VEHICLE_IS_CONSIDERED_BY_PLAYER", LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_CONSIDERED_BY_PLAYER);
		VEHICLE.set_function("SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP", LUA_NATIVE_VEHICLE_SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP);
		VEHICLE.set_function("SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON", LUA_NATIVE_VEHICLE_SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON);
		VEHICLE.set_function("SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS", LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS);
		VEHICLE.set_function("SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS", LUA_NATIVE_VEHICLE_SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS);
		VEHICLE.set_function("GET_RANDOM_VEHICLE_MODEL_IN_MEMORY", LUA_NATIVE_VEHICLE_GET_RANDOM_VEHICLE_MODEL_IN_MEMORY);
		VEHICLE.set_function("GET_VEHICLE_DOOR_LOCK_STATUS", LUA_NATIVE_VEHICLE_GET_VEHICLE_DOOR_LOCK_STATUS);
		VEHICLE.set_function("GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS", LUA_NATIVE_VEHICLE_GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS);
		VEHICLE.set_function("IS_VEHICLE_DOOR_DAMAGED", LUA_NATIVE_VEHICLE_IS_VEHICLE_DOOR_DAMAGED);
		VEHICLE.set_function("SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF", LUA_NATIVE_VEHICLE_SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF);
		VEHICLE.set_function("IS_VEHICLE_BUMPER_BOUNCING", LUA_NATIVE_VEHICLE_IS_VEHICLE_BUMPER_BOUNCING);
		VEHICLE.set_function("IS_VEHICLE_BUMPER_BROKEN_OFF", LUA_NATIVE_VEHICLE_IS_VEHICLE_BUMPER_BROKEN_OFF);
		VEHICLE.set_function("IS_COP_VEHICLE_IN_AREA_3D", LUA_NATIVE_VEHICLE_IS_COP_VEHICLE_IN_AREA_3D);
		VEHICLE.set_function("IS_VEHICLE_ON_ALL_WHEELS", LUA_NATIVE_VEHICLE_IS_VEHICLE_ON_ALL_WHEELS);
		VEHICLE.set_function("GET_VEHICLE_MODEL_VALUE", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_VALUE);
		VEHICLE.set_function("GET_VEHICLE_LAYOUT_HASH", LUA_NATIVE_VEHICLE_GET_VEHICLE_LAYOUT_HASH);
		VEHICLE.set_function("GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT", LUA_NATIVE_VEHICLE_GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT);
		VEHICLE.set_function("SET_RENDER_TRAIN_AS_DERAILED", LUA_NATIVE_VEHICLE_SET_RENDER_TRAIN_AS_DERAILED);
		VEHICLE.set_function("SET_VEHICLE_EXTRA_COLOURS", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA_COLOURS);
		VEHICLE.set_function("GET_VEHICLE_EXTRA_COLOURS", LUA_NATIVE_VEHICLE_GET_VEHICLE_EXTRA_COLOURS);
		VEHICLE.set_function("SET_VEHICLE_EXTRA_COLOUR_5", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA_COLOUR_5);
		VEHICLE.set_function("GET_VEHICLE_EXTRA_COLOUR_5", LUA_NATIVE_VEHICLE_GET_VEHICLE_EXTRA_COLOUR_5);
		VEHICLE.set_function("SET_VEHICLE_EXTRA_COLOUR_6", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA_COLOUR_6);
		VEHICLE.set_function("GET_VEHICLE_EXTRA_COLOUR_6", LUA_NATIVE_VEHICLE_GET_VEHICLE_EXTRA_COLOUR_6);
		VEHICLE.set_function("STOP_ALL_GARAGE_ACTIVITY", LUA_NATIVE_VEHICLE_STOP_ALL_GARAGE_ACTIVITY);
		VEHICLE.set_function("SET_VEHICLE_FIXED", LUA_NATIVE_VEHICLE_SET_VEHICLE_FIXED);
		VEHICLE.set_function("SET_VEHICLE_DEFORMATION_FIXED", LUA_NATIVE_VEHICLE_SET_VEHICLE_DEFORMATION_FIXED);
		VEHICLE.set_function("SET_VEHICLE_CAN_ENGINE_MISSFIRE", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_ENGINE_MISSFIRE);
		VEHICLE.set_function("SET_VEHICLE_CAN_LEAK_OIL", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_LEAK_OIL);
		VEHICLE.set_function("SET_VEHICLE_CAN_LEAK_PETROL", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_LEAK_PETROL);
		VEHICLE.set_function("SET_DISABLE_VEHICLE_PETROL_TANK_FIRES", LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_PETROL_TANK_FIRES);
		VEHICLE.set_function("SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE", LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE);
		VEHICLE.set_function("SET_DISABLE_VEHICLE_ENGINE_FIRES", LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_ENGINE_FIRES);
		VEHICLE.set_function("SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE", LUA_NATIVE_VEHICLE_SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE);
		VEHICLE.set_function("SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE", LUA_NATIVE_VEHICLE_SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE);
		VEHICLE.set_function("SET_DISABLE_PRETEND_OCCUPANTS", LUA_NATIVE_VEHICLE_SET_DISABLE_PRETEND_OCCUPANTS);
		VEHICLE.set_function("REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA", LUA_NATIVE_VEHICLE_REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA);
		VEHICLE.set_function("SET_VEHICLE_STEER_BIAS", LUA_NATIVE_VEHICLE_SET_VEHICLE_STEER_BIAS);
		VEHICLE.set_function("IS_VEHICLE_EXTRA_TURNED_ON", LUA_NATIVE_VEHICLE_IS_VEHICLE_EXTRA_TURNED_ON);
		VEHICLE.set_function("SET_VEHICLE_EXTRA", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTRA);
		VEHICLE.set_function("DOES_EXTRA_EXIST", LUA_NATIVE_VEHICLE_DOES_EXTRA_EXIST);
		VEHICLE.set_function("IS_EXTRA_BROKEN_OFF", LUA_NATIVE_VEHICLE_IS_EXTRA_BROKEN_OFF);
		VEHICLE.set_function("SET_CONVERTIBLE_ROOF", LUA_NATIVE_VEHICLE_SET_CONVERTIBLE_ROOF);
		VEHICLE.set_function("LOWER_CONVERTIBLE_ROOF", LUA_NATIVE_VEHICLE_LOWER_CONVERTIBLE_ROOF);
		VEHICLE.set_function("RAISE_CONVERTIBLE_ROOF", LUA_NATIVE_VEHICLE_RAISE_CONVERTIBLE_ROOF);
		VEHICLE.set_function("GET_CONVERTIBLE_ROOF_STATE", LUA_NATIVE_VEHICLE_GET_CONVERTIBLE_ROOF_STATE);
		VEHICLE.set_function("IS_VEHICLE_A_CONVERTIBLE", LUA_NATIVE_VEHICLE_IS_VEHICLE_A_CONVERTIBLE);
		VEHICLE.set_function("TRANSFORM_TO_SUBMARINE", LUA_NATIVE_VEHICLE_TRANSFORM_TO_SUBMARINE);
		VEHICLE.set_function("TRANSFORM_TO_CAR", LUA_NATIVE_VEHICLE_TRANSFORM_TO_CAR);
		VEHICLE.set_function("IS_VEHICLE_IN_SUBMARINE_MODE", LUA_NATIVE_VEHICLE_IS_VEHICLE_IN_SUBMARINE_MODE);
		VEHICLE.set_function("IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS", LUA_NATIVE_VEHICLE_IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS);
		VEHICLE.set_function("SET_VEHICLE_DAMAGE", LUA_NATIVE_VEHICLE_SET_VEHICLE_DAMAGE);
		VEHICLE.set_function("SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE", LUA_NATIVE_VEHICLE_SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE);
		VEHICLE.set_function("GET_VEHICLE_ENGINE_HEALTH", LUA_NATIVE_VEHICLE_GET_VEHICLE_ENGINE_HEALTH);
		VEHICLE.set_function("SET_VEHICLE_ENGINE_HEALTH", LUA_NATIVE_VEHICLE_SET_VEHICLE_ENGINE_HEALTH);
		VEHICLE.set_function("SET_PLANE_ENGINE_HEALTH", LUA_NATIVE_VEHICLE_SET_PLANE_ENGINE_HEALTH);
		VEHICLE.set_function("GET_VEHICLE_PETROL_TANK_HEALTH", LUA_NATIVE_VEHICLE_GET_VEHICLE_PETROL_TANK_HEALTH);
		VEHICLE.set_function("SET_VEHICLE_PETROL_TANK_HEALTH", LUA_NATIVE_VEHICLE_SET_VEHICLE_PETROL_TANK_HEALTH);
		VEHICLE.set_function("IS_VEHICLE_STUCK_TIMER_UP", LUA_NATIVE_VEHICLE_IS_VEHICLE_STUCK_TIMER_UP);
		VEHICLE.set_function("RESET_VEHICLE_STUCK_TIMER", LUA_NATIVE_VEHICLE_RESET_VEHICLE_STUCK_TIMER);
		VEHICLE.set_function("IS_VEHICLE_DRIVEABLE", LUA_NATIVE_VEHICLE_IS_VEHICLE_DRIVEABLE);
		VEHICLE.set_function("SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER", LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER);
		VEHICLE.set_function("SET_VEHICLE_NEEDS_TO_BE_HOTWIRED", LUA_NATIVE_VEHICLE_SET_VEHICLE_NEEDS_TO_BE_HOTWIRED);
		VEHICLE.set_function("SET_VEHICLE_BLIP_THROTTLE_RANDOMLY", LUA_NATIVE_VEHICLE_SET_VEHICLE_BLIP_THROTTLE_RANDOMLY);
		VEHICLE.set_function("SET_POLICE_FOCUS_WILL_TRACK_VEHICLE", LUA_NATIVE_VEHICLE_SET_POLICE_FOCUS_WILL_TRACK_VEHICLE);
		VEHICLE.set_function("START_VEHICLE_HORN", LUA_NATIVE_VEHICLE_START_VEHICLE_HORN);
		VEHICLE.set_function("SET_VEHICLE_IN_CAR_MOD_SHOP", LUA_NATIVE_VEHICLE_SET_VEHICLE_IN_CAR_MOD_SHOP);
		VEHICLE.set_function("SET_VEHICLE_HAS_STRONG_AXLES", LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_STRONG_AXLES);
		VEHICLE.set_function("GET_DISPLAY_NAME_FROM_VEHICLE_MODEL", LUA_NATIVE_VEHICLE_GET_DISPLAY_NAME_FROM_VEHICLE_MODEL);
		VEHICLE.set_function("GET_MAKE_NAME_FROM_VEHICLE_MODEL", LUA_NATIVE_VEHICLE_GET_MAKE_NAME_FROM_VEHICLE_MODEL);
		VEHICLE.set_function("GET_VEHICLE_DEFORMATION_AT_POS", LUA_NATIVE_VEHICLE_GET_VEHICLE_DEFORMATION_AT_POS);
		VEHICLE.set_function("SET_VEHICLE_LIVERY", LUA_NATIVE_VEHICLE_SET_VEHICLE_LIVERY);
		VEHICLE.set_function("GET_VEHICLE_LIVERY", LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY);
		VEHICLE.set_function("GET_VEHICLE_LIVERY_COUNT", LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY_COUNT);
		VEHICLE.set_function("SET_VEHICLE_LIVERY2", LUA_NATIVE_VEHICLE_SET_VEHICLE_LIVERY2);
		VEHICLE.set_function("GET_VEHICLE_LIVERY2", LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY2);
		VEHICLE.set_function("GET_VEHICLE_LIVERY2_COUNT", LUA_NATIVE_VEHICLE_GET_VEHICLE_LIVERY2_COUNT);
		VEHICLE.set_function("IS_VEHICLE_WINDOW_INTACT", LUA_NATIVE_VEHICLE_IS_VEHICLE_WINDOW_INTACT);
		VEHICLE.set_function("ARE_ALL_VEHICLE_WINDOWS_INTACT", LUA_NATIVE_VEHICLE_ARE_ALL_VEHICLE_WINDOWS_INTACT);
		VEHICLE.set_function("ARE_ANY_VEHICLE_SEATS_FREE", LUA_NATIVE_VEHICLE_ARE_ANY_VEHICLE_SEATS_FREE);
		VEHICLE.set_function("RESET_VEHICLE_WHEELS", LUA_NATIVE_VEHICLE_RESET_VEHICLE_WHEELS);
		VEHICLE.set_function("IS_HELI_PART_BROKEN", LUA_NATIVE_VEHICLE_IS_HELI_PART_BROKEN);
		VEHICLE.set_function("GET_HELI_MAIN_ROTOR_HEALTH", LUA_NATIVE_VEHICLE_GET_HELI_MAIN_ROTOR_HEALTH);
		VEHICLE.set_function("GET_HELI_TAIL_ROTOR_HEALTH", LUA_NATIVE_VEHICLE_GET_HELI_TAIL_ROTOR_HEALTH);
		VEHICLE.set_function("GET_HELI_TAIL_BOOM_HEALTH", LUA_NATIVE_VEHICLE_GET_HELI_TAIL_BOOM_HEALTH);
		VEHICLE.set_function("SET_HELI_MAIN_ROTOR_HEALTH", LUA_NATIVE_VEHICLE_SET_HELI_MAIN_ROTOR_HEALTH);
		VEHICLE.set_function("SET_HELI_TAIL_ROTOR_HEALTH", LUA_NATIVE_VEHICLE_SET_HELI_TAIL_ROTOR_HEALTH);
		VEHICLE.set_function("SET_HELI_TAIL_BOOM_CAN_BREAK_OFF", LUA_NATIVE_VEHICLE_SET_HELI_TAIL_BOOM_CAN_BREAK_OFF);
		VEHICLE.set_function("SET_VEHICLE_NAME_DEBUG", LUA_NATIVE_VEHICLE_SET_VEHICLE_NAME_DEBUG);
		VEHICLE.set_function("SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE);
		VEHICLE.set_function("SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH);
		VEHICLE.set_function("SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT", LUA_NATIVE_VEHICLE_SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT);
		VEHICLE.set_function("SET_VEHICLE_DISABLE_TOWING", LUA_NATIVE_VEHICLE_SET_VEHICLE_DISABLE_TOWING);
		VEHICLE.set_function("GET_VEHICLE_HAS_LANDING_GEAR", LUA_NATIVE_VEHICLE_GET_VEHICLE_HAS_LANDING_GEAR);
		VEHICLE.set_function("CONTROL_LANDING_GEAR", LUA_NATIVE_VEHICLE_CONTROL_LANDING_GEAR);
		VEHICLE.set_function("GET_LANDING_GEAR_STATE", LUA_NATIVE_VEHICLE_GET_LANDING_GEAR_STATE);
		VEHICLE.set_function("IS_ANY_VEHICLE_NEAR_POINT", LUA_NATIVE_VEHICLE_IS_ANY_VEHICLE_NEAR_POINT);
		VEHICLE.set_function("REQUEST_VEHICLE_HIGH_DETAIL_MODEL", LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_HIGH_DETAIL_MODEL);
		VEHICLE.set_function("GET_VEHICLE_MODEL_NUM_DRIVE_GEARS_", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_NUM_DRIVE_GEARS_);
		VEHICLE.set_function("GET_VEHICLE_MAX_DRIVE_GEAR_COUNT_", LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_DRIVE_GEAR_COUNT_);
		VEHICLE.set_function("GET_VEHICLE_CURRENT_DRIVE_GEAR_", LUA_NATIVE_VEHICLE_GET_VEHICLE_CURRENT_DRIVE_GEAR_);
		VEHICLE.set_function("GET_VEHICLE_CURRENT_REV_RATIO_", LUA_NATIVE_VEHICLE_GET_VEHICLE_CURRENT_REV_RATIO_);
		VEHICLE.set_function("REMOVE_VEHICLE_HIGH_DETAIL_MODEL", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_HIGH_DETAIL_MODEL);
		VEHICLE.set_function("IS_VEHICLE_HIGH_DETAIL", LUA_NATIVE_VEHICLE_IS_VEHICLE_HIGH_DETAIL);
		VEHICLE.set_function("REQUEST_VEHICLE_ASSET", LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_ASSET);
		VEHICLE.set_function("HAS_VEHICLE_ASSET_LOADED", LUA_NATIVE_VEHICLE_HAS_VEHICLE_ASSET_LOADED);
		VEHICLE.set_function("REMOVE_VEHICLE_ASSET", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_ASSET);
		VEHICLE.set_function("SET_VEHICLE_TOW_TRUCK_ARM_POSITION", LUA_NATIVE_VEHICLE_SET_VEHICLE_TOW_TRUCK_ARM_POSITION);
		VEHICLE.set_function("SET_ATTACHED_VEHICLE_TO_TOW_TRUCK_ARM_", LUA_NATIVE_VEHICLE_SET_ATTACHED_VEHICLE_TO_TOW_TRUCK_ARM_);
		VEHICLE.set_function("ATTACH_VEHICLE_TO_TOW_TRUCK", LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_TO_TOW_TRUCK);
		VEHICLE.set_function("DETACH_VEHICLE_FROM_TOW_TRUCK", LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_TOW_TRUCK);
		VEHICLE.set_function("DETACH_VEHICLE_FROM_ANY_TOW_TRUCK", LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_ANY_TOW_TRUCK);
		VEHICLE.set_function("IS_VEHICLE_ATTACHED_TO_TOW_TRUCK", LUA_NATIVE_VEHICLE_IS_VEHICLE_ATTACHED_TO_TOW_TRUCK);
		VEHICLE.set_function("GET_ENTITY_ATTACHED_TO_TOW_TRUCK", LUA_NATIVE_VEHICLE_GET_ENTITY_ATTACHED_TO_TOW_TRUCK);
		VEHICLE.set_function("SET_VEHICLE_AUTOMATICALLY_ATTACHES", LUA_NATIVE_VEHICLE_SET_VEHICLE_AUTOMATICALLY_ATTACHES);
		VEHICLE.set_function("SET_VEHICLE_BULLDOZER_ARM_POSITION", LUA_NATIVE_VEHICLE_SET_VEHICLE_BULLDOZER_ARM_POSITION);
		VEHICLE.set_function("SET_VEHICLE_TANK_TURRET_POSITION", LUA_NATIVE_VEHICLE_SET_VEHICLE_TANK_TURRET_POSITION);
		VEHICLE.set_function("SET_VEHICLE_TURRET_TARGET", LUA_NATIVE_VEHICLE_SET_VEHICLE_TURRET_TARGET);
		VEHICLE.set_function("SET_VEHICLE_TANK_STATIONARY", LUA_NATIVE_VEHICLE_SET_VEHICLE_TANK_STATIONARY);
		VEHICLE.set_function("SET_VEHICLE_TURRET_SPEED_THIS_FRAME", LUA_NATIVE_VEHICLE_SET_VEHICLE_TURRET_SPEED_THIS_FRAME);
		VEHICLE.set_function("DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME", LUA_NATIVE_VEHICLE_DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME);
		VEHICLE.set_function("SET_VEHICLE_FLIGHT_NOZZLE_POSITION", LUA_NATIVE_VEHICLE_SET_VEHICLE_FLIGHT_NOZZLE_POSITION);
		VEHICLE.set_function("SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE", LUA_NATIVE_VEHICLE_SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE);
		VEHICLE.set_function("GET_VEHICLE_FLIGHT_NOZZLE_POSITION", LUA_NATIVE_VEHICLE_GET_VEHICLE_FLIGHT_NOZZLE_POSITION);
		VEHICLE.set_function("SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION", LUA_NATIVE_VEHICLE_SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION);
		VEHICLE.set_function("GENERATE_VEHICLE_CREATION_POS_FROM_PATHS", LUA_NATIVE_VEHICLE_GENERATE_VEHICLE_CREATION_POS_FROM_PATHS);
		VEHICLE.set_function("SET_VEHICLE_BURNOUT", LUA_NATIVE_VEHICLE_SET_VEHICLE_BURNOUT);
		VEHICLE.set_function("IS_VEHICLE_IN_BURNOUT", LUA_NATIVE_VEHICLE_IS_VEHICLE_IN_BURNOUT);
		VEHICLE.set_function("SET_VEHICLE_REDUCE_GRIP", LUA_NATIVE_VEHICLE_SET_VEHICLE_REDUCE_GRIP);
		VEHICLE.set_function("SET_VEHICLE_REDUCE_GRIP_LEVEL", LUA_NATIVE_VEHICLE_SET_VEHICLE_REDUCE_GRIP_LEVEL);
		VEHICLE.set_function("SET_VEHICLE_INDICATOR_LIGHTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_INDICATOR_LIGHTS);
		VEHICLE.set_function("SET_VEHICLE_BRAKE_LIGHTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_BRAKE_LIGHTS);
		VEHICLE.set_function("SET_VEHICLE_TAIL_LIGHTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_TAIL_LIGHTS);
		VEHICLE.set_function("SET_VEHICLE_HANDBRAKE", LUA_NATIVE_VEHICLE_SET_VEHICLE_HANDBRAKE);
		VEHICLE.set_function("SET_VEHICLE_BRAKE", LUA_NATIVE_VEHICLE_SET_VEHICLE_BRAKE);
		VEHICLE.set_function("INSTANTLY_FILL_VEHICLE_POPULATION", LUA_NATIVE_VEHICLE_INSTANTLY_FILL_VEHICLE_POPULATION);
		VEHICLE.set_function("HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED", LUA_NATIVE_VEHICLE_HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED);
		VEHICLE.set_function("NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL", LUA_NATIVE_VEHICLE_NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL);
		VEHICLE.set_function("NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL", LUA_NATIVE_VEHICLE_NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL);
		VEHICLE.set_function("GET_VEHICLE_TRAILER_VEHICLE", LUA_NATIVE_VEHICLE_GET_VEHICLE_TRAILER_VEHICLE);
		VEHICLE.set_function("GET_VEHICLE_TRAILER_PARENT_VEHICLE_", LUA_NATIVE_VEHICLE_GET_VEHICLE_TRAILER_PARENT_VEHICLE_);
		VEHICLE.set_function("SET_VEHICLE_USES_LARGE_REAR_RAMP", LUA_NATIVE_VEHICLE_SET_VEHICLE_USES_LARGE_REAR_RAMP);
		VEHICLE.set_function("SET_VEHICLE_RUDDER_BROKEN", LUA_NATIVE_VEHICLE_SET_VEHICLE_RUDDER_BROKEN);
		VEHICLE.set_function("SET_CONVERTIBLE_ROOF_LATCH_STATE", LUA_NATIVE_VEHICLE_SET_CONVERTIBLE_ROOF_LATCH_STATE);
		VEHICLE.set_function("GET_VEHICLE_ESTIMATED_MAX_SPEED", LUA_NATIVE_VEHICLE_GET_VEHICLE_ESTIMATED_MAX_SPEED);
		VEHICLE.set_function("GET_VEHICLE_MAX_BRAKING", LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_BRAKING);
		VEHICLE.set_function("GET_VEHICLE_MAX_TRACTION", LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_TRACTION);
		VEHICLE.set_function("GET_VEHICLE_ACCELERATION", LUA_NATIVE_VEHICLE_GET_VEHICLE_ACCELERATION);
		VEHICLE.set_function("GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED);
		VEHICLE.set_function("GET_VEHICLE_MODEL_MAX_BRAKING", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_MAX_BRAKING);
		VEHICLE.set_function("GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS);
		VEHICLE.set_function("GET_VEHICLE_MODEL_MAX_TRACTION", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_MAX_TRACTION);
		VEHICLE.set_function("GET_VEHICLE_MODEL_ACCELERATION", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_ACCELERATION);
		VEHICLE.set_function("GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS", LUA_NATIVE_VEHICLE_GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS);
		VEHICLE.set_function("GET_FLYING_VEHICLE_MODEL_AGILITY", LUA_NATIVE_VEHICLE_GET_FLYING_VEHICLE_MODEL_AGILITY);
		VEHICLE.set_function("GET_BOAT_VEHICLE_MODEL_AGILITY", LUA_NATIVE_VEHICLE_GET_BOAT_VEHICLE_MODEL_AGILITY);
		VEHICLE.set_function("GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED);
		VEHICLE.set_function("GET_VEHICLE_CLASS_MAX_TRACTION", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_TRACTION);
		VEHICLE.set_function("GET_VEHICLE_CLASS_MAX_AGILITY", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_AGILITY);
		VEHICLE.set_function("GET_VEHICLE_CLASS_MAX_ACCELERATION", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_ACCELERATION);
		VEHICLE.set_function("GET_VEHICLE_CLASS_MAX_BRAKING", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_MAX_BRAKING);
		VEHICLE.set_function("ADD_ROAD_NODE_SPEED_ZONE", LUA_NATIVE_VEHICLE_ADD_ROAD_NODE_SPEED_ZONE);
		VEHICLE.set_function("REMOVE_ROAD_NODE_SPEED_ZONE", LUA_NATIVE_VEHICLE_REMOVE_ROAD_NODE_SPEED_ZONE);
		VEHICLE.set_function("OPEN_BOMB_BAY_DOORS", LUA_NATIVE_VEHICLE_OPEN_BOMB_BAY_DOORS);
		VEHICLE.set_function("CLOSE_BOMB_BAY_DOORS", LUA_NATIVE_VEHICLE_CLOSE_BOMB_BAY_DOORS);
		VEHICLE.set_function("GET_ARE_BOMB_BAY_DOORS_OPEN", LUA_NATIVE_VEHICLE_GET_ARE_BOMB_BAY_DOORS_OPEN);
		VEHICLE.set_function("IS_VEHICLE_SEARCHLIGHT_ON", LUA_NATIVE_VEHICLE_IS_VEHICLE_SEARCHLIGHT_ON);
		VEHICLE.set_function("SET_VEHICLE_SEARCHLIGHT", LUA_NATIVE_VEHICLE_SET_VEHICLE_SEARCHLIGHT);
		VEHICLE.set_function("DOES_VEHICLE_HAVE_SEARCHLIGHT", LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_SEARCHLIGHT);
		VEHICLE.set_function("IS_ENTRY_POINT_FOR_SEAT_CLEAR", LUA_NATIVE_VEHICLE_IS_ENTRY_POINT_FOR_SEAT_CLEAR);
		VEHICLE.set_function("GET_ENTRY_POINT_POSITION", LUA_NATIVE_VEHICLE_GET_ENTRY_POINT_POSITION);
		VEHICLE.set_function("CAN_SHUFFLE_SEAT", LUA_NATIVE_VEHICLE_CAN_SHUFFLE_SEAT);
		VEHICLE.set_function("GET_NUM_MOD_KITS", LUA_NATIVE_VEHICLE_GET_NUM_MOD_KITS);
		VEHICLE.set_function("SET_VEHICLE_MOD_KIT", LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD_KIT);
		VEHICLE.set_function("GET_VEHICLE_MOD_KIT", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_KIT);
		VEHICLE.set_function("GET_VEHICLE_MOD_KIT_TYPE", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_KIT_TYPE);
		VEHICLE.set_function("GET_VEHICLE_WHEEL_TYPE", LUA_NATIVE_VEHICLE_GET_VEHICLE_WHEEL_TYPE);
		VEHICLE.set_function("SET_VEHICLE_WHEEL_TYPE", LUA_NATIVE_VEHICLE_SET_VEHICLE_WHEEL_TYPE);
		VEHICLE.set_function("GET_NUM_MOD_COLORS", LUA_NATIVE_VEHICLE_GET_NUM_MOD_COLORS);
		VEHICLE.set_function("SET_VEHICLE_MOD_COLOR_1", LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD_COLOR_1);
		VEHICLE.set_function("SET_VEHICLE_MOD_COLOR_2", LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD_COLOR_2);
		VEHICLE.set_function("GET_VEHICLE_MOD_COLOR_1", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_1);
		VEHICLE.set_function("GET_VEHICLE_MOD_COLOR_2", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_2);
		VEHICLE.set_function("GET_VEHICLE_MOD_COLOR_1_NAME", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_1_NAME);
		VEHICLE.set_function("GET_VEHICLE_MOD_COLOR_2_NAME", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_COLOR_2_NAME);
		VEHICLE.set_function("HAVE_VEHICLE_MODS_STREAMED_IN", LUA_NATIVE_VEHICLE_HAVE_VEHICLE_MODS_STREAMED_IN);
		VEHICLE.set_function("IS_VEHICLE_MOD_GEN9_EXCLUSIVE", LUA_NATIVE_VEHICLE_IS_VEHICLE_MOD_GEN9_EXCLUSIVE);
		VEHICLE.set_function("SET_VEHICLE_MOD", LUA_NATIVE_VEHICLE_SET_VEHICLE_MOD);
		VEHICLE.set_function("GET_VEHICLE_MOD", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD);
		VEHICLE.set_function("GET_VEHICLE_MOD_VARIATION", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_VARIATION);
		VEHICLE.set_function("GET_NUM_VEHICLE_MODS", LUA_NATIVE_VEHICLE_GET_NUM_VEHICLE_MODS);
		VEHICLE.set_function("REMOVE_VEHICLE_MOD", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_MOD);
		VEHICLE.set_function("TOGGLE_VEHICLE_MOD", LUA_NATIVE_VEHICLE_TOGGLE_VEHICLE_MOD);
		VEHICLE.set_function("IS_TOGGLE_MOD_ON", LUA_NATIVE_VEHICLE_IS_TOGGLE_MOD_ON);
		VEHICLE.set_function("GET_MOD_TEXT_LABEL", LUA_NATIVE_VEHICLE_GET_MOD_TEXT_LABEL);
		VEHICLE.set_function("GET_MOD_SLOT_NAME", LUA_NATIVE_VEHICLE_GET_MOD_SLOT_NAME);
		VEHICLE.set_function("GET_LIVERY_NAME", LUA_NATIVE_VEHICLE_GET_LIVERY_NAME);
		VEHICLE.set_function("GET_VEHICLE_MOD_MODIFIER_VALUE", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_MODIFIER_VALUE);
		VEHICLE.set_function("GET_VEHICLE_MOD_IDENTIFIER_HASH", LUA_NATIVE_VEHICLE_GET_VEHICLE_MOD_IDENTIFIER_HASH);
		VEHICLE.set_function("PRELOAD_VEHICLE_MOD", LUA_NATIVE_VEHICLE_PRELOAD_VEHICLE_MOD);
		VEHICLE.set_function("HAS_PRELOAD_MODS_FINISHED", LUA_NATIVE_VEHICLE_HAS_PRELOAD_MODS_FINISHED);
		VEHICLE.set_function("RELEASE_PRELOAD_MODS", LUA_NATIVE_VEHICLE_RELEASE_PRELOAD_MODS);
		VEHICLE.set_function("SET_VEHICLE_TYRE_SMOKE_COLOR", LUA_NATIVE_VEHICLE_SET_VEHICLE_TYRE_SMOKE_COLOR);
		VEHICLE.set_function("GET_VEHICLE_TYRE_SMOKE_COLOR", LUA_NATIVE_VEHICLE_GET_VEHICLE_TYRE_SMOKE_COLOR);
		VEHICLE.set_function("SET_VEHICLE_WINDOW_TINT", LUA_NATIVE_VEHICLE_SET_VEHICLE_WINDOW_TINT);
		VEHICLE.set_function("GET_VEHICLE_WINDOW_TINT", LUA_NATIVE_VEHICLE_GET_VEHICLE_WINDOW_TINT);
		VEHICLE.set_function("GET_NUM_VEHICLE_WINDOW_TINTS", LUA_NATIVE_VEHICLE_GET_NUM_VEHICLE_WINDOW_TINTS);
		VEHICLE.set_function("GET_VEHICLE_COLOR", LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOR);
		VEHICLE.set_function("GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET", LUA_NATIVE_VEHICLE_GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET);
		VEHICLE.set_function("GET_VEHICLE_CAUSE_OF_DESTRUCTION", LUA_NATIVE_VEHICLE_GET_VEHICLE_CAUSE_OF_DESTRUCTION);
		VEHICLE.set_function("OVERRIDE_PLANE_DAMAGE_THREHSOLD", LUA_NATIVE_VEHICLE_OVERRIDE_PLANE_DAMAGE_THREHSOLD);
		VEHICLE.set_function("SET_TRANSMISSION_REDUCED_GEAR_RATIO_", LUA_NATIVE_VEHICLE_SET_TRANSMISSION_REDUCED_GEAR_RATIO_);
		VEHICLE.set_function("GET_VEHICLE_DESIRED_DRIVE_GEAR_", LUA_NATIVE_VEHICLE_GET_VEHICLE_DESIRED_DRIVE_GEAR_);
		VEHICLE.set_function("GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED", LUA_NATIVE_VEHICLE_GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED);
		VEHICLE.set_function("GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED", LUA_NATIVE_VEHICLE_GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED);
		VEHICLE.set_function("GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED", LUA_NATIVE_VEHICLE_GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED);
		VEHICLE.set_function("MODIFY_VEHICLE_TOP_SPEED", LUA_NATIVE_VEHICLE_MODIFY_VEHICLE_TOP_SPEED);
		VEHICLE.set_function("SET_VEHICLE_MAX_SPEED", LUA_NATIVE_VEHICLE_SET_VEHICLE_MAX_SPEED);
		VEHICLE.set_function("SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP", LUA_NATIVE_VEHICLE_SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP);
		VEHICLE.set_function("SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING", LUA_NATIVE_VEHICLE_SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING);
		VEHICLE.set_function("SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE", LUA_NATIVE_VEHICLE_SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE);
		VEHICLE.set_function("ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA", LUA_NATIVE_VEHICLE_ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA);
		VEHICLE.set_function("REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA", LUA_NATIVE_VEHICLE_REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA);
		VEHICLE.set_function("IS_ANY_PED_RAPPELLING_FROM_HELI", LUA_NATIVE_VEHICLE_IS_ANY_PED_RAPPELLING_FROM_HELI);
		VEHICLE.set_function("SET_VEHICLE_CHEAT_POWER_INCREASE", LUA_NATIVE_VEHICLE_SET_VEHICLE_CHEAT_POWER_INCREASE);
		VEHICLE.set_function("SET_VEHICLE_INFLUENCES_WANTED_LEVEL", LUA_NATIVE_VEHICLE_SET_VEHICLE_INFLUENCES_WANTED_LEVEL);
		VEHICLE.set_function("SET_VEHICLE_IS_WANTED", LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_WANTED);
		VEHICLE.set_function("SWING_BOAT_BOOM_TO_RATIO", LUA_NATIVE_VEHICLE_SWING_BOAT_BOOM_TO_RATIO);
		VEHICLE.set_function("SWING_BOAT_BOOM_FREELY", LUA_NATIVE_VEHICLE_SWING_BOAT_BOOM_FREELY);
		VEHICLE.set_function("ALLOW_BOAT_BOOM_TO_ANIMATE", LUA_NATIVE_VEHICLE_ALLOW_BOAT_BOOM_TO_ANIMATE);
		VEHICLE.set_function("GET_BOAT_BOOM_POSITION_RATIO", LUA_NATIVE_VEHICLE_GET_BOAT_BOOM_POSITION_RATIO);
		VEHICLE.set_function("DISABLE_PLANE_AILERON", LUA_NATIVE_VEHICLE_DISABLE_PLANE_AILERON);
		VEHICLE.set_function("GET_IS_VEHICLE_ENGINE_RUNNING", LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_ENGINE_RUNNING);
		VEHICLE.set_function("SET_VEHICLE_USE_ALTERNATE_HANDLING", LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_ALTERNATE_HANDLING);
		VEHICLE.set_function("SET_BIKE_ON_STAND", LUA_NATIVE_VEHICLE_SET_BIKE_ON_STAND);
		VEHICLE.set_function("SET_VEHICLE_NOT_STEALABLE_AMBIENTLY", LUA_NATIVE_VEHICLE_SET_VEHICLE_NOT_STEALABLE_AMBIENTLY);
		VEHICLE.set_function("LOCK_DOORS_WHEN_NO_LONGER_NEEDED", LUA_NATIVE_VEHICLE_LOCK_DOORS_WHEN_NO_LONGER_NEEDED);
		VEHICLE.set_function("SET_LAST_DRIVEN_VEHICLE", LUA_NATIVE_VEHICLE_SET_LAST_DRIVEN_VEHICLE);
		VEHICLE.set_function("GET_LAST_DRIVEN_VEHICLE", LUA_NATIVE_VEHICLE_GET_LAST_DRIVEN_VEHICLE);
		VEHICLE.set_function("CLEAR_LAST_DRIVEN_VEHICLE", LUA_NATIVE_VEHICLE_CLEAR_LAST_DRIVEN_VEHICLE);
		VEHICLE.set_function("SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG", LUA_NATIVE_VEHICLE_SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG);
		VEHICLE.set_function("SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN", LUA_NATIVE_VEHICLE_SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN);
		VEHICLE.set_function("SET_VEHICLE_LOD_MULTIPLIER", LUA_NATIVE_VEHICLE_SET_VEHICLE_LOD_MULTIPLIER);
		VEHICLE.set_function("SET_VEHICLE_CAN_SAVE_IN_GARAGE", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_SAVE_IN_GARAGE);
		VEHICLE.set_function("GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS", LUA_NATIVE_VEHICLE_GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS);
		VEHICLE.set_function("GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS", LUA_NATIVE_VEHICLE_GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS);
		VEHICLE.set_function("SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET", LUA_NATIVE_VEHICLE_SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET);
		VEHICLE.set_function("SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS);
		VEHICLE.set_function("COPY_VEHICLE_DAMAGES", LUA_NATIVE_VEHICLE_COPY_VEHICLE_DAMAGES);
		VEHICLE.set_function("DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS", LUA_NATIVE_VEHICLE_DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS);
		VEHICLE.set_function("SET_LIGHTS_CUTOFF_DISTANCE_TWEAK", LUA_NATIVE_VEHICLE_SET_LIGHTS_CUTOFF_DISTANCE_TWEAK);
		VEHICLE.set_function("SET_VEHICLE_SHOOT_AT_TARGET", LUA_NATIVE_VEHICLE_SET_VEHICLE_SHOOT_AT_TARGET);
		VEHICLE.set_function("GET_VEHICLE_LOCK_ON_TARGET", LUA_NATIVE_VEHICLE_GET_VEHICLE_LOCK_ON_TARGET);
		VEHICLE.set_function("SET_FORCE_HD_VEHICLE", LUA_NATIVE_VEHICLE_SET_FORCE_HD_VEHICLE);
		VEHICLE.set_function("SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS", LUA_NATIVE_VEHICLE_SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS);
		VEHICLE.set_function("GET_VEHICLE_PLATE_TYPE", LUA_NATIVE_VEHICLE_GET_VEHICLE_PLATE_TYPE);
		VEHICLE.set_function("TRACK_VEHICLE_VISIBILITY", LUA_NATIVE_VEHICLE_TRACK_VEHICLE_VISIBILITY);
		VEHICLE.set_function("IS_VEHICLE_VISIBLE", LUA_NATIVE_VEHICLE_IS_VEHICLE_VISIBLE);
		VEHICLE.set_function("SET_VEHICLE_GRAVITY", LUA_NATIVE_VEHICLE_SET_VEHICLE_GRAVITY);
		VEHICLE.set_function("SET_ENABLE_VEHICLE_SLIPSTREAMING", LUA_NATIVE_VEHICLE_SET_ENABLE_VEHICLE_SLIPSTREAMING);
		VEHICLE.set_function("SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT", LUA_NATIVE_VEHICLE_SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT);
		VEHICLE.set_function("GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM", LUA_NATIVE_VEHICLE_GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM);
		VEHICLE.set_function("IS_VEHICLE_PRODUCING_SLIP_STREAM", LUA_NATIVE_VEHICLE_IS_VEHICLE_PRODUCING_SLIP_STREAM);
		VEHICLE.set_function("SET_VEHICLE_INACTIVE_DURING_PLAYBACK", LUA_NATIVE_VEHICLE_SET_VEHICLE_INACTIVE_DURING_PLAYBACK);
		VEHICLE.set_function("SET_VEHICLE_ACTIVE_DURING_PLAYBACK", LUA_NATIVE_VEHICLE_SET_VEHICLE_ACTIVE_DURING_PLAYBACK);
		VEHICLE.set_function("IS_VEHICLE_SPRAYABLE", LUA_NATIVE_VEHICLE_IS_VEHICLE_SPRAYABLE);
		VEHICLE.set_function("SET_VEHICLE_ENGINE_CAN_DEGRADE", LUA_NATIVE_VEHICLE_SET_VEHICLE_ENGINE_CAN_DEGRADE);
		VEHICLE.set_function("DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES", LUA_NATIVE_VEHICLE_DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES);
		VEHICLE.set_function("ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES", LUA_NATIVE_VEHICLE_ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES);
		VEHICLE.set_function("IS_PLANE_LANDING_GEAR_INTACT", LUA_NATIVE_VEHICLE_IS_PLANE_LANDING_GEAR_INTACT);
		VEHICLE.set_function("ARE_PLANE_PROPELLERS_INTACT", LUA_NATIVE_VEHICLE_ARE_PLANE_PROPELLERS_INTACT);
		VEHICLE.set_function("SET_PLANE_PROPELLER_HEALTH", LUA_NATIVE_VEHICLE_SET_PLANE_PROPELLER_HEALTH);
		VEHICLE.set_function("SET_VEHICLE_CAN_DEFORM_WHEELS", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_DEFORM_WHEELS);
		VEHICLE.set_function("IS_VEHICLE_STOLEN", LUA_NATIVE_VEHICLE_IS_VEHICLE_STOLEN);
		VEHICLE.set_function("SET_VEHICLE_IS_STOLEN", LUA_NATIVE_VEHICLE_SET_VEHICLE_IS_STOLEN);
		VEHICLE.set_function("SET_PLANE_TURBULENCE_MULTIPLIER", LUA_NATIVE_VEHICLE_SET_PLANE_TURBULENCE_MULTIPLIER);
		VEHICLE.set_function("ARE_WINGS_OF_PLANE_INTACT", LUA_NATIVE_VEHICLE_ARE_WINGS_OF_PLANE_INTACT);
		VEHICLE.set_function("ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS", LUA_NATIVE_VEHICLE_ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS);
		VEHICLE.set_function("DETACH_VEHICLE_FROM_CARGOBOB", LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_CARGOBOB);
		VEHICLE.set_function("DETACH_VEHICLE_FROM_ANY_CARGOBOB", LUA_NATIVE_VEHICLE_DETACH_VEHICLE_FROM_ANY_CARGOBOB);
		VEHICLE.set_function("DETACH_ENTITY_FROM_CARGOBOB", LUA_NATIVE_VEHICLE_DETACH_ENTITY_FROM_CARGOBOB);
		VEHICLE.set_function("IS_VEHICLE_ATTACHED_TO_CARGOBOB", LUA_NATIVE_VEHICLE_IS_VEHICLE_ATTACHED_TO_CARGOBOB);
		VEHICLE.set_function("GET_VEHICLE_ATTACHED_TO_CARGOBOB", LUA_NATIVE_VEHICLE_GET_VEHICLE_ATTACHED_TO_CARGOBOB);
		VEHICLE.set_function("GET_ENTITY_ATTACHED_TO_CARGOBOB", LUA_NATIVE_VEHICLE_GET_ENTITY_ATTACHED_TO_CARGOBOB);
		VEHICLE.set_function("ATTACH_VEHICLE_TO_CARGOBOB", LUA_NATIVE_VEHICLE_ATTACH_VEHICLE_TO_CARGOBOB);
		VEHICLE.set_function("ATTACH_ENTITY_TO_CARGOBOB", LUA_NATIVE_VEHICLE_ATTACH_ENTITY_TO_CARGOBOB);
		VEHICLE.set_function("SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE", LUA_NATIVE_VEHICLE_SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE);
		VEHICLE.set_function("SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY", LUA_NATIVE_VEHICLE_SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY);
		VEHICLE.set_function("CAN_CARGOBOB_PICK_UP_ENTITY", LUA_NATIVE_VEHICLE_CAN_CARGOBOB_PICK_UP_ENTITY);
		VEHICLE.set_function("GET_ATTACHED_PICK_UP_HOOK_POSITION", LUA_NATIVE_VEHICLE_GET_ATTACHED_PICK_UP_HOOK_POSITION);
		VEHICLE.set_function("DOES_CARGOBOB_HAVE_PICK_UP_ROPE", LUA_NATIVE_VEHICLE_DOES_CARGOBOB_HAVE_PICK_UP_ROPE);
		VEHICLE.set_function("CREATE_PICK_UP_ROPE_FOR_CARGOBOB", LUA_NATIVE_VEHICLE_CREATE_PICK_UP_ROPE_FOR_CARGOBOB);
		VEHICLE.set_function("REMOVE_PICK_UP_ROPE_FOR_CARGOBOB", LUA_NATIVE_VEHICLE_REMOVE_PICK_UP_ROPE_FOR_CARGOBOB);
		VEHICLE.set_function("SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB", LUA_NATIVE_VEHICLE_SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB);
		VEHICLE.set_function("SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB", LUA_NATIVE_VEHICLE_SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_ROPE_TYPE", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_ROPE_TYPE);
		VEHICLE.set_function("DOES_CARGOBOB_HAVE_PICKUP_MAGNET", LUA_NATIVE_VEHICLE_DOES_CARGOBOB_HAVE_PICKUP_MAGNET);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_ACTIVE", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_ACTIVE);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_STRENGTH", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_STRENGTH);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_FALLOFF", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_FALLOFF);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE);
		VEHICLE.set_function("SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT", LUA_NATIVE_VEHICLE_SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT);
		VEHICLE.set_function("DOES_VEHICLE_HAVE_WEAPONS", LUA_NATIVE_VEHICLE_DOES_VEHICLE_HAVE_WEAPONS);
		VEHICLE.set_function("SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY", LUA_NATIVE_VEHICLE_SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY);
		VEHICLE.set_function("DISABLE_VEHICLE_WEAPON", LUA_NATIVE_VEHICLE_DISABLE_VEHICLE_WEAPON);
		VEHICLE.set_function("IS_VEHICLE_WEAPON_DISABLED", LUA_NATIVE_VEHICLE_IS_VEHICLE_WEAPON_DISABLED);
		VEHICLE.set_function("SET_VEHICLE_USED_FOR_PILOT_SCHOOL", LUA_NATIVE_VEHICLE_SET_VEHICLE_USED_FOR_PILOT_SCHOOL);
		VEHICLE.set_function("SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION", LUA_NATIVE_VEHICLE_SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION);
		VEHICLE.set_function("GET_VEHICLE_CLASS", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS);
		VEHICLE.set_function("GET_VEHICLE_CLASS_FROM_NAME", LUA_NATIVE_VEHICLE_GET_VEHICLE_CLASS_FROM_NAME);
		VEHICLE.set_function("SET_PLAYERS_LAST_VEHICLE", LUA_NATIVE_VEHICLE_SET_PLAYERS_LAST_VEHICLE);
		VEHICLE.set_function("SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS", LUA_NATIVE_VEHICLE_SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS);
		VEHICLE.set_function("SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR", LUA_NATIVE_VEHICLE_SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR);
		VEHICLE.set_function("SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP", LUA_NATIVE_VEHICLE_SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP);
		VEHICLE.set_function("SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED", LUA_NATIVE_VEHICLE_SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED);
		VEHICLE.set_function("SET_VEHICLE_IMPATIENCE_TIMER", LUA_NATIVE_VEHICLE_SET_VEHICLE_IMPATIENCE_TIMER);
		VEHICLE.set_function("SET_VEHICLE_HANDLING_OVERRIDE", LUA_NATIVE_VEHICLE_SET_VEHICLE_HANDLING_OVERRIDE);
		VEHICLE.set_function("SET_VEHICLE_EXTENDED_REMOVAL_RANGE", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXTENDED_REMOVAL_RANGE);
		VEHICLE.set_function("SET_VEHICLE_STEERING_BIAS_SCALAR", LUA_NATIVE_VEHICLE_SET_VEHICLE_STEERING_BIAS_SCALAR);
		VEHICLE.set_function("SET_HELI_CONTROL_LAGGING_RATE_SCALAR", LUA_NATIVE_VEHICLE_SET_HELI_CONTROL_LAGGING_RATE_SCALAR);
		VEHICLE.set_function("SET_VEHICLE_FRICTION_OVERRIDE", LUA_NATIVE_VEHICLE_SET_VEHICLE_FRICTION_OVERRIDE);
		VEHICLE.set_function("SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP", LUA_NATIVE_VEHICLE_SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP);
		VEHICLE.set_function("ARE_PLANE_CONTROL_PANELS_INTACT", LUA_NATIVE_VEHICLE_ARE_PLANE_CONTROL_PANELS_INTACT);
		VEHICLE.set_function("SET_VEHICLE_CEILING_HEIGHT", LUA_NATIVE_VEHICLE_SET_VEHICLE_CEILING_HEIGHT);
		VEHICLE.set_function("SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER", LUA_NATIVE_VEHICLE_SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER);
		VEHICLE.set_function("CLEAR_VEHICLE_ROUTE_HISTORY", LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_ROUTE_HISTORY);
		VEHICLE.set_function("DOES_VEHICLE_EXIST_WITH_DECORATOR", LUA_NATIVE_VEHICLE_DOES_VEHICLE_EXIST_WITH_DECORATOR);
		VEHICLE.set_function("SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS", LUA_NATIVE_VEHICLE_SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS);
		VEHICLE.set_function("SET_VEHICLE_EXCLUSIVE_DRIVER", LUA_NATIVE_VEHICLE_SET_VEHICLE_EXCLUSIVE_DRIVER);
		VEHICLE.set_function("IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE", LUA_NATIVE_VEHICLE_IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE);
		VEHICLE.set_function("DISABLE_INDIVIDUAL_PLANE_PROPELLER", LUA_NATIVE_VEHICLE_DISABLE_INDIVIDUAL_PLANE_PROPELLER);
		VEHICLE.set_function("SET_VEHICLE_FORCE_AFTERBURNER", LUA_NATIVE_VEHICLE_SET_VEHICLE_FORCE_AFTERBURNER);
		VEHICLE.set_function("SET_DONT_PROCESS_VEHICLE_GLASS", LUA_NATIVE_VEHICLE_SET_DONT_PROCESS_VEHICLE_GLASS);
		VEHICLE.set_function("SET_DISABLE_WANTED_CONES_RESPONSE", LUA_NATIVE_VEHICLE_SET_DISABLE_WANTED_CONES_RESPONSE);
		VEHICLE.set_function("SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING", LUA_NATIVE_VEHICLE_SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING);
		VEHICLE.set_function("SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK", LUA_NATIVE_VEHICLE_SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK);
		VEHICLE.set_function("SET_VEHICLE_READY_FOR_CLEANUP", LUA_NATIVE_VEHICLE_SET_VEHICLE_READY_FOR_CLEANUP);
		VEHICLE.set_function("SET_DISTANT_CARS_ENABLED", LUA_NATIVE_VEHICLE_SET_DISTANT_CARS_ENABLED);
		VEHICLE.set_function("SET_VEHICLE_NEON_COLOUR", LUA_NATIVE_VEHICLE_SET_VEHICLE_NEON_COLOUR);
		VEHICLE.set_function("SET_VEHICLE_NEON_INDEX_COLOUR", LUA_NATIVE_VEHICLE_SET_VEHICLE_NEON_INDEX_COLOUR);
		VEHICLE.set_function("GET_VEHICLE_NEON_COLOUR", LUA_NATIVE_VEHICLE_GET_VEHICLE_NEON_COLOUR);
		VEHICLE.set_function("SET_VEHICLE_NEON_ENABLED", LUA_NATIVE_VEHICLE_SET_VEHICLE_NEON_ENABLED);
		VEHICLE.set_function("GET_VEHICLE_NEON_ENABLED", LUA_NATIVE_VEHICLE_GET_VEHICLE_NEON_ENABLED);
		VEHICLE.set_function("SET_AMBIENT_VEHICLE_NEON_ENABLED", LUA_NATIVE_VEHICLE_SET_AMBIENT_VEHICLE_NEON_ENABLED);
		VEHICLE.set_function("SUPPRESS_NEONS_ON_VEHICLE", LUA_NATIVE_VEHICLE_SUPPRESS_NEONS_ON_VEHICLE);
		VEHICLE.set_function("SET_DISABLE_SUPERDUMMY", LUA_NATIVE_VEHICLE_SET_DISABLE_SUPERDUMMY);
		VEHICLE.set_function("REQUEST_VEHICLE_DIAL", LUA_NATIVE_VEHICLE_REQUEST_VEHICLE_DIAL);
		VEHICLE.set_function("GET_VEHICLE_BODY_HEALTH", LUA_NATIVE_VEHICLE_GET_VEHICLE_BODY_HEALTH);
		VEHICLE.set_function("SET_VEHICLE_BODY_HEALTH", LUA_NATIVE_VEHICLE_SET_VEHICLE_BODY_HEALTH);
		VEHICLE.set_function("GET_VEHICLE_SIZE", LUA_NATIVE_VEHICLE_GET_VEHICLE_SIZE);
		VEHICLE.set_function("GET_FAKE_SUSPENSION_LOWERING_AMOUNT", LUA_NATIVE_VEHICLE_GET_FAKE_SUSPENSION_LOWERING_AMOUNT);
		VEHICLE.set_function("SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER", LUA_NATIVE_VEHICLE_SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER);
		VEHICLE.set_function("GET_NUMBER_OF_VEHICLE_DOORS", LUA_NATIVE_VEHICLE_GET_NUMBER_OF_VEHICLE_DOORS);
		VEHICLE.set_function("SET_HYDRAULICS_CONTROL", LUA_NATIVE_VEHICLE_SET_HYDRAULICS_CONTROL);
		VEHICLE.set_function("SET_CAN_ADJUST_GROUND_CLEARANCE", LUA_NATIVE_VEHICLE_SET_CAN_ADJUST_GROUND_CLEARANCE);
		VEHICLE.set_function("GET_VEHICLE_HEALTH_PERCENTAGE", LUA_NATIVE_VEHICLE_GET_VEHICLE_HEALTH_PERCENTAGE);
		VEHICLE.set_function("GET_VEHICLE_IS_MERCENARY", LUA_NATIVE_VEHICLE_GET_VEHICLE_IS_MERCENARY);
		VEHICLE.set_function("SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING", LUA_NATIVE_VEHICLE_SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING);
		VEHICLE.set_function("SET_VEHICLE_KERS_ALLOWED", LUA_NATIVE_VEHICLE_SET_VEHICLE_KERS_ALLOWED);
		VEHICLE.set_function("GET_VEHICLE_HAS_KERS", LUA_NATIVE_VEHICLE_GET_VEHICLE_HAS_KERS);
		VEHICLE.set_function("SET_PLANE_RESIST_TO_EXPLOSION", LUA_NATIVE_VEHICLE_SET_PLANE_RESIST_TO_EXPLOSION);
		VEHICLE.set_function("SET_HELI_RESIST_TO_EXPLOSION", LUA_NATIVE_VEHICLE_SET_HELI_RESIST_TO_EXPLOSION);
		VEHICLE.set_function("SET_DISABLE_BMX_EXTRA_TRICK_FORCES", LUA_NATIVE_VEHICLE_SET_DISABLE_BMX_EXTRA_TRICK_FORCES);
		VEHICLE.set_function("SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR", LUA_NATIVE_VEHICLE_SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR);
		VEHICLE.set_function("GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR", LUA_NATIVE_VEHICLE_GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR);
		VEHICLE.set_function("SET_CAN_USE_HYDRAULICS", LUA_NATIVE_VEHICLE_SET_CAN_USE_HYDRAULICS);
		VEHICLE.set_function("SET_HYDRAULIC_VEHICLE_STATE", LUA_NATIVE_VEHICLE_SET_HYDRAULIC_VEHICLE_STATE);
		VEHICLE.set_function("SET_HYDRAULIC_WHEEL_STATE", LUA_NATIVE_VEHICLE_SET_HYDRAULIC_WHEEL_STATE);
		VEHICLE.set_function("HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY", LUA_NATIVE_VEHICLE_HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY);
		VEHICLE.set_function("CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT", LUA_NATIVE_VEHICLE_CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT);
		VEHICLE.set_function("SET_VEHICLE_BOBBLEHEAD_VELOCITY", LUA_NATIVE_VEHICLE_SET_VEHICLE_BOBBLEHEAD_VELOCITY);
		VEHICLE.set_function("GET_VEHICLE_IS_DUMMY", LUA_NATIVE_VEHICLE_GET_VEHICLE_IS_DUMMY);
		VEHICLE.set_function("SET_VEHICLE_DAMAGE_SCALE", LUA_NATIVE_VEHICLE_SET_VEHICLE_DAMAGE_SCALE);
		VEHICLE.set_function("SET_VEHICLE_WEAPON_DAMAGE_SCALE", LUA_NATIVE_VEHICLE_SET_VEHICLE_WEAPON_DAMAGE_SCALE);
		VEHICLE.set_function("SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY", LUA_NATIVE_VEHICLE_SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY);
		VEHICLE.set_function("SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER", LUA_NATIVE_VEHICLE_SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER);
		VEHICLE.set_function("SET_BIKE_EASY_TO_LAND", LUA_NATIVE_VEHICLE_SET_BIKE_EASY_TO_LAND);
		VEHICLE.set_function("SET_INVERT_VEHICLE_CONTROLS", LUA_NATIVE_VEHICLE_SET_INVERT_VEHICLE_CONTROLS);
		VEHICLE.set_function("SET_SPEED_BOOST_EFFECT_DISABLED", LUA_NATIVE_VEHICLE_SET_SPEED_BOOST_EFFECT_DISABLED);
		VEHICLE.set_function("SET_SLOW_DOWN_EFFECT_DISABLED", LUA_NATIVE_VEHICLE_SET_SLOW_DOWN_EFFECT_DISABLED);
		VEHICLE.set_function("SET_FORMATION_LEADER", LUA_NATIVE_VEHICLE_SET_FORMATION_LEADER);
		VEHICLE.set_function("RESET_FORMATION_LEADER", LUA_NATIVE_VEHICLE_RESET_FORMATION_LEADER);
		VEHICLE.set_function("GET_IS_BOAT_CAPSIZED", LUA_NATIVE_VEHICLE_GET_IS_BOAT_CAPSIZED);
		VEHICLE.set_function("SET_ALLOW_RAMMING_SOOP_OR_RAMP", LUA_NATIVE_VEHICLE_SET_ALLOW_RAMMING_SOOP_OR_RAMP);
		VEHICLE.set_function("SET_SCRIPT_RAMP_IMPULSE_SCALE", LUA_NATIVE_VEHICLE_SET_SCRIPT_RAMP_IMPULSE_SCALE);
		VEHICLE.set_function("GET_IS_DOOR_VALID", LUA_NATIVE_VEHICLE_GET_IS_DOOR_VALID);
		VEHICLE.set_function("SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME", LUA_NATIVE_VEHICLE_SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME);
		VEHICLE.set_function("GET_HAS_ROCKET_BOOST", LUA_NATIVE_VEHICLE_GET_HAS_ROCKET_BOOST);
		VEHICLE.set_function("IS_ROCKET_BOOST_ACTIVE", LUA_NATIVE_VEHICLE_IS_ROCKET_BOOST_ACTIVE);
		VEHICLE.set_function("SET_ROCKET_BOOST_ACTIVE", LUA_NATIVE_VEHICLE_SET_ROCKET_BOOST_ACTIVE);
		VEHICLE.set_function("GET_HAS_RETRACTABLE_WHEELS", LUA_NATIVE_VEHICLE_GET_HAS_RETRACTABLE_WHEELS);
		VEHICLE.set_function("GET_IS_WHEELS_RETRACTED", LUA_NATIVE_VEHICLE_GET_IS_WHEELS_RETRACTED);
		VEHICLE.set_function("SET_WHEELS_EXTENDED_INSTANTLY", LUA_NATIVE_VEHICLE_SET_WHEELS_EXTENDED_INSTANTLY);
		VEHICLE.set_function("SET_WHEELS_RETRACTED_INSTANTLY", LUA_NATIVE_VEHICLE_SET_WHEELS_RETRACTED_INSTANTLY);
		VEHICLE.set_function("GET_CAR_HAS_JUMP", LUA_NATIVE_VEHICLE_GET_CAR_HAS_JUMP);
		VEHICLE.set_function("SET_USE_HIGHER_CAR_JUMP", LUA_NATIVE_VEHICLE_SET_USE_HIGHER_CAR_JUMP);
		VEHICLE.set_function("SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS", LUA_NATIVE_VEHICLE_SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS);
		VEHICLE.set_function("SET_VEHICLE_WEAPON_RESTRICTED_AMMO", LUA_NATIVE_VEHICLE_SET_VEHICLE_WEAPON_RESTRICTED_AMMO);
		VEHICLE.set_function("GET_VEHICLE_WEAPON_RESTRICTED_AMMO", LUA_NATIVE_VEHICLE_GET_VEHICLE_WEAPON_RESTRICTED_AMMO);
		VEHICLE.set_function("GET_VEHICLE_HAS_PARACHUTE", LUA_NATIVE_VEHICLE_GET_VEHICLE_HAS_PARACHUTE);
		VEHICLE.set_function("GET_VEHICLE_CAN_DEPLOY_PARACHUTE", LUA_NATIVE_VEHICLE_GET_VEHICLE_CAN_DEPLOY_PARACHUTE);
		VEHICLE.set_function("VEHICLE_START_PARACHUTING", LUA_NATIVE_VEHICLE_VEHICLE_START_PARACHUTING);
		VEHICLE.set_function("IS_VEHICLE_PARACHUTE_DEPLOYED", LUA_NATIVE_VEHICLE_IS_VEHICLE_PARACHUTE_DEPLOYED);
		VEHICLE.set_function("VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE", LUA_NATIVE_VEHICLE_VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE);
		VEHICLE.set_function("VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE", LUA_NATIVE_VEHICLE_VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE);
		VEHICLE.set_function("VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY", LUA_NATIVE_VEHICLE_VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY);
		VEHICLE.set_function("VEHICLE_SET_JET_WASH_FORCE_ENABLED", LUA_NATIVE_VEHICLE_VEHICLE_SET_JET_WASH_FORCE_ENABLED);
		VEHICLE.set_function("SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS", LUA_NATIVE_VEHICLE_SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS);
		VEHICLE.set_function("SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT", LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT);
		VEHICLE.set_function("SET_VEHICLE_USE_HORN_BUTTON_FOR_NITROUS_", LUA_NATIVE_VEHICLE_SET_VEHICLE_USE_HORN_BUTTON_FOR_NITROUS_);
		VEHICLE.set_function("VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE", LUA_NATIVE_VEHICLE_VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE);
		VEHICLE.set_function("VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX", LUA_NATIVE_VEHICLE_VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX);
		VEHICLE.set_function("VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO", LUA_NATIVE_VEHICLE_VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO);
		VEHICLE.set_function("VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO", LUA_NATIVE_VEHICLE_VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO);
		VEHICLE.set_function("VEHICLE_SET_OVERRIDE_SIDE_RATIO", LUA_NATIVE_VEHICLE_VEHICLE_SET_OVERRIDE_SIDE_RATIO);
		VEHICLE.set_function("GET_ALL_VEHICLES", LUA_NATIVE_VEHICLE_GET_ALL_VEHICLES);
		VEHICLE.set_function("SET_CARGOBOB_EXTA_PICKUP_RANGE", LUA_NATIVE_VEHICLE_SET_CARGOBOB_EXTA_PICKUP_RANGE);
		VEHICLE.set_function("SET_OVERRIDE_VEHICLE_DOOR_TORQUE", LUA_NATIVE_VEHICLE_SET_OVERRIDE_VEHICLE_DOOR_TORQUE);
		VEHICLE.set_function("SET_WHEELIE_ENABLED", LUA_NATIVE_VEHICLE_SET_WHEELIE_ENABLED);
		VEHICLE.set_function("SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE", LUA_NATIVE_VEHICLE_SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE);
		VEHICLE.set_function("SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION", LUA_NATIVE_VEHICLE_SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION);
		VEHICLE.set_function("SET_TRAILER_ATTACHMENT_ENABLED", LUA_NATIVE_VEHICLE_SET_TRAILER_ATTACHMENT_ENABLED);
		VEHICLE.set_function("SET_ROCKET_BOOST_FILL", LUA_NATIVE_VEHICLE_SET_ROCKET_BOOST_FILL);
		VEHICLE.set_function("SET_GLIDER_ACTIVE", LUA_NATIVE_VEHICLE_SET_GLIDER_ACTIVE);
		VEHICLE.set_function("SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS", LUA_NATIVE_VEHICLE_SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS);
		VEHICLE.set_function("SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION", LUA_NATIVE_VEHICLE_SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION);
		VEHICLE.set_function("SET_GROUND_EFFECT_REDUCES_DRAG", LUA_NATIVE_VEHICLE_SET_GROUND_EFFECT_REDUCES_DRAG);
		VEHICLE.set_function("SET_DISABLE_MAP_COLLISION", LUA_NATIVE_VEHICLE_SET_DISABLE_MAP_COLLISION);
		VEHICLE.set_function("SET_DISABLE_PED_STAND_ON_TOP", LUA_NATIVE_VEHICLE_SET_DISABLE_PED_STAND_ON_TOP);
		VEHICLE.set_function("SET_VEHICLE_DAMAGE_SCALES", LUA_NATIVE_VEHICLE_SET_VEHICLE_DAMAGE_SCALES);
		VEHICLE.set_function("SET_PLANE_SECTION_DAMAGE_SCALE", LUA_NATIVE_VEHICLE_SET_PLANE_SECTION_DAMAGE_SCALE);
		VEHICLE.set_function("SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED", LUA_NATIVE_VEHICLE_SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED);
		VEHICLE.set_function("SET_VEHICLE_BOMB_AMMO", LUA_NATIVE_VEHICLE_SET_VEHICLE_BOMB_AMMO);
		VEHICLE.set_function("GET_VEHICLE_BOMB_AMMO", LUA_NATIVE_VEHICLE_GET_VEHICLE_BOMB_AMMO);
		VEHICLE.set_function("SET_VEHICLE_COUNTERMEASURE_AMMO", LUA_NATIVE_VEHICLE_SET_VEHICLE_COUNTERMEASURE_AMMO);
		VEHICLE.set_function("GET_VEHICLE_COUNTERMEASURE_AMMO", LUA_NATIVE_VEHICLE_GET_VEHICLE_COUNTERMEASURE_AMMO);
		VEHICLE.set_function("SET_HELI_COMBAT_OFFSET", LUA_NATIVE_VEHICLE_SET_HELI_COMBAT_OFFSET);
		VEHICLE.set_function("GET_CAN_VEHICLE_BE_PLACED_HERE", LUA_NATIVE_VEHICLE_GET_CAN_VEHICLE_BE_PLACED_HERE);
		VEHICLE.set_function("SET_DISABLE_AUTOMATIC_CRASH_TASK", LUA_NATIVE_VEHICLE_SET_DISABLE_AUTOMATIC_CRASH_TASK);
		VEHICLE.set_function("SET_SPECIAL_FLIGHT_MODE_RATIO", LUA_NATIVE_VEHICLE_SET_SPECIAL_FLIGHT_MODE_RATIO);
		VEHICLE.set_function("SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO", LUA_NATIVE_VEHICLE_SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO);
		VEHICLE.set_function("SET_SPECIAL_FLIGHT_MODE_ALLOWED", LUA_NATIVE_VEHICLE_SET_SPECIAL_FLIGHT_MODE_ALLOWED);
		VEHICLE.set_function("SET_DISABLE_HOVER_MODE_FLIGHT", LUA_NATIVE_VEHICLE_SET_DISABLE_HOVER_MODE_FLIGHT);
		VEHICLE.set_function("GET_OUTRIGGERS_DEPLOYED", LUA_NATIVE_VEHICLE_GET_OUTRIGGERS_DEPLOYED);
		VEHICLE.set_function("FIND_SPAWN_COORDINATES_FOR_HELI", LUA_NATIVE_VEHICLE_FIND_SPAWN_COORDINATES_FOR_HELI);
		VEHICLE.set_function("SET_DEPLOY_FOLDING_WINGS", LUA_NATIVE_VEHICLE_SET_DEPLOY_FOLDING_WINGS);
		VEHICLE.set_function("ARE_FOLDING_WINGS_DEPLOYED", LUA_NATIVE_VEHICLE_ARE_FOLDING_WINGS_DEPLOYED);
		VEHICLE.set_function("SET_DEPLOY_MISSILE_BAYS_", LUA_NATIVE_VEHICLE_SET_DEPLOY_MISSILE_BAYS_);
		VEHICLE.set_function("ARE_MISSILE_BAYS_DEPLOYED_", LUA_NATIVE_VEHICLE_ARE_MISSILE_BAYS_DEPLOYED_);
		VEHICLE.set_function("SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE", LUA_NATIVE_VEHICLE_SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE);
		VEHICLE.set_function("SET_TURRET_HIDDEN", LUA_NATIVE_VEHICLE_SET_TURRET_HIDDEN);
		VEHICLE.set_function("SET_HOVER_MODE_WING_RATIO", LUA_NATIVE_VEHICLE_SET_HOVER_MODE_WING_RATIO);
		VEHICLE.set_function("SET_DISABLE_TURRET_MOVEMENT", LUA_NATIVE_VEHICLE_SET_DISABLE_TURRET_MOVEMENT);
		VEHICLE.set_function("SET_FORCE_FIX_LINK_MATRICES", LUA_NATIVE_VEHICLE_SET_FORCE_FIX_LINK_MATRICES);
		VEHICLE.set_function("SET_TRANSFORM_RATE_FOR_ANIMATION", LUA_NATIVE_VEHICLE_SET_TRANSFORM_RATE_FOR_ANIMATION);
		VEHICLE.set_function("SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT", LUA_NATIVE_VEHICLE_SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT);
		VEHICLE.set_function("SET_VEHICLE_COMBAT_MODE", LUA_NATIVE_VEHICLE_SET_VEHICLE_COMBAT_MODE);
		VEHICLE.set_function("SET_VEHICLE_DETONATION_MODE", LUA_NATIVE_VEHICLE_SET_VEHICLE_DETONATION_MODE);
		VEHICLE.set_function("SET_VEHICLE_SHUNT_ON_STICK", LUA_NATIVE_VEHICLE_SET_VEHICLE_SHUNT_ON_STICK);
		VEHICLE.set_function("GET_IS_VEHICLE_SHUNTING", LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_SHUNTING);
		VEHICLE.set_function("GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT", LUA_NATIVE_VEHICLE_GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT);
		VEHICLE.set_function("GET_LAST_SHUNT_VEHICLE", LUA_NATIVE_VEHICLE_GET_LAST_SHUNT_VEHICLE);
		VEHICLE.set_function("SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE", LUA_NATIVE_VEHICLE_SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE);
		VEHICLE.set_function("SET_OVERRIDE_NITROUS_LEVEL", LUA_NATIVE_VEHICLE_SET_OVERRIDE_NITROUS_LEVEL);
		VEHICLE.set_function("SET_NITROUS_IS_ACTIVE", LUA_NATIVE_VEHICLE_SET_NITROUS_IS_ACTIVE);
		VEHICLE.set_function("SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER_", LUA_NATIVE_VEHICLE_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER_);
		VEHICLE.set_function("SET_DRIFT_SLIP_ANGLE_LIMITS_", LUA_NATIVE_VEHICLE_SET_DRIFT_SLIP_ANGLE_LIMITS_);
		VEHICLE.set_function("SET_MINIMUM_TIME_BETWEEN_GEAR_SHIFTS_", LUA_NATIVE_VEHICLE_SET_MINIMUM_TIME_BETWEEN_GEAR_SHIFTS_);
		VEHICLE.set_function("FULLY_CHARGE_NITROUS", LUA_NATIVE_VEHICLE_FULLY_CHARGE_NITROUS);
		VEHICLE.set_function("GET_REMAINING_NITROUS_DURATION_", LUA_NATIVE_VEHICLE_GET_REMAINING_NITROUS_DURATION_);
		VEHICLE.set_function("IS_NITROUS_ACTIVE", LUA_NATIVE_VEHICLE_IS_NITROUS_ACTIVE);
		VEHICLE.set_function("CLEAR_NITROUS", LUA_NATIVE_VEHICLE_CLEAR_NITROUS);
		VEHICLE.set_function("SET_INCREASE_WHEEL_CRUSH_DAMAGE", LUA_NATIVE_VEHICLE_SET_INCREASE_WHEEL_CRUSH_DAMAGE);
		VEHICLE.set_function("SET_DISABLE_WEAPON_BLADE_FORCES", LUA_NATIVE_VEHICLE_SET_DISABLE_WEAPON_BLADE_FORCES);
		VEHICLE.set_function("SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP", LUA_NATIVE_VEHICLE_SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP);
		VEHICLE.set_function("GET_DOES_VEHICLE_HAVE_TOMBSTONE", LUA_NATIVE_VEHICLE_GET_DOES_VEHICLE_HAVE_TOMBSTONE);
		VEHICLE.set_function("HIDE_TOMBSTONE", LUA_NATIVE_VEHICLE_HIDE_TOMBSTONE);
		VEHICLE.set_function("APPLY_EMP_EFFECT", LUA_NATIVE_VEHICLE_APPLY_EMP_EFFECT);
		VEHICLE.set_function("GET_IS_VEHICLE_DISABLED_BY_EMP", LUA_NATIVE_VEHICLE_GET_IS_VEHICLE_DISABLED_BY_EMP);
		VEHICLE.set_function("SET_DISABLE_RETRACTING_WEAPON_BLADES", LUA_NATIVE_VEHICLE_SET_DISABLE_RETRACTING_WEAPON_BLADES);
		VEHICLE.set_function("GET_TYRE_HEALTH", LUA_NATIVE_VEHICLE_GET_TYRE_HEALTH);
		VEHICLE.set_function("SET_TYRE_HEALTH", LUA_NATIVE_VEHICLE_SET_TYRE_HEALTH);
		VEHICLE.set_function("GET_TYRE_WEAR_RATE", LUA_NATIVE_VEHICLE_GET_TYRE_WEAR_RATE);
		VEHICLE.set_function("SET_TYRE_WEAR_RATE", LUA_NATIVE_VEHICLE_SET_TYRE_WEAR_RATE);
		VEHICLE.set_function("SET_TYRE_WEAR_RATE_SCALE", LUA_NATIVE_VEHICLE_SET_TYRE_WEAR_RATE_SCALE);
		VEHICLE.set_function("SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE", LUA_NATIVE_VEHICLE_SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE);
		VEHICLE.set_function("SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION", LUA_NATIVE_VEHICLE_SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION);
		VEHICLE.set_function("SET_REDUCED_SUSPENSION_FORCE", LUA_NATIVE_VEHICLE_SET_REDUCED_SUSPENSION_FORCE);
		VEHICLE.set_function("SET_DRIFT_TYRES", LUA_NATIVE_VEHICLE_SET_DRIFT_TYRES);
		VEHICLE.set_function("GET_DRIFT_TYRES_SET", LUA_NATIVE_VEHICLE_GET_DRIFT_TYRES_SET);
		VEHICLE.set_function("NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING", LUA_NATIVE_VEHICLE_NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING);
		VEHICLE.set_function("SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED", LUA_NATIVE_VEHICLE_SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED);
		VEHICLE.set_function("SET_ALLOW_COLLISION_WHEN_IN_VEHICLE_", LUA_NATIVE_VEHICLE_SET_ALLOW_COLLISION_WHEN_IN_VEHICLE_);
		VEHICLE.set_function("IS_VEHICLE_GEN9_EXCLUSIVE_MODEL_", LUA_NATIVE_VEHICLE_IS_VEHICLE_GEN9_EXCLUSIVE_MODEL_);
		VEHICLE.set_function("GET_VEHICLE_MAX_EXHAUST_BONE_COUNT_", LUA_NATIVE_VEHICLE_GET_VEHICLE_MAX_EXHAUST_BONE_COUNT_);
		VEHICLE.set_function("GET_VEHICLE_EXHAUST_BONE_", LUA_NATIVE_VEHICLE_GET_VEHICLE_EXHAUST_BONE_);
	}
}
