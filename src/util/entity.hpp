#pragma once
#include "gta/joaat.hpp"
#include "gta/replay.hpp"
#include "gta_util.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pools.hpp"
#include "script.hpp"

namespace big::entity
{
	inline void cage_ped(Ped ped)
	{
		Hash hash = RAGE_JOAAT("prop_gold_cont_01");

		Vector3 location = ENTITY::GET_ENTITY_COORDS(ped, true);
		OBJECT::CREATE_OBJECT(hash, location.x, location.y, location.z - 1.f, true, false, false);
	}

	inline void clean_ped(Ped ped)
	{
		Ped player_ped = self::ped;

		PED::CLEAR_PED_BLOOD_DAMAGE(player_ped);
		PED::CLEAR_PED_WETNESS(player_ped);
		PED::CLEAR_PED_ENV_DIRT(player_ped);
		PED::RESET_PED_VISIBLE_DAMAGE(player_ped);
	}

	inline void delete_entity(Entity ent)
	{
		ENTITY::DETACH_ENTITY(ent, 1, 1);
		ENTITY::SET_ENTITY_VISIBLE(ent, false, false);
		NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(ent, true);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 0, 0, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, 1, 1);
		ENTITY::DELETE_ENTITY(&ent);
	}

	inline bool raycast(Entity* ent)
	{
		BOOL hit;
		Vector3 endCoords;
		Vector3 surfaceNormal;

		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot       = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir       = math::rotation_to_direction(rot);
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x,
		    camCoords.y,
		    camCoords.z,
		    farCoords.x,
		    farCoords.y,
		    farCoords.z,
		    -1,
		    0,
		    7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

		return (bool)hit;
	}

	inline bool network_has_control_of_entity(rage::netObject* net_object)
	{
		return !net_object || !net_object->m_next_owner_id && (net_object->m_control_id == -1);
	}

	inline bool take_control_of(Entity ent, int timeout = 300)
	{
		if (!*g_pointers->m_gta.m_is_session_started)
			return true;

		auto hnd = g_pointers->m_gta.m_handle_to_ptr(ent);

		if (!hnd || !hnd->m_net_object || !*g_pointers->m_gta.m_is_session_started)
			return false;

		if (network_has_control_of_entity(hnd->m_net_object))
			return true;

		for (int i = 0; i < timeout; i++)
		{
			g_pointers->m_gta.m_request_control(hnd->m_net_object);

			if (network_has_control_of_entity(hnd->m_net_object))
				return true;

			if (timeout != 0)
				script::get_current()->yield();
		}

		return false;
	}

	inline std::vector<Entity> get_entities(bool vehicles, bool peds)
	{
		std::vector<Entity> target_entities;
		target_entities.clear();

		if (vehicles)
		{
			for (auto vehicle : pools::get_all_vehicles())
			{
				if (vehicle == gta_util::get_local_vehicle())
					continue;

				target_entities.push_back(g_pointers->m_gta.m_ptr_to_handle(vehicle));
			}
		}

		if (peds)
		{
			for (auto ped : pools::get_all_peds())
			{
				// make sure to not include ourselves
				if (ped == gta_util::get_local_ped())
					continue;

				target_entities.push_back(g_pointers->m_gta.m_ptr_to_handle(ped));
			}
		}
		return target_entities;
	}

	inline bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			script::get_current()->yield();
		}

		location.z = 1000.f;

		return false;
	}

	inline double distance_to_middle_of_screen(const rage::fvector2& screen_pos)
	{
		double cumulative_distance{};

		if (screen_pos.x > 0.5)
			cumulative_distance += screen_pos.x - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.x;

		if (screen_pos.y > 0.5)
			cumulative_distance += screen_pos.y - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.y;

		return cumulative_distance;
	}

	inline Entity get_entity_closest_to_middle_of_screen()
	{
		Entity closest_entity{};
		float distance = 1;

		auto replayInterface = *g_pointers->m_gta.m_replay_interface;

		for (const auto veh : pools::get_all_vehicles())
		{
			if (veh)
			{
				Vehicle handle = g_pointers->m_gta.m_ptr_to_handle(veh);
				Vector3 pos    = ENTITY::GET_ENTITY_COORDS(handle, 1);
				rage::fvector2 screenpos;
				HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos.x, pos.y, pos.z, &screenpos.x, &screenpos.y);

				if (distance_to_middle_of_screen(screenpos) < distance && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), handle, 17))
				{
					closest_entity = handle;
					distance       = distance_to_middle_of_screen(screenpos);
				}
			}
		}

		for (auto ped : pools::get_all_peds())
		{
			if (ped)
			{
				Vehicle handle = g_pointers->m_gta.m_ptr_to_handle(ped);
				Vector3 pos    = ENTITY::GET_ENTITY_COORDS(handle, 1);
				rage::fvector2 screenpos;
				HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos.x, pos.y, pos.z, &screenpos.x, &screenpos.y);

				if (distance_to_middle_of_screen(screenpos) < distance && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), handle, 17) && handle != PLAYER::PLAYER_PED_ID())
				{
					closest_entity = handle;
					distance       = distance_to_middle_of_screen(screenpos);
				}
			}
		}

		return closest_entity;
	}
}