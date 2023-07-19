#pragma once
#include "lua/sol.hpp"
#include "lua/natives/lua_native_binding.hpp"

namespace lua::native
{
	void bind(sol::state& state)
	{
		init_native_binding(state);
	}
}