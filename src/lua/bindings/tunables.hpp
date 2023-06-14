#pragma once
#include "services/tunables/tunables_service.hpp"

namespace lua::tunables
{
	template<typename T>
	static T get(const std::string tunable_name)
	{
		if (auto tunable = big::g_tunables_service->get_tunable<T*>(rage::joaat(tunable_name)))
			return *tunable;

		return T();
	}

	template<typename T>
	static void set(const std::string tunable_name, T val)
	{
		big::g_tunables_service->set_tunable<T>(rage::joaat(tunable_name), val);
	}

	static void bind(sol::state& state)
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