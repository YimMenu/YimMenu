#pragma once
#include "lua/sol.hpp"

namespace lua::vector
{
	// Lua API: Class
	// Name: vec3
	// Class representing a 3D vector.

	// Lua API: Constructor
	// Class: vec3
	// Param: x: float: x component of the vector.
	// Param: y: float: y component of the vector.
	// Param: z: float: z component of the vector.
	// Returns a vector that contains the x, y, and z values.

	// Lua API: Field
	// Class: vec3
	// Field: x: float
	// x component of the vector.

	// Lua API: Field
	// Class: vec3
	// Field: y: float
	// y component of the vector.

	// Lua API: Field
	// Class: vec3
	// Field: z: float
	// z component of the vector.

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