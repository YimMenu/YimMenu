#include "hooking/hooking.hpp"

namespace big
{
	int hooks::task_parachute_object(uint64_t _this, int a2, int a3)
	{
		if (a2 == 1 && a3 == 1) // enter crash func 
		{
			if (auto ptr = *(uint64_t*)(_this + 16)) [[likely]]
				if (auto ptr2 = *(uint64_t*)(ptr + 80)) [[likely]]
					if (auto ptr3 = *(uint64_t*)(ptr2 + 64)) [[likely]]
						return g_hooking->get_original<hooks::task_parachute_object>()(_this, a2, a3);
			return 0;
		}
		return g_hooking->get_original<hooks::task_parachute_object>()(_this, a2, a3);
	}
}