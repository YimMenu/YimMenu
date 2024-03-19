#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	static bool last_online = false;

	inline void cleanup_spawned_ped(spawned_ped& ped)
	{
		PED::DELETE_PED(&ped.ped_handle);
	}

	static bool bLastLoadPathNodes = false;
	void looped::world_spawn_ped()
	{
		if (*g_pointers->m_gta.m_is_session_started != last_online)
		{
			last_online = *g_pointers->m_gta.m_is_session_started;

			for (auto& ped : spawned_peds)
				cleanup_spawned_ped(ped);

			spawned_peds.clear();
		}

		if (bLastLoadPathNodes && (spawned_peds.size() == 0))
		{
			PATHFIND::LOAD_ALL_PATH_NODES(false);
			bLastLoadPathNodes = false;
		}
		else if (spawned_peds.size() != 0)
		{
			PATHFIND::LOAD_ALL_PATH_NODES(true);
			bLastLoadPathNodes = true;
		}

		for (auto it = spawned_peds.begin(); it != spawned_peds.end();)
		{
			if ((*g_pointers->m_gta.m_is_session_started && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(it->spawned_for_player)) || !ENTITY::DOES_ENTITY_EXIST(it->ped_handle))
			{
				cleanup_spawned_ped(*it);
				it = spawned_peds.erase(it);
				continue;
			}

			if (it->is_attacker || it->is_bodyguard)
			{
				auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player), false);
				auto vel = NETWORK::NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player));
				bool is_veh  = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player), true) || PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(it->spawned_for_player);
				auto ped_pos = ENTITY::GET_ENTITY_COORDS(it->ped_handle, false);

				float distance       = is_veh ? 170.0f : 120.0f;
				float spawn_distance = is_veh ? 150.0f : 70.0f;

				if (pos.x != 0.0f && SYSTEM::VDIST2(pos.x, pos.y, pos.z, ped_pos.x, ped_pos.y, ped_pos.z) > distance * distance)
				{
					Vector3 spawn_point;
					if (MISC::FIND_SPAWN_POINT_IN_DIRECTION(pos.x, pos.y, pos.z, vel.x, vel.y, vel.z, spawn_distance, &spawn_point) && entity::take_control_of(it->ped_handle, 0))
					{
						PED::SET_PED_COORDS_KEEP_VEHICLE(it->ped_handle, spawn_point.x, spawn_point.y, spawn_point.z);

						if (it->is_attacker)
							TASK::TASK_COMBAT_PED(it->ped_handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player), 0, 16);

						if (it->is_bodyguard)
							TASK::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(it->ped_handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player), 0.0f, 0.0f, 0.0f, 4.0f, -1, 0.0f, true);
					}
				}
			}

			if (it->is_attacker && TASK::GET_SCRIPT_TASK_STATUS(it->ped_handle, "SCRIPT_TASK_COMBAT"_J) == 7)
			{
				TASK::TASK_COMBAT_PED(it->ped_handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player), 0, 16);
			}
			else if (it->is_bodyguard && it->spawned_for_player != self::id && TASK::GET_SCRIPT_TASK_STATUS(it->ped_handle, "SCRIPT_TASK_FOLLOW_TO_OFFSET_OF_ENTITY"_J) == 7)
			{
				TASK::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(it->ped_handle, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(it->spawned_for_player), 0.0f, 0.0f, 0.0f, 4.0f, -1, 0.0f, true);
			}

			it++;
		}
	}
}
