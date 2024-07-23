#pragma once

namespace lua::vector
{
	void bind(sol::state& state)
	{
		auto usertype = state.new_usertype<Vector3>("vec3", sol::constructors<Vector3(float, float, float)>());

		usertype["x"]          = &Vector3::x;
		usertype["y"]          = &Vector3::y;
		usertype["z"]          = &Vector3::z;
		usertype["__tostring"] = &Vector3::to_string;
	}
}