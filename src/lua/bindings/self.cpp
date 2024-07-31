#pragma once

namespace lua_self = self;

namespace lua::self
{
	// Lua API: Table
	// Name: self
	// Table for retrieving data or info about our own player object.

	// Lua API: Function
	// Table: self
	// Name: get_ped
	// Returns: integer: Script handle of our ped.
	static Ped get_ped()
	{
		return lua_self::ped;
	}

	// Lua API: Function
	// Table: self
	// Name: get_id
	// Returns: integer: Our player id.
	static Player get_id()
	{
		return lua_self::id;
	}

	// Lua API: Function
	// Table: self
	// Name: get_pos
	// Returns: vec3: Position of our ped.
	static Vector3 get_pos()
	{
		return lua_self::pos;
	}

	// Lua API: Function
	// Table: self
	// Name: get_rot
	// Returns: vec3: Rotation of our ped.
	static Vector3 get_rot()
	{
		return lua_self::rot;
	}

	// Lua API: Function
	// Table: self
	// Name: get_veh
	// Returns: integer: Script handle of our current vehicle.
	static Vehicle get_veh()
	{
		return lua_self::veh;
	}

	void bind(sol::state& state)
	{
		auto ns = state["self"].get_or_create<sol::table>();

		ns["get_ped"] = get_ped;
		ns["get_id"]  = get_id;
		ns["get_pos"] = get_pos;
		ns["get_rot"] = get_rot;
		ns["get_veh"] = get_veh;
	}
}