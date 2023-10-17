
#include "core/data/world.hpp"
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
			components::command_checkbox<"timeoverride">();

			if (g_world.custom_time.override_time)
			{
				ImGui::SliderInt("Hour", &g_world.custom_time.hour, 0, 23);
				ImGui::SliderInt("Minute", &g_world.custom_time.minute, 0, 59);
				ImGui::SliderInt("Second", &g_world.custom_time.second, 0, 59);
			}
		}

		ImGui::SeparatorText("Peds");
		{
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

			components::command_checkbox<"pedsignore">();
			ImGui::SameLine(140.f);
			components::command_checkbox<"autodisarm">();
		}

		ImGui::SeparatorText("Entities");
		{
			static bool included_entity_types[2];
			static bool deleting, force;
			static int quantity, remaining;

			ImGui::Text("Include:");
			ImGui::Checkbox("Peds", &included_entity_types[0]);
			ImGui::SameLine();
			ImGui::Checkbox("Props", &included_entity_types[1]);
			ImGui::Spacing();
			ImGui::Checkbox("Force", &force);
			ImGui::Spacing();
			
			if (deleting)
			{
				float progress = 1 - static_cast<float>(remaining) / quantity;
				ImGui::ProgressBar(progress, ImVec2(200, 25));
			}
			else
			{
				components::button("Delete all", [&] {
					auto list = entity::get_entities(false, included_entity_types[0], included_entity_types[1]);
					remaining = quantity = list.size();

					g_notification_service->push("Entity Deletion", std::format("Deleting {} entities", quantity));

					deleting   = true;
					int failed = 0;

					for (auto ent : list)
					{
						if (PED::IS_PED_A_PLAYER(ent))
							continue;

						if (ENTITY::DOES_ENTITY_EXIST(ent))
						{
							if (force)
							{
								auto ptr = g_pointers->m_gta.m_handle_to_ptr(ent);

								switch (ptr->m_entity_type)
								{
								case 4: g_pointers->m_gta.m_delete_ped(reinterpret_cast<CPed*>(ptr)); break;
								// case 3: g_pointers->m_gta.m_delete_vehicle(reinterpret_cast<CVehicle*>(ptr)); break;
								case 5:
									g_pointers->m_gta.m_delete_object(reinterpret_cast<CObject*>(ptr), false);
									break;
								}
							}
							else if (entity::take_control_of(ent, 25))
								entity::delete_entity(ent);
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
}