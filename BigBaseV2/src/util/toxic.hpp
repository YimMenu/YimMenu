#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "system.hpp"
#include "entity.hpp"
#include "util/teleport.hpp"
#include "gta_util.hpp"
#include "util/vehicle.hpp"
#include "util/ped.hpp"
#include "services/players/player_service.hpp"

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
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, RAGE_JOAAT("WEAPON_STUNGUN"), target, false, true, 1);
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
			*script_global(1892703).at(target, 599).at(510).as<int*>()
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
			std::int64_t args2[10] = { static_cast<int64_t>(eRemoteEvent::VehicleKick), pid, pid, 0, 0, 0, 0, 1, pid, std::min(2147483647, MISC::GET_FRAME_COUNT()) };
			g_pointers->m_trigger_script_event(1, args2, 10, 1 << pid);
			g_notification_service->push("Toxic", "Destroyed Player Vehicle");
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
		std::int64_t argarr[4] = { static_cast<int64_t>(eRemoteEvent::KickToSP), player, 0, 0 };
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

	inline void LockDoors(Player player)
	{
		int lockStatus = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player), 4);
		}
	}

	inline void UnLockDoors(Player player)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
		{
			entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player));
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player), 0);
		}
	}

	inline void ModelCrash(const Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(ped, true);
		Vector3 selfCoords = ENTITY::GET_ENTITY_COORDS(self::ped, true);
		Vector3 location = Vector3(-4036, 8000, 1); //Away from Peds
		float Heading = ENTITY::GET_ENTITY_HEADING(player);
		Hash hash = VEHICLE_CYCLONE2; //Dont change unless its a invalid Car
		//Script starts here
		teleport::to_coords(location);
		script::get_current()->yield(3s);
		Vehicle veh = vehicle::spawn(hash, playerCoords, Heading, true);
		g_notification_service->push("Toxic", "Crash Model Spawned to Player");
		script::get_current()->yield(3s);
		entity::delete_entity(veh);
		g_notification_service->push("Toxic", "Deleted Invalid Model");
		script::get_current()->yield(5s);
		teleport::to_coords(selfCoords);
	}

	inline void ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != self::id && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == false) 
		{ 
			entity::RequestNetworkControlOfEntity(e);
		}
		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);
	}

	inline void CEO_BAN(Player player)
	{
		std::int64_t argarr[4] = { static_cast<int64_t>(eRemoteEvent::CeoBan), player, 1, 5 };
		g_pointers->m_trigger_script_event(1, argarr, sizeof(argarr) / sizeof(argarr[0]), 1 << player);
	}

	inline void CEO_KICK(Player player)
	{
		std::int64_t argarr[4] = { static_cast<int64_t>(eRemoteEvent::CeoKick), player, 1, 5 };
		g_pointers->m_trigger_script_event(1, argarr, sizeof(argarr) / sizeof(argarr[0]), 1 << player);
	}

	inline void Spawn_G4E(Hash vehicle, float z)
	{
		Ped ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(ply, true) + Vector3(1, 1, z);
		float heading = ENTITY::GET_ENTITY_HEADING(PED::IS_PED_IN_ANY_VEHICLE(ply, false) ? PED::GET_VEHICLE_PED_IS_IN(ply, false) : ply);

		Vehicle veh = vehicle::spawn(vehicle, pos, heading, true);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, false);
		VEHICLE::CONTROL_LANDING_GEAR(veh, 3);

		static const Hash playerGroup = rage::joaat("PLAYER");
		static const Hash civGroup = rage::joaat("CIVMALE");
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

	inline void EarRape()
	{
		Vector3 plyrCoords = ENTITY::GET_ENTITY_COORDS(g_player_service->get_selected()->id(), true);
		AUDIO::PLAY_SOUND_FROM_COORD(1, "BED", plyrCoords.x, plyrCoords.y, plyrCoords.z, "WASTEDSOUNDS", true, 0, false);
	}
}