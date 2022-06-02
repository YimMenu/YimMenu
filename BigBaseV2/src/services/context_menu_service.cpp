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

	double context_menu_service::distance_to_middle_of_screen(const rage::vector2& screen_pos)
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

	s_context_menu* context_menu_service::get_context_menu()
	{
		if (m_pointer && m_pointer->m_model_info)
		{
			switch (m_pointer->m_model_info->m_model_type)
			{
			case eModelType::Object: // Object
			{
				return &options.at(ContextEntityType::OBJECT);
			}
			case eModelType::Ped:
			{
				if (const auto ped = reinterpret_cast<CPed*>(m_pointer); ped)
				{
					if (ped->m_ped_task_flag & static_cast<uint8_t>(ePedTask::TASK_DRIVING) &&
						ped->m_vehicle)
					{
						m_pointer = ped->m_vehicle;
						return &options.at(ContextEntityType::VEHICLE);
					}
					if (ped->m_player_info)
						return &options.at(ContextEntityType::PLAYER);
				}
				return &options.at(ContextEntityType::PED);
			}
			case eModelType::Vehicle:
			{
				return &options.at(ContextEntityType::VEHICLE);
			}
			default:
				break;
			}
		}
		return nullptr;
	}

	void context_menu_service::get_entity_closest_to_screen_center()
	{
		if (const auto replay = *g_pointers->m_replay_interface; replay)
		{
			const auto veh_interface = replay->m_vehicle_interface;
			const auto ped_interface = replay->m_ped_interface;
			const auto obj_interface = replay->m_object_interface;

			if (veh_interface && ped_interface && obj_interface)
			{
				const auto veh_interface_size = veh_interface->m_max_vehicles;
				const auto ped_interface_size = ped_interface->m_max_peds;
				const auto obj_interface_size = obj_interface->m_max_objects;
				const auto all_entities = std::make_unique<rage::CEntityHandle[]>(veh_interface_size + ped_interface_size + obj_interface_size);

				const auto ptr = all_entities.get();
				std::uint32_t offset = 0;
				std::copy(ped_interface->m_ped_list->m_peds, ped_interface->m_ped_list->m_peds + ped_interface_size,ptr);
				offset += ped_interface_size;

				std::copy(veh_interface->m_vehicle_list->m_vehicles, veh_interface->m_vehicle_list->m_vehicles + veh_interface_size, ptr + offset);
				offset += veh_interface_size;

				std::copy(obj_interface->m_object_list->m_objects, obj_interface->m_object_list->m_objects + obj_interface_size, ptr + offset);
				offset += obj_interface_size;

				double distance = 1;
				rage::vector2 screen_pos{};
				for (std::uint32_t i = 0; i < offset; i++)
				{
					if (!all_entities[i].m_entity_ptr)
						continue;

					const auto temp_pointer = all_entities[i].m_entity_ptr;
					const auto temp_handle = g_pointers->m_ptr_to_handle(temp_pointer);
					if (!temp_pointer->m_navigation)
						continue;

					const auto pos = temp_pointer->m_navigation->m_position;
					HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos.x, pos.y, pos.z, &screen_pos.x, &screen_pos.y);
					if (distance_to_middle_of_screen(screen_pos) < distance &&
						ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), temp_handle, 17) &&
						temp_handle != PLAYER::PLAYER_PED_ID()) {
						m_handle = temp_handle;
						m_pointer = temp_pointer;
						distance = distance_to_middle_of_screen(screen_pos);
					}
				}
			}
		}
	}

	void context_menu_service::load_shared()
	{
		for (auto& [type, menu] : options)
		{
			if (type == ContextEntityType::SHARED)
				continue;
			menu.options.insert(menu.options.end(), options.at(ContextEntityType::SHARED).options.begin(), options.at(ContextEntityType::SHARED).options.end());

			std::uint32_t max_size = 0;
			for (auto& [name, _] : menu.options)
			{
				max_size = static_cast<int>(max_size < name.length() ? name.length() : max_size);
			}

			menu.menu_size = { (10.f * static_cast<float>(max_size)) + 10.f , 2 * (10.f * static_cast<float>(menu.options.size())) + 10.f };
		}
	}
	void context_menu_service::context_menu()
	{
		while (g_running)
		{
			if (!g->context_menu.enabled) {
				g_context_menu_service->enabled = false;

				script::get_current()->yield();
				continue;
			}

			if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_DUCK))
			{
				g_context_menu_service->enabled = !g_context_menu_service->enabled;
			}

			if (g_context_menu_service->enabled)
			{
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_NEXT_WEAPON, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_PREV_WEAPON, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_NEXT_RADIO, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SELECT_NEXT_WEAPON, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SELECT_PREV_WEAPON, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY, true);
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_MOUSE_CONTROL_OVERRIDE, true);

				g_context_menu_service->get_entity_closest_to_screen_center();

				const auto cm = g_context_menu_service->get_context_menu();
				if (cm == nullptr)
				{
					script::get_current()->yield();

					continue;
				}

				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
					cm->current_option = cm->options.size() <= cm->current_option + 1 ? 0 : cm->current_option + 1;
				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
					cm->current_option = 0 > cm->current_option - 1 ? static_cast<int>(cm->options.size()) - 1 : cm->current_option - 1;
				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) ||
					PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY))
				{
					if (!g_context_menu_service->m_pointer)
						continue;
					cm->options.at(cm->current_option).command();
				}
			}

			script::get_current()->yield();
		}
	}
}
