#pragma once
#include "invoker.hpp"
#include "lua/lua_module.hpp"
#include "lua/natives/lua_native_binding.hpp"
#include "memory.hpp"

namespace lua::native
{
	void bind(sol::state& state)
	{
		init_native_binding(state);
	}
}