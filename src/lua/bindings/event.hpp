#pragma once
#include "fiber_pool.hpp"
#include "lua/lua_module.hpp"
#include "script_mgr.hpp"

namespace lua::event
{
	static void register_handler(const std::string& name, sol::function func, sol::this_state state)
	{
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

		auto hash = rage::joaat(name);
		module->m_event_callbacks.emplace(hash, std::vector<sol::function>());
		module->m_event_callbacks[hash].push_back(func);
	}

	static void bind(sol::state& state)
	{
		auto ns                = state["event"].get_or_create<sol::table>();
		ns["register_handler"] = register_handler;
		// TODO: triggering events through script?
	}
}