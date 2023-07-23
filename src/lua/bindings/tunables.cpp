#pragma once
#include "../../script.hpp"
#include "tunables.hpp"

namespace lua::tunables
{
	void bind(sol::state& state)
	{
		auto ns         = state["tunables"].get_or_create<sol::table>();
		ns["get_int"]   = get<int>;
		ns["get_float"] = get<float>;
		ns["get_bool"]  = get<bool>;
		ns["set_int"]   = set<int>;
		ns["set_float"] = set<float>;
		ns["set_bool"]  = set<bool>;
	}
}