#pragma once
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "core/enums.hpp"
#include "gta/net_object_mgr.hpp"
#include "gta/pickup_rewards.hpp"
#include "util/session.hpp"
#include "util/scripts.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "util/system.hpp"

namespace big::toxic
{
	inline void blame_explode_coord(player_ptr to_blame, Vector3 pos, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		g_pointers->m_blame_explode->apply();
		FIRE::ADD_OWNED_EXPLOSION(
			PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame->id()),
			pos.x, pos.y, pos.z,
			(int)explosion_type,
			damage,
			is_audible,
			is_invisible,
			camera_shake
		);
		g_pointers->m_blame_explode->restore();
	}

	inline void blame_explode_player(player_ptr to_blame, player_ptr target, eExplosionTag explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), true);
		blame_explode_coord(to_blame, coords, explosion_type, damage, is_audible, is_invisible, camera_shake);
	}

	inline void ceo_kick(player_ptr target)
	{
		auto leader = *scr_globals::gpbd_fm_3.at(target->id(), scr_globals::size::gpbd_fm_3).at(10).as<int*>();

		if (leader == -1)
			g_notification_service->push_warning("CEO Kick", "Player is not in a CEO/MC");
		else if (leader == target->id())
		{
			// use "normal" method to remove from CEO
			const size_t arg_count = 4;
			int64_t args[arg_count] = {
				(int64_t)eRemoteEvent::CeoKick,
				(int64_t)self::id,
				FALSE,
				5
			};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
		}
		else
		{
			// use a more private method to remove associate
			const size_t arg_count = 3;
			int64_t args[arg_count] = {
				(int64_t)eRemoteEvent::MarkPlayerAsBeast,
				(int64_t)self::id,
				leader
			};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
		}
	}

	inline void ceo_ban(player_ptr target)
	{
		const size_t arg_count = 3;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::CeoBan,
			(int64_t)self::id,
			TRUE
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_island(player_ptr target)
	{
		const size_t arg_count = 2;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::SendToCayoPerico,
			(int64_t)self::id,
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_apartment(player_ptr target, int index)
	{
		const size_t arg_count = 9;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::Teleport,
			self::id,
			(int64_t)target->id(),
			(int64_t)(int)-1, 1, (int64_t)index, 1, 1, 1
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_warehouse(player_ptr target, int index)
	{
		const size_t arg_count = 6;
		int64_t args[arg_count] = {
			(int64_t)eRemoteEvent::TeleportToWarehouse,
			self::id,
			(int64_t)target->id(),
			1,
			index
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void send_player_to_interior(player_ptr player, int interior)
	{
		float max = 1e+38f;
		auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), FALSE);
		const size_t arg_count = 15;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::InteriorControl,
			(int64_t)self::id,
			(int64_t)(int)interior,
			(int64_t)self::id,
			(int64_t)false,
			(int64_t)true, // true means enter sender interior
			(int64_t)*(uint32_t*)&coords.x,
			(int64_t)*(uint32_t*)&coords.y,
			(int64_t)*(uint32_t*)&coords.z,
			0,
			0,
			1,
			(int64_t)*(uint32_t*)&max,
			(int64_t)true,
			-1
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}

	inline void kick_player_from_vehicle(player_ptr target)
	{
		auto vehicle = target->get_current_vehicle();

		if (!vehicle || !vehicle->m_net_object)
		{
			// vehicle hasn't synced yet, use TSE
			const size_t arg_count = 9;
			int64_t args[arg_count] = {
				(int64_t)eRemoteEvent::VehicleKick,
				self::id, 0, 0, 0, 0, 0, 0, 0
			};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
		}
		else
		{
			// use a private method to kick player from vehicle
			(*g_pointers->m_network_object_mgr)->ChangeOwner(vehicle->m_net_object, g_player_service->get_self()->get_net_game_player(), 0);
		}
	}

	inline void ragdoll_player(player_ptr target)
	{
		if (auto ped = target->get_ped())
			if (auto net_object = ped->m_net_object)
				g_pointers->m_request_ragdoll(net_object->m_object_id);
	}

	inline void start_activity(player_ptr target, eActivityType type)
	{
		const size_t arg_count = 4;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::StartActivity,
			(int64_t)self::id,
			(int64_t)type,
			(int64_t)true
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void kick_player_from_interior(player_ptr target)
	{
		const size_t arg_count = 8;
		int64_t args[arg_count]{
			(int64_t)eRemoteEvent::KickFromInterior,
			(int64_t)self::id,
			*scr_globals::globalplayer_bd.at(target->id(), scr_globals::size::globalplayer_bd).at(318).at(6).as<int64_t*>(),
			*scr_globals::globalplayer_bd.at(target->id(), scr_globals::size::globalplayer_bd).at(318).at(7).as<int64_t*>(),
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

	inline void turn_player_into_animal(player_ptr target)
	{
		bool bOldPlayerControl = PLAYER::IS_PLAYER_CONTROL_ON(target->id());

		for (int i = 0; i < 30; i++)
		{
			session::give_collectible(target->id(), eCollectibleType::Treat, 0, false);
			session::give_collectible(target->id(), eCollectibleType::Treat, 0, true);
			g_pointers->m_give_pickup_rewards(1 << target->id(), REWARD_HEALTH); // try to keep them alive
			g_pointers->m_give_pickup_rewards(1 << target->id(), REWARD_ARMOUR);
			script::get_current()->yield(400ms);

			Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id());
			Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);

			if (bOldPlayerControl && !PLAYER::IS_PLAYER_CONTROL_ON(target->id()))
				return;

			if (model != RAGE_JOAAT("mp_m_freemode_01") && model != RAGE_JOAAT("mp_f_freemode_01"))
				return;

			if (ENTITY::IS_ENTITY_DEAD(playerPed, FALSE))
				script::get_current()->yield(7s);
		}

		g_notification_service->push_warning("Turn to Animal", "Failed to turn player into an animal");
	}

	inline void set_wanted_level(player_ptr target, int wanted_level)
	{
		int id = target->id();

		if (PLAYER::GET_PLAYER_WANTED_LEVEL(id) > wanted_level)
		{
			// clear existing wanted
			globals::clear_wanted_player(id);

			for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) > wanted_level && i < 3600; i++)
				script::get_current()->yield(1ms);
		}

		if (wanted_level > 0)
		{
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(212).as<Player*>() = id;
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = wanted_level;

			for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) < wanted_level && i < 3600; i++)
				script::get_current()->yield(1ms);

			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(212).as<Player*>() = -1; // reset to prevent wanted from being constantly set
			*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(213).as<int*>() = -1;
		}
	}

	inline void turn_player_into_beast(player_ptr target)
	{
		auto id = target->id();

		if (!NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_hunt_the_beast", -1))
		{
			if (!NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_launcher", -1))
			{
				g_notification_service->push_error("Turn to Beast", "Cannot start the Hunt the Beast event, player not a participant of am_launcher");
				return;
			}

			g_notification_service->push("Turn to Beast", "Starting Hunt The Beast event. Please wait...");

			scripts::start_launcher_script(47);

			for (int i = 0; !NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(id, "am_hunt_the_beast", -1); i++)
			{
				if (i >= 1000)
				{
					g_notification_service->push_error("Turn to Beast", "Failed to start the Hunt The Beast event");
					return;
				}

				script::get_current()->yield(1ms);
			}
		}

		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(id))
			return;

		if (!scripts::force_host(RAGE_JOAAT("am_hunt_the_beast")))
		{
			g_notification_service->push_error("Turn to Beast", "Failed to take control of am_hunt_the_beast");
			return;
		}

		auto thread = gta_util::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));
		auto stack = thread->m_stack;
		auto net_component = thread->m_net_component;
		auto idx = scr_locals::am_hunt_the_beast::broadcast_idx;

		if (!stack || !net_component || !target->is_valid())
			return;

		*script_local(stack, idx).as<int*>() = 1;
		*script_local(stack, idx).at(1).as<int*>() = 2; // stage
		*script_local(stack, idx).at(1).at(6).as<int*>() = net_component->get_participant_index(target->get_net_game_player()); // beast participant idx
		*script_local(stack, idx).at(1).at(7).as<Player*>() = id; // beast player idx
		*script_local(stack, idx).at(1).at(2).as<int*>() = INT_MAX; // stopwatch time
		*script_local(stack, idx).at(1).at(2).at(1).as<bool*>() = true; // stopwatch initialized
		*script_local(stack, idx).at(1).at(4).at(1).as<bool*>() = false; // destroy old stage 1 stopwatch
		*script_local(stack, idx).at(1).at(9).as<int*>() = 2; // some distance check
		*script_local(stack, idx).at(83).as<int*>() = 0; // transformed bitset
	}

	inline void turn_everyone_into_beast()
	{
		scripts::start_launcher_script(47);
		
		for (int i = 0; !scripts::is_running(RAGE_JOAAT("am_launcher")); i++)
		{
			if (i >= 7000)
			{
				g_notification_service->push_error("Turn to Beast", "Failed to start the Hunt The Beast event");
				return;
			}

			script::get_current()->yield(1ms);
		}

		script::get_current()->yield(500ms);

		if (!scripts::force_host(RAGE_JOAAT("am_hunt_the_beast")))
		{
			g_notification_service->push_error("Turn to Beast", "Failed to take control of am_hunt_the_beast");
			return;
		}

		script::get_current()->yield(3s);
		
		auto thread = gta_util::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));

		if (!thread)
			return;

		auto stack = thread->m_stack;
		auto net_component = thread->m_net_component;
		auto idx = scr_locals::am_hunt_the_beast::broadcast_idx;

		if (!stack || !net_component)
			return;

		thread->m_net_component->block_host_migration(true);
		thread->m_context.m_state = rage::eThreadState::unk_3;
		g->m_hunt_the_beast_thread = thread;

		for (int i = 0; i < 15; i++)
		{
			*script_local(stack, idx).as<int*>() = 1;
			*script_local(stack, idx).at(1).as<int*>() = 2; // stage
			*script_local(stack, idx).at(1).at(6).as<int*>() = __rdtsc(); // participant idx
			*script_local(stack, idx).at(1).at(7).as<Player*>() = __rdtsc(); // beast player idx
			*script_local(stack, idx).at(1).at(2).as<int*>() = INT_MAX; // stopwatch time
			*script_local(stack, idx).at(1).at(2).at(1).as<bool*>() = true; // stopwatch initialized
			*script_local(stack, idx).at(1).at(4).at(1).as<bool*>() = false; // destroy old stage 1 stopwatch
			*script_local(stack, idx).at(1).at(9).as<int*>() = 2; // some distance check
			*script_local(stack, idx).at(83).as<int*>() = 0; // transformed bitset
			script::get_current()->yield(350ms);
		}

		// unfortunately we must also turn ourselves into the beast to prevent the script from exiting due to a "missing player"

		*script_local(stack, idx).at(1).at(6).as<int*>() = net_component->m_local_participant_index; // participant idx
		*script_local(stack, idx).at(1).at(7).as<Player*>() = self::id; // beast player idx
		*script_local(stack, idx).at(1).at(2).as<int*>() = INT_MAX; // stopwatch time
		*script_local(stack, idx).at(83).as<int*>() = 0; // transformed bitset

		thread->m_context.m_state = rage::eThreadState::running;
	}

	// the blamed player cannot be the target itself
	inline void kill_player(player_ptr player, player_ptr to_blame)
	{
		if (!player->get_ped() || !to_blame->get_ped())
			return;

		g_pointers->m_send_network_damage((CEntity*)to_blame->get_ped(), (CEntity*)player->get_ped(), player->get_ped()->m_navigation->get_position(),
			0, true, RAGE_JOAAT("weapon_explosion"), 10000.0f, 2, 0, (1 << 4), 0, 0, 0, false, false, true, true, nullptr);
	}

	inline void give_all_weapons(player_ptr target)
	{
		for (auto& weapon : g_gta_data_service->weapons())
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), weapon.second.m_hash, 9999, FALSE, FALSE);
	}

	inline void remove_all_weapons(player_ptr target)
	{
		WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target->id()), FALSE);
	}
}