#include "util/mobile.hpp"
#include "views/view.hpp"

void render_range_comp(const char* name, float& ref, float step, float step_fast, const char* format, float orig_val, float defVal)
{
	ImGui::InputFloat(name, &ref, step, step_fast, format);
	ImGui::Text(("Original: " + std::to_string(orig_val)).c_str());
	ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
	ImGui::Text(("Default: " + std::to_string(defVal)).c_str());
	ImGui::Spacing();
}

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

				render_range_comp("Speed##rocket",
				    g.vehicle.vehicle_ammo_special.rocket_launch_speed,
				    10,
				    100,
				    "%.1f",
				    g.vehicle.vehicle_ammo_special.m_rocket_launch_speed,
				    ROCKET_LAUNCH_SPEED);
				render_range_comp("Range##rocket",
				    g.vehicle.vehicle_ammo_special.rocket_range,
				    50,
				    100,
				    "%.1f",
				    g.vehicle.vehicle_ammo_special.m_rocket_range,
				    ROCKET_RANGE);
				render_range_comp("Lock-on Range",
				    g.vehicle.vehicle_ammo_special.rocket_lock_on_range,
				    50,
				    100,
				    "%.1f",
				    g.vehicle.vehicle_ammo_special.m_rocket_lock_on_range,
				    ROCKET_LOCK_ON_RANGE);
				render_range_comp("Lock-on Time",
				    g.vehicle.vehicle_ammo_special.rocket_time_before_homing,
				    0.01,
				    0.1,
				    "%.2f",
				    g.vehicle.vehicle_ammo_special.m_rocket_time_before_homing,
				    ROCKET_TIME_BEFORE_HOMING);
				render_range_comp("Life Time",
				    g.vehicle.vehicle_ammo_special.rocket_lifetime,
				    0.1,
				    1,
				    "%.1f",
				    g.vehicle.vehicle_ammo_special.m_rocket_lifetime,
				    ROCKET_LIFETIME);

				ImGui::Checkbox("Smart Missiles", &g.vehicle.vehicle_ammo_special.rocket_improve_tracking);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Improves current missile's tracking ability.");

				ImGui::Spacing();

				components::button("Apply Original", [] {
					g.vehicle.vehicle_ammo_special.rocket_launch_speed = g.vehicle.vehicle_ammo_special.m_rocket_launch_speed;
					g.vehicle.vehicle_ammo_special.rocket_range = g.vehicle.vehicle_ammo_special.m_rocket_range;
					g.vehicle.vehicle_ammo_special.rocket_lock_on_range = g.vehicle.vehicle_ammo_special.m_rocket_lock_on_range;
					g.vehicle.vehicle_ammo_special.rocket_time_before_homing = g.vehicle.vehicle_ammo_special.m_rocket_time_before_homing;
					g.vehicle.vehicle_ammo_special.rocket_lifetime = g.vehicle.vehicle_ammo_special.m_rocket_lifetime;
				});
				ImGui::SameLine();
				components::button("Apply Defaults", [] {
					g.vehicle.vehicle_ammo_special.rocket_launch_speed       = ROCKET_LAUNCH_SPEED;
					g.vehicle.vehicle_ammo_special.rocket_range              = ROCKET_RANGE;
					g.vehicle.vehicle_ammo_special.rocket_lock_on_range      = ROCKET_LOCK_ON_RANGE;
					g.vehicle.vehicle_ammo_special.rocket_time_before_homing = ROCKET_TIME_BEFORE_HOMING;
					g.vehicle.vehicle_ammo_special.rocket_lifetime           = ROCKET_LIFETIME;
				});
			});
		}
	}
}
