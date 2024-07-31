#pragma once
#include "locals.hpp"
#include "memory.hpp"

namespace lua::locals
{
	// Lua API: Table
	// Name: locals
	// Table for manipulating GTA scripts locals.

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
	// Name: get_uint
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Returns: unsigned integer: The value of the given local.
	static std::uint32_t get_uint(const std::string& script, int index)
	{
		return *get<std::uint32_t*>(script, index);
	}

	// Lua API: Function
	// Table: locals
	// Name: get_float
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Returns: float: The value of the given local.
	static float get_float(const std::string& script, int index)
	{
		return *get<float*>(script, index);
	}

	// Lua API: Function
	// Table: locals
	// Name: get_vec3
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Returns: Vector3: The value of the given local.
	static Vector3 get_vec3(const std::string& script, int index)
	{
		return *get<Vector3*>(script, index);
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
	// Name: set_int
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Param: val: unsigned integer: The new value of the given local.
	static void set_uint(const std::string& script, int index, std::uint32_t val)
	{
		*get<std::uint32_t*>(script, index) = val;
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
	// Name: set_vec3
	// Param: script: string: The name of the script
	// Param: index: index: Index of the script local.
	// Param: val: Vector3: The new value of the given local.
	static void set_vec3(const std::string& script, int index, Vector3 val)
	{
		*get<Vector3*>(script, index) = val;
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

	void bind(sol::state& state)
	{
		auto ns           = state["locals"].get_or_create<sol::table>();
		ns["get_int"]     = get_int;
		ns["get_uint"]    = get_uint;
		ns["get_float"]   = get_float;
		ns["get_vec3"]    = get_vec3;
		ns["set_int"]     = set_int;
		ns["set_uint"]    = set_uint;
		ns["set_float"]   = set_float;
		ns["set_vec3"]    = set_vec3;
		ns["get_pointer"] = get_pointer;
	}
}