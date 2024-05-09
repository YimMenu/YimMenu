#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_BRAIN_ADD_SCRIPT_TO_RANDOM_PED(sol::stack_object name, Hash model, float p2, float p3)
	{
		BRAIN::ADD_SCRIPT_TO_RANDOM_PED(name.is<const char*>() ? name.as<const char*>() : nullptr, model, p2, p3);
	}

	static void LUA_NATIVE_BRAIN_REGISTER_OBJECT_SCRIPT_BRAIN(sol::stack_object scriptName, Hash modelHash, int p2, float activationRange, int p4, int p5)
	{
		BRAIN::REGISTER_OBJECT_SCRIPT_BRAIN(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr, modelHash, p2, activationRange, p4, p5);
	}

	static bool LUA_NATIVE_BRAIN_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object object)
	{
		auto retval = (bool)BRAIN::IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(object);
		return retval;
	}

	static void LUA_NATIVE_BRAIN_REGISTER_WORLD_POINT_SCRIPT_BRAIN(sol::stack_object scriptName, float activationRange, int p2)
	{
		BRAIN::REGISTER_WORLD_POINT_SCRIPT_BRAIN(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr, activationRange, p2);
	}

	static bool LUA_NATIVE_BRAIN_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE()
	{
		auto retval = (bool)BRAIN::IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE();
		return retval;
	}

	static void LUA_NATIVE_BRAIN_ENABLE_SCRIPT_BRAIN_SET(int brainSet)
	{
		BRAIN::ENABLE_SCRIPT_BRAIN_SET(brainSet);
	}

	static void LUA_NATIVE_BRAIN_DISABLE_SCRIPT_BRAIN_SET(int brainSet)
	{
		BRAIN::DISABLE_SCRIPT_BRAIN_SET(brainSet);
	}

	static void LUA_NATIVE_BRAIN_REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE()
	{
		BRAIN::REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE();
	}

	static void LUA_NATIVE_BRAIN_REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE()
	{
		BRAIN::REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE();
	}

	static void LUA_NATIVE_BRAIN_REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE(sol::stack_object scriptName)
	{
		BRAIN::REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_BRAIN_REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE(sol::stack_object scriptName)
	{
		BRAIN::REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
	}

	void init_native_binding_BRAIN(sol::state& L)
	{
		auto BRAIN = L["BRAIN"].get_or_create<sol::table>();
		BRAIN.set_function("ADD_SCRIPT_TO_RANDOM_PED", LUA_NATIVE_BRAIN_ADD_SCRIPT_TO_RANDOM_PED);
		BRAIN.set_function("REGISTER_OBJECT_SCRIPT_BRAIN", LUA_NATIVE_BRAIN_REGISTER_OBJECT_SCRIPT_BRAIN);
		BRAIN.set_function("IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE", LUA_NATIVE_BRAIN_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE);
		BRAIN.set_function("REGISTER_WORLD_POINT_SCRIPT_BRAIN", LUA_NATIVE_BRAIN_REGISTER_WORLD_POINT_SCRIPT_BRAIN);
		BRAIN.set_function("IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE", LUA_NATIVE_BRAIN_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE);
		BRAIN.set_function("ENABLE_SCRIPT_BRAIN_SET", LUA_NATIVE_BRAIN_ENABLE_SCRIPT_BRAIN_SET);
		BRAIN.set_function("DISABLE_SCRIPT_BRAIN_SET", LUA_NATIVE_BRAIN_DISABLE_SCRIPT_BRAIN_SET);
		BRAIN.set_function("REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE", LUA_NATIVE_BRAIN_REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE);
		BRAIN.set_function("REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE", LUA_NATIVE_BRAIN_REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE);
		BRAIN.set_function("REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE", LUA_NATIVE_BRAIN_REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE);
		BRAIN.set_function("REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE", LUA_NATIVE_BRAIN_REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE);
	}
}