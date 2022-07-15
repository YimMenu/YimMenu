#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "system.hpp"
#include "entity.hpp"
#include "util/teleport.hpp"
#include "gta_util.hpp"

namespace big::toxic
{
	inline void blame_explode_coord(Player to_blame, Vector3 pos, eExplosionType explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		system::patch_blame(true);
		FIRE::ADD_OWNED_EXPLOSION(
			PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame),
			pos.x, pos.y, pos.z,
			explosion_type,
			damage,
			is_audible,
			is_invisible,
			camera_shake
		);
		system::patch_blame(false);
	}

	inline void blame_explode_player(Player to_blame, Player target, eExplosionType explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), true);
		blame_explode_coord(to_blame, coords, explosion_type, damage, is_audible, is_invisible, camera_shake);
	}

	inline void bounty_player(Player target, int amount)
	{
		const size_t arg_count = 22;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::Bounty),
			self::id,
			target,
			0, // set by player or NPC?
			amount,
			0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			*script_global(1921039).at(9).as<int*>(),
			*script_global(1921039).at(10).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, -1);
	}

	inline void taze_player(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 20;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, RAGE_JOAAT("WEAPON_STUNGUN"), self::ped, false, true, 1);
		}
	}

	inline void emp_player(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 2;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_R_Hand, 0.0f, 0.0f, 0.1f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 2, 0, RAGE_JOAAT("WEAPON_EMPLAUNCHER"), self::id, false, true, 0);
		}
	}

	inline void airstrike(Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		constexpr auto max_attempts = 20;
		for (size_t attempts = 0; attempts < max_attempts && !ENTITY::IS_ENTITY_DEAD(target, false); attempts++)
		{
			const Vector3 destination = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 0.0f);
			const Vector3 origin = PED::GET_PED_BONE_COORDS(target, (int)PedBones::SKEL_ROOT, 0.0f, 0.0f, 50.f);

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 400, 0, RAGE_JOAAT("VEHICLE_WEAPON_SPACE_ROCKET"), self::id, false, false, 50.f);
		}
	}

	inline void kick_from_vehicle(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		TASK::CLEAR_PED_TASKS_IMMEDIATELY(target);
	}

	inline void flying_vehicle(const Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

			if (entity::take_control_of(ent))
				ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, 0.f, 0.f, 50000.f, 0.f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);
			else
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
		}
	}


	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
			self::id,
			*script_global(1893551).at(target, 599).at(510).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline void send_to_cayo_perico(const Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::SendToCayoPerico),//SendToLocation
			self::id,
			target
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline void destroyveh(Player pid)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(pid);

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		else {
			std::int64_t args[4] = { static_cast<int64_t>(eRemoteEvent::Destroyvehicle), pid, pid, pid };
			g_pointers->m_trigger_script_event(1, args, 4, 1 << pid);
			//std::int64_t args2[10] = { static_cast<int64_t>(eRemoteEvent::VehicleKick), pid, pid, 0, 0, 0, 0, 1, pid, std::min(2147483647, MISC::GET_FRAME_COUNT()) };
			//g_pointers->m_trigger_script_event(1, args2, 10, 1 << pid);
		}
	}

	inline void kick(const Player player)
	{
		if (NETWORK::NETWORK_IS_HOST())
		{
			NETWORK::NETWORK_SESSION_KICK_PLAYER(player);
			g_notification_service->push("Toxic", "Kicked Player as Host");
			return;
		}
		//bad stuff here, look away kid

		g_notification_service->push("Toxic", "Kicked Player");
	}

	inline void bitching(const Player player)
	{
		int eclone[1000];
		int egcount = 0;
		while (egcount < 1)
		{
			Ped SelectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Hash stungun = RAGE_JOAAT("WEAPON_STUNGUN");
			Entity ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			eclone[egcount] = PED::CLONE_PED(ped, true, false, true);
			ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
			ENTITY::SET_ENTITY_HEALTH(eclone[egcount], 1000, 0);
			PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
			WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], stungun, stungun, 9999, 9999);
			PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
			TASK::TASK_COMBAT_PED(eclone[egcount], ped, 1, 1);
			PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
			PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
			ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&eclone[egcount]);
			egcount++;
			script::get_current()->yield(100ms);
		}
	}

	inline void bodyguard(const Player player)
	{
		int clone[1000];
		int gcount = 0;
		while (gcount < 1)
		{
			Ped SelectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Hash railgun = RAGE_JOAAT("WEAPON_RAILGUN");
			Entity ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			//Ped enemy = TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(SelectedPlayer, 20, 0);
			int my_group = PLAYER::GET_PLAYER_GROUP(SelectedPlayer);
			clone[gcount] = PED::CLONE_PED(ped, true, false, true);
			PED::SET_PED_AS_GROUP_LEADER(SelectedPlayer, my_group);
			PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
			PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount],1);
			ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], true);
			ENTITY::SET_ENTITY_HEALTH(clone[gcount], 1000, 0);
			PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
			WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], railgun, railgun, 9999, 9999);
			PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
			TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(player, 20, 0);
			PED::SET_GROUP_FORMATION(my_group, 1);
			PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
			PED::SET_PED_ALERTNESS(clone[gcount], 1000);
			PED::SET_PED_COMBAT_RANGE(clone[gcount], 1000);
			gcount++;
			script::get_current()->yield(100ms);
		}
	}

	inline void Apartment(Player player)
	{
		std::int64_t args1[9] = { static_cast<int64_t>(eRemoteEvent::Teleport), player, player, 1, 0, 69, 1, 1, 1 };
		g_pointers->m_trigger_script_event(1, args1, 9, 1 << player);
	}

	inline void KICK_TO_SP(Player player)
	{
		std::int64_t argarr[4] = { static_cast<int64_t>(eRemoteEvent::SEC10), player, 0, 0 };
		g_pointers->m_trigger_script_event(1, argarr, sizeof(argarr) / sizeof(argarr[0]), 1 << player);
	}

	inline void BurstTires(Player player) 
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(PED::GET_VEHICLE_PED_IS_USING(player), true);
			static int tireID = 0;
			for (tireID = 0; tireID < 8; tireID++)
			{
				VEHICLE::SET_VEHICLE_TYRE_BURST(PED::GET_VEHICLE_PED_IS_USING(player), tireID, true, 1000.0);
			}
		}
	}

	inline void ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != self::id && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == false) 
		{ 
			entity::RequestNetworkControlOfEntity(e);
		}
		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);
	}
}