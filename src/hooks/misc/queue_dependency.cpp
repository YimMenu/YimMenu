#include "hooking.hpp"
#include "pointers.hpp"

namespace big
{
	void hooks::queue_dependency(void* dependency)
	{
		if (dependency == g_pointers->m_interval_check_func)
		{
			//LOG(INFO) << "Prevent attempt to queue a report to R*.";
			return;
		}

		return g_hooking->get_original<hooks::queue_dependency>()(dependency);
	}
}