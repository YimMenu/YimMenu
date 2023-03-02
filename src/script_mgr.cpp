#include "script_mgr.hpp"

#include "common.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "gta_util.hpp"
#include "invoker.hpp"
#include "pointers.hpp"

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

	script_list& script_mgr::scripts()
	{
		return m_scripts;
	}

	void script_mgr::tick()
	{
		gta_util::execute_as_script(RAGE_JOAAT("main_persistent"), std::mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);

		std::lock_guard lock(m_mutex);
		for (auto const& script : m_scripts)
			if (script->is_enabled())
				script->tick();
	}
}
