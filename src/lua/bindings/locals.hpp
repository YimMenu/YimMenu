#pragma once
#include "gta_util.hpp"
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

	void bind(sol::state& state);
}