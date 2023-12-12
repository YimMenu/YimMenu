#pragma once

namespace lua::global_table
{
	// Lua API: Table
	// Name: Global Table
	// Custom fields, functions, etc added to The Lua [Global Table](https://www.lua.org/pil/15.4.html).

	// Lua API: Function
	// Table: Global Table
	// Name: joaat
	// Param: str: string: The string that needs to be joaat hashed.
	// Returns: integer: The joaat hashed input string.

	void bind(sol::state& state)
	{
		state["joaat"] = rage::joaat;
	}
}