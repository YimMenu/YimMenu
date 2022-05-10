#include "context_menu_service.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/replay.hpp"

namespace big
{
	context_menu_service::context_menu_service()
	{
		g_context_menu_service = this;
		load_shared();
	}

	context_menu_service::~context_menu_service()
	{
		g_context_menu_service = nullptr;
	}

	void context_menu_service::load_shared()
	{
		for (auto& item : options)
		{
			if (item.first == ContextEntityType::SHARED) continue;
			item.second.options.insert(item.second.options.end(), options.at(ContextEntityType::SHARED).options.begin(), options.at(ContextEntityType::SHARED).options.end());

			int max_size = 0;
			for (auto& option : item.second.options)
			{
				max_size = (float)(max_size < option.name.length() ? option.name.length() : max_size);
			}

			LOG(INFO) << (int)item.second.options.size();

			item.second.menu_size = { (10.f * max_size) + 10.f , 2 * (10.f * (float)item.second.options.size()) + 10.f  };
		}
	}


	s_context_menu* context_menu_service::get_context_menu()
	{
		if (pointer && pointer->m_model_info)
			switch (pointer->m_model_info->m_model_type)
			{
			case (int)eModelType::Ped:
					if (((CPed*)pointer)->m_vehicle && ((CPed*)pointer)->m_ped_task_flag & (int)ePedTask::TASK_DRIVING)
					{
						pointer = ((CPed*)pointer)->m_vehicle;
						return &options.at(ContextEntityType::VEHICLE);
					}
					if (((CPed*)pointer)->m_player_info)
						return &options.at(ContextEntityType::PLAYER);
					return &options.at(ContextEntityType::PED);
				case (int)eModelType::Vehicle:
					return &options.at(ContextEntityType::VEHICLE);
				default:
					return &options.at(ContextEntityType::SHARED);
			}
		return nullptr;
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
			rage::CObjectInterface* objinterface = replay->m_object_interface;

			if (vehinterface && pedinterface && objinterface) {

				int vehinterfacesize = vehinterface->m_max_vehicles;
				int pedinterfacesize = pedinterface->m_max_peds;
				int objectinterfacesize = objinterface->m_max_objects;
				rage::CEntityHandle* allentities = new rage::CEntityHandle[vehinterfacesize + pedinterfacesize + objectinterfacesize];

				std::copy(pedinterface->m_ped_list->m_peds, pedinterface->m_ped_list->m_peds + pedinterfacesize, allentities);
				std::copy(vehinterface->m_vehicle_list->m_vehicles, vehinterface->m_vehicle_list->m_vehicles + vehinterfacesize, allentities + pedinterfacesize);
				std::copy(objinterface->m_object_list->m_objects, objinterface->m_object_list->m_objects + objectinterfacesize, allentities + pedinterfacesize + vehinterfacesize);

				for (int i = 0; i < vehinterfacesize + pedinterfacesize + objectinterfacesize; i++)
				{
					if (allentities[i].m_entity_ptr) {
						temp_pointer = allentities[i].m_entity_ptr;
						temp_handle = g_pointers->m_ptr_to_handle(temp_pointer);

						if (!temp_pointer->m_navigation) continue;

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
