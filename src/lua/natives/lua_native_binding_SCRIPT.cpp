#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_SCRIPT_REQUEST_SCRIPT(sol::stack_object scriptName)
	{
		SCRIPT::REQUEST_SCRIPT(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_SCRIPT_SET_SCRIPT_AS_NO_LONGER_NEEDED(sol::stack_object scriptName)
	{
		SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_SCRIPT_HAS_SCRIPT_LOADED(sol::stack_object scriptName)
	{
		auto retval = (bool)SCRIPT::HAS_SCRIPT_LOADED(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_SCRIPT_DOES_SCRIPT_EXIST(sol::stack_object scriptName)
	{
		auto retval = (bool)SCRIPT::DOES_SCRIPT_EXIST(scriptName.is<const char*>() ? scriptName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_REQUEST_SCRIPT_WITH_NAME_HASH(Hash scriptHash)
	{
		SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(scriptHash);
	}

	static void LUA_NATIVE_SCRIPT_SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(Hash scriptHash)
	{
		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(scriptHash);
	}

	static bool LUA_NATIVE_SCRIPT_HAS_SCRIPT_WITH_NAME_HASH_LOADED(Hash scriptHash)
	{
		auto retval = (bool)SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(scriptHash);
		return retval;
	}

	static bool LUA_NATIVE_SCRIPT_DOES_SCRIPT_WITH_NAME_HASH_EXIST(Hash scriptHash)
	{
		auto retval = (bool)SCRIPT::DOES_SCRIPT_WITH_NAME_HASH_EXIST(scriptHash);
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_TERMINATE_THREAD(int threadId)
	{
		SCRIPT::TERMINATE_THREAD(threadId);
	}

	static bool LUA_NATIVE_SCRIPT_IS_THREAD_ACTIVE(int threadId)
	{
		auto retval = (bool)SCRIPT::IS_THREAD_ACTIVE(threadId);
		return retval;
	}

	static const char* LUA_NATIVE_SCRIPT_GET_NAME_OF_SCRIPT_WITH_THIS_ID(int threadId)
	{
		auto retval = SCRIPT::GET_NAME_OF_SCRIPT_WITH_THIS_ID(threadId);
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_SCRIPT_THREAD_ITERATOR_RESET()
	{
		SCRIPT::SCRIPT_THREAD_ITERATOR_RESET();
	}

	static int LUA_NATIVE_SCRIPT_SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID()
	{
		auto retval = SCRIPT::SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID();
		return retval;
	}

	static int LUA_NATIVE_SCRIPT_GET_ID_OF_THIS_THREAD()
	{
		auto retval = SCRIPT::GET_ID_OF_THIS_THREAD();
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_TERMINATE_THIS_THREAD()
	{
		SCRIPT::TERMINATE_THIS_THREAD();
	}

	static int LUA_NATIVE_SCRIPT_GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(Hash scriptHash)
	{
		auto retval = SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(scriptHash);
		return retval;
	}

	static const char* LUA_NATIVE_SCRIPT_GET_THIS_SCRIPT_NAME()
	{
		auto retval = SCRIPT::GET_THIS_SCRIPT_NAME();
		return retval;
	}

	static Hash LUA_NATIVE_SCRIPT_GET_HASH_OF_THIS_SCRIPT_NAME()
	{
		auto retval = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
		return retval;
	}

	static int LUA_NATIVE_SCRIPT_GET_NUMBER_OF_EVENTS(int eventGroup)
	{
		auto retval = SCRIPT::GET_NUMBER_OF_EVENTS(eventGroup);
		return retval;
	}

	static bool LUA_NATIVE_SCRIPT_GET_EVENT_EXISTS(int eventGroup, int eventIndex)
	{
		auto retval = (bool)SCRIPT::GET_EVENT_EXISTS(eventGroup, eventIndex);
		return retval;
	}

	static int LUA_NATIVE_SCRIPT_GET_EVENT_AT_INDEX(int eventGroup, int eventIndex)
	{
		auto retval = SCRIPT::GET_EVENT_AT_INDEX(eventGroup, eventIndex);
		return retval;
	}

	static bool LUA_NATIVE_SCRIPT_GET_EVENT_DATA(int eventGroup, int eventIndex, uintptr_t eventData, int eventDataSize)
	{
		auto retval = (bool)SCRIPT::GET_EVENT_DATA(eventGroup, eventIndex, (Any*)eventData, eventDataSize);
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_TRIGGER_SCRIPT_EVENT(int eventGroup, uintptr_t eventData, int eventDataSize, int playerBits)
	{
		SCRIPT::TRIGGER_SCRIPT_EVENT(eventGroup, (Any*)eventData, eventDataSize, playerBits);
	}

	static void LUA_NATIVE_SCRIPT_SHUTDOWN_LOADING_SCREEN()
	{
		SCRIPT::SHUTDOWN_LOADING_SCREEN();
	}

	static void LUA_NATIVE_SCRIPT_SET_NO_LOADING_SCREEN(bool toggle)
	{
		SCRIPT::SET_NO_LOADING_SCREEN(toggle);
	}

	static bool LUA_NATIVE_SCRIPT_GET_NO_LOADING_SCREEN()
	{
		auto retval = (bool)SCRIPT::GET_NO_LOADING_SCREEN();
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_COMMIT_TO_LOADINGSCREEN_SELCTION()
	{
		SCRIPT::COMMIT_TO_LOADINGSCREEN_SELCTION();
	}

	static bool LUA_NATIVE_SCRIPT_BG_IS_EXITFLAG_SET()
	{
		auto retval = (bool)SCRIPT::BG_IS_EXITFLAG_SET();
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_BG_SET_EXITFLAG_RESPONSE()
	{
		SCRIPT::BG_SET_EXITFLAG_RESPONSE();
	}

	static void LUA_NATIVE_SCRIPT_BG_START_CONTEXT_HASH(Hash contextHash)
	{
		SCRIPT::BG_START_CONTEXT_HASH(contextHash);
	}

	static void LUA_NATIVE_SCRIPT_BG_END_CONTEXT_HASH(Hash contextHash)
	{
		SCRIPT::BG_END_CONTEXT_HASH(contextHash);
	}

	static void LUA_NATIVE_SCRIPT_BG_START_CONTEXT(sol::stack_object contextName)
	{
		SCRIPT::BG_START_CONTEXT(contextName.is<const char*>() ? contextName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_SCRIPT_BG_END_CONTEXT(sol::stack_object contextName)
	{
		SCRIPT::BG_END_CONTEXT(contextName.is<const char*>() ? contextName.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_SCRIPT_BG_DOES_LAUNCH_PARAM_EXIST(int scriptIndex, sol::stack_object p1)
	{
		auto retval = (bool)SCRIPT::BG_DOES_LAUNCH_PARAM_EXIST(scriptIndex, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_SCRIPT_BG_GET_LAUNCH_PARAM_VALUE(int scriptIndex, sol::stack_object p1)
	{
		auto retval = SCRIPT::BG_GET_LAUNCH_PARAM_VALUE(scriptIndex, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_SCRIPT_BG_GET_SCRIPT_ID_FROM_NAME_HASH(Hash p0)
	{
		auto retval = SCRIPT::BG_GET_SCRIPT_ID_FROM_NAME_HASH(p0);
		return retval;
	}

	static void LUA_NATIVE_SCRIPT_SEND_TU_SCRIPT_EVENT_NEW_(int eventGroup, uintptr_t eventData, int eventDataSize, int playerBits, Hash eventType)
	{
		SCRIPT::_SEND_TU_SCRIPT_EVENT_NEW(eventGroup, (Any*)eventData, eventDataSize, playerBits, eventType);
	}

	void init_native_binding_SCRIPT(sol::state& L)
	{
		auto SCRIPT = L["SCRIPT"].get_or_create<sol::table>();
		SCRIPT.set_function("REQUEST_SCRIPT", LUA_NATIVE_SCRIPT_REQUEST_SCRIPT);
		SCRIPT.set_function("SET_SCRIPT_AS_NO_LONGER_NEEDED", LUA_NATIVE_SCRIPT_SET_SCRIPT_AS_NO_LONGER_NEEDED);
		SCRIPT.set_function("HAS_SCRIPT_LOADED", LUA_NATIVE_SCRIPT_HAS_SCRIPT_LOADED);
		SCRIPT.set_function("DOES_SCRIPT_EXIST", LUA_NATIVE_SCRIPT_DOES_SCRIPT_EXIST);
		SCRIPT.set_function("REQUEST_SCRIPT_WITH_NAME_HASH", LUA_NATIVE_SCRIPT_REQUEST_SCRIPT_WITH_NAME_HASH);
		SCRIPT.set_function("SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED", LUA_NATIVE_SCRIPT_SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED);
		SCRIPT.set_function("HAS_SCRIPT_WITH_NAME_HASH_LOADED", LUA_NATIVE_SCRIPT_HAS_SCRIPT_WITH_NAME_HASH_LOADED);
		SCRIPT.set_function("DOES_SCRIPT_WITH_NAME_HASH_EXIST", LUA_NATIVE_SCRIPT_DOES_SCRIPT_WITH_NAME_HASH_EXIST);
		SCRIPT.set_function("TERMINATE_THREAD", LUA_NATIVE_SCRIPT_TERMINATE_THREAD);
		SCRIPT.set_function("IS_THREAD_ACTIVE", LUA_NATIVE_SCRIPT_IS_THREAD_ACTIVE);
		SCRIPT.set_function("GET_NAME_OF_SCRIPT_WITH_THIS_ID", LUA_NATIVE_SCRIPT_GET_NAME_OF_SCRIPT_WITH_THIS_ID);
		SCRIPT.set_function("SCRIPT_THREAD_ITERATOR_RESET", LUA_NATIVE_SCRIPT_SCRIPT_THREAD_ITERATOR_RESET);
		SCRIPT.set_function("SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID", LUA_NATIVE_SCRIPT_SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID);
		SCRIPT.set_function("GET_ID_OF_THIS_THREAD", LUA_NATIVE_SCRIPT_GET_ID_OF_THIS_THREAD);
		SCRIPT.set_function("TERMINATE_THIS_THREAD", LUA_NATIVE_SCRIPT_TERMINATE_THIS_THREAD);
		SCRIPT.set_function("GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH", LUA_NATIVE_SCRIPT_GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		SCRIPT.set_function("GET_THIS_SCRIPT_NAME", LUA_NATIVE_SCRIPT_GET_THIS_SCRIPT_NAME);
		SCRIPT.set_function("GET_HASH_OF_THIS_SCRIPT_NAME", LUA_NATIVE_SCRIPT_GET_HASH_OF_THIS_SCRIPT_NAME);
		SCRIPT.set_function("GET_NUMBER_OF_EVENTS", LUA_NATIVE_SCRIPT_GET_NUMBER_OF_EVENTS);
		SCRIPT.set_function("GET_EVENT_EXISTS", LUA_NATIVE_SCRIPT_GET_EVENT_EXISTS);
		SCRIPT.set_function("GET_EVENT_AT_INDEX", LUA_NATIVE_SCRIPT_GET_EVENT_AT_INDEX);
		SCRIPT.set_function("GET_EVENT_DATA", LUA_NATIVE_SCRIPT_GET_EVENT_DATA);
		SCRIPT.set_function("TRIGGER_SCRIPT_EVENT", LUA_NATIVE_SCRIPT_TRIGGER_SCRIPT_EVENT);
		SCRIPT.set_function("SHUTDOWN_LOADING_SCREEN", LUA_NATIVE_SCRIPT_SHUTDOWN_LOADING_SCREEN);
		SCRIPT.set_function("SET_NO_LOADING_SCREEN", LUA_NATIVE_SCRIPT_SET_NO_LOADING_SCREEN);
		SCRIPT.set_function("GET_NO_LOADING_SCREEN", LUA_NATIVE_SCRIPT_GET_NO_LOADING_SCREEN);
		SCRIPT.set_function("COMMIT_TO_LOADINGSCREEN_SELCTION", LUA_NATIVE_SCRIPT_COMMIT_TO_LOADINGSCREEN_SELCTION);
		SCRIPT.set_function("BG_IS_EXITFLAG_SET", LUA_NATIVE_SCRIPT_BG_IS_EXITFLAG_SET);
		SCRIPT.set_function("BG_SET_EXITFLAG_RESPONSE", LUA_NATIVE_SCRIPT_BG_SET_EXITFLAG_RESPONSE);
		SCRIPT.set_function("BG_START_CONTEXT_HASH", LUA_NATIVE_SCRIPT_BG_START_CONTEXT_HASH);
		SCRIPT.set_function("BG_END_CONTEXT_HASH", LUA_NATIVE_SCRIPT_BG_END_CONTEXT_HASH);
		SCRIPT.set_function("BG_START_CONTEXT", LUA_NATIVE_SCRIPT_BG_START_CONTEXT);
		SCRIPT.set_function("BG_END_CONTEXT", LUA_NATIVE_SCRIPT_BG_END_CONTEXT);
		SCRIPT.set_function("BG_DOES_LAUNCH_PARAM_EXIST", LUA_NATIVE_SCRIPT_BG_DOES_LAUNCH_PARAM_EXIST);
		SCRIPT.set_function("BG_GET_LAUNCH_PARAM_VALUE", LUA_NATIVE_SCRIPT_BG_GET_LAUNCH_PARAM_VALUE);
		SCRIPT.set_function("BG_GET_SCRIPT_ID_FROM_NAME_HASH", LUA_NATIVE_SCRIPT_BG_GET_SCRIPT_ID_FROM_NAME_HASH);
		SCRIPT.set_function("SEND_TU_SCRIPT_EVENT_NEW_", LUA_NATIVE_SCRIPT_SEND_TU_SCRIPT_EVENT_NEW_);
	}
}
