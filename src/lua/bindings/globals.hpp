#pragma once
#include "memory.hpp"
#include "script_global.hpp"

namespace lua::globals
{
	static int get_int(int global)
	{
		return *big::script_global(global).as<int*>();
	}

	static int get_float(int global)
	{
		return *big::script_global(global).as<float*>();
	}

	static void set_int(int global, int val)
	{
		*big::script_global(global).as<int*>() = val;
	}

	static void set_float(int global, float val)
	{
		*big::script_global(global).as<float*>() = val;
	}

	static memory::pointer get_global_pointer(int global)
	{
		return memory::pointer((uint64_t)big::script_global(global).as<void*>());
	}

	static void bind(sol::state& state)
	{
		auto ns                  = state["globals"].get_or_create<sol::table>();
		ns["get_int"]            = get_int;
		ns["get_float"]          = get_float;
		ns["set_int"]            = set_int;
		ns["set_float"]          = set_float;
		ns["get_global_pointer"] = get_global_pointer;
	}
}