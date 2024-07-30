#pragma once

#include "script_function.hpp"
#include "lua/bindings/network.hpp"

namespace lua::scr_function
{
	// Lua API: Table
	// Name: tunables
	// Table for calling GTA script functions.

	// Lua API: function
	// Table: script_function
	// Name: call_void
	// Param: script_name: string: Name of the script.
	// Param: pattern: string: Pattern to scan for within the script.
	// Param _args: table: Arguments to pass to the function.

	// Lua API: function
	// Table: script_function
	// Name: call_int
	// Param: script_name: string: Name of the script.
	// Param: pattern: string: Pattern to scan for within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: integer: The return value of the function.

	// Lua API: function
	// Table: script_function
	// Name: call_float
	// Param: script_name: string: Name of the script.
	// Param: pattern: string: Pattern to scan for within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: float: The return value of the function.

	// Lua API: function
	// Table: script_function
	// Name: call_string
	// Param: script_name: string: Name of the script.
	// Param: pattern: string: Pattern to scan for within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: string: The return value of the function.

	// Lua API: function
	// Table: script_function
	// Name: call_vec3
	// Param: script_name: string: Name of the script.
	// Param: pattern: string: Pattern to scan for within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: Vector3: The return value of the function.

	template<typename T>
	inline T call_function(const std::string& script_name, const std::string& pattern, sol::table _args)
	{
		auto args = convert_sequence<uint64_t>(_args);

		big::script_function lua_instance("add param for this", rage::joaat(script_name), pattern);
		return lua_instance.call<T>(args);
	}

	// Lua API: function
	// Table: script_function
	// Name: call_void
	// Param: script_name: string: Name of the script.
	// Param: ip: integer: Position of the function within the script.
	// Param _args: table: Arguments to pass to the function.

	// Lua API: function
	// Table: script_function
	// Name: call_int
	// Param: script_name: string: Name of the script.
	// Param: ip: integer: Position of the function within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: integer: The return value of the function.

	// Lua API: function
	// Table: script_function
	// Name: call_float
	// Param: script_name: string: Name of the script.
	// Param: ip: integer: Position of the function within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: float: The return value of the function.

	// Lua API: function
	// Table: script_function
	// Name: call_string
	// Param: script_name: string: Name of the script.
	// Param: ip: integer: Position of the function within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: string: The return value of the function.

	// Lua API: function
	// Table: script_function
	// Name: call_vec3
	// Param: script_name: string: Name of the script.
	// Param: ip: integer: Position of the function within the script.
	// Param _args: table: Arguments to pass to the script function.
	// Returns: Vector3: The return value of the function.

	template<typename T>
	inline T call_function_by_ip(const std::string& script_name, uint32_t ip, sol::table _args)
	{
		auto args = convert_sequence<uint64_t>(_args);
	
		return big::script_function::call<T>(rage::joaat(script_name), ip, args);
	}

	void bind(sol::state& state);
}