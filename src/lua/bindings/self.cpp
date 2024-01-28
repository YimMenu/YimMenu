#pragma once
#include "self.hpp"

namespace lua_self = self;

namespace lua::self
{
	static Ped get_ped()
	{
		return lua_self::ped;
	}

	static Player get_id()
	{
		return lua_self::id;
	}

	static Vector3 get_pos()
	{
		return lua_self::pos;
	}

	static Vector3 get_rot()
	{
		return lua_self::rot;
	}

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