#include "hooking.hpp"

namespace big
{
	uint64_t hooks::task_parachute_object_0x270(uint64_t _this, int a2, int a3)
	{
		if (a2 == 1 && a3 == 1)// enter crash func
		{
			if (auto ptr = *(uint64_t*)(_this + 16))
				if (auto ptr2 = *(uint64_t*)(ptr + 80))
					if (auto ptr3 = *(uint64_t*)(ptr2 + 64))
						return g_hooking->get_original<hooks::task_parachute_object_0x270>()(_this, a2, a3);
			return 0;
		}
		return g_hooking->get_original<hooks::task_parachute_object_0x270>()(_this, a2, a3);
	}
}