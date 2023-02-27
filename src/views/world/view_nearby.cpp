#include "util/entity.hpp"
#include "util/local_player.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

namespace big
{
	void view::nearby()
	{
		components::sub_title("Peds");
		// Nearby Ped Actions
		components::button<ImVec2(110, 0)>("Delete", [] {
			for (auto peds : entity::get_entities(false, true))
			{
				entity::delete_entity(peds);
			}
		});
		ImGui::SameLine();

		components::button<ImVec2(110, 0), ImVec4(0.70196f, 0.3333f, 0.00392f, 1.f)>("Kill", [] {
			for (auto peds : entity::get_entities(false, true))
			{
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
		components::command_checkbox<"highalert">();
		ImGui::SameLine(140.f);
		components::command_checkbox<"pedrush">();

		ImGui::Separator();
		components::sub_title("Vehicles");
		// Nearby Vehicle Actions

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
	}
}