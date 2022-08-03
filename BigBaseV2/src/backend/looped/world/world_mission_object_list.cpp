#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/enums.hpp"
#include "gta/joaat.hpp"
#include "util/math.hpp"

namespace big
{
	void looped::world_mission_object_list()
	{
		if (!g->world.mission_veh_list_updated)
		{
			g->world.mission_veh_list.clear();

			if (const auto replay = *g_pointers->m_replay_interface; replay)
			{
				if (const auto veh_interface = replay->m_vehicle_interface; veh_interface)
				{
					const auto veh_interface_size = veh_interface->m_max_vehicles;

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
							g->world.mission_veh_list[veh] = veh_ptr->m_model_info->m_model_hash;
						}
					}
				}
			}

			g->world.mission_veh_list_updated = true;
		}

		if (!g->world.mission_ped_list_updated)
		{
			g->world.mission_ped_list.clear();

			if (const auto replay = *g_pointers->m_replay_interface; replay)
			{
				if (const auto ped_interface = replay->m_ped_interface; ped_interface)
				{
					const auto ped_interface_size = ped_interface->m_max_peds;

					for (int32_t i = 0; i < ped_interface_size; i++)
					{
						auto ped_entity = ped_interface->m_ped_list->m_peds[i];
						CPed* ped_ptr = (CPed*)ped_entity.m_entity_ptr;

						if (!ped_ptr || !ped_ptr->m_navigation || !ped_ptr->m_model_info)
						{
							continue;
						}

						Ped ped = g_pointers->m_ptr_to_handle(ped_ptr);

						if (ENTITY::IS_ENTITY_A_MISSION_ENTITY(ped))
						{
							Hash model = ped_ptr->m_model_info->m_model_hash;

							if (
								model == RAGE_JOAAT("MP_M_Freemode_01") || 
								model == RAGE_JOAAT("MP_F_Freemode_01") ||
								model == RAGE_JOAAT("S_M_M_AmmyCountry") ||
								model == RAGE_JOAAT("U_M_Y_Tattoo_01") ||
								model == RAGE_JOAAT("S_M_M_HairDress_01") ||
								model == RAGE_JOAAT("S_F_M_Fembarber_01") ||
								model == RAGE_JOAAT("MP_M_ShopKeep_01") ||
								model == RAGE_JOAAT("S_F_M_Shop_HIGH") ||
								model == RAGE_JOAAT("S_F_Y_Shop_MID") ||
								model == RAGE_JOAAT("S_F_Y_Shop_LOW") ||
								model == RAGE_JOAAT("S_M_M_AutoShop_01")
							) {
								continue;
							}

							g->world.mission_ped_list[ped] = ped_ptr->m_model_info->m_model_hash;
						}
					}
				}
			}

			g->world.mission_ped_list_updated = true;
		}
	}
}