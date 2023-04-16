#include "squad_spawner.hpp"

#include "gta/joaat.hpp"
#include "util/math.hpp"
#include "util/pathfind.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

namespace big
{

	squad_member squad_spawner::spawn_squad_member(squad s)
	{
		Ped handle{};
		CPed* ptr{};

		handle = ped::spawn(ePedType::PED_TYPE_CIVMALE, rage::joaat(s.m_ped_model), 0, s.m_spawn_pos, 0, true);
		ptr    = reinterpret_cast<CPed*>(g_pointers->m_gta.m_handle_to_ptr(handle));

		if (entity::take_control_of(handle))
		{
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(handle, true);
			PED::SET_PED_CAN_BE_DRAGGED_OUT(handle, false);
			PED::SET_RAGDOLL_BLOCKING_FLAGS(handle, 1 | 16);  //Block player ragdoll impacts, bullet and colission
			if (s.m_ped_proofs[4])
				PED::SET_RAGDOLL_BLOCKING_FLAGS(handle, 128); //Check for melee proof and disable corresponding ragdoll

			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 2, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 4, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 5, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 21, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 23, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 25, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 26, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 28, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 46, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 58, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 59, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 69, true);
			PED::SET_PED_COMBAT_ATTRIBUTES(handle, 70, true);

			PED::SET_PED_CONFIG_FLAG(handle, 26, true);
			PED::SET_PED_CONFIG_FLAG(handle, 42, true);
			PED::SET_PED_CONFIG_FLAG(handle, 44, true);
			PED::SET_PED_CONFIG_FLAG(handle, 45, false);
			PED::SET_PED_CONFIG_FLAG(handle, 229, true);
			PED::SET_PED_CONFIG_FLAG(handle, 241, true);
			PED::SET_PED_CONFIG_FLAG(handle, 268, true);

			ENTITY::SET_ENTITY_PROOFS(handle, s.m_ped_proofs[1], s.m_ped_proofs[2], s.m_ped_proofs[4], false, s.m_ped_proofs[3], 0, 0, 0);
			PED::SET_PED_SUFFERS_CRITICAL_HITS(handle, !s.m_ped_proofs[0]); //Headshot bool is true to disable, hence the unary prefix '!'
			TASK::SET_PED_PATH_MAY_ENTER_WATER(handle, true);
			TASK::SET_PED_PATH_PREFER_TO_AVOID_WATER(handle, true);

			if (s.should_override_health())
			{
				PED::SET_PED_MAX_HEALTH(handle, s.m_ped_health);
				ENTITY::SET_ENTITY_HEALTH(handle, s.m_ped_health, 0);
			}
			if (s.should_override_armor())
			{
				PED::SET_PED_ARMOUR(handle, s.m_ped_armor);
			}

			WEAPON::GIVE_WEAPON_TO_PED(handle, rage::joaat(s.m_weapon_model), 999, false, true);
			PED::SET_PED_ACCURACY(handle, s.m_ped_accuracy);
			PED::SET_PED_COMBAT_ABILITY(handle, (int)s.m_combat_ability_level);
			ENTITY::SET_ENTITY_INVINCIBLE(handle, s.m_ped_invincibility);
			HUD::SET_PED_HAS_AI_BLIP(handle, true);
			HUD::SET_PED_AI_BLIP_FORCED_ON(handle, true);
		}
		return {handle, ptr};
	}

	std::pair<Vehicle, CVehicle*> squad_spawner::spawn_squad_vehicle(squad s)
	{
		Vehicle handle{};
		CVehicle* ptr{};

		handle = vehicle::spawn(rage::joaat(s.m_vehicle_model), s.m_spawn_pos, 0);
		ptr    = reinterpret_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(handle));

		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(handle, 5);
		ENTITY::SET_ENTITY_INVINCIBLE(handle, s.m_veh_invincibility);
		VEHICLE::SET_VEHICLE_ENGINE_ON(handle, true, true, false);

		return std::pair<Vehicle, CVehicle*>(handle, ptr);
	}

	bool squad_spawner::find_suitable_spawn_pos(squad& s)
	{
		Hash veh_model_hash = rage::joaat(s.m_vehicle_model);
		int node_search_flag = (VEHICLE::IS_THIS_MODEL_A_BOAT(veh_model_hash) || VEHICLE::IS_THIS_MODEL_A_JETSKI(veh_model_hash)) ? 2 : 0;
		Vector3 new_pos = s.m_spawn_pos;

		if (!s.should_override_spawn_distance())
		{
			switch (s.m_spawn_distance_mode)
			{
			case eSquadSpawnDistance::CLOSEBY: s.m_spawn_distance = 25.f; break;
			case eSquadSpawnDistance::FAR_AWAY: s.m_spawn_distance = 100.f; break;
			case eSquadSpawnDistance::ON_TARGET: s.m_spawn_distance = 10.f; break;
			case eSquadSpawnDistance::MODERATELY_DISTANCED: s.m_spawn_distance = 70.f; break;
			}
		}

		//LOG(INFO) << "Squad spawner: Desired distance determined at " << s.m_spawn_distance;

		static auto reset_spawn_pos_to_offset = [&]() -> void {
			Ped player_ped_handle = g_pointers->m_gta.m_ptr_to_handle(s.target->get_ped());
			s.m_spawn_pos         = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped_handle, 0, -7, 0);
			//LOG(INFO) << "Squad spawner: No suitable spot found, spawning at an offset";
			g_notification_service->push_warning("Squad Spawner", "No suitable spot found, spawning at an offset");
		};

		for (int i = 0; i < 10; i++)
		{
			if (pathfind::find_random_location_in_vicinity(s.m_spawn_pos, new_pos, s.m_spawn_heading, node_search_flag, s.m_spawn_distance))
				break;
		}

		//Reset at a distance of 150 or if all searches failed
		if (math::distance_between_vectors(new_pos, s.m_spawn_pos) > 150 || new_pos == s.m_spawn_pos)
		{
			reset_spawn_pos_to_offset();
			return false;
		}

		s.m_spawn_pos = new_pos;

		return true;
	}

	bool squad_spawner::spawn_squad(squad s, player_ptr target_player, bool override_spawn_pos = false, Vector3 custom_pos = {})
	{
		s.target = target_player;

		if (!s.target->get_net_game_player() || s.m_squad_size < 1 || !STREAMING::IS_MODEL_VALID(rage::joaat(s.m_ped_model)))
		{
			g_notification_service->push_error("Squad spawner", "Error spawning squad");
			return false;
		}

		if (std::string(s.m_name).empty())
			strcpy(s.m_name,
			    std::string(std::to_string(s.m_squad_size) + std::string("_").append(s.m_ped_model).append("_").append(std::to_string(s.m_internal_id)))
			        .data());

		Hash veh_model_hash = rage::joaat(s.m_vehicle_model);
		Ped target_ped      = g_pointers->m_gta.m_ptr_to_handle(s.target->get_ped());
		float heading;

		//Check if squad size is suitable in case a vehicle is defined
		if (s.does_squad_have_vehicle())
		{
			if (VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(veh_model_hash) < s.m_squad_size)
			{
				s.m_squad_size = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(veh_model_hash);
				g_notification_service->push_warning("Squad Spawner", "The squad vehicle has insufficient seats, decreasing the squad size");
			}
		}

		//Decide spawn location
		if (!override_spawn_pos)
		{
			s.m_spawn_pos = ENTITY::GET_ENTITY_COORDS(target_ped, true);

			if (s.m_spawn_distance_mode == eSquadSpawnDistance::ON_TARGET)
			{
				s.m_spawn_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target_ped, 0.0, -7.f, 0.0);
			}
			else
			{
				g_squad_spawner_service.find_suitable_spawn_pos(s);
			}
		}
		else
		{
			s.m_spawn_pos = custom_pos;
		}


		//LOG(INFO) << "Squad spawner: Distance from target determined: " << math::distance_between_vectors(s.m_spawn_pos, ENTITY::GET_ENTITY_COORDS(target_ped, true));

		//Spawn squad vehicle
		if (s.does_squad_have_vehicle())
		{
			std::pair<Vehicle, CVehicle*> squad_veh = squad_spawner::spawn_squad_vehicle(s);
			s.m_veh_handle                          = squad_veh.first;
			s.m_veh_ptr                             = squad_veh.second;
		}
		bool veh_spawned = ENTITY::DOES_ENTITY_EXIST(s.m_veh_handle);

		//if (!veh_spawned && s.does_squad_have_vehicle())
		//	LOG(INFO) << "Squad spawner: Failed spawning squad vehicle";

		//Spawn squad members
		for (int i = 0; i < s.m_squad_size; i++)
		{
			s.m_members.push_back(squad_spawner::spawn_squad_member(s));

			if (entity::take_control_of(s.m_members[i].handle))
			{
				if (veh_spawned)
					PED::SET_PED_INTO_VEHICLE(s.m_members[i].handle, s.m_veh_handle, (i - 1));
				PED::SET_PED_RELATIONSHIP_GROUP_HASH(s.m_members[i].handle, RAGE_JOAAT("HATES_PLAYER"));

				int seq;
				TASK::OPEN_SEQUENCE_TASK(&seq);
				if (veh_spawned)
				{
					if (i == 0)
					{
						if (VEHICLE::IS_THIS_MODEL_A_CAR(veh_model_hash))
						{
							TASK::TASK_VEHICLE_MISSION_PED_TARGET(0, s.m_veh_handle, target_ped, s.m_stay_in_veh ? 6 : 4, 100.f, 786468, 5.f, 5.f, true);
							if (!s.m_stay_in_veh)
								TASK::TASK_LEAVE_ANY_VEHICLE(0, 0, 0);
						}
						else if (VEHICLE::IS_THIS_MODEL_A_HELI(veh_model_hash))
						{
							TASK::TASK_HELI_MISSION(0, s.m_veh_handle, 0, target_ped, 0, 0, 0, 6, 200.f, 30.f, -1, 50.f, 20.f, -1, 128 | 4096);
							VEHICLE::SET_HELI_BLADES_FULL_SPEED(s.m_veh_handle);
						}
						else if (VEHICLE::IS_THIS_MODEL_A_PLANE(veh_model_hash))
						{
							TASK::TASK_PLANE_MISSION(0, s.m_veh_handle, 0, target_ped, 0, 0, 0, 6, 300, 35.f, -1, 100.f, 20.f, true);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(s.m_veh_handle, 30.f);
						}
						else if (VEHICLE::IS_THIS_MODEL_A_BOAT(veh_model_hash))
						{
							TASK::TASK_BOAT_MISSION(0, s.m_veh_handle, 0, target_ped, 0, 0, 0, 6, 300, 786468, 10.f, 7);
						}
					}
				}

				TASK::TASK_COMBAT_PED(0, target_ped, 67108864, 16); //flag 67108864 should prevent peds from attaining other targets
				TASK::CLOSE_SEQUENCE_TASK(seq);
				TASK::TASK_PERFORM_SEQUENCE(s.m_members[i].handle, seq);
				TASK::CLEAR_SEQUENCE_TASK(&seq);

				if (s.m_stay_in_veh)
					PED::SET_PED_COMBAT_ATTRIBUTES(s.m_members[i].handle, 3, false);
			}
		}

		if (s.m_spawn_behind_same_velocity && s.does_squad_have_vehicle() && veh_spawned && target_player->get_current_vehicle())
		{
			Vehicle target_vehicle = g_pointers->m_gta.m_ptr_to_handle(target_player->get_current_vehicle());

			if (ENTITY::GET_ENTITY_SPEED(target_vehicle) > 25.f && entity::take_control_of(s.m_veh_handle))
			{
				Vector3 velocity  = ENTITY::GET_ENTITY_VELOCITY(target_vehicle);
				Vector3 behindpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target_vehicle, 0.f, -7.f, 0.f);
				float heading     = ENTITY::GET_ENTITY_HEADING(target_vehicle);

				ENTITY::SET_ENTITY_COORDS(s.m_veh_handle, behindpos.x, behindpos.y, behindpos.z, 0, 0, 0, false);
				ENTITY::SET_ENTITY_HEADING(s.m_veh_handle, heading);
				ENTITY::SET_ENTITY_VELOCITY(s.m_veh_handle, velocity.x, velocity.y, velocity.z);
			}
		}

		if (VEHICLE::IS_THIS_MODEL_A_PLANE(veh_model_hash) || VEHICLE::IS_THIS_MODEL_A_HELI(veh_model_hash))
			s.m_spawn_pos.z += 50.f;

		if (s.has_squad_spawned())
		{
			m_active_squads.push_back(s);
			return true;
		}
		return false;
	}
}