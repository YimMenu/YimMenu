#pragma once
#include "util/explosion_anti_cheat_bypass.hpp"

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
}