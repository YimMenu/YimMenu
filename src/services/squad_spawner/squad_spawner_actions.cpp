#include "squad_spawner.hpp"
#include "util/entity.hpp"

namespace big
{

	void squad_spawner::terminate_squads()
	{
		for (auto& s : m_active_squads)
		{
			if (entity::take_control_of(s.m_veh_handle))
			{
				entity::delete_entity(s.m_veh_handle);
			}

			for (auto& m : s.m_members)
			{
				if (entity::take_control_of(m.handle))
				{
					ENTITY::SET_ENTITY_HEALTH(m.handle, 0, false, 0);
					entity::delete_entity(m.handle);
				}
			}
		}
	}

	void squad_spawner::terminate_squad(squad* s)
	{
		if (!s)
			return;

		if (entity::take_control_of(s->m_veh_handle))
		{
			entity::delete_entity(s->m_veh_handle);
		}

		for (auto& m : s->m_members)
		{
			if (entity::take_control_of(m.handle))
			{
				ENTITY::SET_ENTITY_HEALTH(m.handle, 0, false, 0);
				entity::delete_entity(m.handle);
			}
		}
	}

	void squad_spawner::build_and_perform_sequence(squad& s, int member)
	{
		TASK::OPEN_SEQUENCE_TASK(&s.m_members[member].task_sequence);

		if (member == 0 && s.does_squad_have_vehicle())
		{
			if (VEHICLE::IS_THIS_MODEL_A_CAR(rage::joaat(s.m_vehicle_model)))
			{
				TASK::TASK_VEHICLE_MISSION_PED_TARGET(0, s.m_veh_handle, s.current_target_ped, s.m_stay_in_veh ? 6 : 4, 100.f, 786468, 12.f, 5.f, true);
				if (!s.m_stay_in_veh)
					TASK::TASK_LEAVE_ANY_VEHICLE(0, 0, 0);
			}
			else if (VEHICLE::IS_THIS_MODEL_A_HELI(rage::joaat(s.m_vehicle_model)))
			{
				TASK::TASK_HELI_MISSION(0, s.m_veh_handle, 0, s.current_target_ped, 0, 0, 0, 6, 200.f, 30.f, -1, 50.f, 20.f, -1, 128 | 4096);
				VEHICLE::SET_HELI_BLADES_FULL_SPEED(s.m_veh_handle);
			}
			else if (VEHICLE::IS_THIS_MODEL_A_PLANE(rage::joaat(s.m_vehicle_model)))
			{
				TASK::TASK_PLANE_MISSION(0, s.m_veh_handle, 0, s.current_target_ped, 0, 0, 0, 6, 300, 35.f, -1, 100.f, 20.f, true);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(s.m_veh_handle, 30.f);
			}
			else if (VEHICLE::IS_THIS_MODEL_A_BOAT(rage::joaat(s.m_vehicle_model)))
			{
				TASK::TASK_BOAT_MISSION(0, s.m_veh_handle, 0, s.current_target_ped, 0, 0, 0, 6, 300, 786468, 10.f, 7);
			}
		}

		TASK::TASK_COMBAT_PED(0, s.current_target_ped, 67108864, 16); //flag 67108864 should prevent peds from attaining other targets
		TASK::SET_SEQUENCE_TO_REPEAT(s.m_members[member].task_sequence, 1);
		TASK::CLOSE_SEQUENCE_TASK(s.m_members[member].task_sequence);
		TASK::TASK_PERFORM_SEQUENCE(s.m_members[member].handle, s.m_members[member].task_sequence);
	}
}