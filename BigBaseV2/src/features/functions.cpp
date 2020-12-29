#include "functions.hpp"
#include "gta/levels.hpp"
#include "script_global.hpp"

namespace big::features::functions
{
	void get_active_character_slot(int* statSlot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), statSlot, true);
	}

	void join_session_type(session_type session)
	{
		features::notify::above_map(session.id == -1 ? "Leaving GTA Online." : "Joining specified session.");

		if (session.id == -1)
			*script_global(1312443).at(2).as<int*>() = -1;
		else
			*script_global(1312854).as<int*>() = session.id;

		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 1);
		script::get_current()->yield(200ms);
		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 0);
	}

	void reset_vehicle_sell_stats()
	{
		get_active_character_slot(&g_temp.character_slot);

		char stat_string[64];
		sprintf(stat_string, "MP%d_MONEY_EARN_SELLING_VEH", g_temp.character_slot);

		STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_VEHICLE_SELL_TIME"), 0, true);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(stat_string), 50000, true);
	}

	void set_car_sell_value(int value)
	{
		*script_global(99007).at(970).as<int*>() = value;
	}

	void set_player_level(int level)
	{
		get_active_character_slot(&g_temp.character_slot);

		char level_string[64];
		sprintf(level_string, "MP%d_CHAR_SET_RP_GIFT_ADMIN", g_temp.character_slot);

		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(level_string), levels[level - 1], 0);
	}

	void spoof_rank(int rank)
	{
		*script_global(1590682).at(PLAYER::PLAYER_ID(), 883).at(211).at(6).as<int*>() = rank;
	}
}