#pragma once

#include "script_function.hpp"

namespace big::scr_functions
{ 
	inline void set_as_ceo(Player pid, int pay_grade, bool help_text, bool bParam3)
	{
		big::set_as_ceo.call<void>(pid, pay_grade, help_text, bParam3);
	}

	inline void set_freemode_session_active()
	{
		big::set_freemode_session_active.call<void>();
	}

	inline void save_to_datafile(uint64_t storage)
	{
		big::save_to_datafile.call<void>(storage);
	}

	inline void load_from_datafile(int iParam0, bool bParam1, bool bParam2, int iParam3)
	{
		big::load_from_datafile.call<void>(iParam0, bParam1, bParam2, iParam3);
	}

	inline void reset_session_data(bool bParam0, bool bParam1)
	{
		big::reset_session_data.call<void>(bParam0, bParam1);
	}

	inline bool add_clan_logo_to_vehicle(Vehicle* vehicle, Player pid)
	{
		return big::add_clan_logo_to_vehicle.call<bool>(vehicle, pid);
	}
}