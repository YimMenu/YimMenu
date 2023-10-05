
#include "util/entity.hpp"
#include "util/notify.hpp"
#include "util/ped.hpp"
#include "views/view.hpp"

namespace big
{
	void view::world()
	{
		ImGui::SeparatorText("Time And Weather");
		{
			view::time_and_weather();
		}

		ImGui::SeparatorText("Peds");

		components::button<ImVec2(110, 0), ImVec4(0.76078f, 0.f, 0.03529f, 1.f)>("Kill Enemies", [] {
			for (auto ped : entity::get_entities(false, true))
			{
				if (!PED::IS_PED_A_PLAYER(ped))
				{
					auto relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, self::ped);
					if (relation == 4 || relation == 5)
						ped::kill_ped(ped);
				}
			}
		});

		// Nearby Ped Loops / Toggles
		components::command_checkbox<"pedsignore">();
		ImGui::SameLine(140.f);
		components::command_checkbox<"autodisarm">();	

		ImGui::SeparatorText("Entities");

		static bool included_entity_types[3];
		static bool own_vehicle, deleting, force;
		static int quantity, remaining;

		ImGui::Text("Include:");
		ImGui::Checkbox("Vehicles", &included_entity_types[0]);
		ImGui::SameLine();
		ImGui::Checkbox("Peds", &included_entity_types[1]);
		ImGui::SameLine();
		ImGui::Checkbox("Props", &included_entity_types[2]);

		if (included_entity_types[0])
		{
			ImGui::Checkbox("Self vehicle", &own_vehicle);
			ImGui::SameLine();
		}

		ImGui::Checkbox("Force", &force);

		if (deleting)
		{
			float progress = 1 - static_cast<float>(remaining) / quantity;
			ImGui::ProgressBar(progress, ImVec2(200, 25));
		}
		else
		{
			components::button("Delete all", [&] {
				auto list = entity::get_entities(included_entity_types[0], included_entity_types[1], included_entity_types[2], own_vehicle);

				quantity  = list.size();
				remaining = quantity;
				g_notification_service->push("Entity Deletion", std::format("Deleting {} entities", quantity));
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
					g_notification_service->push_warning("Entity Deletion", std::format("Failed deleting {} entities", failed));

				deleting = false;
			});
		}
	}
}