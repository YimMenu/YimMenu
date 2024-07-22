#pragma once
#include "util/entity.hpp"
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

	static bool take_control_of(Entity entity)
	{
		return big::entity::take_control_of(entity);
	}

	// Lua API: Function
	// Table: entities
	// Name: take_control_of
	// Must be called from a script (script.run_in_fiber for example)
	// Param: entity: Entity: Script handle of the entity we are trying to take control of.
	// Param: try_count: integer: Optional. Number of time we'll try taking control of the entity. Default to 300.
	// Returns: boolean: Returns true if we successfully got control of the entity.
	static bool take_control_of_try_count(Entity entity, int try_count)
	{
		return big::entity::take_control_of(entity, try_count);
	}

	void bind(sol::state& state)
	{
		auto ns = state["entities"].get_or_create<sol::table>();

		ns["get_all_vehicles_as_handles"] = get_all_vehicles_as_handles;
		ns["get_all_peds_as_handles"]     = get_all_peds_as_handles;
		ns["get_all_objects_as_handles"]  = get_all_objects_as_handles;

		ns["take_control_of"] = sol::overload(take_control_of, take_control_of_try_count);
	}
}