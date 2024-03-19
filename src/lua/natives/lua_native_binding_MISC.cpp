#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static int LUA_NATIVE_MISC_GET_ALLOCATED_STACK_SIZE()
	{
		auto retval = MISC::GET_ALLOCATED_STACK_SIZE();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(int stackSize)
	{
		auto retval = MISC::GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(stackSize);
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_RANDOM_SEED(int seed)
	{
		MISC::SET_RANDOM_SEED(seed);
	}

	static void LUA_NATIVE_MISC_SET_TIME_SCALE(float timeScale)
	{
		MISC::SET_TIME_SCALE(timeScale);
	}

	static void LUA_NATIVE_MISC_SET_MISSION_FLAG(bool toggle)
	{
		MISC::SET_MISSION_FLAG(toggle);
	}

	static bool LUA_NATIVE_MISC_GET_MISSION_FLAG()
	{
		auto retval = (bool)MISC::GET_MISSION_FLAG();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_RANDOM_EVENT_FLAG(bool toggle)
	{
		MISC::SET_RANDOM_EVENT_FLAG(toggle);
	}

	static bool LUA_NATIVE_MISC_GET_RANDOM_EVENT_FLAG()
	{
		auto retval = (bool)MISC::GET_RANDOM_EVENT_FLAG();
		return retval;
	}

	static const char* LUA_NATIVE_MISC_GET_CONTENT_TO_LOAD()
	{
		auto retval = MISC::GET_CONTENT_TO_LOAD();
		return retval;
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_CREATE(sol::stack_object p0, sol::stack_object p1)
	{
		MISC::ACTIVITY_FEED_CREATE(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION(sol::stack_object p0)
	{
		MISC::ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION(sol::stack_object p0)
	{
		MISC::ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_ADD_INT_TO_CAPTION(Any p0)
	{
		MISC::ACTIVITY_FEED_ADD_INT_TO_CAPTION(p0);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_LARGE_IMAGE_URL(sol::stack_object p0)
	{
		MISC::ACTIVITY_FEED_LARGE_IMAGE_URL(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE(sol::stack_object p0, sol::stack_object p1)
	{
		MISC::ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD(sol::stack_object p0)
	{
		MISC::ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_POST()
	{
		MISC::ACTIVITY_FEED_POST();
	}

	static void LUA_NATIVE_MISC_ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST(sol::stack_object p0)
	{
		MISC::ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_MISC_HAS_RESUMED_FROM_SUSPEND()
	{
		auto retval = (bool)MISC::HAS_RESUMED_FROM_SUSPEND();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_SCRIPT_HIGH_PRIO(bool toggle)
	{
		MISC::SET_SCRIPT_HIGH_PRIO(toggle);
	}

	static void LUA_NATIVE_MISC_SET_THIS_IS_A_TRIGGER_SCRIPT(bool toggle)
	{
		MISC::SET_THIS_IS_A_TRIGGER_SCRIPT(toggle);
	}

	static void LUA_NATIVE_MISC_INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION(sol::stack_object p0)
	{
		MISC::INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_MISC_GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK(uintptr_t p0, uintptr_t p1, Any p2, bool p3)
	{
		auto retval = (bool)MISC::GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK((Any*)p0, (Any*)p1, p2, p3);
		return retval;
	}

	static Hash LUA_NATIVE_MISC_GET_PREV_WEATHER_TYPE_HASH_NAME()
	{
		auto retval = MISC::GET_PREV_WEATHER_TYPE_HASH_NAME();
		return retval;
	}

	static Hash LUA_NATIVE_MISC_GET_NEXT_WEATHER_TYPE_HASH_NAME()
	{
		auto retval = MISC::GET_NEXT_WEATHER_TYPE_HASH_NAME();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PREV_WEATHER_TYPE(sol::stack_object weatherType)
	{
		auto retval = (bool)MISC::IS_PREV_WEATHER_TYPE(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_NEXT_WEATHER_TYPE(sol::stack_object weatherType)
	{
		auto retval = (bool)MISC::IS_NEXT_WEATHER_TYPE(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_WEATHER_TYPE_PERSIST(sol::stack_object weatherType)
	{
		MISC::SET_WEATHER_TYPE_PERSIST(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_SET_WEATHER_TYPE_NOW_PERSIST(sol::stack_object weatherType)
	{
		MISC::SET_WEATHER_TYPE_NOW_PERSIST(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_SET_WEATHER_TYPE_NOW(sol::stack_object weatherType)
	{
		MISC::SET_WEATHER_TYPE_NOW(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_SET_WEATHER_TYPE_OVERTIME_PERSIST(sol::stack_object weatherType, float time)
	{
		MISC::SET_WEATHER_TYPE_OVERTIME_PERSIST(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr, time);
	}

	static void LUA_NATIVE_MISC_SET_RANDOM_WEATHER_TYPE()
	{
		MISC::SET_RANDOM_WEATHER_TYPE();
	}

	static void LUA_NATIVE_MISC_CLEAR_WEATHER_TYPE_PERSIST()
	{
		MISC::CLEAR_WEATHER_TYPE_PERSIST();
	}

	static void LUA_NATIVE_MISC_CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK(int milliseconds)
	{
		MISC::CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK(milliseconds);
	}

	static std::tuple<Hash, Hash, float> LUA_NATIVE_MISC_GET_CURR_WEATHER_STATE(Hash weatherType1, Hash weatherType2, float percentWeather2)
	{
		std::tuple<Hash, Hash, float> return_values;
		MISC::GET_CURR_WEATHER_STATE(&weatherType1, &weatherType2, &percentWeather2);
		std::get<0>(return_values) = weatherType1;
		std::get<1>(return_values) = weatherType2;
		std::get<2>(return_values) = percentWeather2;

		return return_values;
	}

	static void LUA_NATIVE_MISC_SET_CURR_WEATHER_STATE(Hash weatherType1, Hash weatherType2, float percentWeather2)
	{
		MISC::SET_CURR_WEATHER_STATE(weatherType1, weatherType2, percentWeather2);
	}

	static void LUA_NATIVE_MISC_SET_OVERRIDE_WEATHER(sol::stack_object weatherType)
	{
		MISC::SET_OVERRIDE_WEATHER(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_SET_OVERRIDE_WEATHEREX(sol::stack_object weatherType, bool p1)
	{
		MISC::SET_OVERRIDE_WEATHEREX(weatherType.is<const char*>() ? weatherType.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_MISC_CLEAR_OVERRIDE_WEATHER()
	{
		MISC::CLEAR_OVERRIDE_WEATHER();
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE(float amplitude)
	{
		MISC::WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE(amplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE(float minAmplitude)
	{
		MISC::WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE(minAmplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE(float maxAmplitude)
	{
		MISC::WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE(maxAmplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE(float minAmplitude)
	{
		MISC::WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE(minAmplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE(float amplitude)
	{
		MISC::WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE(amplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE(float minAmplitude)
	{
		MISC::WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE(minAmplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE(float maxAmplitude)
	{
		MISC::WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE(maxAmplitude);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEBUMPINESS(float bumpiness)
	{
		MISC::WATER_OVERRIDE_SET_RIPPLEBUMPINESS(bumpiness);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS(float minBumpiness)
	{
		MISC::WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS(minBumpiness);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS(float maxBumpiness)
	{
		MISC::WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS(maxBumpiness);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEDISTURB(float disturb)
	{
		MISC::WATER_OVERRIDE_SET_RIPPLEDISTURB(disturb);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_SET_STRENGTH(float strength)
	{
		MISC::WATER_OVERRIDE_SET_STRENGTH(strength);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_FADE_IN(float p0)
	{
		MISC::WATER_OVERRIDE_FADE_IN(p0);
	}

	static void LUA_NATIVE_MISC_WATER_OVERRIDE_FADE_OUT(float p0)
	{
		MISC::WATER_OVERRIDE_FADE_OUT(p0);
	}

	static void LUA_NATIVE_MISC_SET_WIND(float speed)
	{
		MISC::SET_WIND(speed);
	}

	static void LUA_NATIVE_MISC_SET_WIND_SPEED(float speed)
	{
		MISC::SET_WIND_SPEED(speed);
	}

	static float LUA_NATIVE_MISC_GET_WIND_SPEED()
	{
		auto retval = MISC::GET_WIND_SPEED();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_WIND_DIRECTION(float direction)
	{
		MISC::SET_WIND_DIRECTION(direction);
	}

	static Vector3 LUA_NATIVE_MISC_GET_WIND_DIRECTION()
	{
		auto retval = MISC::GET_WIND_DIRECTION();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_RAIN(float intensity)
	{
		MISC::SET_RAIN(intensity);
	}

	static float LUA_NATIVE_MISC_GET_RAIN_LEVEL()
	{
		auto retval = MISC::GET_RAIN_LEVEL();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_SNOW(float level)
	{
		MISC::SET_SNOW(level);
	}

	static float LUA_NATIVE_MISC_GET_SNOW_LEVEL()
	{
		auto retval = MISC::GET_SNOW_LEVEL();
		return retval;
	}

	static void LUA_NATIVE_MISC_FORCE_LIGHTNING_FLASH()
	{
		MISC::FORCE_LIGHTNING_FLASH();
	}

	static void LUA_NATIVE_MISC_SET_CLOUD_SETTINGS_OVERRIDE(sol::stack_object p0)
	{
		MISC::SET_CLOUD_SETTINGS_OVERRIDE(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_PRELOAD_CLOUD_HAT(sol::stack_object name)
	{
		MISC::PRELOAD_CLOUD_HAT(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_LOAD_CLOUD_HAT(sol::stack_object name, float transitionTime)
	{
		MISC::LOAD_CLOUD_HAT(name.is<const char*>() ? name.as<const char*>() : nullptr, transitionTime);
	}

	static void LUA_NATIVE_MISC_UNLOAD_CLOUD_HAT(sol::stack_object name, float p1)
	{
		MISC::UNLOAD_CLOUD_HAT(name.is<const char*>() ? name.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_MISC_UNLOAD_ALL_CLOUD_HATS()
	{
		MISC::UNLOAD_ALL_CLOUD_HATS();
	}

	static void LUA_NATIVE_MISC_SET_CLOUDS_ALPHA(float opacity)
	{
		MISC::SET_CLOUDS_ALPHA(opacity);
	}

	static float LUA_NATIVE_MISC_GET_CLOUDS_ALPHA()
	{
		auto retval = MISC::GET_CLOUDS_ALPHA();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_GAME_TIMER()
	{
		auto retval = MISC::GET_GAME_TIMER();
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_FRAME_TIME()
	{
		auto retval = MISC::GET_FRAME_TIME();
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_SYSTEM_TIME_STEP()
	{
		auto retval = MISC::GET_SYSTEM_TIME_STEP();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_FRAME_COUNT()
	{
		auto retval = MISC::GET_FRAME_COUNT();
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_RANDOM_FLOAT_IN_RANGE(float startRange, float endRange)
	{
		auto retval = MISC::GET_RANDOM_FLOAT_IN_RANGE(startRange, endRange);
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_RANDOM_INT_IN_RANGE(int startRange, int endRange)
	{
		auto retval = MISC::GET_RANDOM_INT_IN_RANGE(startRange, endRange);
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_RANDOM_MWC_INT_IN_RANGE(int startRange, int endRange)
	{
		auto retval = MISC::GET_RANDOM_MWC_INT_IN_RANGE(startRange, endRange);
		return retval;
	}

	static std::tuple<bool, float> LUA_NATIVE_MISC_GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float groundZ, bool ignoreWater, bool p5)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_GROUND_Z_FOR_3D_COORD(x, y, z, &groundZ, ignoreWater, p5);
		std::get<1>(return_values) = groundZ;

		return return_values;
	}

	static std::tuple<bool, float, Vector3> LUA_NATIVE_MISC_GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD(float x, float y, float z, float groundZ, Vector3 normal)
	{
		std::tuple<bool, float, Vector3> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD(x, y, z, &groundZ, &normal);
		std::get<1>(return_values) = groundZ;
		std::get<2>(return_values) = normal;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_MISC_GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD(float x, float y, float z, float groundZ, bool p4, bool p5)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD(x, y, z, &groundZ, p4, p5);
		std::get<1>(return_values) = groundZ;

		return return_values;
	}

	static float LUA_NATIVE_MISC_ASIN(float p0)
	{
		auto retval = MISC::ASIN(p0);
		return retval;
	}

	static float LUA_NATIVE_MISC_ACOS(float p0)
	{
		auto retval = MISC::ACOS(p0);
		return retval;
	}

	static float LUA_NATIVE_MISC_TAN(float p0)
	{
		auto retval = MISC::TAN(p0);
		return retval;
	}

	static float LUA_NATIVE_MISC_ATAN(float p0)
	{
		auto retval = MISC::ATAN(p0);
		return retval;
	}

	static float LUA_NATIVE_MISC_ATAN2(float p0, float p1)
	{
		auto retval = MISC::ATAN2(p0, p1);
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_DISTANCE_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, bool useZ)
	{
		auto retval = MISC::GET_DISTANCE_BETWEEN_COORDS(x1, y1, z1, x2, y2, z2, useZ);
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_ANGLE_BETWEEN_2D_VECTORS(float x1, float y1, float x2, float y2)
	{
		auto retval = MISC::GET_ANGLE_BETWEEN_2D_VECTORS(x1, y1, x2, y2);
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_HEADING_FROM_VECTOR_2D(float dx, float dy)
	{
		auto retval = MISC::GET_HEADING_FROM_VECTOR_2D(dx, dy);
		return retval;
	}

	static float LUA_NATIVE_MISC_GET_RATIO_OF_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, bool clamp)
	{
		auto retval = MISC::GET_RATIO_OF_CLOSEST_POINT_ON_LINE(x1, y1, z1, x2, y2, z2, x3, y3, z3, clamp);
		return retval;
	}

	static Vector3 LUA_NATIVE_MISC_GET_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, bool clamp)
	{
		auto retval = MISC::GET_CLOSEST_POINT_ON_LINE(x1, y1, z1, x2, y2, z2, x3, y3, z3, clamp);
		return retval;
	}

	static std::tuple<bool, float> LUA_NATIVE_MISC_GET_LINE_PLANE_INTERSECTION(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_LINE_PLANE_INTERSECTION(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, &p12);
		std::get<1>(return_values) = p12;

		return return_values;
	}

	static bool LUA_NATIVE_MISC_GET_POINT_AREA_OVERLAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13)
	{
		auto retval = (bool)MISC::GET_POINT_AREA_OVERLAP(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
		return retval;
	}

	static int LUA_NATIVE_MISC_SET_BIT(int address, int offset)
	{
		MISC::SET_BIT(&address, offset);
		return address;
	}

	static int LUA_NATIVE_MISC_CLEAR_BIT(int address, int offset)
	{
		MISC::CLEAR_BIT(&address, offset);
		return address;
	}

	static Hash LUA_NATIVE_MISC_GET_HASH_KEY(sol::stack_object string)
	{
		auto retval = MISC::GET_HASH_KEY(string.is<const char*>() ? string.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<float, float, float, float> LUA_NATIVE_MISC_SLERP_NEAR_QUATERNION(float t, float x, float y, float z, float w, float x1, float y1, float z1, float w1, float outX, float outY, float outZ, float outW)
	{
		std::tuple<float, float, float, float> return_values;
		MISC::SLERP_NEAR_QUATERNION(t, x, y, z, w, x1, y1, z1, w1, &outX, &outY, &outZ, &outW);
		std::get<0>(return_values) = outX;
		std::get<1>(return_values) = outY;
		std::get<2>(return_values) = outZ;
		std::get<3>(return_values) = outW;

		return return_values;
	}

	static bool LUA_NATIVE_MISC_IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, Any p11, bool p12)
	{
		auto retval = (bool)MISC::IS_AREA_OCCUPIED(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_AREA_OCCUPIED_SLOW(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12)
	{
		auto retval = (bool)MISC::IS_AREA_OCCUPIED_SLOW(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_POSITION_OCCUPIED(float x, float y, float z, float range, bool p4, bool checkVehicles, bool checkPeds, bool p7, bool p8, Entity ignoreEntity, bool p10)
	{
		auto retval = (bool)MISC::IS_POSITION_OCCUPIED(x, y, z, range, p4, checkVehicles, checkPeds, p7, p8, ignoreEntity, p10);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, Any p6)
	{
		auto retval = (bool)MISC::IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(p0, p1, p2, p3, p4, p5, p6);
		return retval;
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA(float X, float Y, float Z, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7)
	{
		MISC::CLEAR_AREA(X, Y, Z, radius, p4, ignoreCopCars, ignoreObjects, p7);
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA_LEAVE_VEHICLE_HEALTH(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7)
	{
		MISC::CLEAR_AREA_LEAVE_VEHICLE_HEALTH(x, y, z, radius, p4, p5, p6, p7);
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA_OF_VEHICLES(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7, bool p8, bool p9, Any p10)
	{
		MISC::CLEAR_AREA_OF_VEHICLES(x, y, z, radius, p4, p5, p6, p7, p8, p9, p10);
	}

	static void LUA_NATIVE_MISC_CLEAR_ANGLED_AREA_OF_VEHICLES(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool p7, bool p8, bool p9, bool p10, bool p11, Any p12, Any p13)
	{
		MISC::CLEAR_ANGLED_AREA_OF_VEHICLES(x1, y1, z1, x2, y2, z2, width, p7, p8, p9, p10, p11, p12, p13);
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius, int flags)
	{
		MISC::CLEAR_AREA_OF_OBJECTS(x, y, z, radius, flags);
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA_OF_PEDS(float x, float y, float z, float radius, int flags)
	{
		MISC::CLEAR_AREA_OF_PEDS(x, y, z, radius, flags);
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA_OF_COPS(float x, float y, float z, float radius, int flags)
	{
		MISC::CLEAR_AREA_OF_COPS(x, y, z, radius, flags);
	}

	static void LUA_NATIVE_MISC_CLEAR_AREA_OF_PROJECTILES(float x, float y, float z, float radius, int flags)
	{
		MISC::CLEAR_AREA_OF_PROJECTILES(x, y, z, radius, flags);
	}

	static void LUA_NATIVE_MISC_CLEAR_SCENARIO_SPAWN_HISTORY()
	{
		MISC::CLEAR_SCENARIO_SPAWN_HISTORY();
	}

	static void LUA_NATIVE_MISC_SET_SAVE_MENU_ACTIVE(bool ignoreVehicle)
	{
		MISC::SET_SAVE_MENU_ACTIVE(ignoreVehicle);
	}

	static int LUA_NATIVE_MISC_GET_STATUS_OF_MANUAL_SAVE()
	{
		auto retval = MISC::GET_STATUS_OF_MANUAL_SAVE();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_CREDITS_ACTIVE(bool toggle)
	{
		MISC::SET_CREDITS_ACTIVE(toggle);
	}

	static void LUA_NATIVE_MISC_SET_CREDITS_FADE_OUT_WITH_SCREEN(bool toggle)
	{
		MISC::SET_CREDITS_FADE_OUT_WITH_SCREEN(toggle);
	}

	static bool LUA_NATIVE_MISC_HAVE_CREDITS_REACHED_END()
	{
		auto retval = (bool)MISC::HAVE_CREDITS_REACHED_END();
		return retval;
	}

	static bool LUA_NATIVE_MISC_ARE_CREDITS_RUNNING()
	{
		auto retval = (bool)MISC::ARE_CREDITS_RUNNING();
		return retval;
	}

	static void LUA_NATIVE_MISC_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(sol::stack_object scriptName)
	{
		MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME()
	{
		MISC::NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	}

	static int LUA_NATIVE_MISC_ADD_HOSPITAL_RESTART(float x, float y, float z, float p3, Any p4)
	{
		auto retval = MISC::ADD_HOSPITAL_RESTART(x, y, z, p3, p4);
		return retval;
	}

	static void LUA_NATIVE_MISC_DISABLE_HOSPITAL_RESTART(int hospitalIndex, bool toggle)
	{
		MISC::DISABLE_HOSPITAL_RESTART(hospitalIndex, toggle);
	}

	static int LUA_NATIVE_MISC_ADD_POLICE_RESTART(float p0, float p1, float p2, float p3, Any p4)
	{
		auto retval = MISC::ADD_POLICE_RESTART(p0, p1, p2, p3, p4);
		return retval;
	}

	static void LUA_NATIVE_MISC_DISABLE_POLICE_RESTART(int policeIndex, bool toggle)
	{
		MISC::DISABLE_POLICE_RESTART(policeIndex, toggle);
	}

	static void LUA_NATIVE_MISC_SET_RESTART_COORD_OVERRIDE(float x, float y, float z, float heading)
	{
		MISC::SET_RESTART_COORD_OVERRIDE(x, y, z, heading);
	}

	static void LUA_NATIVE_MISC_CLEAR_RESTART_COORD_OVERRIDE()
	{
		MISC::CLEAR_RESTART_COORD_OVERRIDE();
	}

	static void LUA_NATIVE_MISC_PAUSE_DEATH_ARREST_RESTART(bool toggle)
	{
		MISC::PAUSE_DEATH_ARREST_RESTART(toggle);
	}

	static void LUA_NATIVE_MISC_IGNORE_NEXT_RESTART(bool toggle)
	{
		MISC::IGNORE_NEXT_RESTART(toggle);
	}

	static void LUA_NATIVE_MISC_SET_FADE_OUT_AFTER_DEATH(bool toggle)
	{
		MISC::SET_FADE_OUT_AFTER_DEATH(toggle);
	}

	static void LUA_NATIVE_MISC_SET_FADE_OUT_AFTER_ARREST(bool toggle)
	{
		MISC::SET_FADE_OUT_AFTER_ARREST(toggle);
	}

	static void LUA_NATIVE_MISC_SET_FADE_IN_AFTER_DEATH_ARREST(bool toggle)
	{
		MISC::SET_FADE_IN_AFTER_DEATH_ARREST(toggle);
	}

	static void LUA_NATIVE_MISC_SET_FADE_IN_AFTER_LOAD(bool toggle)
	{
		MISC::SET_FADE_IN_AFTER_LOAD(toggle);
	}

	static int LUA_NATIVE_MISC_REGISTER_SAVE_HOUSE(float x, float y, float z, float p3, sol::stack_object p4, Any p5, Any p6)
	{
		auto retval = MISC::REGISTER_SAVE_HOUSE(x, y, z, p3, p4.is<const char*>() ? p4.as<const char*>() : nullptr, p5, p6);
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_SAVE_HOUSE(int savehouseHandle, bool p1, bool p2)
	{
		MISC::SET_SAVE_HOUSE(savehouseHandle, p1, p2);
	}

	static bool LUA_NATIVE_MISC_OVERRIDE_SAVE_HOUSE(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7)
	{
		auto retval = (bool)MISC::OVERRIDE_SAVE_HOUSE(p0, p1, p2, p3, p4, p5, p6, p7);
		return retval;
	}

	static std::tuple<bool, Vector3, float, bool, bool> LUA_NATIVE_MISC_GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD(Vector3 p0, float p1, bool fadeInAfterLoad, bool p3)
	{
		std::tuple<bool, Vector3, float, bool, bool> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD(&p0, &p1, (BOOL*)&fadeInAfterLoad, (BOOL*)&p3);
		std::get<1>(return_values) = p0;
		std::get<2>(return_values) = p1;
		std::get<3>(return_values) = fadeInAfterLoad;
		std::get<4>(return_values) = p3;

		return return_values;
	}

	static void LUA_NATIVE_MISC_DO_AUTO_SAVE()
	{
		MISC::DO_AUTO_SAVE();
	}

	static bool LUA_NATIVE_MISC_GET_IS_AUTO_SAVE_OFF()
	{
		auto retval = (bool)MISC::GET_IS_AUTO_SAVE_OFF();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_AUTO_SAVE_IN_PROGRESS()
	{
		auto retval = (bool)MISC::IS_AUTO_SAVE_IN_PROGRESS();
		return retval;
	}

	static bool LUA_NATIVE_MISC_HAS_CODE_REQUESTED_AUTOSAVE()
	{
		auto retval = (bool)MISC::HAS_CODE_REQUESTED_AUTOSAVE();
		return retval;
	}

	static void LUA_NATIVE_MISC_CLEAR_CODE_REQUESTED_AUTOSAVE()
	{
		MISC::CLEAR_CODE_REQUESTED_AUTOSAVE();
	}

	static void LUA_NATIVE_MISC_BEGIN_REPLAY_STATS(Any p0, Any p1)
	{
		MISC::BEGIN_REPLAY_STATS(p0, p1);
	}

	static void LUA_NATIVE_MISC_ADD_REPLAY_STAT_VALUE(Any value)
	{
		MISC::ADD_REPLAY_STAT_VALUE(value);
	}

	static void LUA_NATIVE_MISC_END_REPLAY_STATS()
	{
		MISC::END_REPLAY_STATS();
	}

	static bool LUA_NATIVE_MISC_HAVE_REPLAY_STATS_BEEN_STORED()
	{
		auto retval = (bool)MISC::HAVE_REPLAY_STATS_BEEN_STORED();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_REPLAY_STAT_MISSION_ID()
	{
		auto retval = MISC::GET_REPLAY_STAT_MISSION_ID();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_REPLAY_STAT_MISSION_TYPE()
	{
		auto retval = MISC::GET_REPLAY_STAT_MISSION_TYPE();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_REPLAY_STAT_COUNT()
	{
		auto retval = MISC::GET_REPLAY_STAT_COUNT();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_REPLAY_STAT_AT_INDEX(int index)
	{
		auto retval = MISC::GET_REPLAY_STAT_AT_INDEX(index);
		return retval;
	}

	static void LUA_NATIVE_MISC_CLEAR_REPLAY_STATS()
	{
		MISC::CLEAR_REPLAY_STATS();
	}

	static bool LUA_NATIVE_MISC_QUEUE_MISSION_REPEAT_LOAD()
	{
		auto retval = (bool)MISC::QUEUE_MISSION_REPEAT_LOAD();
		return retval;
	}

	static bool LUA_NATIVE_MISC_QUEUE_MISSION_REPEAT_SAVE()
	{
		auto retval = (bool)MISC::QUEUE_MISSION_REPEAT_SAVE();
		return retval;
	}

	static bool LUA_NATIVE_MISC_QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST()
	{
		auto retval = (bool)MISC::QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_STATUS_OF_MISSION_REPEAT_SAVE()
	{
		auto retval = MISC::GET_STATUS_OF_MISSION_REPEAT_SAVE();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_MEMORY_CARD_IN_USE()
	{
		auto retval = (bool)MISC::IS_MEMORY_CARD_IN_USE();
		return retval;
	}

	static void LUA_NATIVE_MISC_SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed)
	{
		MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed);
	}

	static void LUA_NATIVE_MISC_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, Any p14)
	{
		MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14);
	}

	static void LUA_NATIVE_MISC_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, bool p14, bool p15, Entity targetEntity, bool p17, Any p18, Any p19, Any p20)
	{
		MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW(x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14, p15, targetEntity, p17, p18, p19, p20);
	}

	static std::tuple<Vector3, Vector3> LUA_NATIVE_MISC_GET_MODEL_DIMENSIONS(Hash modelHash, Vector3 minimum, Vector3 maximum)
	{
		std::tuple<Vector3, Vector3> return_values;
		MISC::GET_MODEL_DIMENSIONS(modelHash, &minimum, &maximum);
		std::get<0>(return_values) = minimum;
		std::get<1>(return_values) = maximum;

		return return_values;
	}

	static void LUA_NATIVE_MISC_SET_FAKE_WANTED_LEVEL(int fakeWantedLevel)
	{
		MISC::SET_FAKE_WANTED_LEVEL(fakeWantedLevel);
	}

	static int LUA_NATIVE_MISC_GET_FAKE_WANTED_LEVEL()
	{
		auto retval = MISC::GET_FAKE_WANTED_LEVEL();
		return retval;
	}

	static void LUA_NATIVE_MISC_USING_MISSION_CREATOR(bool toggle)
	{
		MISC::USING_MISSION_CREATOR(toggle);
	}

	static void LUA_NATIVE_MISC_ALLOW_MISSION_CREATOR_WARP(bool toggle)
	{
		MISC::ALLOW_MISSION_CREATOR_WARP(toggle);
	}

	static void LUA_NATIVE_MISC_SET_MINIGAME_IN_PROGRESS(bool toggle)
	{
		MISC::SET_MINIGAME_IN_PROGRESS(toggle);
	}

	static bool LUA_NATIVE_MISC_IS_MINIGAME_IN_PROGRESS()
	{
		auto retval = (bool)MISC::IS_MINIGAME_IN_PROGRESS();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_THIS_A_MINIGAME_SCRIPT()
	{
		auto retval = (bool)MISC::IS_THIS_A_MINIGAME_SCRIPT();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_SNIPER_INVERTED()
	{
		auto retval = (bool)MISC::IS_SNIPER_INVERTED();
		return retval;
	}

	static bool LUA_NATIVE_MISC_SHOULD_USE_METRIC_MEASUREMENTS()
	{
		auto retval = (bool)MISC::SHOULD_USE_METRIC_MEASUREMENTS();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_PROFILE_SETTING(int profileSetting)
	{
		auto retval = MISC::GET_PROFILE_SETTING(profileSetting);
		return retval;
	}

	static bool LUA_NATIVE_MISC_ARE_STRINGS_EQUAL(sol::stack_object string1, sol::stack_object string2)
	{
		auto retval = (bool)MISC::ARE_STRINGS_EQUAL(string1.is<const char*>() ? string1.as<const char*>() : nullptr, string2.is<const char*>() ? string2.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_MISC_COMPARE_STRINGS(sol::stack_object str1, sol::stack_object str2, bool matchCase, int maxLength)
	{
		auto retval = MISC::COMPARE_STRINGS(str1.is<const char*>() ? str1.as<const char*>() : nullptr, str2.is<const char*>() ? str2.as<const char*>() : nullptr, matchCase, maxLength);
		return retval;
	}

	static int LUA_NATIVE_MISC_ABSI(int value)
	{
		auto retval = MISC::ABSI(value);
		return retval;
	}

	static float LUA_NATIVE_MISC_ABSF(float value)
	{
		auto retval = MISC::ABSF(value);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_SNIPER_BULLET_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = (bool)MISC::IS_SNIPER_BULLET_IN_AREA(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PROJECTILE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_PROJECTILE_IN_AREA(x1, y1, z1, x2, y2, z2, ownedByPlayer);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, int type, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_PROJECTILE_TYPE_IN_AREA(x1, y1, z1, x2, y2, z2, type, ownedByPlayer);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, Any p7, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_PROJECTILE_TYPE_IN_ANGLED_AREA(x1, y1, z1, x2, y2, z2, width, p7, ownedByPlayer);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PROJECTILE_TYPE_WITHIN_DISTANCE(float x, float y, float z, Hash projectileHash, float radius, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_PROJECTILE_TYPE_WITHIN_DISTANCE(x, y, z, projectileHash, radius, ownedByPlayer);
		return retval;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_MISC_GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Hash projectileHash, Vector3 projectilePos, bool ownedByPlayer)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA(x1, y1, z1, x2, y2, z2, projectileHash, &projectilePos, ownedByPlayer);
		std::get<1>(return_values) = projectilePos;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_MISC_GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA(float vecAngledAreaPoint1X, float vecAngledAreaPoint1Y, float vecAngledAreaPoint1Z, float vecAngledAreaPoint2X, float vecAngledAreaPoint2Y, float vecAngledAreaPoint2Z, float distanceOfOppositeFace, Hash weaponType, Vector3 positionOut, bool bIsPlayer)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA(vecAngledAreaPoint1X, vecAngledAreaPoint1Y, vecAngledAreaPoint1Z, vecAngledAreaPoint2X, vecAngledAreaPoint2Y, vecAngledAreaPoint2Z, distanceOfOppositeFace, weaponType, &positionOut, bIsPlayer);
		std::get<1>(return_values) = positionOut;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_MISC_GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, Vector3 outCoords, bool p4)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(ped, weaponHash, distance, &outCoords, p4);
		std::get<1>(return_values) = outCoords;

		return return_values;
	}

	static std::tuple<bool, Vector3, Object> LUA_NATIVE_MISC_GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, Vector3 outCoords, Object outProjectile, bool p5)
	{
		std::tuple<bool, Vector3, Object> return_values;
		std::get<0>(return_values) = (bool)MISC::GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(ped, weaponHash, distance, &outCoords, &outProjectile, p5);
		std::get<1>(return_values) = outCoords;
		std::get<2>(return_values) = outProjectile;

		return return_values;
	}

	static bool LUA_NATIVE_MISC_IS_BULLET_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_BULLET_IN_ANGLED_AREA(x1, y1, z1, x2, y2, z2, width, ownedByPlayer);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_BULLET_IN_AREA(float x, float y, float z, float radius, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_BULLET_IN_AREA(x, y, z, radius, ownedByPlayer);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_BULLET_IN_BOX(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer)
	{
		auto retval = (bool)MISC::IS_BULLET_IN_BOX(x1, y1, z1, x2, y2, z2, ownedByPlayer);
		return retval;
	}

	static bool LUA_NATIVE_MISC_HAS_BULLET_IMPACTED_IN_AREA(float x, float y, float z, float p3, bool p4, bool p5)
	{
		auto retval = (bool)MISC::HAS_BULLET_IMPACTED_IN_AREA(x, y, z, p3, p4, p5);
		return retval;
	}

	static bool LUA_NATIVE_MISC_HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7)
	{
		auto retval = (bool)MISC::HAS_BULLET_IMPACTED_IN_BOX(p0, p1, p2, p3, p4, p5, p6, p7);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_ORBIS_VERSION()
	{
		auto retval = (bool)MISC::IS_ORBIS_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_DURANGO_VERSION()
	{
		auto retval = (bool)MISC::IS_DURANGO_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_XBOX360_VERSION()
	{
		auto retval = (bool)MISC::IS_XBOX360_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PS3_VERSION()
	{
		auto retval = (bool)MISC::IS_PS3_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PC_VERSION()
	{
		auto retval = (bool)MISC::IS_PC_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_STEAM_VERSION()
	{
		auto retval = (bool)MISC::IS_STEAM_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_AUSSIE_VERSION()
	{
		auto retval = (bool)MISC::IS_AUSSIE_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_JAPANESE_VERSION()
	{
		auto retval = (bool)MISC::IS_JAPANESE_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_XBOX_PLATFORM()
	{
		auto retval = (bool)MISC::IS_XBOX_PLATFORM();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_SCARLETT_VERSION()
	{
		auto retval = (bool)MISC::IS_SCARLETT_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_SCE_PLATFORM()
	{
		auto retval = (bool)MISC::IS_SCE_PLATFORM();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_PROSPERO_VERSION()
	{
		auto retval = (bool)MISC::IS_PROSPERO_VERSION();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_STRING_NULL(sol::stack_object string)
	{
		auto retval = (bool)MISC::IS_STRING_NULL(string.is<const char*>() ? string.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_STRING_NULL_OR_EMPTY(sol::stack_object string)
	{
		auto retval = (bool)MISC::IS_STRING_NULL_OR_EMPTY(string.is<const char*>() ? string.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_MISC_STRING_TO_INT(sol::stack_object string, int outInteger)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)MISC::STRING_TO_INT(string.is<const char*>() ? string.as<const char*>() : nullptr, &outInteger);
		std::get<1>(return_values) = outInteger;

		return return_values;
	}

	static int LUA_NATIVE_MISC_SET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd, int p3)
	{
		MISC::SET_BITS_IN_RANGE(&var, rangeStart, rangeEnd, p3);
		return var;
	}

	static int LUA_NATIVE_MISC_GET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd)
	{
		auto retval = MISC::GET_BITS_IN_RANGE(var, rangeStart, rangeEnd);
		return retval;
	}

	static int LUA_NATIVE_MISC_ADD_STUNT_JUMP(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float camX, float camY, float camZ, int p15, int p16, int p17)
	{
		auto retval = MISC::ADD_STUNT_JUMP(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, camX, camY, camZ, p15, p16, p17);
		return retval;
	}

	static int LUA_NATIVE_MISC_ADD_STUNT_JUMP_ANGLED(float x1, float y1, float z1, float x2, float y2, float z2, float radius1, float x3, float y3, float z3, float x4, float y4, float z4, float radius2, float camX, float camY, float camZ, int p17, int p18, int p19)
	{
		auto retval = MISC::ADD_STUNT_JUMP_ANGLED(x1, y1, z1, x2, y2, z2, radius1, x3, y3, z3, x4, y4, z4, radius2, camX, camY, camZ, p17, p18, p19);
		return retval;
	}

	static void LUA_NATIVE_MISC_TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA(bool toggle)
	{
		MISC::TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA(toggle);
	}

	static void LUA_NATIVE_MISC_DELETE_STUNT_JUMP(int p0)
	{
		MISC::DELETE_STUNT_JUMP(p0);
	}

	static void LUA_NATIVE_MISC_ENABLE_STUNT_JUMP_SET(int p0)
	{
		MISC::ENABLE_STUNT_JUMP_SET(p0);
	}

	static void LUA_NATIVE_MISC_DISABLE_STUNT_JUMP_SET(int p0)
	{
		MISC::DISABLE_STUNT_JUMP_SET(p0);
	}

	static void LUA_NATIVE_MISC_SET_STUNT_JUMPS_CAN_TRIGGER(bool toggle)
	{
		MISC::SET_STUNT_JUMPS_CAN_TRIGGER(toggle);
	}

	static bool LUA_NATIVE_MISC_IS_STUNT_JUMP_IN_PROGRESS()
	{
		auto retval = (bool)MISC::IS_STUNT_JUMP_IN_PROGRESS();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_STUNT_JUMP_MESSAGE_SHOWING()
	{
		auto retval = (bool)MISC::IS_STUNT_JUMP_MESSAGE_SHOWING();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_NUM_SUCCESSFUL_STUNT_JUMPS()
	{
		auto retval = MISC::GET_NUM_SUCCESSFUL_STUNT_JUMPS();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_TOTAL_SUCCESSFUL_STUNT_JUMPS()
	{
		auto retval = MISC::GET_TOTAL_SUCCESSFUL_STUNT_JUMPS();
		return retval;
	}

	static void LUA_NATIVE_MISC_CANCEL_STUNT_JUMP()
	{
		MISC::CANCEL_STUNT_JUMP();
	}

	static void LUA_NATIVE_MISC_SET_GAME_PAUSED(bool toggle)
	{
		MISC::SET_GAME_PAUSED(toggle);
	}

	static void LUA_NATIVE_MISC_SET_THIS_SCRIPT_CAN_BE_PAUSED(bool toggle)
	{
		MISC::SET_THIS_SCRIPT_CAN_BE_PAUSED(toggle);
	}

	static void LUA_NATIVE_MISC_SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(bool toggle)
	{
		MISC::SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(toggle);
	}

	static bool LUA_NATIVE_MISC_HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash, int amount)
	{
		auto retval = (bool)MISC::HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED(hash, amount);
		return retval;
	}

	static bool LUA_NATIVE_MISC_HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash)
	{
		auto retval = (bool)MISC::HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(hash);
		return retval;
	}

	static void LUA_NATIVE_MISC_OVERRIDE_FREEZE_FLAGS(bool p0)
	{
		MISC::OVERRIDE_FREEZE_FLAGS(p0);
	}

	static void LUA_NATIVE_MISC_SET_INSTANCE_PRIORITY_MODE(int p0)
	{
		MISC::SET_INSTANCE_PRIORITY_MODE(p0);
	}

	static void LUA_NATIVE_MISC_SET_INSTANCE_PRIORITY_HINT(int flag)
	{
		MISC::SET_INSTANCE_PRIORITY_HINT(flag);
	}

	static bool LUA_NATIVE_MISC_IS_FRONTEND_FADING()
	{
		auto retval = (bool)MISC::IS_FRONTEND_FADING();
		return retval;
	}

	static void LUA_NATIVE_MISC_POPULATE_NOW()
	{
		MISC::POPULATE_NOW();
	}

	static int LUA_NATIVE_MISC_GET_INDEX_OF_CURRENT_LEVEL()
	{
		auto retval = MISC::GET_INDEX_OF_CURRENT_LEVEL();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_GRAVITY_LEVEL(int level)
	{
		MISC::SET_GRAVITY_LEVEL(level);
	}

	static void LUA_NATIVE_MISC_START_SAVE_DATA(uintptr_t p0, Any p1, bool p2)
	{
		MISC::START_SAVE_DATA((Any*)p0, p1, p2);
	}

	static void LUA_NATIVE_MISC_STOP_SAVE_DATA()
	{
		MISC::STOP_SAVE_DATA();
	}

	static int LUA_NATIVE_MISC_GET_SIZE_OF_SAVE_DATA(bool p0)
	{
		auto retval = MISC::GET_SIZE_OF_SAVE_DATA(p0);
		return retval;
	}

	static void LUA_NATIVE_MISC_REGISTER_INT_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_INT_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_INT64_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_INT64_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_ENUM_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_ENUM_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_FLOAT_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_FLOAT_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_BOOL_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_BOOL_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_TEXT_LABEL_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_15_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_TEXT_LABEL_15_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_23_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_TEXT_LABEL_23_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_31_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_TEXT_LABEL_31_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_63_TO_SAVE(uintptr_t p0, sol::stack_object name)
	{
		MISC::REGISTER_TEXT_LABEL_63_TO_SAVE((Any*)p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_START_SAVE_STRUCT_WITH_SIZE(uintptr_t p0, int size, sol::stack_object structName)
	{
		MISC::START_SAVE_STRUCT_WITH_SIZE((Any*)p0, size, structName.is<const char*>() ? structName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_STOP_SAVE_STRUCT()
	{
		MISC::STOP_SAVE_STRUCT();
	}

	static void LUA_NATIVE_MISC_START_SAVE_ARRAY_WITH_SIZE(uintptr_t p0, int size, sol::stack_object arrayName)
	{
		MISC::START_SAVE_ARRAY_WITH_SIZE((Any*)p0, size, arrayName.is<const char*>() ? arrayName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_MISC_STOP_SAVE_ARRAY()
	{
		MISC::STOP_SAVE_ARRAY();
	}

	static void LUA_NATIVE_MISC_COPY_SCRIPT_STRUCT(uintptr_t dst, uintptr_t src, int size)
	{
		MISC::COPY_SCRIPT_STRUCT((Any*)dst, (Any*)src, size);
	}

	static void LUA_NATIVE_MISC_ENABLE_DISPATCH_SERVICE(int dispatchService, bool toggle)
	{
		MISC::ENABLE_DISPATCH_SERVICE(dispatchService, toggle);
	}

	static void LUA_NATIVE_MISC_BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION(int dispatchService, bool toggle)
	{
		MISC::BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION(dispatchService, toggle);
	}

	static int LUA_NATIVE_MISC_GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL(int dispatchService)
	{
		auto retval = MISC::GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL(dispatchService);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_MISC_CREATE_INCIDENT(int dispatchService, float x, float y, float z, int numUnits, float radius, int outIncidentID, Any p7, Any p8)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)MISC::CREATE_INCIDENT(dispatchService, x, y, z, numUnits, radius, &outIncidentID, p7, p8);
		std::get<1>(return_values) = outIncidentID;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_MISC_CREATE_INCIDENT_WITH_ENTITY(int dispatchService, Ped ped, int numUnits, float radius, int outIncidentID, Any p5, Any p6)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)MISC::CREATE_INCIDENT_WITH_ENTITY(dispatchService, ped, numUnits, radius, &outIncidentID, p5, p6);
		std::get<1>(return_values) = outIncidentID;

		return return_values;
	}

	static void LUA_NATIVE_MISC_DELETE_INCIDENT(int incidentId)
	{
		MISC::DELETE_INCIDENT(incidentId);
	}

	static bool LUA_NATIVE_MISC_IS_INCIDENT_VALID(int incidentId)
	{
		auto retval = (bool)MISC::IS_INCIDENT_VALID(incidentId);
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_INCIDENT_REQUESTED_UNITS(int incidentId, int dispatchService, int numUnits)
	{
		MISC::SET_INCIDENT_REQUESTED_UNITS(incidentId, dispatchService, numUnits);
	}

	static void LUA_NATIVE_MISC_SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT(int incidentId, float p1)
	{
		MISC::SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT(incidentId, p1);
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_MISC_FIND_SPAWN_POINT_IN_DIRECTION(float posX, float posY, float posZ, float fwdVecX, float fwdVecY, float fwdVecZ, float distance, Vector3 spawnPoint)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)MISC::FIND_SPAWN_POINT_IN_DIRECTION(posX, posY, posZ, fwdVecX, fwdVecY, fwdVecZ, distance, &spawnPoint);
		std::get<1>(return_values) = spawnPoint;

		return return_values;
	}

	static int LUA_NATIVE_MISC_ADD_POP_MULTIPLIER_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float p6, float p7, bool p8, bool p9)
	{
		auto retval = MISC::ADD_POP_MULTIPLIER_AREA(x1, y1, z1, x2, y2, z2, p6, p7, p8, p9);
		return retval;
	}

	static bool LUA_NATIVE_MISC_DOES_POP_MULTIPLIER_AREA_EXIST(int id)
	{
		auto retval = (bool)MISC::DOES_POP_MULTIPLIER_AREA_EXIST(id);
		return retval;
	}

	static void LUA_NATIVE_MISC_REMOVE_POP_MULTIPLIER_AREA(int id, bool p1)
	{
		MISC::REMOVE_POP_MULTIPLIER_AREA(id, p1);
	}

	static bool LUA_NATIVE_MISC_IS_POP_MULTIPLIER_AREA_NETWORKED(int id)
	{
		auto retval = (bool)MISC::IS_POP_MULTIPLIER_AREA_NETWORKED(id);
		return retval;
	}

	static int LUA_NATIVE_MISC_ADD_POP_MULTIPLIER_SPHERE(float x, float y, float z, float radius, float pedMultiplier, float vehicleMultiplier, bool p6, bool p7)
	{
		auto retval = MISC::ADD_POP_MULTIPLIER_SPHERE(x, y, z, radius, pedMultiplier, vehicleMultiplier, p6, p7);
		return retval;
	}

	static bool LUA_NATIVE_MISC_DOES_POP_MULTIPLIER_SPHERE_EXIST(int id)
	{
		auto retval = (bool)MISC::DOES_POP_MULTIPLIER_SPHERE_EXIST(id);
		return retval;
	}

	static void LUA_NATIVE_MISC_REMOVE_POP_MULTIPLIER_SPHERE(int id, bool p1)
	{
		MISC::REMOVE_POP_MULTIPLIER_SPHERE(id, p1);
	}

	static void LUA_NATIVE_MISC_ENABLE_TENNIS_MODE(Ped ped, bool toggle, bool p2)
	{
		MISC::ENABLE_TENNIS_MODE(ped, toggle, p2);
	}

	static bool LUA_NATIVE_MISC_IS_TENNIS_MODE(Ped ped)
	{
		auto retval = (bool)MISC::IS_TENNIS_MODE(ped);
		return retval;
	}

	static void LUA_NATIVE_MISC_PLAY_TENNIS_SWING_ANIM(Ped ped, sol::stack_object animDict, sol::stack_object animName, float p3, float p4, bool p5)
	{
		MISC::PLAY_TENNIS_SWING_ANIM(ped, animDict.is<const char*>() ? animDict.as<const char*>() : nullptr, animName.is<const char*>() ? animName.as<const char*>() : nullptr, p3, p4, p5);
	}

	static bool LUA_NATIVE_MISC_GET_TENNIS_SWING_ANIM_COMPLETE(Ped ped)
	{
		auto retval = (bool)MISC::GET_TENNIS_SWING_ANIM_COMPLETE(ped);
		return retval;
	}

	static bool LUA_NATIVE_MISC_GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED(Ped ped)
	{
		auto retval = (bool)MISC::GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED(ped);
		return retval;
	}

	static bool LUA_NATIVE_MISC_GET_TENNIS_SWING_ANIM_SWUNG(Ped ped)
	{
		auto retval = (bool)MISC::GET_TENNIS_SWING_ANIM_SWUNG(ped);
		return retval;
	}

	static void LUA_NATIVE_MISC_PLAY_TENNIS_DIVE_ANIM(Ped ped, int p1, float p2, float p3, float p4, bool p5)
	{
		MISC::PLAY_TENNIS_DIVE_ANIM(ped, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_MISC_SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, sol::stack_object p1, float p2)
	{
		MISC::SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT(ped, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_MISC_RESET_DISPATCH_SPAWN_LOCATION()
	{
		MISC::RESET_DISPATCH_SPAWN_LOCATION();
	}

	static void LUA_NATIVE_MISC_SET_DISPATCH_SPAWN_LOCATION(float x, float y, float z)
	{
		MISC::SET_DISPATCH_SPAWN_LOCATION(x, y, z);
	}

	static void LUA_NATIVE_MISC_RESET_DISPATCH_IDEAL_SPAWN_DISTANCE()
	{
		MISC::RESET_DISPATCH_IDEAL_SPAWN_DISTANCE();
	}

	static void LUA_NATIVE_MISC_SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float distance)
	{
		MISC::SET_DISPATCH_IDEAL_SPAWN_DISTANCE(distance);
	}

	static void LUA_NATIVE_MISC_RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0)
	{
		MISC::RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(p0);
	}

	static void LUA_NATIVE_MISC_SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0, float p1)
	{
		MISC::SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(p0, p1);
	}

	static void LUA_NATIVE_MISC_SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(Any p0, float p1)
	{
		MISC::SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(p0, p1);
	}

	static int LUA_NATIVE_MISC_ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width)
	{
		auto retval = MISC::ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA(x1, y1, z1, x2, y2, z2, width);
		return retval;
	}

	static int LUA_NATIVE_MISC_ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA(float x1, float y1, float x2, float y2)
	{
		auto retval = MISC::ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA(x1, y1, x2, y2);
		return retval;
	}

	static void LUA_NATIVE_MISC_REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(int p0)
	{
		MISC::REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(p0);
	}

	static void LUA_NATIVE_MISC_RESET_DISPATCH_SPAWN_BLOCKING_AREAS()
	{
		MISC::RESET_DISPATCH_SPAWN_BLOCKING_AREAS();
	}

	static void LUA_NATIVE_MISC_RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN()
	{
		MISC::RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN();
	}

	static void LUA_NATIVE_MISC_SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN(int p0, int p1)
	{
		MISC::SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN(p0, p1);
	}

	static void LUA_NATIVE_MISC_ADD_TACTICAL_NAV_MESH_POINT(float x, float y, float z)
	{
		MISC::ADD_TACTICAL_NAV_MESH_POINT(x, y, z);
	}

	static void LUA_NATIVE_MISC_CLEAR_TACTICAL_NAV_MESH_POINTS()
	{
		MISC::CLEAR_TACTICAL_NAV_MESH_POINTS();
	}

	static void LUA_NATIVE_MISC_SET_RIOT_MODE_ENABLED(bool toggle)
	{
		MISC::SET_RIOT_MODE_ENABLED(toggle);
	}

	static void LUA_NATIVE_MISC_DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING(int p0, sol::stack_object windowTitle, uintptr_t p2, sol::stack_object defaultText, sol::stack_object defaultConcat1, sol::stack_object defaultConcat2, sol::stack_object defaultConcat3, sol::stack_object defaultConcat4, sol::stack_object defaultConcat5, sol::stack_object defaultConcat6, sol::stack_object defaultConcat7, int maxInputLength)
	{
		MISC::DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING(p0, windowTitle.is<const char*>() ? windowTitle.as<const char*>() : nullptr, (Any*)p2, defaultText.is<const char*>() ? defaultText.as<const char*>() : nullptr, defaultConcat1.is<const char*>() ? defaultConcat1.as<const char*>() : nullptr, defaultConcat2.is<const char*>() ? defaultConcat2.as<const char*>() : nullptr, defaultConcat3.is<const char*>() ? defaultConcat3.as<const char*>() : nullptr, defaultConcat4.is<const char*>() ? defaultConcat4.as<const char*>() : nullptr, defaultConcat5.is<const char*>() ? defaultConcat5.as<const char*>() : nullptr, defaultConcat6.is<const char*>() ? defaultConcat6.as<const char*>() : nullptr, defaultConcat7.is<const char*>() ? defaultConcat7.as<const char*>() : nullptr, maxInputLength);
	}

	static void LUA_NATIVE_MISC_DISPLAY_ONSCREEN_KEYBOARD(int p0, sol::stack_object windowTitle, sol::stack_object p2, sol::stack_object defaultText, sol::stack_object defaultConcat1, sol::stack_object defaultConcat2, sol::stack_object defaultConcat3, int maxInputLength)
	{
		MISC::DISPLAY_ONSCREEN_KEYBOARD(p0, windowTitle.is<const char*>() ? windowTitle.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, defaultText.is<const char*>() ? defaultText.as<const char*>() : nullptr, defaultConcat1.is<const char*>() ? defaultConcat1.as<const char*>() : nullptr, defaultConcat2.is<const char*>() ? defaultConcat2.as<const char*>() : nullptr, defaultConcat3.is<const char*>() ? defaultConcat3.as<const char*>() : nullptr, maxInputLength);
	}

	static int LUA_NATIVE_MISC_UPDATE_ONSCREEN_KEYBOARD()
	{
		auto retval = MISC::UPDATE_ONSCREEN_KEYBOARD();
		return retval;
	}

	static const char* LUA_NATIVE_MISC_GET_ONSCREEN_KEYBOARD_RESULT()
	{
		auto retval = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
		return retval;
	}

	static void LUA_NATIVE_MISC_CANCEL_ONSCREEN_KEYBOARD()
	{
		MISC::CANCEL_ONSCREEN_KEYBOARD();
	}

	static void LUA_NATIVE_MISC_NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS(int p0)
	{
		MISC::NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS(p0);
	}

	static void LUA_NATIVE_MISC_ACTION_MANAGER_ENABLE_ACTION(Hash hash, bool enable)
	{
		MISC::ACTION_MANAGER_ENABLE_ACTION(hash, enable);
	}

	static int LUA_NATIVE_MISC_GET_REAL_WORLD_TIME()
	{
		auto retval = MISC::GET_REAL_WORLD_TIME();
		return retval;
	}

	static void LUA_NATIVE_MISC_SUPRESS_RANDOM_EVENT_THIS_FRAME(int eventType, bool suppress)
	{
		MISC::SUPRESS_RANDOM_EVENT_THIS_FRAME(eventType, suppress);
	}

	static void LUA_NATIVE_MISC_SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player)
	{
		MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}

	static void LUA_NATIVE_MISC_SET_FIRE_AMMO_THIS_FRAME(Player player)
	{
		MISC::SET_FIRE_AMMO_THIS_FRAME(player);
	}

	static void LUA_NATIVE_MISC_SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player)
	{
		MISC::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}

	static void LUA_NATIVE_MISC_SET_SUPER_JUMP_THIS_FRAME(Player player)
	{
		MISC::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	static void LUA_NATIVE_MISC_SET_BEAST_JUMP_THIS_FRAME(Player player)
	{
		MISC::SET_BEAST_JUMP_THIS_FRAME(player);
	}

	static void LUA_NATIVE_MISC_SET_FORCED_JUMP_THIS_FRAME(Player player)
	{
		MISC::SET_FORCED_JUMP_THIS_FRAME(player);
	}

	static bool LUA_NATIVE_MISC_HAS_GAME_INSTALLED_THIS_SESSION()
	{
		auto retval = (bool)MISC::HAS_GAME_INSTALLED_THIS_SESSION();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_TICKER_JOHNMARSTON_IS_DONE()
	{
		MISC::SET_TICKER_JOHNMARSTON_IS_DONE();
	}

	static bool LUA_NATIVE_MISC_ARE_PROFILE_SETTINGS_VALID()
	{
		auto retval = (bool)MISC::ARE_PROFILE_SETTINGS_VALID();
		return retval;
	}

	static void LUA_NATIVE_MISC_PREVENT_ARREST_STATE_THIS_FRAME()
	{
		MISC::PREVENT_ARREST_STATE_THIS_FRAME();
	}

	static void LUA_NATIVE_MISC_FORCE_GAME_STATE_PLAYING()
	{
		MISC::FORCE_GAME_STATE_PLAYING();
	}

	static void LUA_NATIVE_MISC_SCRIPT_RACE_INIT(int p0, int p1, Any p2, Any p3)
	{
		MISC::SCRIPT_RACE_INIT(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_MISC_SCRIPT_RACE_SHUTDOWN()
	{
		MISC::SCRIPT_RACE_SHUTDOWN();
	}

	static void LUA_NATIVE_MISC_SCRIPT_RACE_PLAYER_HIT_CHECKPOINT(Player player, Any p1, Any p2, Any p3)
	{
		MISC::SCRIPT_RACE_PLAYER_HIT_CHECKPOINT(player, p1, p2, p3);
	}

	static std::tuple<bool, int, int> LUA_NATIVE_MISC_SCRIPT_RACE_GET_PLAYER_SPLIT_TIME(Player player, int p1, int p2)
	{
		std::tuple<bool, int, int> return_values;
		std::get<0>(return_values) = (bool)MISC::SCRIPT_RACE_GET_PLAYER_SPLIT_TIME(player, &p1, &p2);
		std::get<1>(return_values) = p1;
		std::get<2>(return_values) = p2;

		return return_values;
	}

	static void LUA_NATIVE_MISC_START_END_USER_BENCHMARK()
	{
		MISC::START_END_USER_BENCHMARK();
	}

	static void LUA_NATIVE_MISC_STOP_END_USER_BENCHMARK()
	{
		MISC::STOP_END_USER_BENCHMARK();
	}

	static void LUA_NATIVE_MISC_RESET_END_USER_BENCHMARK()
	{
		MISC::RESET_END_USER_BENCHMARK();
	}

	static void LUA_NATIVE_MISC_SAVE_END_USER_BENCHMARK()
	{
		MISC::SAVE_END_USER_BENCHMARK();
	}

	static bool LUA_NATIVE_MISC_UI_STARTED_END_USER_BENCHMARK()
	{
		auto retval = (bool)MISC::UI_STARTED_END_USER_BENCHMARK();
		return retval;
	}

	static bool LUA_NATIVE_MISC_LANDING_SCREEN_STARTED_END_USER_BENCHMARK()
	{
		auto retval = (bool)MISC::LANDING_SCREEN_STARTED_END_USER_BENCHMARK();
		return retval;
	}

	static bool LUA_NATIVE_MISC_IS_COMMANDLINE_END_USER_BENCHMARK()
	{
		auto retval = (bool)MISC::IS_COMMANDLINE_END_USER_BENCHMARK();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_BENCHMARK_ITERATIONS()
	{
		auto retval = MISC::GET_BENCHMARK_ITERATIONS();
		return retval;
	}

	static int LUA_NATIVE_MISC_GET_BENCHMARK_PASS()
	{
		auto retval = MISC::GET_BENCHMARK_PASS();
		return retval;
	}

	static void LUA_NATIVE_MISC_RESTART_GAME()
	{
		MISC::RESTART_GAME();
	}

	static void LUA_NATIVE_MISC_QUIT_GAME()
	{
		MISC::QUIT_GAME();
	}

	static bool LUA_NATIVE_MISC_HAS_ASYNC_INSTALL_FINISHED()
	{
		auto retval = (bool)MISC::HAS_ASYNC_INSTALL_FINISHED();
		return retval;
	}

	static void LUA_NATIVE_MISC_CLEANUP_ASYNC_INSTALL()
	{
		MISC::CLEANUP_ASYNC_INSTALL();
	}

	static bool LUA_NATIVE_MISC_PLM_IS_IN_CONSTRAINED_MODE()
	{
		auto retval = (bool)MISC::PLM_IS_IN_CONSTRAINED_MODE();
		return retval;
	}

	static int LUA_NATIVE_MISC_PLM_GET_CONSTRAINED_DURATION_MS()
	{
		auto retval = MISC::PLM_GET_CONSTRAINED_DURATION_MS();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_PLAYER_IS_IN_ANIMAL_FORM(bool toggle)
	{
		MISC::SET_PLAYER_IS_IN_ANIMAL_FORM(toggle);
	}

	static bool LUA_NATIVE_MISC_GET_IS_PLAYER_IN_ANIMAL_FORM()
	{
		auto retval = (bool)MISC::GET_IS_PLAYER_IN_ANIMAL_FORM();
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_PLAYER_IS_REPEATING_A_MISSION(bool toggle)
	{
		MISC::SET_PLAYER_IS_REPEATING_A_MISSION(toggle);
	}

	static void LUA_NATIVE_MISC_DISABLE_SCREEN_DIMMING_THIS_FRAME()
	{
		MISC::DISABLE_SCREEN_DIMMING_THIS_FRAME();
	}

	static float LUA_NATIVE_MISC_GET_CITY_DENSITY()
	{
		auto retval = MISC::GET_CITY_DENSITY();
		return retval;
	}

	static void LUA_NATIVE_MISC_USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE()
	{
		MISC::USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE();
	}

	static void LUA_NATIVE_MISC_SET_CONTENT_ID_INDEX(Hash contentId, int index)
	{
		MISC::SET_CONTENT_ID_INDEX(contentId, index);
	}

	static int LUA_NATIVE_MISC_GET_CONTENT_ID_INDEX(Hash contentId)
	{
		auto retval = MISC::GET_CONTENT_ID_INDEX(contentId);
		return retval;
	}

	static void LUA_NATIVE_MISC_SET_CONTENT_PROP_TYPE_(Hash model, int type)
	{
		MISC::_SET_CONTENT_PROP_TYPE(model, type);
	}

	static int LUA_NATIVE_MISC_GET_CONTENT_PROP_TYPE_(Hash model)
	{
		auto retval = MISC::_GET_CONTENT_PROP_TYPE(model);
		return retval;
	}

	void init_native_binding_MISC(sol::state& L)
	{
		auto MISC = L["MISC"].get_or_create<sol::table>();
		MISC.set_function("GET_ALLOCATED_STACK_SIZE", LUA_NATIVE_MISC_GET_ALLOCATED_STACK_SIZE);
		MISC.set_function("GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE", LUA_NATIVE_MISC_GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE);
		MISC.set_function("SET_RANDOM_SEED", LUA_NATIVE_MISC_SET_RANDOM_SEED);
		MISC.set_function("SET_TIME_SCALE", LUA_NATIVE_MISC_SET_TIME_SCALE);
		MISC.set_function("SET_MISSION_FLAG", LUA_NATIVE_MISC_SET_MISSION_FLAG);
		MISC.set_function("GET_MISSION_FLAG", LUA_NATIVE_MISC_GET_MISSION_FLAG);
		MISC.set_function("SET_RANDOM_EVENT_FLAG", LUA_NATIVE_MISC_SET_RANDOM_EVENT_FLAG);
		MISC.set_function("GET_RANDOM_EVENT_FLAG", LUA_NATIVE_MISC_GET_RANDOM_EVENT_FLAG);
		MISC.set_function("GET_CONTENT_TO_LOAD", LUA_NATIVE_MISC_GET_CONTENT_TO_LOAD);
		MISC.set_function("ACTIVITY_FEED_CREATE", LUA_NATIVE_MISC_ACTIVITY_FEED_CREATE);
		MISC.set_function("ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION", LUA_NATIVE_MISC_ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION);
		MISC.set_function("ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION", LUA_NATIVE_MISC_ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION);
		MISC.set_function("ACTIVITY_FEED_ADD_INT_TO_CAPTION", LUA_NATIVE_MISC_ACTIVITY_FEED_ADD_INT_TO_CAPTION);
		MISC.set_function("ACTIVITY_FEED_LARGE_IMAGE_URL", LUA_NATIVE_MISC_ACTIVITY_FEED_LARGE_IMAGE_URL);
		MISC.set_function("ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE", LUA_NATIVE_MISC_ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE);
		MISC.set_function("ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD", LUA_NATIVE_MISC_ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD);
		MISC.set_function("ACTIVITY_FEED_POST", LUA_NATIVE_MISC_ACTIVITY_FEED_POST);
		MISC.set_function("ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST", LUA_NATIVE_MISC_ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST);
		MISC.set_function("HAS_RESUMED_FROM_SUSPEND", LUA_NATIVE_MISC_HAS_RESUMED_FROM_SUSPEND);
		MISC.set_function("SET_SCRIPT_HIGH_PRIO", LUA_NATIVE_MISC_SET_SCRIPT_HIGH_PRIO);
		MISC.set_function("SET_THIS_IS_A_TRIGGER_SCRIPT", LUA_NATIVE_MISC_SET_THIS_IS_A_TRIGGER_SCRIPT);
		MISC.set_function("INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION", LUA_NATIVE_MISC_INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION);
		MISC.set_function("GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK", LUA_NATIVE_MISC_GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK);
		MISC.set_function("GET_PREV_WEATHER_TYPE_HASH_NAME", LUA_NATIVE_MISC_GET_PREV_WEATHER_TYPE_HASH_NAME);
		MISC.set_function("GET_NEXT_WEATHER_TYPE_HASH_NAME", LUA_NATIVE_MISC_GET_NEXT_WEATHER_TYPE_HASH_NAME);
		MISC.set_function("IS_PREV_WEATHER_TYPE", LUA_NATIVE_MISC_IS_PREV_WEATHER_TYPE);
		MISC.set_function("IS_NEXT_WEATHER_TYPE", LUA_NATIVE_MISC_IS_NEXT_WEATHER_TYPE);
		MISC.set_function("SET_WEATHER_TYPE_PERSIST", LUA_NATIVE_MISC_SET_WEATHER_TYPE_PERSIST);
		MISC.set_function("SET_WEATHER_TYPE_NOW_PERSIST", LUA_NATIVE_MISC_SET_WEATHER_TYPE_NOW_PERSIST);
		MISC.set_function("SET_WEATHER_TYPE_NOW", LUA_NATIVE_MISC_SET_WEATHER_TYPE_NOW);
		MISC.set_function("SET_WEATHER_TYPE_OVERTIME_PERSIST", LUA_NATIVE_MISC_SET_WEATHER_TYPE_OVERTIME_PERSIST);
		MISC.set_function("SET_RANDOM_WEATHER_TYPE", LUA_NATIVE_MISC_SET_RANDOM_WEATHER_TYPE);
		MISC.set_function("CLEAR_WEATHER_TYPE_PERSIST", LUA_NATIVE_MISC_CLEAR_WEATHER_TYPE_PERSIST);
		MISC.set_function("CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK", LUA_NATIVE_MISC_CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK);
		MISC.set_function("GET_CURR_WEATHER_STATE", LUA_NATIVE_MISC_GET_CURR_WEATHER_STATE);
		MISC.set_function("SET_CURR_WEATHER_STATE", LUA_NATIVE_MISC_SET_CURR_WEATHER_STATE);
		MISC.set_function("SET_OVERRIDE_WEATHER", LUA_NATIVE_MISC_SET_OVERRIDE_WEATHER);
		MISC.set_function("SET_OVERRIDE_WEATHEREX", LUA_NATIVE_MISC_SET_OVERRIDE_WEATHEREX);
		MISC.set_function("CLEAR_OVERRIDE_WEATHER", LUA_NATIVE_MISC_CLEAR_OVERRIDE_WEATHER);
		MISC.set_function("WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE);
		MISC.set_function("WATER_OVERRIDE_SET_RIPPLEBUMPINESS", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEBUMPINESS);
		MISC.set_function("WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS);
		MISC.set_function("WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS);
		MISC.set_function("WATER_OVERRIDE_SET_RIPPLEDISTURB", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_RIPPLEDISTURB);
		MISC.set_function("WATER_OVERRIDE_SET_STRENGTH", LUA_NATIVE_MISC_WATER_OVERRIDE_SET_STRENGTH);
		MISC.set_function("WATER_OVERRIDE_FADE_IN", LUA_NATIVE_MISC_WATER_OVERRIDE_FADE_IN);
		MISC.set_function("WATER_OVERRIDE_FADE_OUT", LUA_NATIVE_MISC_WATER_OVERRIDE_FADE_OUT);
		MISC.set_function("SET_WIND", LUA_NATIVE_MISC_SET_WIND);
		MISC.set_function("SET_WIND_SPEED", LUA_NATIVE_MISC_SET_WIND_SPEED);
		MISC.set_function("GET_WIND_SPEED", LUA_NATIVE_MISC_GET_WIND_SPEED);
		MISC.set_function("SET_WIND_DIRECTION", LUA_NATIVE_MISC_SET_WIND_DIRECTION);
		MISC.set_function("GET_WIND_DIRECTION", LUA_NATIVE_MISC_GET_WIND_DIRECTION);
		MISC.set_function("SET_RAIN", LUA_NATIVE_MISC_SET_RAIN);
		MISC.set_function("GET_RAIN_LEVEL", LUA_NATIVE_MISC_GET_RAIN_LEVEL);
		MISC.set_function("SET_SNOW", LUA_NATIVE_MISC_SET_SNOW);
		MISC.set_function("GET_SNOW_LEVEL", LUA_NATIVE_MISC_GET_SNOW_LEVEL);
		MISC.set_function("FORCE_LIGHTNING_FLASH", LUA_NATIVE_MISC_FORCE_LIGHTNING_FLASH);
		MISC.set_function("SET_CLOUD_SETTINGS_OVERRIDE", LUA_NATIVE_MISC_SET_CLOUD_SETTINGS_OVERRIDE);
		MISC.set_function("PRELOAD_CLOUD_HAT", LUA_NATIVE_MISC_PRELOAD_CLOUD_HAT);
		MISC.set_function("LOAD_CLOUD_HAT", LUA_NATIVE_MISC_LOAD_CLOUD_HAT);
		MISC.set_function("UNLOAD_CLOUD_HAT", LUA_NATIVE_MISC_UNLOAD_CLOUD_HAT);
		MISC.set_function("UNLOAD_ALL_CLOUD_HATS", LUA_NATIVE_MISC_UNLOAD_ALL_CLOUD_HATS);
		MISC.set_function("SET_CLOUDS_ALPHA", LUA_NATIVE_MISC_SET_CLOUDS_ALPHA);
		MISC.set_function("GET_CLOUDS_ALPHA", LUA_NATIVE_MISC_GET_CLOUDS_ALPHA);
		MISC.set_function("GET_GAME_TIMER", LUA_NATIVE_MISC_GET_GAME_TIMER);
		MISC.set_function("GET_FRAME_TIME", LUA_NATIVE_MISC_GET_FRAME_TIME);
		MISC.set_function("GET_SYSTEM_TIME_STEP", LUA_NATIVE_MISC_GET_SYSTEM_TIME_STEP);
		MISC.set_function("GET_FRAME_COUNT", LUA_NATIVE_MISC_GET_FRAME_COUNT);
		MISC.set_function("GET_RANDOM_FLOAT_IN_RANGE", LUA_NATIVE_MISC_GET_RANDOM_FLOAT_IN_RANGE);
		MISC.set_function("GET_RANDOM_INT_IN_RANGE", LUA_NATIVE_MISC_GET_RANDOM_INT_IN_RANGE);
		MISC.set_function("GET_RANDOM_MWC_INT_IN_RANGE", LUA_NATIVE_MISC_GET_RANDOM_MWC_INT_IN_RANGE);
		MISC.set_function("GET_GROUND_Z_FOR_3D_COORD", LUA_NATIVE_MISC_GET_GROUND_Z_FOR_3D_COORD);
		MISC.set_function("GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD", LUA_NATIVE_MISC_GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD);
		MISC.set_function("GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD", LUA_NATIVE_MISC_GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD);
		MISC.set_function("ASIN", LUA_NATIVE_MISC_ASIN);
		MISC.set_function("ACOS", LUA_NATIVE_MISC_ACOS);
		MISC.set_function("TAN", LUA_NATIVE_MISC_TAN);
		MISC.set_function("ATAN", LUA_NATIVE_MISC_ATAN);
		MISC.set_function("ATAN2", LUA_NATIVE_MISC_ATAN2);
		MISC.set_function("GET_DISTANCE_BETWEEN_COORDS", LUA_NATIVE_MISC_GET_DISTANCE_BETWEEN_COORDS);
		MISC.set_function("GET_ANGLE_BETWEEN_2D_VECTORS", LUA_NATIVE_MISC_GET_ANGLE_BETWEEN_2D_VECTORS);
		MISC.set_function("GET_HEADING_FROM_VECTOR_2D", LUA_NATIVE_MISC_GET_HEADING_FROM_VECTOR_2D);
		MISC.set_function("GET_RATIO_OF_CLOSEST_POINT_ON_LINE", LUA_NATIVE_MISC_GET_RATIO_OF_CLOSEST_POINT_ON_LINE);
		MISC.set_function("GET_CLOSEST_POINT_ON_LINE", LUA_NATIVE_MISC_GET_CLOSEST_POINT_ON_LINE);
		MISC.set_function("GET_LINE_PLANE_INTERSECTION", LUA_NATIVE_MISC_GET_LINE_PLANE_INTERSECTION);
		MISC.set_function("GET_POINT_AREA_OVERLAP", LUA_NATIVE_MISC_GET_POINT_AREA_OVERLAP);
		MISC.set_function("SET_BIT", LUA_NATIVE_MISC_SET_BIT);
		MISC.set_function("CLEAR_BIT", LUA_NATIVE_MISC_CLEAR_BIT);
		MISC.set_function("GET_HASH_KEY", LUA_NATIVE_MISC_GET_HASH_KEY);
		MISC.set_function("SLERP_NEAR_QUATERNION", LUA_NATIVE_MISC_SLERP_NEAR_QUATERNION);
		MISC.set_function("IS_AREA_OCCUPIED", LUA_NATIVE_MISC_IS_AREA_OCCUPIED);
		MISC.set_function("IS_AREA_OCCUPIED_SLOW", LUA_NATIVE_MISC_IS_AREA_OCCUPIED_SLOW);
		MISC.set_function("IS_POSITION_OCCUPIED", LUA_NATIVE_MISC_IS_POSITION_OCCUPIED);
		MISC.set_function("IS_POINT_OBSCURED_BY_A_MISSION_ENTITY", LUA_NATIVE_MISC_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY);
		MISC.set_function("CLEAR_AREA", LUA_NATIVE_MISC_CLEAR_AREA);
		MISC.set_function("CLEAR_AREA_LEAVE_VEHICLE_HEALTH", LUA_NATIVE_MISC_CLEAR_AREA_LEAVE_VEHICLE_HEALTH);
		MISC.set_function("CLEAR_AREA_OF_VEHICLES", LUA_NATIVE_MISC_CLEAR_AREA_OF_VEHICLES);
		MISC.set_function("CLEAR_ANGLED_AREA_OF_VEHICLES", LUA_NATIVE_MISC_CLEAR_ANGLED_AREA_OF_VEHICLES);
		MISC.set_function("CLEAR_AREA_OF_OBJECTS", LUA_NATIVE_MISC_CLEAR_AREA_OF_OBJECTS);
		MISC.set_function("CLEAR_AREA_OF_PEDS", LUA_NATIVE_MISC_CLEAR_AREA_OF_PEDS);
		MISC.set_function("CLEAR_AREA_OF_COPS", LUA_NATIVE_MISC_CLEAR_AREA_OF_COPS);
		MISC.set_function("CLEAR_AREA_OF_PROJECTILES", LUA_NATIVE_MISC_CLEAR_AREA_OF_PROJECTILES);
		MISC.set_function("CLEAR_SCENARIO_SPAWN_HISTORY", LUA_NATIVE_MISC_CLEAR_SCENARIO_SPAWN_HISTORY);
		MISC.set_function("SET_SAVE_MENU_ACTIVE", LUA_NATIVE_MISC_SET_SAVE_MENU_ACTIVE);
		MISC.set_function("GET_STATUS_OF_MANUAL_SAVE", LUA_NATIVE_MISC_GET_STATUS_OF_MANUAL_SAVE);
		MISC.set_function("SET_CREDITS_ACTIVE", LUA_NATIVE_MISC_SET_CREDITS_ACTIVE);
		MISC.set_function("SET_CREDITS_FADE_OUT_WITH_SCREEN", LUA_NATIVE_MISC_SET_CREDITS_FADE_OUT_WITH_SCREEN);
		MISC.set_function("HAVE_CREDITS_REACHED_END", LUA_NATIVE_MISC_HAVE_CREDITS_REACHED_END);
		MISC.set_function("ARE_CREDITS_RUNNING", LUA_NATIVE_MISC_ARE_CREDITS_RUNNING);
		MISC.set_function("TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME", LUA_NATIVE_MISC_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME);
		MISC.set_function("NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME", LUA_NATIVE_MISC_NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME);
		MISC.set_function("ADD_HOSPITAL_RESTART", LUA_NATIVE_MISC_ADD_HOSPITAL_RESTART);
		MISC.set_function("DISABLE_HOSPITAL_RESTART", LUA_NATIVE_MISC_DISABLE_HOSPITAL_RESTART);
		MISC.set_function("ADD_POLICE_RESTART", LUA_NATIVE_MISC_ADD_POLICE_RESTART);
		MISC.set_function("DISABLE_POLICE_RESTART", LUA_NATIVE_MISC_DISABLE_POLICE_RESTART);
		MISC.set_function("SET_RESTART_COORD_OVERRIDE", LUA_NATIVE_MISC_SET_RESTART_COORD_OVERRIDE);
		MISC.set_function("CLEAR_RESTART_COORD_OVERRIDE", LUA_NATIVE_MISC_CLEAR_RESTART_COORD_OVERRIDE);
		MISC.set_function("PAUSE_DEATH_ARREST_RESTART", LUA_NATIVE_MISC_PAUSE_DEATH_ARREST_RESTART);
		MISC.set_function("IGNORE_NEXT_RESTART", LUA_NATIVE_MISC_IGNORE_NEXT_RESTART);
		MISC.set_function("SET_FADE_OUT_AFTER_DEATH", LUA_NATIVE_MISC_SET_FADE_OUT_AFTER_DEATH);
		MISC.set_function("SET_FADE_OUT_AFTER_ARREST", LUA_NATIVE_MISC_SET_FADE_OUT_AFTER_ARREST);
		MISC.set_function("SET_FADE_IN_AFTER_DEATH_ARREST", LUA_NATIVE_MISC_SET_FADE_IN_AFTER_DEATH_ARREST);
		MISC.set_function("SET_FADE_IN_AFTER_LOAD", LUA_NATIVE_MISC_SET_FADE_IN_AFTER_LOAD);
		MISC.set_function("REGISTER_SAVE_HOUSE", LUA_NATIVE_MISC_REGISTER_SAVE_HOUSE);
		MISC.set_function("SET_SAVE_HOUSE", LUA_NATIVE_MISC_SET_SAVE_HOUSE);
		MISC.set_function("OVERRIDE_SAVE_HOUSE", LUA_NATIVE_MISC_OVERRIDE_SAVE_HOUSE);
		MISC.set_function("GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD", LUA_NATIVE_MISC_GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD);
		MISC.set_function("DO_AUTO_SAVE", LUA_NATIVE_MISC_DO_AUTO_SAVE);
		MISC.set_function("GET_IS_AUTO_SAVE_OFF", LUA_NATIVE_MISC_GET_IS_AUTO_SAVE_OFF);
		MISC.set_function("IS_AUTO_SAVE_IN_PROGRESS", LUA_NATIVE_MISC_IS_AUTO_SAVE_IN_PROGRESS);
		MISC.set_function("HAS_CODE_REQUESTED_AUTOSAVE", LUA_NATIVE_MISC_HAS_CODE_REQUESTED_AUTOSAVE);
		MISC.set_function("CLEAR_CODE_REQUESTED_AUTOSAVE", LUA_NATIVE_MISC_CLEAR_CODE_REQUESTED_AUTOSAVE);
		MISC.set_function("BEGIN_REPLAY_STATS", LUA_NATIVE_MISC_BEGIN_REPLAY_STATS);
		MISC.set_function("ADD_REPLAY_STAT_VALUE", LUA_NATIVE_MISC_ADD_REPLAY_STAT_VALUE);
		MISC.set_function("END_REPLAY_STATS", LUA_NATIVE_MISC_END_REPLAY_STATS);
		MISC.set_function("HAVE_REPLAY_STATS_BEEN_STORED", LUA_NATIVE_MISC_HAVE_REPLAY_STATS_BEEN_STORED);
		MISC.set_function("GET_REPLAY_STAT_MISSION_ID", LUA_NATIVE_MISC_GET_REPLAY_STAT_MISSION_ID);
		MISC.set_function("GET_REPLAY_STAT_MISSION_TYPE", LUA_NATIVE_MISC_GET_REPLAY_STAT_MISSION_TYPE);
		MISC.set_function("GET_REPLAY_STAT_COUNT", LUA_NATIVE_MISC_GET_REPLAY_STAT_COUNT);
		MISC.set_function("GET_REPLAY_STAT_AT_INDEX", LUA_NATIVE_MISC_GET_REPLAY_STAT_AT_INDEX);
		MISC.set_function("CLEAR_REPLAY_STATS", LUA_NATIVE_MISC_CLEAR_REPLAY_STATS);
		MISC.set_function("QUEUE_MISSION_REPEAT_LOAD", LUA_NATIVE_MISC_QUEUE_MISSION_REPEAT_LOAD);
		MISC.set_function("QUEUE_MISSION_REPEAT_SAVE", LUA_NATIVE_MISC_QUEUE_MISSION_REPEAT_SAVE);
		MISC.set_function("QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST", LUA_NATIVE_MISC_QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST);
		MISC.set_function("GET_STATUS_OF_MISSION_REPEAT_SAVE", LUA_NATIVE_MISC_GET_STATUS_OF_MISSION_REPEAT_SAVE);
		MISC.set_function("IS_MEMORY_CARD_IN_USE", LUA_NATIVE_MISC_IS_MEMORY_CARD_IN_USE);
		MISC.set_function("SHOOT_SINGLE_BULLET_BETWEEN_COORDS", LUA_NATIVE_MISC_SHOOT_SINGLE_BULLET_BETWEEN_COORDS);
		MISC.set_function("SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY", LUA_NATIVE_MISC_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY);
		MISC.set_function("SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW", LUA_NATIVE_MISC_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW);
		MISC.set_function("GET_MODEL_DIMENSIONS", LUA_NATIVE_MISC_GET_MODEL_DIMENSIONS);
		MISC.set_function("SET_FAKE_WANTED_LEVEL", LUA_NATIVE_MISC_SET_FAKE_WANTED_LEVEL);
		MISC.set_function("GET_FAKE_WANTED_LEVEL", LUA_NATIVE_MISC_GET_FAKE_WANTED_LEVEL);
		MISC.set_function("USING_MISSION_CREATOR", LUA_NATIVE_MISC_USING_MISSION_CREATOR);
		MISC.set_function("ALLOW_MISSION_CREATOR_WARP", LUA_NATIVE_MISC_ALLOW_MISSION_CREATOR_WARP);
		MISC.set_function("SET_MINIGAME_IN_PROGRESS", LUA_NATIVE_MISC_SET_MINIGAME_IN_PROGRESS);
		MISC.set_function("IS_MINIGAME_IN_PROGRESS", LUA_NATIVE_MISC_IS_MINIGAME_IN_PROGRESS);
		MISC.set_function("IS_THIS_A_MINIGAME_SCRIPT", LUA_NATIVE_MISC_IS_THIS_A_MINIGAME_SCRIPT);
		MISC.set_function("IS_SNIPER_INVERTED", LUA_NATIVE_MISC_IS_SNIPER_INVERTED);
		MISC.set_function("SHOULD_USE_METRIC_MEASUREMENTS", LUA_NATIVE_MISC_SHOULD_USE_METRIC_MEASUREMENTS);
		MISC.set_function("GET_PROFILE_SETTING", LUA_NATIVE_MISC_GET_PROFILE_SETTING);
		MISC.set_function("ARE_STRINGS_EQUAL", LUA_NATIVE_MISC_ARE_STRINGS_EQUAL);
		MISC.set_function("COMPARE_STRINGS", LUA_NATIVE_MISC_COMPARE_STRINGS);
		MISC.set_function("ABSI", LUA_NATIVE_MISC_ABSI);
		MISC.set_function("ABSF", LUA_NATIVE_MISC_ABSF);
		MISC.set_function("IS_SNIPER_BULLET_IN_AREA", LUA_NATIVE_MISC_IS_SNIPER_BULLET_IN_AREA);
		MISC.set_function("IS_PROJECTILE_IN_AREA", LUA_NATIVE_MISC_IS_PROJECTILE_IN_AREA);
		MISC.set_function("IS_PROJECTILE_TYPE_IN_AREA", LUA_NATIVE_MISC_IS_PROJECTILE_TYPE_IN_AREA);
		MISC.set_function("IS_PROJECTILE_TYPE_IN_ANGLED_AREA", LUA_NATIVE_MISC_IS_PROJECTILE_TYPE_IN_ANGLED_AREA);
		MISC.set_function("IS_PROJECTILE_TYPE_WITHIN_DISTANCE", LUA_NATIVE_MISC_IS_PROJECTILE_TYPE_WITHIN_DISTANCE);
		MISC.set_function("GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA", LUA_NATIVE_MISC_GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA);
		MISC.set_function("GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA", LUA_NATIVE_MISC_GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA);
		MISC.set_function("GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE", LUA_NATIVE_MISC_GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE);
		MISC.set_function("GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE", LUA_NATIVE_MISC_GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE);
		MISC.set_function("IS_BULLET_IN_ANGLED_AREA", LUA_NATIVE_MISC_IS_BULLET_IN_ANGLED_AREA);
		MISC.set_function("IS_BULLET_IN_AREA", LUA_NATIVE_MISC_IS_BULLET_IN_AREA);
		MISC.set_function("IS_BULLET_IN_BOX", LUA_NATIVE_MISC_IS_BULLET_IN_BOX);
		MISC.set_function("HAS_BULLET_IMPACTED_IN_AREA", LUA_NATIVE_MISC_HAS_BULLET_IMPACTED_IN_AREA);
		MISC.set_function("HAS_BULLET_IMPACTED_IN_BOX", LUA_NATIVE_MISC_HAS_BULLET_IMPACTED_IN_BOX);
		MISC.set_function("IS_ORBIS_VERSION", LUA_NATIVE_MISC_IS_ORBIS_VERSION);
		MISC.set_function("IS_DURANGO_VERSION", LUA_NATIVE_MISC_IS_DURANGO_VERSION);
		MISC.set_function("IS_XBOX360_VERSION", LUA_NATIVE_MISC_IS_XBOX360_VERSION);
		MISC.set_function("IS_PS3_VERSION", LUA_NATIVE_MISC_IS_PS3_VERSION);
		MISC.set_function("IS_PC_VERSION", LUA_NATIVE_MISC_IS_PC_VERSION);
		MISC.set_function("IS_STEAM_VERSION", LUA_NATIVE_MISC_IS_STEAM_VERSION);
		MISC.set_function("IS_AUSSIE_VERSION", LUA_NATIVE_MISC_IS_AUSSIE_VERSION);
		MISC.set_function("IS_JAPANESE_VERSION", LUA_NATIVE_MISC_IS_JAPANESE_VERSION);
		MISC.set_function("IS_XBOX_PLATFORM", LUA_NATIVE_MISC_IS_XBOX_PLATFORM);
		MISC.set_function("IS_SCARLETT_VERSION", LUA_NATIVE_MISC_IS_SCARLETT_VERSION);
		MISC.set_function("IS_SCE_PLATFORM", LUA_NATIVE_MISC_IS_SCE_PLATFORM);
		MISC.set_function("IS_PROSPERO_VERSION", LUA_NATIVE_MISC_IS_PROSPERO_VERSION);
		MISC.set_function("IS_STRING_NULL", LUA_NATIVE_MISC_IS_STRING_NULL);
		MISC.set_function("IS_STRING_NULL_OR_EMPTY", LUA_NATIVE_MISC_IS_STRING_NULL_OR_EMPTY);
		MISC.set_function("STRING_TO_INT", LUA_NATIVE_MISC_STRING_TO_INT);
		MISC.set_function("SET_BITS_IN_RANGE", LUA_NATIVE_MISC_SET_BITS_IN_RANGE);
		MISC.set_function("GET_BITS_IN_RANGE", LUA_NATIVE_MISC_GET_BITS_IN_RANGE);
		MISC.set_function("ADD_STUNT_JUMP", LUA_NATIVE_MISC_ADD_STUNT_JUMP);
		MISC.set_function("ADD_STUNT_JUMP_ANGLED", LUA_NATIVE_MISC_ADD_STUNT_JUMP_ANGLED);
		MISC.set_function("TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA", LUA_NATIVE_MISC_TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA);
		MISC.set_function("DELETE_STUNT_JUMP", LUA_NATIVE_MISC_DELETE_STUNT_JUMP);
		MISC.set_function("ENABLE_STUNT_JUMP_SET", LUA_NATIVE_MISC_ENABLE_STUNT_JUMP_SET);
		MISC.set_function("DISABLE_STUNT_JUMP_SET", LUA_NATIVE_MISC_DISABLE_STUNT_JUMP_SET);
		MISC.set_function("SET_STUNT_JUMPS_CAN_TRIGGER", LUA_NATIVE_MISC_SET_STUNT_JUMPS_CAN_TRIGGER);
		MISC.set_function("IS_STUNT_JUMP_IN_PROGRESS", LUA_NATIVE_MISC_IS_STUNT_JUMP_IN_PROGRESS);
		MISC.set_function("IS_STUNT_JUMP_MESSAGE_SHOWING", LUA_NATIVE_MISC_IS_STUNT_JUMP_MESSAGE_SHOWING);
		MISC.set_function("GET_NUM_SUCCESSFUL_STUNT_JUMPS", LUA_NATIVE_MISC_GET_NUM_SUCCESSFUL_STUNT_JUMPS);
		MISC.set_function("GET_TOTAL_SUCCESSFUL_STUNT_JUMPS", LUA_NATIVE_MISC_GET_TOTAL_SUCCESSFUL_STUNT_JUMPS);
		MISC.set_function("CANCEL_STUNT_JUMP", LUA_NATIVE_MISC_CANCEL_STUNT_JUMP);
		MISC.set_function("SET_GAME_PAUSED", LUA_NATIVE_MISC_SET_GAME_PAUSED);
		MISC.set_function("SET_THIS_SCRIPT_CAN_BE_PAUSED", LUA_NATIVE_MISC_SET_THIS_SCRIPT_CAN_BE_PAUSED);
		MISC.set_function("SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT", LUA_NATIVE_MISC_SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT);
		MISC.set_function("HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED", LUA_NATIVE_MISC_HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED);
		MISC.set_function("HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED", LUA_NATIVE_MISC_HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED);
		MISC.set_function("OVERRIDE_FREEZE_FLAGS", LUA_NATIVE_MISC_OVERRIDE_FREEZE_FLAGS);
		MISC.set_function("SET_INSTANCE_PRIORITY_MODE", LUA_NATIVE_MISC_SET_INSTANCE_PRIORITY_MODE);
		MISC.set_function("SET_INSTANCE_PRIORITY_HINT", LUA_NATIVE_MISC_SET_INSTANCE_PRIORITY_HINT);
		MISC.set_function("IS_FRONTEND_FADING", LUA_NATIVE_MISC_IS_FRONTEND_FADING);
		MISC.set_function("POPULATE_NOW", LUA_NATIVE_MISC_POPULATE_NOW);
		MISC.set_function("GET_INDEX_OF_CURRENT_LEVEL", LUA_NATIVE_MISC_GET_INDEX_OF_CURRENT_LEVEL);
		MISC.set_function("SET_GRAVITY_LEVEL", LUA_NATIVE_MISC_SET_GRAVITY_LEVEL);
		MISC.set_function("START_SAVE_DATA", LUA_NATIVE_MISC_START_SAVE_DATA);
		MISC.set_function("STOP_SAVE_DATA", LUA_NATIVE_MISC_STOP_SAVE_DATA);
		MISC.set_function("GET_SIZE_OF_SAVE_DATA", LUA_NATIVE_MISC_GET_SIZE_OF_SAVE_DATA);
		MISC.set_function("REGISTER_INT_TO_SAVE", LUA_NATIVE_MISC_REGISTER_INT_TO_SAVE);
		MISC.set_function("REGISTER_INT64_TO_SAVE", LUA_NATIVE_MISC_REGISTER_INT64_TO_SAVE);
		MISC.set_function("REGISTER_ENUM_TO_SAVE", LUA_NATIVE_MISC_REGISTER_ENUM_TO_SAVE);
		MISC.set_function("REGISTER_FLOAT_TO_SAVE", LUA_NATIVE_MISC_REGISTER_FLOAT_TO_SAVE);
		MISC.set_function("REGISTER_BOOL_TO_SAVE", LUA_NATIVE_MISC_REGISTER_BOOL_TO_SAVE);
		MISC.set_function("REGISTER_TEXT_LABEL_TO_SAVE", LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_TO_SAVE);
		MISC.set_function("REGISTER_TEXT_LABEL_15_TO_SAVE", LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_15_TO_SAVE);
		MISC.set_function("REGISTER_TEXT_LABEL_23_TO_SAVE", LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_23_TO_SAVE);
		MISC.set_function("REGISTER_TEXT_LABEL_31_TO_SAVE", LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_31_TO_SAVE);
		MISC.set_function("REGISTER_TEXT_LABEL_63_TO_SAVE", LUA_NATIVE_MISC_REGISTER_TEXT_LABEL_63_TO_SAVE);
		MISC.set_function("START_SAVE_STRUCT_WITH_SIZE", LUA_NATIVE_MISC_START_SAVE_STRUCT_WITH_SIZE);
		MISC.set_function("STOP_SAVE_STRUCT", LUA_NATIVE_MISC_STOP_SAVE_STRUCT);
		MISC.set_function("START_SAVE_ARRAY_WITH_SIZE", LUA_NATIVE_MISC_START_SAVE_ARRAY_WITH_SIZE);
		MISC.set_function("STOP_SAVE_ARRAY", LUA_NATIVE_MISC_STOP_SAVE_ARRAY);
		MISC.set_function("COPY_SCRIPT_STRUCT", LUA_NATIVE_MISC_COPY_SCRIPT_STRUCT);
		MISC.set_function("ENABLE_DISPATCH_SERVICE", LUA_NATIVE_MISC_ENABLE_DISPATCH_SERVICE);
		MISC.set_function("BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION", LUA_NATIVE_MISC_BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION);
		MISC.set_function("GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL", LUA_NATIVE_MISC_GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL);
		MISC.set_function("CREATE_INCIDENT", LUA_NATIVE_MISC_CREATE_INCIDENT);
		MISC.set_function("CREATE_INCIDENT_WITH_ENTITY", LUA_NATIVE_MISC_CREATE_INCIDENT_WITH_ENTITY);
		MISC.set_function("DELETE_INCIDENT", LUA_NATIVE_MISC_DELETE_INCIDENT);
		MISC.set_function("IS_INCIDENT_VALID", LUA_NATIVE_MISC_IS_INCIDENT_VALID);
		MISC.set_function("SET_INCIDENT_REQUESTED_UNITS", LUA_NATIVE_MISC_SET_INCIDENT_REQUESTED_UNITS);
		MISC.set_function("SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT", LUA_NATIVE_MISC_SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT);
		MISC.set_function("FIND_SPAWN_POINT_IN_DIRECTION", LUA_NATIVE_MISC_FIND_SPAWN_POINT_IN_DIRECTION);
		MISC.set_function("ADD_POP_MULTIPLIER_AREA", LUA_NATIVE_MISC_ADD_POP_MULTIPLIER_AREA);
		MISC.set_function("DOES_POP_MULTIPLIER_AREA_EXIST", LUA_NATIVE_MISC_DOES_POP_MULTIPLIER_AREA_EXIST);
		MISC.set_function("REMOVE_POP_MULTIPLIER_AREA", LUA_NATIVE_MISC_REMOVE_POP_MULTIPLIER_AREA);
		MISC.set_function("IS_POP_MULTIPLIER_AREA_NETWORKED", LUA_NATIVE_MISC_IS_POP_MULTIPLIER_AREA_NETWORKED);
		MISC.set_function("ADD_POP_MULTIPLIER_SPHERE", LUA_NATIVE_MISC_ADD_POP_MULTIPLIER_SPHERE);
		MISC.set_function("DOES_POP_MULTIPLIER_SPHERE_EXIST", LUA_NATIVE_MISC_DOES_POP_MULTIPLIER_SPHERE_EXIST);
		MISC.set_function("REMOVE_POP_MULTIPLIER_SPHERE", LUA_NATIVE_MISC_REMOVE_POP_MULTIPLIER_SPHERE);
		MISC.set_function("ENABLE_TENNIS_MODE", LUA_NATIVE_MISC_ENABLE_TENNIS_MODE);
		MISC.set_function("IS_TENNIS_MODE", LUA_NATIVE_MISC_IS_TENNIS_MODE);
		MISC.set_function("PLAY_TENNIS_SWING_ANIM", LUA_NATIVE_MISC_PLAY_TENNIS_SWING_ANIM);
		MISC.set_function("GET_TENNIS_SWING_ANIM_COMPLETE", LUA_NATIVE_MISC_GET_TENNIS_SWING_ANIM_COMPLETE);
		MISC.set_function("GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED", LUA_NATIVE_MISC_GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED);
		MISC.set_function("GET_TENNIS_SWING_ANIM_SWUNG", LUA_NATIVE_MISC_GET_TENNIS_SWING_ANIM_SWUNG);
		MISC.set_function("PLAY_TENNIS_DIVE_ANIM", LUA_NATIVE_MISC_PLAY_TENNIS_DIVE_ANIM);
		MISC.set_function("SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT", LUA_NATIVE_MISC_SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT);
		MISC.set_function("RESET_DISPATCH_SPAWN_LOCATION", LUA_NATIVE_MISC_RESET_DISPATCH_SPAWN_LOCATION);
		MISC.set_function("SET_DISPATCH_SPAWN_LOCATION", LUA_NATIVE_MISC_SET_DISPATCH_SPAWN_LOCATION);
		MISC.set_function("RESET_DISPATCH_IDEAL_SPAWN_DISTANCE", LUA_NATIVE_MISC_RESET_DISPATCH_IDEAL_SPAWN_DISTANCE);
		MISC.set_function("SET_DISPATCH_IDEAL_SPAWN_DISTANCE", LUA_NATIVE_MISC_SET_DISPATCH_IDEAL_SPAWN_DISTANCE);
		MISC.set_function("RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS", LUA_NATIVE_MISC_RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS);
		MISC.set_function("SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS", LUA_NATIVE_MISC_SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS);
		MISC.set_function("SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER", LUA_NATIVE_MISC_SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER);
		MISC.set_function("ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA", LUA_NATIVE_MISC_ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA);
		MISC.set_function("ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA", LUA_NATIVE_MISC_ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA);
		MISC.set_function("REMOVE_DISPATCH_SPAWN_BLOCKING_AREA", LUA_NATIVE_MISC_REMOVE_DISPATCH_SPAWN_BLOCKING_AREA);
		MISC.set_function("RESET_DISPATCH_SPAWN_BLOCKING_AREAS", LUA_NATIVE_MISC_RESET_DISPATCH_SPAWN_BLOCKING_AREAS);
		MISC.set_function("RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN", LUA_NATIVE_MISC_RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN);
		MISC.set_function("SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN", LUA_NATIVE_MISC_SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN);
		MISC.set_function("ADD_TACTICAL_NAV_MESH_POINT", LUA_NATIVE_MISC_ADD_TACTICAL_NAV_MESH_POINT);
		MISC.set_function("CLEAR_TACTICAL_NAV_MESH_POINTS", LUA_NATIVE_MISC_CLEAR_TACTICAL_NAV_MESH_POINTS);
		MISC.set_function("SET_RIOT_MODE_ENABLED", LUA_NATIVE_MISC_SET_RIOT_MODE_ENABLED);
		MISC.set_function("DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING", LUA_NATIVE_MISC_DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING);
		MISC.set_function("DISPLAY_ONSCREEN_KEYBOARD", LUA_NATIVE_MISC_DISPLAY_ONSCREEN_KEYBOARD);
		MISC.set_function("UPDATE_ONSCREEN_KEYBOARD", LUA_NATIVE_MISC_UPDATE_ONSCREEN_KEYBOARD);
		MISC.set_function("GET_ONSCREEN_KEYBOARD_RESULT", LUA_NATIVE_MISC_GET_ONSCREEN_KEYBOARD_RESULT);
		MISC.set_function("CANCEL_ONSCREEN_KEYBOARD", LUA_NATIVE_MISC_CANCEL_ONSCREEN_KEYBOARD);
		MISC.set_function("NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS", LUA_NATIVE_MISC_NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS);
		MISC.set_function("ACTION_MANAGER_ENABLE_ACTION", LUA_NATIVE_MISC_ACTION_MANAGER_ENABLE_ACTION);
		MISC.set_function("GET_REAL_WORLD_TIME", LUA_NATIVE_MISC_GET_REAL_WORLD_TIME);
		MISC.set_function("SUPRESS_RANDOM_EVENT_THIS_FRAME", LUA_NATIVE_MISC_SUPRESS_RANDOM_EVENT_THIS_FRAME);
		MISC.set_function("SET_EXPLOSIVE_AMMO_THIS_FRAME", LUA_NATIVE_MISC_SET_EXPLOSIVE_AMMO_THIS_FRAME);
		MISC.set_function("SET_FIRE_AMMO_THIS_FRAME", LUA_NATIVE_MISC_SET_FIRE_AMMO_THIS_FRAME);
		MISC.set_function("SET_EXPLOSIVE_MELEE_THIS_FRAME", LUA_NATIVE_MISC_SET_EXPLOSIVE_MELEE_THIS_FRAME);
		MISC.set_function("SET_SUPER_JUMP_THIS_FRAME", LUA_NATIVE_MISC_SET_SUPER_JUMP_THIS_FRAME);
		MISC.set_function("SET_BEAST_JUMP_THIS_FRAME", LUA_NATIVE_MISC_SET_BEAST_JUMP_THIS_FRAME);
		MISC.set_function("SET_FORCED_JUMP_THIS_FRAME", LUA_NATIVE_MISC_SET_FORCED_JUMP_THIS_FRAME);
		MISC.set_function("HAS_GAME_INSTALLED_THIS_SESSION", LUA_NATIVE_MISC_HAS_GAME_INSTALLED_THIS_SESSION);
		MISC.set_function("SET_TICKER_JOHNMARSTON_IS_DONE", LUA_NATIVE_MISC_SET_TICKER_JOHNMARSTON_IS_DONE);
		MISC.set_function("ARE_PROFILE_SETTINGS_VALID", LUA_NATIVE_MISC_ARE_PROFILE_SETTINGS_VALID);
		MISC.set_function("PREVENT_ARREST_STATE_THIS_FRAME", LUA_NATIVE_MISC_PREVENT_ARREST_STATE_THIS_FRAME);
		MISC.set_function("FORCE_GAME_STATE_PLAYING", LUA_NATIVE_MISC_FORCE_GAME_STATE_PLAYING);
		MISC.set_function("SCRIPT_RACE_INIT", LUA_NATIVE_MISC_SCRIPT_RACE_INIT);
		MISC.set_function("SCRIPT_RACE_SHUTDOWN", LUA_NATIVE_MISC_SCRIPT_RACE_SHUTDOWN);
		MISC.set_function("SCRIPT_RACE_PLAYER_HIT_CHECKPOINT", LUA_NATIVE_MISC_SCRIPT_RACE_PLAYER_HIT_CHECKPOINT);
		MISC.set_function("SCRIPT_RACE_GET_PLAYER_SPLIT_TIME", LUA_NATIVE_MISC_SCRIPT_RACE_GET_PLAYER_SPLIT_TIME);
		MISC.set_function("START_END_USER_BENCHMARK", LUA_NATIVE_MISC_START_END_USER_BENCHMARK);
		MISC.set_function("STOP_END_USER_BENCHMARK", LUA_NATIVE_MISC_STOP_END_USER_BENCHMARK);
		MISC.set_function("RESET_END_USER_BENCHMARK", LUA_NATIVE_MISC_RESET_END_USER_BENCHMARK);
		MISC.set_function("SAVE_END_USER_BENCHMARK", LUA_NATIVE_MISC_SAVE_END_USER_BENCHMARK);
		MISC.set_function("UI_STARTED_END_USER_BENCHMARK", LUA_NATIVE_MISC_UI_STARTED_END_USER_BENCHMARK);
		MISC.set_function("LANDING_SCREEN_STARTED_END_USER_BENCHMARK", LUA_NATIVE_MISC_LANDING_SCREEN_STARTED_END_USER_BENCHMARK);
		MISC.set_function("IS_COMMANDLINE_END_USER_BENCHMARK", LUA_NATIVE_MISC_IS_COMMANDLINE_END_USER_BENCHMARK);
		MISC.set_function("GET_BENCHMARK_ITERATIONS", LUA_NATIVE_MISC_GET_BENCHMARK_ITERATIONS);
		MISC.set_function("GET_BENCHMARK_PASS", LUA_NATIVE_MISC_GET_BENCHMARK_PASS);
		MISC.set_function("RESTART_GAME", LUA_NATIVE_MISC_RESTART_GAME);
		MISC.set_function("QUIT_GAME", LUA_NATIVE_MISC_QUIT_GAME);
		MISC.set_function("HAS_ASYNC_INSTALL_FINISHED", LUA_NATIVE_MISC_HAS_ASYNC_INSTALL_FINISHED);
		MISC.set_function("CLEANUP_ASYNC_INSTALL", LUA_NATIVE_MISC_CLEANUP_ASYNC_INSTALL);
		MISC.set_function("PLM_IS_IN_CONSTRAINED_MODE", LUA_NATIVE_MISC_PLM_IS_IN_CONSTRAINED_MODE);
		MISC.set_function("PLM_GET_CONSTRAINED_DURATION_MS", LUA_NATIVE_MISC_PLM_GET_CONSTRAINED_DURATION_MS);
		MISC.set_function("SET_PLAYER_IS_IN_ANIMAL_FORM", LUA_NATIVE_MISC_SET_PLAYER_IS_IN_ANIMAL_FORM);
		MISC.set_function("GET_IS_PLAYER_IN_ANIMAL_FORM", LUA_NATIVE_MISC_GET_IS_PLAYER_IN_ANIMAL_FORM);
		MISC.set_function("SET_PLAYER_IS_REPEATING_A_MISSION", LUA_NATIVE_MISC_SET_PLAYER_IS_REPEATING_A_MISSION);
		MISC.set_function("DISABLE_SCREEN_DIMMING_THIS_FRAME", LUA_NATIVE_MISC_DISABLE_SCREEN_DIMMING_THIS_FRAME);
		MISC.set_function("GET_CITY_DENSITY", LUA_NATIVE_MISC_GET_CITY_DENSITY);
		MISC.set_function("USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE", LUA_NATIVE_MISC_USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE);
		MISC.set_function("SET_CONTENT_ID_INDEX", LUA_NATIVE_MISC_SET_CONTENT_ID_INDEX);
		MISC.set_function("GET_CONTENT_ID_INDEX", LUA_NATIVE_MISC_GET_CONTENT_ID_INDEX);
		MISC.set_function("SET_CONTENT_PROP_TYPE_", LUA_NATIVE_MISC_SET_CONTENT_PROP_TYPE_);
		MISC.set_function("GET_CONTENT_PROP_TYPE_", LUA_NATIVE_MISC_GET_CONTENT_PROP_TYPE_);
	}
}
