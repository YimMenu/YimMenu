#include "scr_function.hpp"

namespace lua::scr_function
{
	void bind(sol::state& state)
	{
		auto ns = state["scr_function"].get_or_create<sol::table>();

		ns["call_void"]   = sol::overload(call_function<void>, call_function_by_ip<void>);
		ns["call_int"]    = sol::overload(call_function<int>, call_function_by_ip<int>);
		ns["call_float"]  = sol::overload(call_function<float>, call_function_by_ip<float>);
		ns["call_string"] = sol::overload(call_function<char*>, call_function_by_ip<char*>);
		ns["call_vec3"]   = sol::overload(call_function<Vector3>, call_function_by_ip<Vector3>);
	}
}