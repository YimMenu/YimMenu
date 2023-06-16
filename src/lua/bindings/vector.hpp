#pragma once

namespace lua::vector
{
	static void bind(sol::state& state)
	{
		// clang-format off
		state.new_usertype<rage::fvector3>("vec3", sol::constructors<rage::fvector3(float, float, float)>(), 
		"x", &rage::fvector3::x,
		"y", &rage::fvector3::y,
		"z", &rage::fvector3::z
		);
		// clang-format on
	}
}