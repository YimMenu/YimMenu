#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static ScrHandle LUA_NATIVE_ITEMSET_CREATE_ITEMSET(bool p0)
	{
		auto retval = ITEMSET::CREATE_ITEMSET(p0);
		return retval;
	}

	static void LUA_NATIVE_ITEMSET_DESTROY_ITEMSET(ScrHandle itemset)
	{
		ITEMSET::DESTROY_ITEMSET(itemset);
	}

	static bool LUA_NATIVE_ITEMSET_IS_ITEMSET_VALID(ScrHandle itemset)
	{
		auto retval = (bool)ITEMSET::IS_ITEMSET_VALID(itemset);
		return retval;
	}

	static bool LUA_NATIVE_ITEMSET_ADD_TO_ITEMSET(ScrHandle item, ScrHandle itemset)
	{
		auto retval = (bool)ITEMSET::ADD_TO_ITEMSET(item, itemset);
		return retval;
	}

	static void LUA_NATIVE_ITEMSET_REMOVE_FROM_ITEMSET(ScrHandle item, ScrHandle itemset)
	{
		ITEMSET::REMOVE_FROM_ITEMSET(item, itemset);
	}

	static int LUA_NATIVE_ITEMSET_GET_ITEMSET_SIZE(ScrHandle itemset)
	{
		auto retval = ITEMSET::GET_ITEMSET_SIZE(itemset);
		return retval;
	}

	static ScrHandle LUA_NATIVE_ITEMSET_GET_INDEXED_ITEM_IN_ITEMSET(int index, ScrHandle itemset)
	{
		auto retval = ITEMSET::GET_INDEXED_ITEM_IN_ITEMSET(index, itemset);
		return retval;
	}

	static bool LUA_NATIVE_ITEMSET_IS_IN_ITEMSET(ScrHandle item, ScrHandle itemset)
	{
		auto retval = (bool)ITEMSET::IS_IN_ITEMSET(item, itemset);
		return retval;
	}

	static void LUA_NATIVE_ITEMSET_CLEAN_ITEMSET(ScrHandle itemset)
	{
		ITEMSET::CLEAN_ITEMSET(itemset);
	}

	void init_native_binding_ITEMSET(sol::state& L)
	{
		auto ITEMSET = L["ITEMSET"].get_or_create<sol::table>();
		ITEMSET.set_function("CREATE_ITEMSET", LUA_NATIVE_ITEMSET_CREATE_ITEMSET);
		ITEMSET.set_function("DESTROY_ITEMSET", LUA_NATIVE_ITEMSET_DESTROY_ITEMSET);
		ITEMSET.set_function("IS_ITEMSET_VALID", LUA_NATIVE_ITEMSET_IS_ITEMSET_VALID);
		ITEMSET.set_function("ADD_TO_ITEMSET", LUA_NATIVE_ITEMSET_ADD_TO_ITEMSET);
		ITEMSET.set_function("REMOVE_FROM_ITEMSET", LUA_NATIVE_ITEMSET_REMOVE_FROM_ITEMSET);
		ITEMSET.set_function("GET_ITEMSET_SIZE", LUA_NATIVE_ITEMSET_GET_ITEMSET_SIZE);
		ITEMSET.set_function("GET_INDEXED_ITEM_IN_ITEMSET", LUA_NATIVE_ITEMSET_GET_INDEXED_ITEM_IN_ITEMSET);
		ITEMSET.set_function("IS_IN_ITEMSET", LUA_NATIVE_ITEMSET_IS_IN_ITEMSET);
		ITEMSET.set_function("CLEAN_ITEMSET", LUA_NATIVE_ITEMSET_CLEAN_ITEMSET);
	}
}
