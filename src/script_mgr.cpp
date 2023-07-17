#include "script_mgr.hpp"

#include "common.hpp"
#include "gta/script_thread.hpp"
#include "script/tlsContext.hpp"
#include "gta_util.hpp"
#include "invoker.hpp"
#include "pointers.hpp"
#include "lua/lua_manager.hpp"

namespace big
{
	script* script_mgr::add_script(std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);

		auto* ret = script.get();
		m_scripts_to_add.push_back(std::move(script));
		return ret;
	}

	void script_mgr::remove_script(script* scr)
	{
		std::lock_guard lock(m_mutex);

		scr->m_should_be_deleted = true;
	}

	void script_mgr::remove_all_scripts()
	{
		std::lock_guard lock(m_mutex);

		m_scripts.clear();
	}

	void script_mgr::add_on_script_batch_removed(std::function<void()> f)
	{
		m_on_script_batch_removed.push(f);
	}

	void script_mgr::tick()
	{
		gta_util::execute_as_script(RAGE_JOAAT("main_persistent"), std::mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::ensure_main_fiber()
	{
		ConvertThreadToFiber(nullptr);

		m_can_tick = true;
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_it = (ensure_main_fiber(), true);

		std::lock_guard lock(m_mutex);

		if (g_lua_manager->m_schedule_reload_modules)
		{
			g_lua_manager->unload_all_modules();
		}

		g_lua_manager->reload_changed_scripts();

		std::erase_if(m_scripts, [](std::unique_ptr<script>& iter) {
			return iter->m_should_be_deleted;
		});

		while (m_on_script_batch_removed.size())
		{
			auto& f = m_on_script_batch_removed.front();

			if (f)
			{
				f();
			}

			m_on_script_batch_removed.pop();
		}

		if (g_lua_manager->m_schedule_reload_modules)
		{
			g_lua_manager->load_all_modules();
			g_lua_manager->m_schedule_reload_modules = false;
		}
		else
		{
			g_lua_manager->load_modules_from_queue();
		}

		if (m_scripts_to_add.size())
		{
			for (auto& script_to_add : m_scripts_to_add)
			{
				m_scripts.push_back(std::move(script_to_add));
			}

			m_scripts_to_add.clear();
		}

		for (const auto& script : m_scripts)
		{
			if (script->is_enabled())
				script->tick();
		}
	}
}
