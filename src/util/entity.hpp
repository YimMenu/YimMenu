#pragma once
#include "gta/joaat.hpp"
#include "gta/replay.hpp"
#include "gta_util.hpp"
#include "math.hpp"
#include "natives.hpp"
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
		auto ptr = g_pointers->m_handle_to_ptr(ent);
		if (ptr)
		{
			if (!*g_pointers->m_is_session_started || network_has_control_of_entity(ptr->m_net_object))
				return true;
			for (int i = 0; !network_has_control_of_entity(ptr->m_net_object) && i < timeout; i++)
			{
				g_pointers->m_request_control(ptr->m_net_object);
				if (timeout != 0)
					script::get_current()->yield();
			}
			if (!network_has_control_of_entity(ptr->m_net_object))
				return false;
			int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);
		}
		return true;
	}

	inline std::vector<Entity> get_entities(bool vehicles, bool peds)
	{
		std::vector<Entity> target_entities;
		target_entities.clear();
		const auto replay_interface = *g_pointers->m_replay_interface;
		if (!replay_interface)
			return target_entities;

		if (vehicles)
		{
			const auto vehicle_interface = replay_interface->m_vehicle_interface;
			for (int i = 0; i < vehicle_interface->m_max_vehicles; i++)
			{
				const auto vehicle_ptr = vehicle_interface->get_vehicle(i);
				if (!vehicle_ptr)
					continue;

				if (vehicle_ptr == gta_util::get_local_vehicle())
					continue;

				const auto veh = g_pointers->m_ptr_to_handle(vehicle_ptr);
				if (!veh)
					break;

				target_entities.push_back(veh);
			}
		}

		if (peds)
		{
			const auto ped_interface = replay_interface->m_ped_interface;
			for (int i = 0; i < ped_interface->m_max_peds; i++)
			{
				const auto ped_ptr = ped_interface->get_ped(i);
				if (!ped_ptr)
					continue;

				//make sure to don't include ourselves
				if (ped_ptr == gta_util::get_local_ped())
					continue;

				const auto ped = g_pointers->m_ptr_to_handle(ped_ptr);
				if (!ped)
					break;

				target_entities.push_back(ped);
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
}