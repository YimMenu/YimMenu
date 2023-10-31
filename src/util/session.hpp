#pragma once
#include "core/data/infractions.hpp"
#include "core/data/session_types.hpp"
#include "core/settings/reactions.hpp"
#include "core/settings/session.hpp"
#include "fiber_pool.hpp"
#include "gta/joaat.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "rage/rlSessionByGamerTaskResult.hpp"
#include "script.hpp"
#include "script_function.hpp"
#include "services/api/api_service.hpp"
#include "services/gui/gui_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/players/player_service.hpp"
#include "services/recent_modders/recent_modders.hpp"
#include "thread_pool.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"

#include <network/Network.hpp>
#include <script/globals/GPBD_FM_3.hpp>

namespace big::session
{
	inline bool join_type(eSessionType session)
	{
		SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("pausemenu_multiplayer"));

		while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(RAGE_JOAAT("pausemenu_multiplayer")))
			script::get_current()->yield();

		if (session == eSessionType::LEAVE_ONLINE)
			*scr_globals::session.at(2).as<int*>() = -1;
		else
		{
			*scr_globals::session.at(2).as<int*>() = 0;
			*scr_globals::session2.as<int*>()      = (int)session;
		}

		*scr_globals::session.as<int*>() = 1;

		if (*g_pointers->m_gta.m_is_session_started && session != eSessionType::LEAVE_ONLINE)
		{
			*scr_globals::transition_state.as<eTransitionState*>() = eTransitionState::TRANSITION_STATE_LOOK_TO_JOIN_ANOTHER_SESSION_FM;
		}
		else if (session == eSessionType::LEAVE_ONLINE)
		{
			*scr_globals::transition_state.as<eTransitionState*>() = eTransitionState::TRANSITION_STATE_RETURN_TO_SINGLEPLAYER;
		}

		scr_functions::reset_session_data({true, true});
		*scr_globals::session3.as<int*>() = 0;
		*scr_globals::session4.as<int*>() = 1;
		*scr_globals::session5.as<int*>() = 32;

		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) == 0)
		{
			*scr_globals::session6.as<int*>() = 1;
			script::get_current()->yield(200ms);
			*scr_globals::session.as<int*>() = 0;
		}

		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(RAGE_JOAAT("pausemenu_multiplayer"));
		return true;
	}

	inline void set_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		misc::set_bit(scr_globals::gsbd_fm_events.at(11).at(361).at(idx, 1).as<int*>(), bit);
		misc::set_bit(scr_globals::gsbd_fm_events.at(11).at(353).at(idx, 1).as<int*>(), bit);
		misc::set_bit((int*)&scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.ActiveFreemodeEvents[idx], bit);
	}

	inline void clear_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		misc::clear_bit(scr_globals::gsbd_fm_events.at(11).at(361).at(idx, 1).as<int*>(), bit);
		misc::clear_bit(scr_globals::gsbd_fm_events.at(11).at(353).at(idx, 1).as<int*>(), bit);
		misc::clear_bit((int*)&scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.ActiveFreemodeEvents[idx], bit);
	}

	inline void join_session(const rage::rlSessionInfo& info)
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			g_notification_service->push_error("RID Joiner", "Player switch in progress, wait a bit.");
			return;
		}

		g_session.join_queued = true;
		g_session.info        = info;
		session::join_type({eSessionType::NEW_PUBLIC});
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) == 0)
		{
			g_session.join_queued = false;
			g_notification_service->push_error("RID Joiner", "Unable to launch maintransition");
		}
		return;
	}

	inline void join_by_rockstar_id(uint64_t rid)
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			g_notification_service->push_error("RID Joiner", "Player switch in progress, wait a bit.");
			return;
		}

		rage::rlGamerHandle player_handle(rid);
		rage::rlSessionByGamerTaskResult result;
		bool success = false;
		rage::rlTaskStatus state{};

		if (g_pointers->m_gta.m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
		{
			while (state.status == 1)
				script::get_current()->yield();

			if (state.status == 3 && success)
			{
				join_session(result.m_session_info);
				return;
			}
		}

		g_notification_service->push_error("RID Joiner", "Target player is offline?");
	}

	inline void join_by_username(std::string username)
	{
		g_thread_pool->push([username] {
			uint64_t rid;
			if (g_api_service->get_rid_from_username(username, rid))
			{
				g_fiber_pool->queue_job([rid] {
					join_by_rockstar_id(rid);
				});
				return;
			}
			g_notification_service->push_error("RID Joiner", "Target player is offline?");
		});
	}

	inline void add_infraction(player_ptr player, Infraction infraction)
	{
		if (auto net_data = player->get_net_data())
		{
			auto rockstar_id = net_data->m_gamer_handle.m_rockstar_id;
			auto name        = net_data->m_name;

			if (infraction == Infraction::TRIED_CRASH_PLAYER || infraction == Infraction::TRIED_KICK_PLAYER)
			{
				player->block_net_events   = true;
				player->block_clone_sync   = true;
				player->block_clone_create = true;

				g_gui_service->set_selected(tabs::PLAYER);
				g_player_service->set_selected(player);

				recent_modders_nm::add_player({name, rockstar_id, true});

				if (g_player_service->get_self()->is_host())
				{
					dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(player, {});
					return;
				}
			}

			if (!player->infractions.contains((int)infraction))
			{
				player->is_modder = true;
				player->infractions.insert((int)infraction);
				g_reactions.modder_detection.process(player);

				auto recent_modder = recent_modders_nm::recent_modders_list.find(rockstar_id);
				if (recent_modder == recent_modders_nm::recent_modders_list.end())
					recent_modders_nm::add_player({name, rockstar_id, false});
			}
		}
	}
}
