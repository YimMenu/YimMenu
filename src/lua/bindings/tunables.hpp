#pragma once
#include "services/tunables/tunables_service.hpp"

namespace lua::tunables
{
	// Lua API: Table
	// Name: tunables
	// Table for manipulating gta tunables.

	// Lua API: Function
	// Table: tunables
	// Name: get_int
	// Param: tunable_name: string: The name of the tunable.
	// Returns: integer: The value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: get_float
	// Param: tunable_name: string: The name of the tunable.
	// Returns: float: The value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: get_bool
	// Param: tunable_name: string: The name of the tunable.
	// Returns: boolean: The value of the given tunable.

	template<typename T>
	static T get(const std::string tunable_name)
	{
		if (auto tunable = big::g_tunables_service->get_tunable<T*>(rage::joaat(tunable_name)))
			return *tunable;

		return T();
	}

	// Lua API: Function
	// Table: tunables
	// Name: set_int
	// Param: tunable_name: string: The name of the tunable.
	// Param: val: integer: The new value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: set_float
	// Param: tunable_name: string: The name of the tunable.
	// Param: val: float: The new value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: set_bool
	// Param: tunable_name: string: The name of the tunable.
	// Param: val: boolean: The new value of the given tunable.

	template<typename T>
	static void set(const std::string tunable_name, T val)
	{
		big::g_tunables_service->set_tunable<T>(rage::joaat(tunable_name), val);
	}

	static void bind(sol::state& state)
	{
		auto ns         = state["tunables"].get_or_create<sol::table>();
		ns["get_int"]   = get<int>;
		ns["get_float"] = get<float>;
		ns["get_bool"]  = get<bool>;
		ns["set_int"]   = set<int>;
		ns["set_float"] = set<float>;
		ns["set_bool"]  = set<bool>;
	}
}