#include "pointers.hpp"
#include "util/entity.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::world()
	{
		ImGui::SeparatorText("GUI_TAB_TIME_N_WEATHER"_T.data());
		{
			view::time_and_weather();
		}

		ImGui::SeparatorText("GUI_TAB_GRAVITY"_T.data());
		{
			view::gravity();
		}

		ImGui::SeparatorText("GUI_TAB_OCEAN"_T.data());
		{
			view::ocean();
		}

		ImGui::SeparatorText("GUI_TAB_WAYPOINT_N_OBJECTIVE"_T.data());
		{
			view::waypoint_and_objective();
		}

		ImGui::SeparatorText("PED"_T.data());

		components::button<ImVec2(150, 0), ImVec4(0.70196f, 0.3333f, 0.00392f, 1.f)>("VIEW_DEBUG_THREADS_KILL"_T, [] {
			for (auto peds : entity::get_entities(false, true))
			{
				if (!PED::IS_PED_A_PLAYER(peds))
					ped::kill_ped(peds);
			}
		});
		ImGui::SameLine();

		components::button<ImVec2(150, 0), ImVec4(0.76078f, 0.f, 0.03529f, 1.f)>("VIEW_WORLD_KILL_ENEMIES"_T, [] {
			for (auto ped : entity::get_entities(false, true))
			{
				if (!PED::IS_PED_A_PLAYER(ped))
				{
					auto relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, self::ped);
					if (relation == 4 || relation == 5 || relation == 3)
						ped::kill_ped(ped);
				}
			}
		});

		// Nearby Ped Loops / Toggles
		components::command_checkbox<"pedsignore">();
		ImGui::SameLine();
		components::command_checkbox<"pedrain">();
		ImGui::SameLine();
		components::command_checkbox<"riotmode">();
		components::command_checkbox<"highalert">();
		ImGui::SameLine();
		components::command_checkbox<"pedrush">();
		ImGui::SameLine();
		components::command_checkbox<"autodisarm">();
		components::options_modal("VIEW_WORLD_AUTO_DISARM"_T.data(), [] {
			ImGui::Checkbox("VIEW_WORLD_NEUTRALIZE"_T.data(), &g.world.nearby.auto_disarm.neutralize);
		});

		ImGui::SeparatorText("VEHICLES"_T.data());

		components::button<ImVec2(0, 0), ImVec4(0.02745f, 0.4745f, 0.10196f, 1.f)>("MAX_VEHICLE"_T, [] {
			for (auto vehs : entity::get_entities(true, false))
			{
				if (entity::take_control_of(vehs))
				{
					vehicle::max_vehicle(vehs);
					script::get_current()->yield();
				}
			}
		});
		ImGui::SameLine();

		components::button<ImVec2(0, 0), ImVec4(0.4549f, 0.03529f, 0.03529f, 1.f)>("VIEW_WORLD_DOWNGRADE"_T, [] {
			for (auto vehs : entity::get_entities(true, false))
			{
				if (entity::take_control_of(vehs))
				{
					vehicle::downgrade(vehs);
					script::get_current()->yield();
				}
			}
		});

		components::command_checkbox<"vehiclerain">();

		ImGui::SeparatorText("VIEW_BLACKHOLE_ENTITIES"_T.data());

		static bool included_entity_types[3];
		static bool own_vehicle, deleting, force;
		static int quantity, remaining;

		ImGui::Text("VIEW_WORLD_INCLUDE"_T.data());
		ImGui::Checkbox("VEHICLES"_T.data(), &included_entity_types[0]);
		ImGui::SameLine();
		ImGui::Checkbox("PED"_T.data(), &included_entity_types[1]);
		ImGui::SameLine();
		ImGui::Checkbox("VIEW_WORLD_PROPS"_T.data(), &included_entity_types[2]);

		if (included_entity_types[0])
		{
			ImGui::Checkbox("VIEW_WORLD_SELF_VEHICLE"_T.data(), &own_vehicle);
			ImGui::SameLine();
		}

		ImGui::Checkbox("FORCE"_T.data(), &force);

		if (deleting)
		{
			float progress = 1 - static_cast<float>(remaining) / quantity;
			ImGui::ProgressBar(progress, ImVec2(200, 25));
		}
		else
		{
			components::button("VIEW_WORLD_DELETE_ALL"_T, [&] {
				auto list = entity::get_entities(included_entity_types[0], included_entity_types[1], included_entity_types[2], own_vehicle);

				quantity  = list.size();
				remaining = quantity;
				g_notification_service.push("GUI_TAB_TIME_N_WEATHER"_T.data(), std::format("Deleting {} entities", quantity));
				deleting   = true;
				int failed = 0;

				for (auto ent : list)
				{
					if (PED::IS_PED_A_PLAYER(ent))
						continue;

					if (ENTITY::DOES_ENTITY_EXIST(ent))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
							if (ent == self::veh && own_vehicle)
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);

						if (force)
						{
							auto ptr = g_pointers->m_gta.m_handle_to_ptr(ent);

							switch (ptr->m_entity_type)
							{
							case 4: g_pointers->m_gta.m_delete_ped(reinterpret_cast<CPed*>(ptr)); break;
							case 3: g_pointers->m_gta.m_delete_vehicle(reinterpret_cast<CVehicle*>(ptr)); break;
							case 5: g_pointers->m_gta.m_delete_object(reinterpret_cast<CObject*>(ptr), false); break;
							}
						}
						else
						{
							if (entity::take_control_of(ent, 25))
								entity::delete_entity(ent);
						}
					}

					if (ENTITY::DOES_ENTITY_EXIST(ent))
						failed++;
					else
						remaining--;
				}

				if (failed > 0)
					g_notification_service.push_warning("GUI_TAB_TIME_N_WEATHER"_T.data(), std::format("Failed deleting {} entities", failed));

				deleting = false;
			});
		}
	}
}
