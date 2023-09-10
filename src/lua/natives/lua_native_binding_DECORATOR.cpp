#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_DECORATOR_DECOR_SET_TIME(Entity entity, const char* propertyName, int timestamp)
	{
		auto retval = (bool)DECORATOR::DECOR_SET_TIME(entity, propertyName, timestamp);
		return retval;
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_SET_BOOL(Entity entity, const char* propertyName, bool value)
	{
		auto retval = (bool)DECORATOR::DECOR_SET_BOOL(entity, propertyName, value);
		return retval;
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_SET_FLOAT(Entity entity, const char* propertyName, float value)
	{
		auto retval = (bool)DECORATOR::DECOR_SET_FLOAT(entity, propertyName, value);
		return retval;
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_SET_INT(Entity entity, const char* propertyName, int value)
	{
		auto retval = (bool)DECORATOR::DECOR_SET_INT(entity, propertyName, value);
		return retval;
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_GET_BOOL(Entity entity, const char* propertyName)
	{
		auto retval = (bool)DECORATOR::DECOR_GET_BOOL(entity, propertyName);
		return retval;
	}

	static float LUA_NATIVE_DECORATOR_DECOR_GET_FLOAT(Entity entity, const char* propertyName)
	{
		auto retval = DECORATOR::DECOR_GET_FLOAT(entity, propertyName);
		return retval;
	}

	static int LUA_NATIVE_DECORATOR_DECOR_GET_INT(Entity entity, const char* propertyName)
	{
		auto retval = DECORATOR::DECOR_GET_INT(entity, propertyName);
		return retval;
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_EXIST_ON(Entity entity, const char* propertyName)
	{
		auto retval = (bool)DECORATOR::DECOR_EXIST_ON(entity, propertyName);
		return retval;
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_REMOVE(Entity entity, const char* propertyName)
	{
		auto retval = (bool)DECORATOR::DECOR_REMOVE(entity, propertyName);
		return retval;
	}

	static void LUA_NATIVE_DECORATOR_DECOR_REGISTER(const char* propertyName, int type)
	{
		DECORATOR::DECOR_REGISTER(propertyName, type);
	}

	static bool LUA_NATIVE_DECORATOR_DECOR_IS_REGISTERED_AS_TYPE(const char* propertyName, int type)
	{
		auto retval = (bool)DECORATOR::DECOR_IS_REGISTERED_AS_TYPE(propertyName, type);
		return retval;
	}

	static void LUA_NATIVE_DECORATOR_DECOR_REGISTER_LOCK()
	{
		DECORATOR::DECOR_REGISTER_LOCK();
	}

	void init_native_binding_DECORATOR(sol::state& L)
	{
		auto DECORATOR = L["DECORATOR"].get_or_create<sol::table>();
		DECORATOR.set_function("DECOR_SET_TIME", LUA_NATIVE_DECORATOR_DECOR_SET_TIME);
		DECORATOR.set_function("DECOR_SET_BOOL", LUA_NATIVE_DECORATOR_DECOR_SET_BOOL);
		DECORATOR.set_function("DECOR_SET_FLOAT", LUA_NATIVE_DECORATOR_DECOR_SET_FLOAT);
		DECORATOR.set_function("DECOR_SET_INT", LUA_NATIVE_DECORATOR_DECOR_SET_INT);
		DECORATOR.set_function("DECOR_GET_BOOL", LUA_NATIVE_DECORATOR_DECOR_GET_BOOL);
		DECORATOR.set_function("DECOR_GET_FLOAT", LUA_NATIVE_DECORATOR_DECOR_GET_FLOAT);
		DECORATOR.set_function("DECOR_GET_INT", LUA_NATIVE_DECORATOR_DECOR_GET_INT);
		DECORATOR.set_function("DECOR_EXIST_ON", LUA_NATIVE_DECORATOR_DECOR_EXIST_ON);
		DECORATOR.set_function("DECOR_REMOVE", LUA_NATIVE_DECORATOR_DECOR_REMOVE);
		DECORATOR.set_function("DECOR_REGISTER", LUA_NATIVE_DECORATOR_DECOR_REGISTER);
		DECORATOR.set_function("DECOR_IS_REGISTERED_AS_TYPE", LUA_NATIVE_DECORATOR_DECOR_IS_REGISTERED_AS_TYPE);
		DECORATOR.set_function("DECOR_REGISTER_LOCK", LUA_NATIVE_DECORATOR_DECOR_REGISTER_LOCK);
	}
}
