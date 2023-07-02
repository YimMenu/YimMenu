#pragma once
#include "gta_util.hpp"
#include "memory.hpp"
#include "script_local.hpp"

namespace lua::locals
{
	// Lua API: Table
	// Name: locals
	// Table for manipulating GTA scripts locals.

	template<typename T>
	inline T get(const std::string& script, int index)
	{
		static std::remove_pointer_t<T> null{};
		auto thread = big::gta_util::find_script_thread(rage::joaat(script));
		if (thread)
			return big::script_local(thread->m_stack, index).as<T>();

		return &null;
	}

	// Lua API: Function
	// Table: locals
	// Name: get_int
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Returns: integer: The value of the given local.
	static int get_int(const std::string& script, int index)
	{
		return *get<int*>(script, index);
	}

	// Lua API: Function
	// Table: locals
	// Name: get_float
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Returns: float: The value of the given local.
	static int get_float(const std::string& script, int index)
	{
		return *get<float*>(script, index);
	}
	
	// Lua API: Function
	// Table: locals
	// Name: set_int
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Param: val: integer: The new value of the given local.
	static void set_int(const std::string& script, int index, int val)
	{
		*get<int*>(script, index) = val;
	}

	// Lua API: Function
	// Table: locals
	// Name: set_float
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Param: val: float: The new value of the given local.
	static void set_float(const std::string& script, int index, float val)
	{
		*get<float*>(script, index) = val;
	}

	// Lua API: Function
	// Table: locals
	// Name: get_pointer
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Returns: pointer: The pointer to the given local.
	static memory::pointer get_pointer(const std::string& script, int index)
	{
		return memory::pointer((uint64_t)get<int*>(script, index));
	}

	static void bind(sol::state& state)
	{
		auto ns           = state["locals"].get_or_create<sol::table>();
		ns["get_int"]     = get_int;
		ns["get_float"]   = get_float;
		ns["set_int"]     = set_int;
		ns["set_float"]   = set_float;
		ns["get_pointer"] = get_pointer;
	}
}