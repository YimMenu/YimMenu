#pragma once
#include "core/enums.hpp"
#include "core/scr_globals.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/pickup_rewards.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "util/scripts.hpp"
#include "util/session.hpp"
#include "util/system.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

#include <network/Network.hpp>
#include <network/netTime.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

namespace big::toxic
{
	inline void blame_explode_coord(player_ptr to_blame, Vector3 pos, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		g_pointers->m_blame_explode->apply();
		FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame->id()), pos.x, pos.y, pos.z, (int)explosion_type, damage, is_audible, is_invisible, camera_shake);
		g_pointers->m_blame_explode->restore();
	}

	inline void blame_explode_player(player_ptr to_blame, player_ptr target, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), true);
		blame_explode_coord(to_blame, coords, explosion_type, damage, is_audible, is_invisible, camera_shake);
	}

	inline void start_activity(player_ptr target, eActivityType type)
	{
		const size_t arg_count = 4;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::StartActivity, (int64_t)self::id, (int64_t)type, (int64_t) true};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline bool set_time(player_ptr target, uint32_t millis)
	{
		if (!g_player_service->get_self()->is_host())
		{
			g_notification_service->push_error("MODIFY_TIME"_T.data(), "MODIFY_TIME_HOST_REQUIRED"_T.data());
			return false;
		}

		if (!target->player_time_value.has_value())
		{
			g_notification_service->push_error("MODIFY_TIME"_T.data(), "MODIFY_TIME_NO_PLAYER_TIMESTAMP"_T.data());
			return false;
		}

		target->num_time_syncs_sent++;

		rage::netTimeSyncMsg msg{};
		msg.action    = 1;
		msg.counter   = target->num_time_syncs_sent;
		msg.token     = (*g_pointers->m_network_time)->m_time_token;
		msg.timestamp = target->player_time_value.value()
		    + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now())
		        - target->player_time_value_received_time.value())
		          .count();
		msg.increment = millis;

		auto peer = g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
		    (int)target->get_session_player()->m_player_data.m_peer_id_2);

		for (int j = 0; j < 100; j++)
		{
			g_pointers->m_sync_network_time(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
			    peer,
			    (*g_pointers->m_network_time)->m_connection_identifier,
			    &msg,
			    0x1000000); // repeatedly spamming the event will eventually cause certain bounds checks to disable for some reason
		}

		return true;
	}

	inline void warp_time_forward(player_ptr target, uint32_t millis)
	{
		if (!target->player_time_value.has_value())
		{
			g_notification_service->push_error("WARP_TIME_TITLE"_T.data(), "MODIFY_TIME_NO_PLAYER_TIMESTAMP"_T.data());
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
			g_notification_service->push_error("MODIFY_TIME"_T.data(), "MODIFY_TIME_HOST_REQUIRED"_T.data());
			return;
		}

		std::uint32_t largest_counter = 9999;
		g_player_service->iterate([&largest_counter](const player_entry& plyr) {
			if (plyr.second->num_time_syncs_sent > largest_counter)
				largest_counter = plyr.second->num_time_syncs_sent;
		});

		(*g_pointers->m_network_time)->m_time_offset = millis - timeGetTime();

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
			msg.token     = (*g_pointers->m_network_time)->m_time_token;
			msg.timestamp = plyr.second->player_time_value.value()
			    + (uint32_t)(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now())
			        - plyr.second->player_time_value_received_time.value())
			          .count();
			msg.increment = millis;

			auto peer = g_pointers->m_get_connection_peer(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
			    (int)plyr.second->get_session_player()->m_player_data.m_peer_id_2);

			for (int j = 0; j < 25; j++)
			{
				g_pointers->m_sync_network_time(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr,
				    peer,
				    (*g_pointers->m_network_time)->m_connection_identifier,
				    &msg,
				    0x1000000);
			}

			plyr.second->num_time_syncs_sent = largest_counter + 32;
		});
	}

	inline void warp_time_forward_all(uint32_t millis)
	{
		set_time_all((*g_pointers->m_network_time)->m_time + millis);
	}

	inline void Spawn_Attackers(Hash vehicle, float z)
	{
		Ped ply     = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true) + Vector3(1, 1, z);
		float heading = ENTITY::GET_ENTITY_HEADING(PED::IS_PED_IN_ANY_VEHICLE(ply, false) ? PED::GET_VEHICLE_PED_IS_IN(ply, false) : ply);

		Vehicle veh = vehicle::spawn(vehicle, pos, heading, true);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
		VEHICLE::CONTROL_LANDING_GEAR(veh, 3);

		static const Hash playerGroup = rage::joaat("PLAYER");
		static const Hash civGroup    = rage::joaat("CIVMALE");
		static const Hash femCivGroup = rage::joaat("CIVFEMALE");

		Hash relationshipGroup;
		PED::ADD_RELATIONSHIP_GROUP("_HOSTILE_JESUS", &relationshipGroup);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, playerGroup);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, civGroup);
		PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, relationshipGroup, femCivGroup);

		Ped ped = ped::spawn_in_vehicle("u_m_m_jesus_01", veh, true);

		PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, relationshipGroup);
		PED::SET_PED_HEARING_RANGE(ped, 9999.f);
		PED::SET_PED_CONFIG_FLAG(ped, 281, true);

		TASK::TASK_PLANE_MISSION(ped, veh, 0, ply, 0, 0, 0, 6, 0.0, 0.0, 0.0, 2500.0, -1500.0, 0);
		TASK::TASK_VEHICLE_FOLLOW(ped, veh, ply, 540, 525117, 1);
		TASK::TASK_VEHICLE_SHOOT_AT_PED(ped, ply, 100);

		WEAPON::GIVE_WEAPON_TO_PED(ped, rage::joaat("WEAPON_RAILGUN"), 9999, true, true);
		TASK::TASK_COMBAT_PED(ped, ply, 0, 16);

		PED::SET_PED_FIRING_PATTERN(ped, 0xC6EE6B4C);
	}
}