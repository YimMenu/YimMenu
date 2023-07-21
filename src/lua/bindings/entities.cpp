#pragma once
#include "entities.hpp"

#include "util/pools.hpp"

namespace lua::entities
{
	// Lua API: Table
	// Name: entities
	// Table for manipulating GTA entities.

	// Lua API: Function
	// Table: entities
	// Name: get_all_vehicles_as_handles
	// Returns: table<int, int>: Returns all vehicles as script handles
	static std::vector<Entity> get_all_vehicles_as_handles()
	{
		return big::pools::get_all_vehicles_array();
	}

	// Lua API: Function
	// Table: entities
	// Name: get_all_peds_as_handles
	// Returns: table<int, int>: Returns all peds as script handles
	static std::vector<Entity> get_all_peds_as_handles()
	{
		return big::pools::get_all_peds_array();
	}

	// Lua API: Function
	// Table: entities
	// Name: get_all_objects_as_handles
	// Returns: table<int, int>: Returns all objects as script handles
	static std::vector<Entity> get_all_objects_as_handles()
	{
		return big::pools::get_all_props_array();
	}

	void bind(sol::state& state)
	{
		auto ns                           = state["entities"].get_or_create<sol::table>();
		ns["get_all_vehicles_as_handles"] = get_all_vehicles_as_handles;
		ns["get_all_peds_as_handles"]     = get_all_peds_as_handles;
		ns["get_all_objects_as_handles"]  = get_all_objects_as_handles;
	}
}