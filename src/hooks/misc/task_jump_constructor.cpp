#include "gta/enums.hpp"
#include "hooking/hooking.hpp"

namespace big
{
	__int64 hooks::task_jump_constructor(uint64_t a1, int a2)
	{
		if (g.self.super_jump)
			a2 |= (int)eTaskFlags::SuperJump;
		if (g.self.beast_jump)
			a2 |= (int)eTaskFlags::BeastJumpWithSuper;
		return g_hooking->get_original<task_jump_constructor>()(a1, a2);
	}
}
