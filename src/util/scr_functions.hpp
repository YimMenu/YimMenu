#pragma once

#include "script_function.hpp"

namespace big::scr_functions
{ 
	inline void set_as_ceo(Player pid, int pay_grade, bool help_text, bool is_switching_org)
	{
		big::set_as_ceo.call<void>(pid, pay_grade, help_text, is_switching_org);
	}

	inline void set_freemode_session_active()
	{
		big::set_freemode_session_active.call<void>();
	}

	inline void save_to_datafile(uint64_t storage)
	{
		big::save_to_datafile.call<void>(storage);
	}

	inline bool load_from_datafile(int* load_stage, int ugc_language, bool is_mission)
	{
		return big::load_from_datafile.call<bool>(load_stage, ugc_language, is_mission);
	}

	inline void reset_session_data(bool reset_mission_data, bool reset_ps4_struct)
	{
		big::reset_session_data.call<void>(reset_mission_data, reset_ps4_struct);
	}

	inline bool add_clan_logo_to_vehicle(Vehicle* vehicle, Player pid)
	{
		return big::add_clan_logo_to_vehicle.call<bool>(vehicle, pid);
	}
}