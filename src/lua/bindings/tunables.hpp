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
	T get(const std::string tunable_name)
	{
		if (auto tunable = big::g_tunables_service->get_tunable<T*>(rage::joaat(tunable_name)))
			return *tunable;

		return T();
	}

	// Lua API: Function
	// Table: tunables
	// Name: get_int
	// Param: tunable_joaated_value: integer: The joaated value of the tunable.
	// Returns: integer: The value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: get_float
	// Param: tunable_joaated_value: integer: The joaated value of the tunable.
	// Returns: float: The value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: get_bool
	// Param: tunable_joaated_value: integer: The joaated value of the tunable.
	// Returns: boolean: The value of the given tunable.

	template<typename T>
	T get_already_joaated(rage::joaat_t tunable_joaated_value)
	{
		if (auto tunable = big::g_tunables_service->get_tunable<T*>(tunable_joaated_value))
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
	void set(const std::string tunable_name, T val)
	{
		big::g_tunables_service->set_tunable<T>(rage::joaat(tunable_name), val);
	}

	// Lua API: Function
	// Table: tunables
	// Name: set_int
	// Param: tunable_joaated_value: integer: The joaated value of the tunable.
	// Param: val: integer: The new value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: set_float
	// Param: tunable_joaated_value: integer: The joaated value of the tunable.
	// Param: val: float: The new value of the given tunable.

	// Lua API: Function
	// Table: tunables
	// Name: set_bool
	// Param: tunable_joaated_value: integer: The joaated value of the tunable.
	// Param: val: boolean: The new value of the given tunable.

	template<typename T>
	void set_already_joaated(rage::joaat_t tunable_joaated_value, T val)
	{
		big::g_tunables_service->set_tunable<T>(tunable_joaated_value, val);
	}

	void bind(sol::state& state);
}