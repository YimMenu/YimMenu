#pragma once
#include "gta/joaat.hpp"
#include "natives.hpp"

namespace big::local_player
{
	inline int character_slot;
	
	inline int get_active_character_slot()
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), &character_slot, true);
		return character_slot;
	}

	inline std::string get_mp_prefix()
	{
		return "MP" + std::to_string(get_active_character_slot()) + "_";
	}
}