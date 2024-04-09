#include "hooking/hooking.hpp"
#include "script_mgr.hpp"

namespace big
{
	bool hooks::run_script_threads(uint32_t ops_to_execute)
	{
		if (g_running) [[likely]]
		{
			g_script_mgr.tick();
		}

		return g_hooking->get_original<run_script_threads>()(ops_to_execute);
	}
}
