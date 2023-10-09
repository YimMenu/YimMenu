#include "util/mobile.hpp"
#include "views/view.hpp"

namespace big
{
	void view::vehicle()
	{
		ImGui::Spacing();
		{
			components::button("Mors Mutual Fix All Vehicles", [] {
				int amount_fixed = mobile::mors_mutual::fix_all();
				g_notification_service->push_success("Mobile", std::vformat("{} vehicle{} been fixed.", std::make_format_args(amount_fixed, amount_fixed == 1 ? " has" : "s have")));
			});
			ImGui::SameLine();
			components::button("Repair", [] {
				vehicle::repair(self::veh);
			});
			ImGui::SameLine();
			components::button("Delete Current", [] {
				if (ENTITY::DOES_ENTITY_EXIST(self::veh))
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped), entity::delete_entity(self::veh);
			});
		}
		ImGui::SeparatorText("###General");
		{
			ImGui::BeginGroup();
			{
				components::command_checkbox<"vehgodmode">();
				components::command_checkbox<"vehjump">();
				components::command_checkbox<"blockhoming">();
				components::command_checkbox<"keepengine">();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				components::command_checkbox<"seatbelt">();
				components::command_checkbox<"veh_boost">();
			}
			ImGui::EndGroup();
		}
		ImGui::SeparatorText("###others");
		{
			components::command_checkbox<"allvehsinheists">();

			components::command_checkbox<"customvehweaps">();
			components::options_modal("Custom Vehicle Weapons", [] {
				components::sub_title("Missile");

				ImGui::InputFloat("Reload Time", &g.vehicle.vehicle_ammo_special.rocket_reload_time, 0.1, 1, "%.1f");
				ImGui::InputFloat("Speed##rocket", &g.vehicle.vehicle_ammo_special.rocket_launch_speed, 10, 100, "%.1f");
				ImGui::InputFloat("Range##rocket", &g.vehicle.vehicle_ammo_special.rocket_range, 50, 100, "%.1f");
				ImGui::InputFloat("Lock-on Range", &g.vehicle.vehicle_ammo_special.rocket_lock_on_range, 50, 100, "%.1f");
				ImGui::InputFloat("Lock-on Time", &g.vehicle.vehicle_ammo_special.rocket_time_before_homing, 0.01, 0.1, "%.2f");

				ImGui::InputFloat("Time Between Shots##rocket", &g.vehicle.vehicle_ammo_special.rocket_time_between_shots, 0.001, 0.1, "%.3f");
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Time taken to fire consecutive shots on the same side. Related to rate of fire.");

				ImGui::InputFloat("Alternate Wait Time##rocket", &g.vehicle.vehicle_ammo_special.rocket_alternate_wait_time, 0.001, 0.1, "%.3f");
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Time taken to switch between sides. Related to rate of fire.");

				ImGui::InputFloat("Life Time", &g.vehicle.vehicle_ammo_special.rocket_lifetime, 0.1, 1, "%.1f");
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Time taken for missile to explode if not hitting anything.");

				ImGui::Checkbox("Smart Missiles", &g.vehicle.vehicle_ammo_special.rocket_improve_tracking);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Improves current missile's tracking ability.");
			});
		}
	}
}
