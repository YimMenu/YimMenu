#include "hooking/hooking.hpp"

namespace big
{
	bool hooks::fragment_physics_crash_2(float* a1, float* a2)
	{
		if (!a1 || !a2) [[unlikely]]
			return false;

		return g_hooking->get_original<hooks::fragment_physics_crash_2>()(a1, a2);
	}
}