#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static std::tuple<bool, float> LUA_NATIVE_WATER_GET_WATER_HEIGHT(float x, float y, float z, float height)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)WATER::GET_WATER_HEIGHT(x, y, z, &height);
		std::get<1>(return_values) = height;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_WATER_GET_WATER_HEIGHT_NO_WAVES(float x, float y, float z, float height)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)WATER::GET_WATER_HEIGHT_NO_WAVES(x, y, z, &height);
		std::get<1>(return_values) = height;

		return return_values;
	}

	static std::tuple<bool, Vector3> LUA_NATIVE_WATER_TEST_PROBE_AGAINST_WATER(float x1, float y1, float z1, float x2, float y2, float z2, Vector3 result)
	{
		std::tuple<bool, Vector3> return_values;
		std::get<0>(return_values) = (bool)WATER::TEST_PROBE_AGAINST_WATER(x1, y1, z1, x2, y2, z2, &result);
		std::get<1>(return_values) = result;

		return return_values;
	}

	static std::tuple<int, float> LUA_NATIVE_WATER_TEST_PROBE_AGAINST_ALL_WATER(float x1, float y1, float z1, float x2, float y2, float z2, int flags, float waterHeight)
	{
		std::tuple<int, float> return_values;
		std::get<0>(return_values) = WATER::TEST_PROBE_AGAINST_ALL_WATER(x1, y1, z1, x2, y2, z2, flags, &waterHeight);
		std::get<1>(return_values) = waterHeight;

		return return_values;
	}

	static std::tuple<int, float> LUA_NATIVE_WATER_TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(float x, float y, float z, int flags, float waterHeight)
	{
		std::tuple<int, float> return_values;
		std::get<0>(return_values) = WATER::TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(x, y, z, flags, &waterHeight);
		std::get<1>(return_values) = waterHeight;

		return return_values;
	}

	static void LUA_NATIVE_WATER_MODIFY_WATER(float x, float y, float radius, float height)
	{
		WATER::MODIFY_WATER(x, y, radius, height);
	}

	static int LUA_NATIVE_WATER_ADD_EXTRA_CALMING_QUAD(float xLow, float yLow, float xHigh, float yHigh, float height)
	{
		auto retval = WATER::ADD_EXTRA_CALMING_QUAD(xLow, yLow, xHigh, yHigh, height);
		return retval;
	}

	static void LUA_NATIVE_WATER_REMOVE_EXTRA_CALMING_QUAD(int calmingQuad)
	{
		WATER::REMOVE_EXTRA_CALMING_QUAD(calmingQuad);
	}

	static void LUA_NATIVE_WATER_SET_DEEP_OCEAN_SCALER(float intensity)
	{
		WATER::SET_DEEP_OCEAN_SCALER(intensity);
	}

	static float LUA_NATIVE_WATER_GET_DEEP_OCEAN_SCALER()
	{
		auto retval = WATER::GET_DEEP_OCEAN_SCALER();
		return retval;
	}

	static void LUA_NATIVE_WATER_SET_CALMED_WAVE_HEIGHT_SCALER(float height)
	{
		WATER::SET_CALMED_WAVE_HEIGHT_SCALER(height);
	}

	static void LUA_NATIVE_WATER_RESET_DEEP_OCEAN_SCALER()
	{
		WATER::RESET_DEEP_OCEAN_SCALER();
	}

	void init_native_binding_WATER(sol::state& L)
	{
		auto WATER = L["WATER"].get_or_create<sol::table>();
		WATER.set_function("GET_WATER_HEIGHT", LUA_NATIVE_WATER_GET_WATER_HEIGHT);
		WATER.set_function("GET_WATER_HEIGHT_NO_WAVES", LUA_NATIVE_WATER_GET_WATER_HEIGHT_NO_WAVES);
		WATER.set_function("TEST_PROBE_AGAINST_WATER", LUA_NATIVE_WATER_TEST_PROBE_AGAINST_WATER);
		WATER.set_function("TEST_PROBE_AGAINST_ALL_WATER", LUA_NATIVE_WATER_TEST_PROBE_AGAINST_ALL_WATER);
		WATER.set_function("TEST_VERTICAL_PROBE_AGAINST_ALL_WATER", LUA_NATIVE_WATER_TEST_VERTICAL_PROBE_AGAINST_ALL_WATER);
		WATER.set_function("MODIFY_WATER", LUA_NATIVE_WATER_MODIFY_WATER);
		WATER.set_function("ADD_EXTRA_CALMING_QUAD", LUA_NATIVE_WATER_ADD_EXTRA_CALMING_QUAD);
		WATER.set_function("REMOVE_EXTRA_CALMING_QUAD", LUA_NATIVE_WATER_REMOVE_EXTRA_CALMING_QUAD);
		WATER.set_function("SET_DEEP_OCEAN_SCALER", LUA_NATIVE_WATER_SET_DEEP_OCEAN_SCALER);
		WATER.set_function("GET_DEEP_OCEAN_SCALER", LUA_NATIVE_WATER_GET_DEEP_OCEAN_SCALER);
		WATER.set_function("SET_CALMED_WAVE_HEIGHT_SCALER", LUA_NATIVE_WATER_SET_CALMED_WAVE_HEIGHT_SCALER);
		WATER.set_function("RESET_DEEP_OCEAN_SCALER", LUA_NATIVE_WATER_RESET_DEEP_OCEAN_SCALER);
	}
}
