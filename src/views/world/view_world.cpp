#include "util/entity.hpp"
#include "util/notify.hpp"
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

		ImGui::SeparatorText("Peds");
		// Nearby Ped Actions

		components::button<ImVec2(110, 0), ImVec4(0.70196f, 0.3333f, 0.00392f, 1.f)>("Kill", [] {
			for (auto peds : entity::get_entities(false, true))
			{
				if (!PED::IS_PED_A_PLAYER(peds))
					ped::kill_ped(peds);
			}
		});
		ImGui::SameLine();

		components::button<ImVec2(110, 0), ImVec4(0.76078f, 0.f, 0.03529f, 1.f)>("Kill Enemies", [] {
			for (auto peds : entity::get_entities(false, true))
			{
				ped::kill_ped_by_relation(peds, 4 || 5);
			}
		});

		// Nearby Ped Loops / Toggles
		components::command_checkbox<"pedsignore">();
		ImGui::SameLine(140.f);
		components::command_checkbox<"pedrain">();
		ImGui::SameLine(265.f);
		components::command_checkbox<"riotmode">();
		components::command_checkbox<"highalert">();
		ImGui::SameLine(140.f);
		components::command_checkbox<"pedrush">();
		ImGui::SameLine();
		components::command_checkbox<"autodisarm">();
		components::options_modal("Auto Disarm", [] {
			ImGui::Checkbox("Neutralize", &g.world.nearby.auto_disarm.neutralize);
		});

		ImGui::SeparatorText("Vehicles");
		components::sub_title("Vehicles");

		components::button<ImVec2(110, 0), ImVec4(0.02745f, 0.4745f, 0.10196f, 1.f)>("Max Upgrade", [] {
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

		components::button<ImVec2(110, 0), ImVec4(0.4549f, 0.03529f, 0.03529f, 1.f)>("Downgrade", [] {
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

		ImGui::SeparatorText("Entities");

		static bool included_entity_types[3];
		static bool own_vehicle, deleting;
		static int quantity, remaining;

		ImGui::Text("Include:");
		ImGui::Checkbox("Vehicles", &included_entity_types[0]);
		ImGui::SameLine();
		ImGui::Checkbox("Peds", &included_entity_types[1]);
		ImGui::SameLine();
		ImGui::Checkbox("Props", &included_entity_types[2]);

		if (included_entity_types[0])
			ImGui::Checkbox("Self vehicle", &own_vehicle);

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
				g_notification_service->push("Entity deletion", std::format("Deleting {} entities", quantity));
				deleting   = true;
				int failed = 0;
				for (auto ent : list)
				{
					if (ent == self::ped)
						continue;

					if (ENTITY::DOES_ENTITY_EXIST(ent))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(ent))
							if (ent == self::veh && own_vehicle)
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);

						if (entity::take_control_of(ent, 25))
							entity::delete_entity(ent);
					}

					script::get_current()->yield(5ms);

					if (ENTITY::DOES_ENTITY_EXIST(ent))
						failed++;
					else
						remaining--;
				}

				if (failed > 0)
					g_notification_service->push_warning("Entity deletion", std::format("Failed deleting {} entities", failed));

				deleting = false;
			});
		}
	}
}