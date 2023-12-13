#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_DLC_ARE_ANY_CCS_PENDING()
	{
		auto retval = (bool)DLC::ARE_ANY_CCS_PENDING();
		return retval;
	}

	static bool LUA_NATIVE_DLC_IS_DLC_PRESENT(Hash dlcHash)
	{
		auto retval = (bool)DLC::IS_DLC_PRESENT(dlcHash);
		return retval;
	}

	static bool LUA_NATIVE_DLC_DLC_CHECK_CLOUD_DATA_CORRECT()
	{
		auto retval = (bool)DLC::DLC_CHECK_CLOUD_DATA_CORRECT();
		return retval;
	}

	static int LUA_NATIVE_DLC_GET_EXTRACONTENT_CLOUD_RESULT()
	{
		auto retval = DLC::GET_EXTRACONTENT_CLOUD_RESULT();
		return retval;
	}

	static bool LUA_NATIVE_DLC_DLC_CHECK_COMPAT_PACK_CONFIGURATION()
	{
		auto retval = (bool)DLC::DLC_CHECK_COMPAT_PACK_CONFIGURATION();
		return retval;
	}

	static bool LUA_NATIVE_DLC_GET_EVER_HAD_BAD_PACK_ORDER()
	{
		auto retval = (bool)DLC::GET_EVER_HAD_BAD_PACK_ORDER();
		return retval;
	}

	static bool LUA_NATIVE_DLC_GET_IS_LOADING_SCREEN_ACTIVE()
	{
		auto retval = (bool)DLC::GET_IS_LOADING_SCREEN_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_DLC_GET_IS_INITIAL_LOADING_SCREEN_ACTIVE()
	{
		auto retval = (bool)DLC::GET_IS_INITIAL_LOADING_SCREEN_ACTIVE();
		return retval;
	}

	static std::tuple<bool, bool> LUA_NATIVE_DLC_HAS_CLOUD_REQUESTS_FINISHED(bool p0, int unused)
	{
		std::tuple<bool, bool> return_values;
		std::get<0>(return_values) = (bool)DLC::HAS_CLOUD_REQUESTS_FINISHED((BOOL*)&p0, unused);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static void LUA_NATIVE_DLC_ON_ENTER_SP()
	{
		DLC::ON_ENTER_SP();
	}

	static void LUA_NATIVE_DLC_ON_ENTER_MP()
	{
		DLC::ON_ENTER_MP();
	}

	void init_native_binding_DLC(sol::state& L)
	{
		auto DLC = L["DLC"].get_or_create<sol::table>();
		DLC.set_function("ARE_ANY_CCS_PENDING", LUA_NATIVE_DLC_ARE_ANY_CCS_PENDING);
		DLC.set_function("IS_DLC_PRESENT", LUA_NATIVE_DLC_IS_DLC_PRESENT);
		DLC.set_function("DLC_CHECK_CLOUD_DATA_CORRECT", LUA_NATIVE_DLC_DLC_CHECK_CLOUD_DATA_CORRECT);
		DLC.set_function("GET_EXTRACONTENT_CLOUD_RESULT", LUA_NATIVE_DLC_GET_EXTRACONTENT_CLOUD_RESULT);
		DLC.set_function("DLC_CHECK_COMPAT_PACK_CONFIGURATION", LUA_NATIVE_DLC_DLC_CHECK_COMPAT_PACK_CONFIGURATION);
		DLC.set_function("GET_EVER_HAD_BAD_PACK_ORDER", LUA_NATIVE_DLC_GET_EVER_HAD_BAD_PACK_ORDER);
		DLC.set_function("GET_IS_LOADING_SCREEN_ACTIVE", LUA_NATIVE_DLC_GET_IS_LOADING_SCREEN_ACTIVE);
		DLC.set_function("GET_IS_INITIAL_LOADING_SCREEN_ACTIVE", LUA_NATIVE_DLC_GET_IS_INITIAL_LOADING_SCREEN_ACTIVE);
		DLC.set_function("HAS_CLOUD_REQUESTS_FINISHED", LUA_NATIVE_DLC_HAS_CLOUD_REQUESTS_FINISHED);
		DLC.set_function("ON_ENTER_SP", LUA_NATIVE_DLC_ON_ENTER_SP);
		DLC.set_function("ON_ENTER_MP", LUA_NATIVE_DLC_ON_ENTER_MP);
	}
}
