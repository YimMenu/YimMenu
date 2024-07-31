#pragma once

#include "script_function.hpp"
#include "lua/bindings/network.hpp"

namespace lua::scr_function
{
	void bind(sol::state& state);
}