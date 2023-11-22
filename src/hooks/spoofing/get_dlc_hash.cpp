#include "hooking.hpp"

namespace big
{
	// seed should always be 0
	int hooks::get_dlc_hash(void* mgr, int seed)
	{
		if (g.spoofing.override_game_hashes)
			return g.spoofing.game_dlc_checksum;
		return g_hooking->get_original<hooks::get_dlc_hash>()(mgr, seed);
	}
}