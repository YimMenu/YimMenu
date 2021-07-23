#pragma once
#include "core/data/levels.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big::player
{
	inline void easy_way_out()
	{
		*script_global(262145 + 27907).as<int*>() = 0;
		*script_global(262145 + 27908).as<int*>() = 0;
	}

	inline void get_active_character_slot(int *character_slot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), character_slot, true);
	}

	inline void set_player_level(int level)
	{
		get_active_character_slot(&g.player.character_slot);

		char level_string[64];
		sprintf(level_string, "MP%d_CHAR_SET_RP_GIFT_ADMIN", g.player.character_slot);

		STATS::STAT_SET_INT(rage::joaat(level_string), levels[level - 1], 0);
	}
}