#include "gta/enums.hpp"
#include "hooking/hooking.hpp"

namespace big
{
	void* hooks::task_fall_constructor(uint64_t a1, int a2)
	{
		if (g.self.graceful_landing)
		{
			a2 |= (int)eTaskFlags::GracefulLanding;
		}
		return g_hooking->get_original<task_fall_constructor>()(a1, a2);
	}
}
