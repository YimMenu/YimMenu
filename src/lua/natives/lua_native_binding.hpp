#pragma once
#include "lua/sol.hpp"

namespace lua::native
{
	void init_native_binding(sol::state& L);
}
