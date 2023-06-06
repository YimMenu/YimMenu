#pragma once
#include "fiber_pool.hpp"
#include "lua/lua_manager.hpp"
#include "lua/lua_module.hpp"
#include "script_mgr.hpp"

namespace lua::script
{
	static void register_looped(const std::string& name, sol::function func, sol::this_state state)
	{
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();

		module->m_registered_scripts.push_back(big::g_script_mgr.add_script(std::make_unique<big::script>(
		    [func] {
			    while (big::g_running)
			    {
				    auto res = func();
				    if (!res.valid())
					    big::g_lua_manager->handle_error(res, res.lua_state());

				    big::script::get_current()->yield();
			    }
		    },
		    name)));
	}

	static void run_in_fiber(sol::function func)
	{
		big::g_fiber_pool->queue_job([func] {
			auto res = func();
			if (!res.valid())
				big::g_lua_manager->handle_error(res, res.lua_state());
		});
	}

	static void yield()
	{
		big::script::get_current()->yield();
	}

	static void sleep(int ms)
	{
		big::script::get_current()->yield(std::chrono::milliseconds(ms));
	}

	static void bind(sol::state& state)
	{
		auto ns               = state["script"].get_or_create<sol::table>();
		ns["register_looped"] = register_looped;
		ns["run_in_fiber"]    = run_in_fiber;
		ns["yield"]           = yield;
		ns["sleep"]           = sleep;
	}
}