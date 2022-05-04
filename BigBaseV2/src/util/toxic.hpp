#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "system.hpp"

namespace big::toxic
{
	inline void blame_explode_coord(Player to_blame, Vector3 pos, eExplosionType explosion_type, float damage, bool is_audible, bool is_invisible, float camera_shake)
	{
		system::patch_blame(true);
		FIRE::ADD_OWNED_EXPLOSION(
			PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(to_blame),
			pos.x, pos.y, pos.z,
			(int)explosion_type,
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
			(int)eRemoteEvent::Bounty,
			0, // doesn't matter of we set this to something else, the TRIGGER_SCRIPT_EVENT routine will set it to our player id anyways
			target,
			0, // set by player or NPC?
			amount,
			0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			* script_global(1921039).at(9).as<int*>(),
			* script_global(1921039).at(10).as<int*>()
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

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, RAGE_JOAAT("WEAPON_STUNGUN"), PLAYER::PLAYER_PED_ID(), false, true, 1);
		}
	}
	
	inline void kick_from_vehicle(const Player player)
	{
		const Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		TASK::CLEAR_PED_TASKS_IMMEDIATELY(target);
	}

	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			(int)eRemoteEvent::ClearWantedLevel,
			0,
			*script_global(1893551).at(target, 599).at(510).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}
}
