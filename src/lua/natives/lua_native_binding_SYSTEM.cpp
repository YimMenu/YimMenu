#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_SYSTEM_WAIT(int ms)
	{
		SYSTEM::WAIT(ms);
	}

	static int LUA_NATIVE_SYSTEM_START_NEW_SCRIPT(sol::stack_object scriptName, int stackSize)
	{
		auto retval = SYSTEM::START_NEW_SCRIPT(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr, stackSize);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_START_NEW_SCRIPT_WITH_ARGS(sol::stack_object scriptName, uintptr_t args, int argCount, int stackSize)
	{
		auto retval = SYSTEM::START_NEW_SCRIPT_WITH_ARGS(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr, (Any*)args, argCount, stackSize);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_START_NEW_SCRIPT_WITH_NAME_HASH(Hash scriptHash, int stackSize)
	{
		auto retval = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(scriptHash, stackSize);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(Hash scriptHash, uintptr_t args, int argCount, int stackSize)
	{
		auto retval = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(scriptHash, (Any*)args, argCount, stackSize);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_TIMERA()
	{
		auto retval = SYSTEM::TIMERA();
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_TIMERB()
	{
		auto retval = SYSTEM::TIMERB();
		return retval;
	}

	static void LUA_NATIVE_SYSTEM_SETTIMERA(int value)
	{
		SYSTEM::SETTIMERA(value);
	}

	static void LUA_NATIVE_SYSTEM_SETTIMERB(int value)
	{
		SYSTEM::SETTIMERB(value);
	}

	static float LUA_NATIVE_SYSTEM_TIMESTEP()
	{
		auto retval = SYSTEM::TIMESTEP();
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_SIN(float value)
	{
		auto retval = SYSTEM::SIN(value);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_COS(float value)
	{
		auto retval = SYSTEM::COS(value);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_SQRT(float value)
	{
		auto retval = SYSTEM::SQRT(value);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_POW(float base, float exponent)
	{
		auto retval = SYSTEM::POW(base, exponent);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_LOG10(float value)
	{
		auto retval = SYSTEM::LOG10(value);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_VMAG(float x, float y, float z)
	{
		auto retval = SYSTEM::VMAG(x, y, z);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_VMAG2(float x, float y, float z)
	{
		auto retval = SYSTEM::VMAG2(x, y, z);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_VDIST(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = SYSTEM::VDIST(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_VDIST2(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		auto retval = SYSTEM::VDIST2(x1, y1, z1, x2, y2, z2);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_SHIFT_LEFT(int value, int bitShift)
	{
		auto retval = SYSTEM::SHIFT_LEFT(value, bitShift);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_SHIFT_RIGHT(int value, int bitShift)
	{
		auto retval = SYSTEM::SHIFT_RIGHT(value, bitShift);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_FLOOR(float value)
	{
		auto retval = SYSTEM::FLOOR(value);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_CEIL(float value)
	{
		auto retval = SYSTEM::CEIL(value);
		return retval;
	}

	static int LUA_NATIVE_SYSTEM_ROUND(float value)
	{
		auto retval = SYSTEM::ROUND(value);
		return retval;
	}

	static float LUA_NATIVE_SYSTEM_TO_FLOAT(int value)
	{
		auto retval = SYSTEM::TO_FLOAT(value);
		return retval;
	}

	static void LUA_NATIVE_SYSTEM_SET_THIS_THREAD_PRIORITY(int priority)
	{
		SYSTEM::SET_THIS_THREAD_PRIORITY(priority);
	}

	void init_native_binding_SYSTEM(sol::state& L)
	{
		auto SYSTEM = L["SYSTEM"].get_or_create<sol::table>();
		SYSTEM.set_function("WAIT", LUA_NATIVE_SYSTEM_WAIT);
		SYSTEM.set_function("START_NEW_SCRIPT", LUA_NATIVE_SYSTEM_START_NEW_SCRIPT);
		SYSTEM.set_function("START_NEW_SCRIPT_WITH_ARGS", LUA_NATIVE_SYSTEM_START_NEW_SCRIPT_WITH_ARGS);
		SYSTEM.set_function("START_NEW_SCRIPT_WITH_NAME_HASH", LUA_NATIVE_SYSTEM_START_NEW_SCRIPT_WITH_NAME_HASH);
		SYSTEM.set_function("START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS", LUA_NATIVE_SYSTEM_START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS);
		SYSTEM.set_function("TIMERA", LUA_NATIVE_SYSTEM_TIMERA);
		SYSTEM.set_function("TIMERB", LUA_NATIVE_SYSTEM_TIMERB);
		SYSTEM.set_function("SETTIMERA", LUA_NATIVE_SYSTEM_SETTIMERA);
		SYSTEM.set_function("SETTIMERB", LUA_NATIVE_SYSTEM_SETTIMERB);
		SYSTEM.set_function("TIMESTEP", LUA_NATIVE_SYSTEM_TIMESTEP);
		SYSTEM.set_function("SIN", LUA_NATIVE_SYSTEM_SIN);
		SYSTEM.set_function("COS", LUA_NATIVE_SYSTEM_COS);
		SYSTEM.set_function("SQRT", LUA_NATIVE_SYSTEM_SQRT);
		SYSTEM.set_function("POW", LUA_NATIVE_SYSTEM_POW);
		SYSTEM.set_function("LOG10", LUA_NATIVE_SYSTEM_LOG10);
		SYSTEM.set_function("VMAG", LUA_NATIVE_SYSTEM_VMAG);
		SYSTEM.set_function("VMAG2", LUA_NATIVE_SYSTEM_VMAG2);
		SYSTEM.set_function("VDIST", LUA_NATIVE_SYSTEM_VDIST);
		SYSTEM.set_function("VDIST2", LUA_NATIVE_SYSTEM_VDIST2);
		SYSTEM.set_function("SHIFT_LEFT", LUA_NATIVE_SYSTEM_SHIFT_LEFT);
		SYSTEM.set_function("SHIFT_RIGHT", LUA_NATIVE_SYSTEM_SHIFT_RIGHT);
		SYSTEM.set_function("FLOOR", LUA_NATIVE_SYSTEM_FLOOR);
		SYSTEM.set_function("CEIL", LUA_NATIVE_SYSTEM_CEIL);
		SYSTEM.set_function("ROUND", LUA_NATIVE_SYSTEM_ROUND);
		SYSTEM.set_function("TO_FLOAT", LUA_NATIVE_SYSTEM_TO_FLOAT);
		SYSTEM.set_function("SET_THIS_THREAD_PRIORITY", LUA_NATIVE_SYSTEM_SET_THIS_THREAD_PRIORITY);
	}
}
