#pragma once
#include "core/enums.hpp"
#include "core/scr_globals.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/pickup_rewards.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "util/explosion_anti_cheat_bypass.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "util/system.hpp"

#include <network/Network.hpp>
#include <network/netConnection.hpp>
#include <network/netTime.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

namespace big::toxic
{
	inline void blame_explode_coord(player_ptr to_blame, Vector3 pos, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		explosion_anti_cheat_bypass::apply();

		FIRE::ADD_OWNED_EXPLOSION(
		    (*g_pointers->m_gta.m_is_session_started && to_blame) ? PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame->id()) : 0,
		    pos.x,
		    pos.y,
		    pos.z,
		    (int)explosion_type,
		    damage,
		    is_audible,
		    is_invisible,
		    camera_shake);

		explosion_anti_cheat_bypass::restore();
	}

	inline void blame_explode_player(player_ptr to_blame, player_ptr target, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), true);
		blame_explode_coord(to_blame, coords, explosion_type, damage, is_audible, is_invisible, camera_shake);
	}

	inline void start_activity(player_ptr target, eActivityType type)
	{
		const size_t arg_count = 5;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::StartActivity, (int64_t)self::id, 1 << target->id(), (int64_t) type, (int64_t) true};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << target->id(), (int)eRemoteEvent::StartActivity);
	}

	inline bool set_time(player_ptr target, uint32_t millis)
	{
		if (!g_player_service->get_self()->is_host())
		{
			g_notification_service.push_error("MODIFY_TIME"_T.data(), "MODIFY_TIME_HOST_REQUIRED"_T.data());
			return false;
		}

		if (!target->player_time_value.has_value())
		{
			g_notification_service.push_error("MODIFY_TIME"_T.data(), "MODIFY_TIME_NO_PLAYER_TIMESTAMP"_T.data());
			return false;
		}

		target->num_time_syncs_sent++;

		rage::netTimeSyncMsg msg{};
		msg.action    = 1;
		msg.counter   = target->num_time_syncs_sent;
		msg.token     = (*g_pointers->m_gta.m_network_time)->m_time_token;
		msg.timestamp = target->player_time_value.value()
		    + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now())
		        - target->player_time_value_received_time.value())
		          .count();
		msg.increment = millis;

		auto peer = target->get_connection_peer();

		if (!peer)
			return false;

		for (int j = 0; j < 100; j++)
		{
			g_pointers->m_gta.m_sync_network_time(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
			    &peer->m_peer_address,
			    (*g_pointers->m_gta.m_network_time)->m_connection_identifier,
			    &msg,
			    0x1000000); // repeatedly spamming the event will eventually cause certain bounds checks to disable for some reason
		}

		return true;
	}

	inline void warp_time_forward(player_ptr target, uint32_t millis)
	{
		if (!target->player_time_value.has_value())
		{
			g_notification_service.push_error("WARP_TIME_TITLE"_T.data(), "MODIFY_TIME_NO_PLAYER_TIMESTAMP"_T.data());
			return;
		}

		if (set_time(target,
		        target->time_difference.value() + millis
		            + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now())
		                - target->player_time_value_received_time.value())
		                  .count()))
			target->time_difference.value() += millis;
	}

	inline void set_time_all(uint32_t millis)
	{
		if (!g_player_service->get_self()->is_host())
		{
			g_notification_service.push_error("MODIFY_TIME"_T.data(), "MODIFY_TIME_HOST_REQUIRED"_T.data());
			return;
		}

		uint32_t largest_counter = 9999;
		g_player_service->iterate([&largest_counter](const player_entry& plyr) {
			if (plyr.second->num_time_syncs_sent > largest_counter)
				largest_counter = plyr.second->num_time_syncs_sent;
		});

		(*g_pointers->m_gta.m_network_time)->m_time_offset = millis - timeGetTime();

		rage::netTimeSyncMsg msg{};
		g_player_service->iterate([&largest_counter, &msg, millis](const player_entry& plyr) {
			if (!plyr.second->player_time_value.has_value())
			{
				LOG(WARNING) << "Skipping " << plyr.second->get_name() << " in time warp";
				return;
			}

			largest_counter++;

			msg.action    = 1;
			msg.counter   = largest_counter;
			msg.token     = (*g_pointers->m_gta.m_network_time)->m_time_token;
			msg.timestamp = plyr.second->player_time_value.value()
			    + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now())
			        - plyr.second->player_time_value_received_time.value())
			          .count();
			msg.increment = millis;

			auto peer = plyr.second->get_connection_peer();

			if (!peer)
				return;

			for (int j = 0; j < 25; j++)
			{
				g_pointers->m_gta.m_sync_network_time(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
				    &peer->m_peer_address,
				    (*g_pointers->m_gta.m_network_time)->m_connection_identifier,
				    &msg,
				    0x1000000);
			}

			plyr.second->num_time_syncs_sent = largest_counter + 32;
		});
	}

	inline void warp_time_forward_all(uint32_t millis)
	{
		set_time_all((*g_pointers->m_gta.m_network_time)->m_time + millis);
	}
}
