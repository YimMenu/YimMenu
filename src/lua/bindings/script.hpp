#pragma once
#include "fiber_pool.hpp"
#include "lua/lua_module.hpp"
#include "script_mgr.hpp"

namespace lua::script
{
	static void register_looped_script(const std::string& name, sol::function func, sol::this_state state)
	{
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

		module->m_registered_scripts.push_back(big::g_script_mgr.add_script(std::make_unique<big::script>(
		    [func] {
			    while (big::g_running)
			    {
				    func();
				    big::script::get_current()->yield();
			    }
		    },
		    name)));
	}

	static void run_in_fiber(sol::function func)
	{
		big::g_fiber_pool->queue_job([func] {
			func();
		});
	}

	static void yield()
	{
		big::script::get_current()->yield();
	}

	static void bind(sol::state& state)
	{
		auto ns                      = state["script"].get_or_create<sol::table>();
		ns["register_looped_script"] = register_looped_script;
		ns["run_in_fiber"]           = run_in_fiber;
		ns["yield"]                  = yield;
	}
}