#pragma once
#include "core/data/session_types.hpp"
#include "script_global.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "gta_util.hpp"
#include "pointers.hpp"
#include "rage/rlSessionInfo.hpp"
#include "rage/rlSessionByGamerTaskResult.hpp"

namespace big::session
{
	inline void join_type(SessionType session)
	{
		*script_global(2726795).as<int*>() = (session.id == eSessionType::SC_TV ? 1 : 0); // If SC TV Then Enable Spectator Mode

		if (session.id == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else
			*script_global(1575015).as<int*>() = (int)session.id;

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

	inline void join_by_rockstar_id(uint64_t rid) // Skidded from maybegreat48
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) != 0 ||
			STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			g_notification_service->push_warning("RID Joiner", "Cannot RID join now");
			return;
		}

		rage::rlGamerHandle player_handle(rid);
		rage::rlSessionByGamerTaskResult result;
		bool success = false;
		int state = 0;
		if (g_pointers->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
		{
			while (state == 1)
				script::get_current()->yield();

			if (state == 3 && success)
			{
				g->session.session_join_queued = true;
				g->session.session_info = result.m_session_info;
				join_type({ eSessionType::NEW_PUBLIC, "" });
				script::get_current()->yield(500ms);
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) == 0)
				{
					g->session.session_join_queued = false;
					g_notification_service->push_error("RID Joiner", "RID join failed, unable to launch maintransition");
				}
				return;
			}
		}

		g_notification_service->push_warning("RID Joiner", "RID join failed");
	}

	inline void join_by_session_info(rage::rlSessionInfo m_session_info) // Skidded from maybegreat48
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) != 0 ||
			STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			g_notification_service->push_warning("RID Joiner", "Cannot RID join now");
			return;
		}
			g->session.session_join_queued = true;
			g->session.session_info = m_session_info;
			join_type({ eSessionType::NEW_PUBLIC, "" });
			script::get_current()->yield(500ms);
			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::joaat("maintransition")) == 0)
			{
				g->session.session_join_queued = false;
				g_notification_service->push_error("RID Joiner", "RID join failed, unable to launch maintransition");
			}
			return;

		g_notification_service->push_warning("RID Joiner", "RID join failed");
	}
}