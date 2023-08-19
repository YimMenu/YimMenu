#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_MENU()
	{
		auto retval = (bool)LOADINGSCREEN::LOBBY_AUTO_MULTIPLAYER_MENU();
		return retval;
	}

	static bool LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_FREEMODE()
	{
		auto retval = (bool)LOADINGSCREEN::LOBBY_AUTO_MULTIPLAYER_FREEMODE();
		return retval;
	}

	static void LUA_NATIVE_LOADINGSCREEN_LOBBY_SET_AUTO_MULTIPLAYER(bool toggle)
	{
		LOADINGSCREEN::LOBBY_SET_AUTO_MULTIPLAYER(toggle);
	}

	static bool LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_EVENT()
	{
		auto retval = (bool)LOADINGSCREEN::LOBBY_AUTO_MULTIPLAYER_EVENT();
		return retval;
	}

	static void LUA_NATIVE_LOADINGSCREEN_LOBBY_SET_AUTO_MULTIPLAYER_EVENT(bool toggle)
	{
		LOADINGSCREEN::LOBBY_SET_AUTO_MULTIPLAYER_EVENT(toggle);
	}

	static bool LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB()
	{
		auto retval = (bool)LOADINGSCREEN::LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB();
		return retval;
	}

	static void LUA_NATIVE_LOADINGSCREEN_LOBBY_SET_AUTO_MP_RANDOM_JOB(bool toggle)
	{
		LOADINGSCREEN::LOBBY_SET_AUTO_MP_RANDOM_JOB(toggle);
	}

	static void LUA_NATIVE_LOADINGSCREEN_SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER(bool toggle)
	{
		LOADINGSCREEN::SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER(toggle);
	}

	void init_native_binding_LOADINGSCREEN(sol::state& L)
	{
		auto LOADINGSCREEN = L["LOADINGSCREEN"].get_or_create<sol::table>();
		LOADINGSCREEN.set_function("LOBBY_AUTO_MULTIPLAYER_MENU", LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_MENU);
		LOADINGSCREEN.set_function("LOBBY_AUTO_MULTIPLAYER_FREEMODE", LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_FREEMODE);
		LOADINGSCREEN.set_function("LOBBY_SET_AUTO_MULTIPLAYER", LUA_NATIVE_LOADINGSCREEN_LOBBY_SET_AUTO_MULTIPLAYER);
		LOADINGSCREEN.set_function("LOBBY_AUTO_MULTIPLAYER_EVENT", LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_EVENT);
		LOADINGSCREEN.set_function("LOBBY_SET_AUTO_MULTIPLAYER_EVENT", LUA_NATIVE_LOADINGSCREEN_LOBBY_SET_AUTO_MULTIPLAYER_EVENT);
		LOADINGSCREEN.set_function("LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB", LUA_NATIVE_LOADINGSCREEN_LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB);
		LOADINGSCREEN.set_function("LOBBY_SET_AUTO_MP_RANDOM_JOB", LUA_NATIVE_LOADINGSCREEN_LOBBY_SET_AUTO_MP_RANDOM_JOB);
		LOADINGSCREEN.set_function("SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER", LUA_NATIVE_LOADINGSCREEN_SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER);
	}
}
