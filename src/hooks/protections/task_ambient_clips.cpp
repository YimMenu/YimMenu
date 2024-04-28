#include "hooking/hooking.hpp"

namespace big
{
	int hooks::task_ambient_clips(uint64_t _this, int a2, int a3)
	{
		// enter crash func
		// TODO: this doesn't block the crash completely

		if (*(uint64_t*)(_this + 0x100)) [[likely]]
			return g_hooking->get_original<hooks::task_ambient_clips>()(_this, a2, a3);

		return 0;
	}
}