#include "common.hpp"
#include "gta/array.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "gta_util.hpp"
#include "invoker.hpp"
#include "pointers.hpp"
#include "script_mgr.hpp"

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
		gta_util::execute_as_script(RAGE_JOAAT("main_persistent"), std::mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
		static bool ensure_native_handlers = (g_native_invoker.cache_handlers(), true);

		std::lock_guard lock(m_mutex);
		for (auto const &script : m_scripts)
		{
			script->tick();
		}
	}
}
