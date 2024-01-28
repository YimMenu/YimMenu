#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_APP_APP_DATA_VALID()
	{
		auto retval = (bool)APP::APP_DATA_VALID();
		return retval;
	}

	static int LUA_NATIVE_APP_APP_GET_INT(sol::stack_object property)
	{
		auto retval = APP::APP_GET_INT(property.is<const char*>() ? property.as<const char*>() : nullptr);
		return retval;
	}

	static float LUA_NATIVE_APP_APP_GET_FLOAT(sol::stack_object property)
	{
		auto retval = APP::APP_GET_FLOAT(property.is<const char*>() ? property.as<const char*>() : nullptr);
		return retval;
	}

	static const char* LUA_NATIVE_APP_APP_GET_STRING(sol::stack_object property)
	{
		auto retval = APP::APP_GET_STRING(property.is<const char*>() ? property.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_APP_APP_SET_INT(sol::stack_object property, int value)
	{
		APP::APP_SET_INT(property.is<const char*>() ? property.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_APP_APP_SET_FLOAT(sol::stack_object property, float value)
	{
		APP::APP_SET_FLOAT(property.is<const char*>() ? property.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_APP_APP_SET_STRING(sol::stack_object property, sol::stack_object value)
	{
		APP::APP_SET_STRING(property.is<const char*>() ? property.as<const char*>() : nullptr, value.is<const char*>() ? value.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_APP_APP_SET_APP(sol::stack_object appName)
	{
		APP::APP_SET_APP(appName.is<const char*>() ? appName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_APP_APP_SET_BLOCK(sol::stack_object blockName)
	{
		APP::APP_SET_BLOCK(blockName.is<const char*>() ? blockName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_APP_APP_CLEAR_BLOCK()
	{
		APP::APP_CLEAR_BLOCK();
	}

	static void LUA_NATIVE_APP_APP_CLOSE_APP()
	{
		APP::APP_CLOSE_APP();
	}

	static void LUA_NATIVE_APP_APP_CLOSE_BLOCK()
	{
		APP::APP_CLOSE_BLOCK();
	}

	static bool LUA_NATIVE_APP_APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT()
	{
		auto retval = (bool)APP::APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT();
		return retval;
	}

	static bool LUA_NATIVE_APP_APP_HAS_SYNCED_DATA(sol::stack_object appName)
	{
		auto retval = (bool)APP::APP_HAS_SYNCED_DATA(appName.is<const char*>() ? appName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_APP_APP_SAVE_DATA()
	{
		APP::APP_SAVE_DATA();
	}

	static int LUA_NATIVE_APP_APP_GET_DELETED_FILE_STATUS()
	{
		auto retval = APP::APP_GET_DELETED_FILE_STATUS();
		return retval;
	}

	static bool LUA_NATIVE_APP_APP_DELETE_APP_DATA(sol::stack_object appName)
	{
		auto retval = (bool)APP::APP_DELETE_APP_DATA(appName.is<const char*>() ? appName.as<const char*>() : nullptr);
		return retval;
	}

	void init_native_binding_APP(sol::state& L)
	{
		auto APP = L["APP"].get_or_create<sol::table>();
		APP.set_function("APP_DATA_VALID", LUA_NATIVE_APP_APP_DATA_VALID);
		APP.set_function("APP_GET_INT", LUA_NATIVE_APP_APP_GET_INT);
		APP.set_function("APP_GET_FLOAT", LUA_NATIVE_APP_APP_GET_FLOAT);
		APP.set_function("APP_GET_STRING", LUA_NATIVE_APP_APP_GET_STRING);
		APP.set_function("APP_SET_INT", LUA_NATIVE_APP_APP_SET_INT);
		APP.set_function("APP_SET_FLOAT", LUA_NATIVE_APP_APP_SET_FLOAT);
		APP.set_function("APP_SET_STRING", LUA_NATIVE_APP_APP_SET_STRING);
		APP.set_function("APP_SET_APP", LUA_NATIVE_APP_APP_SET_APP);
		APP.set_function("APP_SET_BLOCK", LUA_NATIVE_APP_APP_SET_BLOCK);
		APP.set_function("APP_CLEAR_BLOCK", LUA_NATIVE_APP_APP_CLEAR_BLOCK);
		APP.set_function("APP_CLOSE_APP", LUA_NATIVE_APP_APP_CLOSE_APP);
		APP.set_function("APP_CLOSE_BLOCK", LUA_NATIVE_APP_APP_CLOSE_BLOCK);
		APP.set_function("APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT", LUA_NATIVE_APP_APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT);
		APP.set_function("APP_HAS_SYNCED_DATA", LUA_NATIVE_APP_APP_HAS_SYNCED_DATA);
		APP.set_function("APP_SAVE_DATA", LUA_NATIVE_APP_APP_SAVE_DATA);
		APP.set_function("APP_GET_DELETED_FILE_STATUS", LUA_NATIVE_APP_APP_GET_DELETED_FILE_STATUS);
		APP.set_function("APP_DELETE_APP_DATA", LUA_NATIVE_APP_APP_DELETE_APP_DATA);
	}
}
