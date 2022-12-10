#include "hooking.hpp"

namespace big
{
	std::int64_t hooks::crash_bdsm(std::int64_t a1, std::int64_t a2, unsigned int a3, int a4, std::int64_t a5)
	{
		if (a3 <= 0)
			a3 = 1;
		return g_hooking->get_original<hooks::crash_bdsm>()(a1, a2, a3, a4, a5);
	}
}