#include "squad_spawner.hpp"

#include "gta/joaat.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "util/math.hpp"
#include "util/pathfind.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

namespace big
{

	squad_member squad_spawner::spawn_squad_member(squad s)
	{
		auto handle = ped::spawn(ePedType::PED_TYPE_CIVMALE, rage::joaat(s.m_ped_model), 0, s.m_spawn_pos, 0, true);

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
				ENTITY::SET_ENTITY_HEALTH(handle, s.m_ped_health, 0, 0);
			}
			if (s.should_override_armor())
			{
				PED::SET_PED_ARMOUR(handle, s.m_ped_armor);
			}

			WEAPON::GIVE_WEAPON_TO_PED(handle, rage::joaat(s.m_weapon_model), 9999, false, true);
			PED::SET_PED_ACCURACY(handle, s.m_ped_accuracy);
			PED::SET_PED_COMBAT_ABILITY(handle, (int)s.m_combat_ability_level);
			ENTITY::SET_ENTITY_INVINCIBLE(handle, s.m_ped_invincibility);
			HUD::SET_PED_HAS_AI_BLIP(handle, true);
			HUD::SET_PED_AI_BLIP_FORCED_ON(handle, true);
		}
		return squad_member(handle, reinterpret_cast<CPed*>(g_pointers->m_gta.m_handle_to_ptr(handle)), -1);
	}

	std::pair<Vehicle, CVehicle*> squad_spawner::spawn_squad_vehicle(squad s)
	{
		std::pair<Vehicle, CVehicle*> veh;
		if (!s.does_squad_have_persistent_vehicle())
		{
			veh.first = vehicle::spawn(rage::joaat(s.m_vehicle_model), s.m_spawn_pos, s.m_spawn_heading);
		}
		else
		{
			const auto persistent_vehicles = persist_car_service::list_files();

			for (auto c : persistent_vehicles)
			{
				if (c == s.m_persistent_vehicle)
				{
					veh.first = persist_car_service::load_vehicle(c);
					ENTITY::SET_ENTITY_COORDS(veh.first, s.m_spawn_pos.x, s.m_spawn_pos.y, s.m_spawn_pos.z, 0, 0, 0, 1);
					break;
				}
			}
		}

		veh.second = (CVehicle*)g_pointers->m_gta.m_handle_to_ptr(veh.first);

		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh.first, 5);
		ENTITY::SET_ENTITY_INVINCIBLE(veh.first, s.m_veh_invincibility);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh.first, true, true, false);
		ENTITY::SET_ENTITY_HEADING(veh.first, s.m_spawn_heading);

		if (s.m_max_vehicle)
			vehicle::max_vehicle(veh.first);

		return veh;
	}

	bool find_road(squad& s)
	{
		const Vector3 original_pos   = s.m_spawn_pos;
		const Vector3 target_ped_pos = ENTITY::GET_ENTITY_COORDS(s.current_target_ped, false);
		Vector3 south, north, chosen_pos;

		//Initial search for an actual road
		pathfind::find_closest_road(s.m_spawn_pos, &south, &north);

		//Check which is closer
		if (math::distance_between_vectors(south, s.m_spawn_pos) <= math::distance_between_vectors(north, s.m_spawn_pos))
			chosen_pos = south;
		else
			chosen_pos = north;

		//Get a node to specify heading
		for (int i = 0; i < 100; i++)
		{
			if (pathfind::find_closest_vehicle_node_favour_direction(chosen_pos, target_ped_pos, s.m_spawn_pos, s.m_spawn_heading, 0, i) && math::distance_between_vectors(target_ped_pos, s.m_spawn_pos) >= s.m_spawn_distance)
				return true;
		}

		s.m_spawn_pos = original_pos;
		return false;
	}

	bool squad_spawner::find_suitable_spawn_pos(squad& s)
	{
		const Vector3 original_pos = s.m_spawn_pos;
		Hash veh_model_hash        = rage::joaat(s.m_vehicle_model);
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

		const float original_spawn_distance = s.m_spawn_distance;

		static auto reset_spawn_pos_to_offset = [&]() -> void {
			Ped player_ped_handle = g_pointers->m_gta.m_ptr_to_handle(s.target->get_ped());
			s.m_spawn_pos         = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped_handle, 0, -7, 0);
			g_notification_service.push_warning("GUI_TAB_SQUAD_SPAWNER"_T.data(), "SQUAD_SPAWNER_NO_SPOT_FOUND"_T.data());
		};

		static auto is_pos_valid = [&]() -> bool {
			return math::distance_between_vectors(new_pos, s.m_spawn_pos) < (s.m_spawn_distance + 50.f) && new_pos != s.m_spawn_pos;
		};

		static auto find_location = [&]() -> void {
			for (int i = 0; i < 10; i++)
			{
				if (pathfind::find_random_location_in_vicinity_precise(s.m_spawn_pos, new_pos, s.m_spawn_heading, node_search_flag, s.m_spawn_distance, 200, true))
					break;
			}
		};

		//Use spawn distance to find a position ahead of target and limit the vicinity
		if (s.m_spawn_ahead)
		{
			s.m_spawn_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(s.current_target_ped, 0.0, s.m_spawn_distance, 0.0);
			s.m_spawn_distance = 5.f;
		}

		//Actual algorithm to find a nice spot
		find_location();

		//Try and find a road
		if (s.m_favour_roads)
		{
			if (find_road(s) && is_pos_valid())
				return true;

			//If the road search failed, revert to original method
			find_location();
		}

		//Reset if all searches failed with an allowance of up to 50.0f
		if (!is_pos_valid())
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
			g_notification_service.push_error("GUI_TAB_SQUAD_SPAWNER"_T.data(), "SQUAD_SPAWNER_ERROR_SPAWN"_T.data());
			return false;
		}

		if (std::string(s.m_name).empty())
		{
			s.m_name = std::string(std::to_string(s.m_squad_size) + std::string("_").append(s.m_ped_model).append("_").append(std::to_string(s.m_internal_id)));
		}

		Hash veh_model_hash  = rage::joaat(s.m_vehicle_model);
		s.current_target_ped = g_pointers->m_gta.m_ptr_to_handle(s.target->get_ped());
		float heading;

		//Check if squad size is suitable in case a vehicle is defined
		if (s.does_squad_have_vehicle())
		{
			if (VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(veh_model_hash) < s.m_squad_size)
			{
				s.m_squad_size = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(veh_model_hash);
				g_notification_service.push_warning("GUI_TAB_SQUAD_SPAWNER"_T.data(), "SQUAD_SPAWNER_INSUFFICIENT_SEATS"_T.data());
			}
		}

		//Decide spawn location
		if (!override_spawn_pos)
		{
			s.m_spawn_pos = ENTITY::GET_ENTITY_COORDS(s.current_target_ped, true);

			if (s.m_spawn_distance_mode == eSquadSpawnDistance::ON_TARGET)
			{
				s.m_spawn_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(s.current_target_ped, 0.0, -7.f, 0.0);
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

		if (VEHICLE::IS_THIS_MODEL_A_PLANE(veh_model_hash) || VEHICLE::IS_THIS_MODEL_A_HELI(veh_model_hash))
			s.m_spawn_pos.z += 50.f;

		//Spawn squad vehicle
		if (s.does_squad_have_vehicle())
		{
			std::pair<Vehicle, CVehicle*> squad_veh = squad_spawner::spawn_squad_vehicle(s);
			s.m_veh_handle                          = squad_veh.first;
			s.m_veh_ptr                             = squad_veh.second;
		}
		bool veh_spawned = ENTITY::DOES_ENTITY_EXIST(s.m_veh_handle);

		//Spawn squad members
		const Vector3 original_pos = s.m_spawn_pos;
		for (int i = 0; i < s.m_squad_size; i++)
		{
			//Find random position for each consecutive member if disperse is enabled
			if (i > 0 && s.m_disperse && !s.does_squad_have_vehicle())
				squad_spawner::find_suitable_spawn_pos(s);

			s.m_members.push_back(squad_spawner::spawn_squad_member(s));

			//Catch position change of Disperse and revert
			s.m_spawn_pos = original_pos;

			if (entity::take_control_of(s.m_members[i].handle))
			{
				if (veh_spawned)
					PED::SET_PED_INTO_VEHICLE(s.m_members[i].handle, s.m_veh_handle, (i - 1));
				PED::SET_PED_RELATIONSHIP_GROUP_HASH(s.m_members[i].handle, "HATES_PLAYER"_J);

				squad_spawner::build_and_perform_sequence(s, i);

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

		if (s.has_squad_spawned())
		{
			m_active_squads.push_back(s);
			script::get_current()->yield(100ms);
			return true;
		}
		return false;
	}

	void squad_spawner::tick()
	{
		for (auto& s : m_active_squads)
		{
			if (s.is_squad_alive())
			{
				for (auto& m : s.m_members)
				{
					//This can be used to track attacker progress regarding their task. Anything above -1 means it is in progress.
					m.task_sequence_progress = TASK::GET_SEQUENCE_PROGRESS(m.handle);
				}
			}
			else
			{
				std::erase_if(g_squad_spawner_service.m_active_squads, [s](squad s_) {
					return s.get_id() == s_.get_id();
				});
			}
		}
	}
}
