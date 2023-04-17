#include "hooking.hpp"

namespace big
{
	void hooks::task_jump_constructor(std::uint64_t a1, int a2)
	{
		if (g.self.super_jump)
			a2 |= 1 << 15;
		if (g.self.beast_jump)
			a2 |= (1 << 15) | (1 << 17);
		return g_hooking->get_original<task_jump_constructor>()(a1, a2);
	}
}
