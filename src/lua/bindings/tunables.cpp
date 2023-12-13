#pragma once
#include "../../script.hpp"
#include "tunables.hpp"

namespace lua::tunables
{
	void bind(sol::state& state)
	{
		auto ns         = state["tunables"].get_or_create<sol::table>();

		ns["get_int"]   = sol::overload(get<int>, get_already_joaated<int>);
		ns["get_float"] = sol::overload(get<float>, get_already_joaated<float>);
		ns["get_bool"]  = sol::overload(get<bool>, get_already_joaated<bool>);

		ns["set_int"]   = sol::overload(set<int>, set_already_joaated<int>);
		ns["set_float"] = sol::overload(set<float>, set_already_joaated<float>);
		ns["set_bool"]  = sol::overload(set<bool>, set_already_joaated<bool>);
	}
}