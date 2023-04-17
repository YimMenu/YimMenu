#include "hooking.hpp"

namespace big
{
	void hooks::invalid_mods_crash_detour(int64_t a1, int64_t a2, int a3, char a4)
	{
		if (!*(int64_t*)(a1 + 0xD8))
			return;
		g_hooking->get_original<hooks::invalid_mods_crash_detour>()(a1, a2, a3, a4);
	}
}