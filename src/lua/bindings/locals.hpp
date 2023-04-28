#pragma once
#include "gta_util.hpp"
#include "memory.hpp"
#include "script_local.hpp"

namespace lua::locals
{
	template<typename T>
	inline T get(const std::string& script, int index)
	{
		static std::remove_pointer_t<T> null{};
		auto thread = big::gta_util::find_script_thread(rage::joaat(script));
		if (thread)
			return big::script_local(thread->m_stack, index).as<T>();

		return &null;
	}

	static int get_int(const std::string& script, int index)
	{
		return *get<int*>(script, index);
	}

	static int get_float(const std::string& script, int index)
	{
		return *get<float*>(script, index);
	}

	static void set_int(const std::string& script, int index, int val)
	{
		*get<int*>(script, index) = val;
	}

	static void set_float(const std::string& script, int index, float val)
	{
		*get<float*>(script, index) = val;
	}

	static memory::pointer get_pointer(const std::string& script, int index)
	{
		return memory::pointer((uint64_t)get<int*>(script, index));
	}

	static void bind(sol::state& state)
	{
		auto ns           = state["locals"].get_or_create<sol::table>();
		ns["get_int"]     = get_int;
		ns["get_float"]   = get_float;
		ns["set_int"]     = set_int;
		ns["set_float"]   = set_float;
		ns["get_pointer"] = get_pointer;
	}
}