#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"
#include "util/mobile.hpp"

namespace big
{
	void view::vehicle_fun()
	{
		components::small_text("Auto Drive");

		components::button("Drive To Waypoint", [] {
			g->vehicle.auto_drive_to_waypoint = true;
		});
		ImGui::SameLine();
		components::button("Wander", [] {
			g->vehicle.auto_drive_wander = true;
		});
		ImGui::SameLine();
		components::button("Emergency Stop", [] {
			g->vehicle.auto_drive_to_waypoint = false;
			g->vehicle.auto_drive_wander = false;
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0);
			TASK::CLEAR_VEHICLE_TASKS_(self::veh);
			TASK::CLEAR_PED_TASKS(self::ped);
		});

		ImGui::SliderInt("Top Speed", &g->vehicle.auto_drive_speed, 1, 200);

		if (ImGui::BeginCombo("Driving Style", vehicle::driving_style_names[g->vehicle.driving_style_id]))
		{
			for (int i = 0; i < 2; i++)
			{
				if (ImGui::Selectable(vehicle::driving_style_names[i], g->vehicle.driving_style_id == i))
				{
					g->vehicle.driving_style_id = i;
					g_notification_service->push_warning("Auto Drive", fmt::format("Driving style set to {}.", vehicle::driving_style_names[i]));
				}

				if (g->vehicle.driving_style_id == i)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::Separator();

		components::small_text("Rainbow Paint");

		ImGui::SetNextItemWidth(120);
		if (ImGui::BeginCombo("RGB Type", vehicle::rgb_types[g->vehicle.rainbow_paint]))
		{
			for (int i = 0; i < 3; i++)
			{
				bool itemSelected = g->vehicle.rainbow_paint == i;

				if (ImGui::Selectable(vehicle::rgb_types[i], itemSelected))
				{
					g->vehicle.rainbow_paint = i;
				}

				if (itemSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
		if (g->vehicle.rainbow_paint != 0)
		{
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150);
			ImGui::SliderInt("RGB Speed", &g->rgb.speed, 1, 10);
		}

		ImGui::Separator();

		components::small_text("Vehicle Fly");

		ImGui::BeginGroup();

		ImGui::Checkbox("Enabled", &g->vehicle.fly.enabled);
		ImGui::Checkbox("Don't Stop", &g->vehicle.fly.dont_stop);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Disable Collision", &g->vehicle.fly.no_collision);
		ImGui::Checkbox("Stop On Exit", &g->vehicle.fly.stop_on_exit);

		ImGui::EndGroup();

		ImGui::SliderFloat("Speed", &g->vehicle.fly.speed, 1.f, 100.f, "%.0f", 1);
	}
}
