#include "views/view.hpp"
#include "util/local_player.hpp"
#include "util/entity.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::nearby()
	{
		components::sub_title("Peds");
		components::button("Delete", [] { for (auto peds : entity::get_entities(false, true)) entity::delete_entity(peds); }, ImVec2(110, 0)); ImGui::SameLine();
		components::button("Kill", [] { for (auto peds : entity::get_entities(false, true)) ped::kill_ped(peds); }, ImVec2(110, 0), ImVec4(0.70196f, 0.3333f, 0.00392f, 1.f)); ImGui::SameLine();
		components::button("Kill Enemies", [] { for (auto peds : entity::get_entities(false, true)) ped::kill_ped_by_relation(peds, 4 || 5); }, ImVec2(110, 0), ImVec4(0.76078f, 0.f, 0.03529f, 1.f));
		
		components::command_checkbox<"pedsignore">(); ImGui::SameLine(140.f);
		components::command_checkbox<"pedrain">(); 
		components::command_checkbox<"highalert">(); ImGui::SameLine(140.f);
		components::command_checkbox<"pedrush">();

		ImGui::Separator();
		components::sub_title("Vehicles");

		components::button("Delete", [] {
			for (auto vehs : entity::get_entities(true, false))
				if (entity::take_control_of(vehs)) {
					entity::delete_entity(vehs);
					script::get_current()->yield();
				}
		}, ImVec2(110, 0)); ImGui::SameLine();

		components::button("Max Upgrade", [] {
			for (auto vehs : entity::get_entities(true, false))
				if (entity::take_control_of(vehs)) {
					vehicle::max_vehicle(vehs);
					script::get_current()->yield();
				}
		}, ImVec2(110, 0), ImVec4(0.02745f, 0.4745f, 0.10196f, 1.f)); ImGui::SameLine();

		components::button("Downgrade", [] {
			for (auto vehs : entity::get_entities(true, false))
				if (entity::take_control_of(vehs)) {
					vehicle::downgrade(vehs);
					script::get_current()->yield();
				}
		}, ImVec2(110, 0), ImVec4(0.4549f, 0.03529f, 0.03529f, 1.f));
		
	}
}