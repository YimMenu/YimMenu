#pragma once
#include "memory.hpp"
#include "script_global.hpp"

namespace lua::globals
{
	// Lua API: Table
	// Name: globals
	// Table containing functions for manipulating gta script globals.

	// Lua API: Function
	// Table: globals
	// Name: get_int
	// Param: global: integer: index of the global
	// Returns: integer: value of the global
	// Retrieves an int global value.
	static int get_int(int global)
	{
		return *big::script_global(global).as<int*>();
	}

	// Lua API: Function
	// Table: globals
	// Name: get_uint
	// Param: global: integer: index of the global
	// Returns: integer: value of the global
	// Retrieves an uint global value.
	static std::uint32_t get_uint(int global)
	{
		return *big::script_global(global).as<std::uint32_t*>();
	}

	// Lua API: Function
	// Table: globals
	// Name: get_float
	// Param: global: integer: index of the global
	// Returns: float: value of the global
	// Retrieves a float global value.
	static float get_float(int global)
	{
		return *big::script_global(global).as<float*>();
	}

	// Lua API: Function
	// Table: globals
	// Name: get_string
	// Param: global: integer: index of the global
	// Returns: string: value of the global
	// Retrieves a string global value.
	static std::string get_string(int global)
	{
		return std::string(big::script_global(global).as<char*>());
	}

	// Lua API: Function
	// Table: globals
	// Name: get_vec3
	// Param: global: integer: index of the global
	// Returns: Vector3: value of the global
	// Retrieves a Vector3 global value.
	static Vector3 get_vec3(int global)
	{
		return *big::script_global(global).as<Vector3*>();
	}

	// Lua API: Function
	// Table: globals
	// Name: set_int
	// Param: global: integer: index of the global
	// Param: val: integer: new value for the global
	// Sets an int global value.
	static void set_int(int global, int val)
	{
		*big::script_global(global).as<int*>() = val;
	}

	// Lua API: Function
	// Table: globals
	// Name: set_uint
	// Param: global: integer: index of the global
	// Param: val: integer: new value for the global
	// Sets an uint global value.
	static void set_uint(int global, std::uint32_t val)
	{
		*big::script_global(global).as<std::uint32_t*>() = val;
	}

	// Lua API: Function
	// Table: globals
	// Name: set_float
	// Param: global: integer: index of the global
	// Param: val: float: new value for the global
	// Sets a float global value.
	static void set_float(int global, float val)
	{
		*big::script_global(global).as<float*>() = val;
	}

	// Lua API: Function
	// Table: globals
	// Name: set_string
	// Param: global: integer: index of the global
	// Param: str: string: new value for the global
	// Sets a string global value.
	static void set_string(int global, const std::string& str, int max_length)
	{
		strncpy(big::script_global(global).as<char*>(), str.data(), max_length);
	}

	// Lua API: Function
	// Table: globals
	// Name: set_vec3
	// Param: global: integer: index of the global
	// Param: param: Vector3: new value for the global
	// Sets a Vector3 global value.
	static void set_vec3(int global, Vector3 param)
	{
		*big::script_global(global).as<Vector3*>() = param;
	}

	// Lua API: Function
	// Table: globals
	// Name: get_pointer
	// Param: global: integer: index of the global
	// Returns: pointer: value of the global
	// Retrieves a pointer global.
	static memory::pointer get_pointer(int global)
	{
		return memory::pointer((uint64_t)big::script_global(global).as<void*>());
	}

	void bind(sol::state& state)
	{
		auto ns           = state["globals"].get_or_create<sol::table>();
		ns["get_int"]     = get_int;
		ns["get_uint"]    = get_uint;
		ns["get_float"]   = get_float;
		ns["get_string"]  = get_string;
		ns["get_vec3"]    = get_vec3;
		ns["set_int"]     = set_int;
		ns["set_uint"]    = set_uint;
		ns["set_float"]   = set_float;
		ns["set_string"]  = set_string;
		ns["set_vec3"]    = set_vec3;
		ns["get_pointer"] = get_pointer;
	}
}