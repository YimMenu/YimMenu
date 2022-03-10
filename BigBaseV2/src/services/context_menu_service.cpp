#include "context_menu_service.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/replay.hpp"

namespace big
{
	context_menu_service::context_menu_service()
	{
		g_context_menu_service = this;
	}

	context_menu_service::~context_menu_service()
	{
		g_context_menu_service = nullptr;
	}

	double context_menu_service::distance_to_middle_of_screen(rage::vector2 screenpos) {

		double cumulativedistance{};

		if (screenpos.x > 0.5)
			cumulativedistance += screenpos.x - 0.5;
		else
			cumulativedistance += 0.5 - screenpos.x;

		if (screenpos.y > 0.5)
			cumulativedistance += screenpos.y - 0.5;
		else
			cumulativedistance += 0.5 - screenpos.y;

		return cumulativedistance;
	}

	void context_menu_service::get_entity_closest_to_screen_center()
	{
		Entity temp_handle{};
		rage::fwEntity* temp_pointer{};
		double distance = 1;
		rage::fvector3 pos{};
		rage::vector2 screenpos{};

		rage::CReplayInterface* replay = *g_pointers->m_replay_interface;

		if (replay) {
			rage::CVehicleInterface* vehinterface = replay->m_vehicle_interface;
			rage::CPedInterface* pedinterface = replay->m_ped_interface;
			//CObjectInterface* objinterface = this->replay->m_object_interface;

			if (vehinterface && pedinterface  /* && objinterface*/) {

				int vehinterfacesize = vehinterface->m_max_vehicles;
				int pedinterfacesize = pedinterface->m_max_peds;
				//int objectinterfacesize = objinterface->m_max_objects;
				rage::CEntityHandle* allentities = new rage::CEntityHandle[vehinterfacesize + pedinterfacesize /* + objectinterfacesize*/];

				std::copy(pedinterface->m_ped_list->m_peds, pedinterface->m_ped_list->m_peds + pedinterfacesize,
				          std::copy(vehinterface->m_vehicle_list->m_vehicles, vehinterface->m_vehicle_list->m_vehicles + vehinterfacesize, allentities));

				for (int i = 0; i < vehinterfacesize + pedinterfacesize; i++)
				{
					if (allentities[i].m_entity_ptr) {
						temp_pointer = allentities[i].m_entity_ptr;
						temp_handle = g_pointers->m_ptr_to_handle(temp_pointer);
						pos = temp_pointer->m_navigation->m_position;
						HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos.x, pos.y, pos.z, &screenpos.x, &screenpos.y);
						if (distance_to_middle_of_screen(screenpos) < distance &&
							ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), temp_handle, 17) &&
							temp_handle != PLAYER::PLAYER_PED_ID()) {
							this->handle = temp_handle;
							this->pointer = temp_pointer;
							distance = distance_to_middle_of_screen(screenpos);
						}
					}
				}

			}
		}
	}

}
