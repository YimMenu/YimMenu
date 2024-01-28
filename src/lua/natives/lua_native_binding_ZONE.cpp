#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static int LUA_NATIVE_ZONE_GET_ZONE_AT_COORDS(float x, float y, float z)
	{
		auto retval = ZONE::GET_ZONE_AT_COORDS(x, y, z);
		return retval;
	}

	static int LUA_NATIVE_ZONE_GET_ZONE_FROM_NAME_ID(sol::stack_object zoneName)
	{
		auto retval = ZONE::GET_ZONE_FROM_NAME_ID(zoneName.is<const char*>() ? zoneName.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_ZONE_GET_ZONE_POPSCHEDULE(int zoneId)
	{
		auto retval = ZONE::GET_ZONE_POPSCHEDULE(zoneId);
		return retval;
	}

	static const char* LUA_NATIVE_ZONE_GET_NAME_OF_ZONE(float x, float y, float z)
	{
		auto retval = ZONE::GET_NAME_OF_ZONE(x, y, z);
		return retval;
	}

	static void LUA_NATIVE_ZONE_SET_ZONE_ENABLED(int zoneId, bool toggle)
	{
		ZONE::SET_ZONE_ENABLED(zoneId, toggle);
	}

	static int LUA_NATIVE_ZONE_GET_ZONE_SCUMMINESS(int zoneId)
	{
		auto retval = ZONE::GET_ZONE_SCUMMINESS(zoneId);
		return retval;
	}

	static void LUA_NATIVE_ZONE_OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(int scheduleId, Hash vehicleHash)
	{
		ZONE::OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(scheduleId, vehicleHash);
	}

	static void LUA_NATIVE_ZONE_CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(int scheduleId)
	{
		ZONE::CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(scheduleId);
	}

	static Hash LUA_NATIVE_ZONE_GET_HASH_OF_MAP_AREA_AT_COORDS(float x, float y, float z)
	{
		auto retval = ZONE::GET_HASH_OF_MAP_AREA_AT_COORDS(x, y, z);
		return retval;
	}

	void init_native_binding_ZONE(sol::state& L)
	{
		auto ZONE = L["ZONE"].get_or_create<sol::table>();
		ZONE.set_function("GET_ZONE_AT_COORDS", LUA_NATIVE_ZONE_GET_ZONE_AT_COORDS);
		ZONE.set_function("GET_ZONE_FROM_NAME_ID", LUA_NATIVE_ZONE_GET_ZONE_FROM_NAME_ID);
		ZONE.set_function("GET_ZONE_POPSCHEDULE", LUA_NATIVE_ZONE_GET_ZONE_POPSCHEDULE);
		ZONE.set_function("GET_NAME_OF_ZONE", LUA_NATIVE_ZONE_GET_NAME_OF_ZONE);
		ZONE.set_function("SET_ZONE_ENABLED", LUA_NATIVE_ZONE_SET_ZONE_ENABLED);
		ZONE.set_function("GET_ZONE_SCUMMINESS", LUA_NATIVE_ZONE_GET_ZONE_SCUMMINESS);
		ZONE.set_function("OVERRIDE_POPSCHEDULE_VEHICLE_MODEL", LUA_NATIVE_ZONE_OVERRIDE_POPSCHEDULE_VEHICLE_MODEL);
		ZONE.set_function("CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL", LUA_NATIVE_ZONE_CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL);
		ZONE.set_function("GET_HASH_OF_MAP_AREA_AT_COORDS", LUA_NATIVE_ZONE_GET_HASH_OF_MAP_AREA_AT_COORDS);
	}
}
