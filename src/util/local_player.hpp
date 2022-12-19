#pragma once
#include "core/data/levels.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big::local_player
{
	inline void get_active_character_slot(int* character_slot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), character_slot, true);
	}

	inline std::string get_mp_prefix()
	{
		get_active_character_slot(&g.player.character_slot);
		return "MP" + std::to_string(g.player.character_slot) + "_";
	}

	inline void set_player_level(int level)
	{
		STATS::STAT_SET_INT(rage::joaat(get_mp_prefix() + "CHAR_SET_RP_GIFT_ADMIN"), levels[level - 1], 0);
	}
}