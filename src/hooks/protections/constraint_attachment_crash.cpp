#include "hooking.hpp"

namespace big
{
	std::int64_t hooks::constraint_attachment_crash(std::uintptr_t a1)
	{
		if (!*reinterpret_cast<void**>(a1 + 0x38))
			return 0;

		return g_hooking->get_original<hooks::constraint_attachment_crash>()(a1);
	}
}