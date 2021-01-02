#pragma once
#include "features.hpp"
#include "gta/joaat.hpp"

namespace big::features::functions
{
	void get_active_character_slot(int* statSlot);
	void join_session_type(session_type session);
	void reset_vehicle_sell_stats();
	void set_car_sell_value(int value);
	void set_player_level(int level);
	void spoof_rank(int rank);
	void toggle_protections(bool toggle);
}