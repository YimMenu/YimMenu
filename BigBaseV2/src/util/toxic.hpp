#pragma once
#include "core/enums.hpp"
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

	// param 0 == should send
	// param 1 == player target
	// param 2 == amount
	// param 3 == unk? => always 1
	// param 4 == if some kind of bit must be set
	inline void bounty_player(Player target, Player origin, int amount)
	{
		const size_t arg_count = 22;
		int args[arg_count] = {
			(int)eRemoteEvent::Bounty,
			0,
			target,
			0,
			10000,
			0, 1, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			*script_global(1921036 + 9).as<int*>(),
			*script_global(1921036 + 10).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, -1);
	}
}