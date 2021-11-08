#include "native_hooks.hpp"
#include "gta/joaat.hpp"

namespace big::native_hook
{
	void STAT_SET_INT(rage::scrNativeCallContext* src)
	{
		Hash stat_hash = src->get_arg<Hash>(0);
		int value = src->get_arg<int>(1);
		BOOL save = src->get_arg<BOOL>(2);

		switch (stat_hash)
		{
		case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_VC_HATE"):
		case RAGE_JOAAT("MPPLY_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_TC_HATE"):
			src->set_return_value<BOOL>(true);

			break;
		default:
			src->set_return_value<BOOL>(STATS::STAT_SET_INT(stat_hash, value, save));

			break;
		}
	}
}