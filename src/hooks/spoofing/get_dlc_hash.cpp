#include "hooking/hooking.hpp"

namespace big
{
	std::uint32_t hooks::get_dlc_hash(void* mgr, std::uint32_t seed)
	{
		if (g.spoofing.spoof_dlc_hash)
			return g.spoofing.dlc_hash;

		return g_hooking->get_original<hooks::get_dlc_hash>()(mgr, seed);
	}
}