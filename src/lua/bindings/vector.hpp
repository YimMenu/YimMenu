#pragma once
#include "lua/sol.hpp"

namespace lua::vector
{
	static void bind(sol::state& state)
	{
		//clang-format off
		state.new_usertype<Vector3>("vec3",
			sol::constructors<Vector3(float, float, float)>(),
			"x", &Vector3::x, "y", &Vector3::y, "z", &Vector3::z,
			"__tostring", &Vector3::to_string
		);
		//clang-format on
	}
}