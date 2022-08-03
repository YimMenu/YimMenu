#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/enums.hpp"
#include "util/math.hpp"

namespace big
{
	void looped::teleport_mission_object_list()
	{
		if (!g->teleport.mission_veh_list_updated)
		{
			g->teleport.mission_veh_list.clear();

			if (const auto replay = *g_pointers->m_replay_interface; replay)
			{
				if (const auto veh_interface = replay->m_vehicle_interface; veh_interface)
				{
					const auto veh_interface_size = veh_interface->m_max_vehicles;

					float min_dist = FLT_MAX;
					int32_t m_handle = 0;

					for (int32_t i = 0; i < veh_interface_size; i++)
					{
						auto veh_entity = veh_interface->m_vehicle_list->m_vehicles[i];
						CAutomobile* veh_ptr = (CAutomobile*)veh_entity.m_entity_ptr;

						if (!veh_ptr || !veh_ptr->m_navigation || !veh_ptr->m_model_info)
						{
							continue;
						}

						Vehicle veh = g_pointers->m_ptr_to_handle(veh_ptr);

						if (ENTITY::IS_ENTITY_A_MISSION_ENTITY(veh))
						{
							g->teleport.mission_veh_list[veh] = veh_ptr->m_model_info->m_model_hash;
						}
					}
				}
			}

			g->teleport.mission_veh_list_updated = true;
		}
	}
}