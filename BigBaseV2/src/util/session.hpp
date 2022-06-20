#pragma once
#include "core/data/session_types.hpp"
#include "script_global.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "gta_util.hpp"

namespace big::session
{
	inline void join_type(SessionType session)
	{
		if (session.id == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else
			*script_global(1575012).as<int*>() = (int)session.id;

		*script_global(1574589).as<int*>() = 1;
		script::get_current()->yield(200ms);
		*script_global(1574589).as<int*>() = 0;
	}

	static constexpr char const* weathers[] = { "EXTRASUNNY", "CLEAR", "CLOUDS", "SMOG", "FOGGY", "OVERCAST", "RAIN", "THUNDER", "CLEARING", "NEUTRAL", "SNOW", "BLIZZARD", "SNOWLIGHT", "XMAS", "HALLOWEEN" };

	inline void local_weather()
	{
		MISC::CLEAR_OVERRIDE_WEATHER();

		MISC::SET_OVERRIDE_WEATHER(weathers[g->session.local_weather]);

		*script_global(262145).at(4723).as<bool*>() = g->session.local_weather == 13;
	}

	inline void force_script_on_lobby(int script_id)
	{
		if (auto launcher = gta_util::find_script_thread(rage::joaat_t("am_launcher")))
		{
			//if (!session::force_script_host(self::id, "am_launcher"))
				//return;

			*script_global(2775756).at(3).at(1).as<int*>() = script_id;
			*script_global(2775756).at(2).as<int*>() = 6;
		}
	}
}