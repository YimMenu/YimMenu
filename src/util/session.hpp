#pragma once
#include "core/data/session_types.hpp"
#include "script_global.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "util/misc.hpp"
#include "util/globals.hpp"
#include "gta/joaat.hpp"
#include "rage/rlSessionByGamerTaskResult.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/api/api_service.hpp"
#include "thread_pool.hpp"
#include "fiber_pool.hpp"
#include "packet.hpp"
#include "gta_util.hpp"

#include <network/Network.hpp>
#include <network/snConnectToPeerTask.hpp>
#include <rage/rlScHandle.hpp>
#include <rage/rlQueryPresenceAttributesContext.hpp>

namespace big::session
{
	static void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(&hnd.m_platform), 8);
		if (*reinterpret_cast<uint8_t*>(&hnd.m_platform) == 3)
		{
			buf.WriteInt64(*(int64_t*)&hnd.m_rockstar_id, 64);
			buf.Write<uint8_t>(*reinterpret_cast<uint8_t*>(reinterpret_cast<__int64>(&hnd) + 9), 8);
		}
	}

	inline void join_type(eSessionType session)
	{
		*script_global(2695915).as<int*>() = (session == eSessionType::SC_TV ? 1 : 0); // If SC TV Then Enable Spectator Mode

		if (session == eSessionType::LEAVE_ONLINE)
			*script_global(1574589).at(2).as<int*>() = -1;
		else
			*script_global(1575017).as<int*>() = (int)session;

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

		MISC::SET_OVERRIDE_WEATHER(weathers[g.session.local_weather]);

		*script_global(262145).at(4752).as<bool*>() = g.session.local_weather == 13;
	}

	inline void set_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		misc::set_bit(scr_globals::gsbd_fm_events.at(11).at(354).at(idx, 1).as<int*>(), bit);
		misc::set_bit(scr_globals::gsbd_fm_events.at(11).at(347).at(idx, 1).as<int*>(), bit);
		misc::set_bit(scr_globals::gpbd_fm_3.at(self::id, scr_globals::size::gpbd_fm_3).at(10).at(205).at(idx, 1).as<int*>(), bit);
	}

	inline void clear_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		misc::clear_bit(scr_globals::gsbd_fm_events.at(11).at(354).at(idx, 1).as<int*>(), bit);
		misc::clear_bit(scr_globals::gsbd_fm_events.at(11).at(347).at(idx, 1).as<int*>(), bit);
		misc::clear_bit(scr_globals::gpbd_fm_3.at(self::id, scr_globals::size::gpbd_fm_3).at(10).at(205).at(idx, 1).as<int*>(), bit);
	}

	inline void join_session(const rage::rlSessionInfo& info)
	{
		g.session.join_queued = true;
		g.session.info = info;
		session::join_type({ eSessionType::NEW_PUBLIC });
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) == 0)
		{
			g.session.join_queued = false;
			g_notification_service->push_error("RID Joiner", "Unable to launch maintransition");
		}
		return;
	}

	inline void join_by_rockstar_id(uint64_t rid)
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 ||
			STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
		{
			g_notification_service->push_error("RID Joiner", "Player switch in progress, wait a bit.");
			return;
		}

		rage::rlGamerHandle player_handle(rid);
		rage::rlSessionByGamerTaskResult result;
		bool success = false;
		rage::rlTaskStatus state{};

		if (g_pointers->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &result, 1, &success, &state))
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

	inline void kick_by_rockstar_id(uint64_t rid)
	{
		rage::rlGamerHandle player_handle(rid);
		rage::rlScHandle socialclub_handle(rid);
		rage::rlSessionByGamerTaskResult get_session_result;
		bool get_session_success = false;
		rage::rlTaskStatus get_session_state{};

		rage::snConnectToPeerTaskData connect_to_peer_data{};
		rage::snConnectToPeerTaskResult connect_to_peer_result{};
		rage::rlTaskStatus connect_to_peer_status{};

		rage::rlQueryPresenceAttributesContext query_presence_attributes_context{};
		rage::rlTaskStatus query_presence_attributes_status{};
		rage::rlGamerInfoBase peer_address{};

		query_presence_attributes_context.m_presence_attibute_type = 3; // string
		strcpy(query_presence_attributes_context.m_presence_attribute_key, "peeraddr");

		if (!g_pointers->m_start_get_presence_attributes(0, &socialclub_handle, &query_presence_attributes_context, 1, &query_presence_attributes_status))
		{
			g_notification_service->push_error("RID Kick", "Cannot start the query presence attributes rline task");
			return;
		}

		while (query_presence_attributes_status.status == 1)
			script::get_current()->yield();

		if (query_presence_attributes_status.status != 3)
		{
			g_notification_service->push_error("RID Kick", "Querying presence attributes failed");
			return;
		}

		g_pointers->m_decode_peer_info(&peer_address, query_presence_attributes_context.m_presence_attribute_value, nullptr);

		if (!g_pointers->m_start_get_session_by_gamer_handle(0, &player_handle, 1, &get_session_result, 1, &get_session_success, &get_session_state))
		{
			g_notification_service->push_error("RID Kick", "Cannot start the get session by gamer handle task");
			return;
		}

		while (get_session_state.status == 1)
			script::get_current()->yield();

		if (get_session_state.status != 3 || !get_session_success)
		{
			g_notification_service->push_error("RID Kick", "Getting session info failed");
			return;
		}

		connect_to_peer_data.m_unk = 0;
		connect_to_peer_data.m_reason = 5;
		connect_to_peer_data.m_session_token = 0; // get_session_result.m_session_info.m_session_token; still works?

		if (!g_pointers->m_connect_to_peer(gta_util::get_network()->m_game_session.m_net_connection_mgr, &peer_address, &connect_to_peer_data, &connect_to_peer_result, &connect_to_peer_status))
		{
			g_notification_service->push_error("RID Kick", "Failed to start a connection with player");
			return;
		}

		g_notification_service->push("RID Kick", "Connecting to player...");

		while (connect_to_peer_status.status == 1)
			script::get_current()->yield();

		if (connect_to_peer_status.status != 3)
		{
			g_notification_service->push_warning("RID Kick", "Failed to connect to player, not attempting to send gamer instruction kick");
		}
		else
		{
			// you can send a MsgTransitionLaunchNotify with an invalid connection ID to crash the player instead (remove the session obtaining code above to make it work in SP)
			packet msg;
			msg.write_message(rage::eNetMessage::MsgTransitionGamerInstruction);
			gamer_handle_serialize(player_handle, msg.m_buffer); // src
			gamer_handle_serialize(player_handle, msg.m_buffer); // target
			msg.write<bool>(false, 1); // string extend
			msg.write<int>(0, 7); // string length
			msg.write<int>(8, 32); // instruction type
			msg.write<int>(0, 32);
			msg.write<int>(0, 32);
			msg.send(connect_to_peer_result.m_peer_id, gta_util::get_network()->m_transition_session_ptr->m_connection_identifier);
			g_notification_service->push("RID Kick", "Sent gamer instruction kick");
		}

		memset(&connect_to_peer_result, 0, sizeof(connect_to_peer_result));
		connect_to_peer_status.status = 0;

		if (!g_pointers->m_connect_to_peer(gta_util::get_network()->m_game_session.m_net_connection_mgr, &get_session_result.m_session_info.m_net_player_data, &connect_to_peer_data, &connect_to_peer_result, &connect_to_peer_status))
		{
			g_notification_service->push_error("RID Kick", "Failed to start a connection with the host");
			return;
		}

		g_notification_service->push("RID Kick", "Connecting to host...");

		while (connect_to_peer_status.status == 1)
			script::get_current()->yield();

		if (connect_to_peer_status.status != 3)
		{
			g_notification_service->push_error("RID Kick", "Failed to connect to the host");
			return;
		}

		packet msg{};
		msg.write_message(rage::eNetMessage::MsgLostConnectionToHost);
		msg.write<uint64_t>(get_session_result.m_session_info.m_unk, 64);
		gamer_handle_serialize(player_handle, msg);
		msg.send(connect_to_peer_result.m_peer_id, gta_util::get_network()->m_game_session_ptr->m_connection_identifier);
		g_notification_service->push("RID Kick", "Sent lost connection kick");
	}

	inline void join_by_username(std::string username)
	{
		g_thread_pool->push([username]
		{
			uint64_t rid;
			if (g_api_service->get_rid_from_username(username, rid))
			{
				g_fiber_pool->queue_job([rid]
				{
					join_by_rockstar_id(rid);
				});
				return;
			}
			g_notification_service->push_error("RID Joiner", "Target player is offline?");
		});
	}

	inline void kick_by_username(std::string username)
	{
		g_thread_pool->push([username]
		{
			uint64_t rid;
			if (g_api_service->get_rid_from_username(username, rid))
			{
				g_fiber_pool->queue_job([rid]
				{
					kick_by_rockstar_id(rid);
				});
				return;
			}
			g_notification_service->push_error("RID Kick", "Target player is offline?");
		});
	}

	inline void add_infraction(player_ptr player, Infraction infraction)
	{
		auto plyr = g_player_database_service->get_or_create_player(player);
		if (!plyr->infractions.contains((int)infraction))
		{
			plyr->is_modder = true;
			player->is_modder = true;
			plyr->infractions.insert((int)infraction);
			g_player_database_service->save();
		}
	}

	inline void give_collectible(Player target, eCollectibleType col, int index = 0, bool uncomplete = false)
	{
		const size_t arg_count = 7;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::GiveCollectible,
			(int64_t)self::id,
			(int64_t)col, // iParam0
			(int64_t)index, // iParam1
			!uncomplete, // bParam2
			true,
			0  // bParam3
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	// TODO this is really broken
	inline void enter_player_interior(player_ptr player)
	{

	}
}
