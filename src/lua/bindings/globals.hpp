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

	static std::string get_string(int global)
	{
		return std::string(big::script_global(global).as<char*>());
	}

	static void set_int(int global, int val)
	{
		*big::script_global(global).as<int*>() = val;
	}

	static void set_float(int global, float val)
	{
		*big::script_global(global).as<float*>() = val;
	}

	static void set_string(int global, const std::string& str, int max_length)
	{
		strncpy(big::script_global(global).as<char*>(), str.data(), max_length);
	}

	static memory::pointer get_pointer(int global)
	{
		return memory::pointer((uint64_t)big::script_global(global).as<void*>());
	}

	static void bind(sol::state& state)
	{
		auto ns           = state["globals"].get_or_create<sol::table>();
		ns["get_int"]     = get_int;
		ns["get_float"]   = get_float;
		ns["get_string"]  = get_string;
		ns["set_int"]     = set_int;
		ns["set_float"]   = set_float;
		ns["set_string"]  = set_string;
		ns["get_pointer"] = get_pointer;
	}
}