#include "hooking.hpp"

namespace big
{
	__int64 hooks::task_jump_constructor(uint64_t a1, int a2)
	{
		return g_hooking->get_original<task_jump_constructor>()(a1, a2);
	}
}
