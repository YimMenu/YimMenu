#include "hooking/hooking.hpp"

namespace big
{
	void hooks::invalid_decal(uintptr_t a1, int a2)
	{
		if (a1 && a2 == 2)
			//*(*(*(a1 + 0x48) + 0x30) + 0x2C8)
			if (const auto ptr = *reinterpret_cast<uintptr_t*>((a1 + 0x48)); ptr)
				if (const auto ptr2 = *reinterpret_cast<uintptr_t*>((ptr + 0x30)); ptr2)
					if (*reinterpret_cast<uintptr_t*>(ptr2 + 0x2C8) == 0)
						return;

		g_hooking->get_original<hooks::invalid_decal>()(a1, a2);
	}
}