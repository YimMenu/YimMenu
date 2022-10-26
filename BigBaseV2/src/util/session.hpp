#pragma once
#include "core/data/session_types.hpp"
#include "script_global.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "util/misc.hpp"
#include "util/globals.hpp"

namespace big::session
{
	inline void join_type(eSessionType session)
	{
		*script_global(2726795).as<int*>() = (session == eSessionType::SC_TV ? 1 : 0); // If SC TV Then Enable Spectator Mode

		if (session == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else
			*script_global(1575015).as<int*>() = (int)session;

		*script_global(1574589).as<int*>() = 1;
		script::get_current()->yield(200ms);
		*script_global(1574589).as<int*>() = 0;
	}

	static constexpr char const* weathers[] = {
		"EXTRASUNNY", "CLEAR", "CLOUDS", "SMOG",
		"FOGGY", "OVERCAST", "RAIN", "THUNDER",
		"CLEARING", "NEUTRAL", "SNOW", "BLIZZARD",
		"SNOWLIGHT", "XMAS", "HALLOWEEN" };
	inline void local_weather()
	{
		MISC::CLEAR_OVERRIDE_WEATHER();

		MISC::SET_OVERRIDE_WEATHER(weathers[g->session.local_weather]);

		*script_global(262145).at(4723).as<bool*>() = g->session.local_weather == 13;
	}

	inline void set_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		misc::set_bit(globals::gsbd_fm_events.at(11).at(341).at(idx, 1).as<int*>(), bit);
		misc::set_bit(globals::gsbd_fm_events.at(11).at(348).at(idx, 1).as<int*>(), bit);
		misc::set_bit(globals::gpbd_fm_3.at(self::id, globals::size::gpbd_fm_3).at(10).at(205).at(idx, 1).as<int*>(), bit);
	}

	inline void force_thunder()
	{
		session::set_fm_event_index(9);
		session::set_fm_event_index(10);
		session::set_fm_event_index(11);
	}
}
