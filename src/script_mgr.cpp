#include "script_mgr.hpp"

#include "common.hpp"
#include "gta/script_thread.hpp"
#include "gta_util.hpp"
#include "pointers.hpp"
#include "script/tlsContext.hpp"

namespace big
{
	void script_mgr::add_script(std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);

		m_scripts.push_back(std::move(script));
	}

	void script_mgr::remove_all_scripts()
	{
		std::lock_guard lock(m_mutex);

		m_scripts.clear();
	}

	void script_mgr::tick()
	{
		gta_util::execute_as_script("main_persistent"_J, std::mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::ensure_main_fiber()
	{
		ConvertThreadToFiber(nullptr);

		m_can_tick = true;
	}

	static void lua_manager_tick()
	{
		g_lua_manager->reload_changed_scripts();

		g_lua_manager->for_each_module([](const std::shared_ptr<lua_module>& module) {
			module->tick_scripts();
			module->cleanup_done_scripts();
		});
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_it = (ensure_main_fiber(), true);

		std::lock_guard lock(m_mutex);

		lua_manager_tick();

		for (const auto& script : m_scripts)
		{
			if (script->is_enabled())
				script->tick();
		}
	}
}
