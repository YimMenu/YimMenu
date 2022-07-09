#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"


namespace big
{
	void view::auto_drive()
	{
		components::button("Drive To Waypoint", [] {
			g->vehicle.auto_drive_to_waypoint = true;
		});
		ImGui::SameLine();
		components::button("Wander", [] {
			g->vehicle.auto_drive_wander = true;
		});
		ImGui::SameLine();
		components::button("E-Stop", [] {
			g->vehicle.auto_drive_to_waypoint = false;
			g->vehicle.auto_drive_wander = false;
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0);
			TASK::CLEAR_VEHICLE_TASKS_(self::veh);
			TASK::CLEAR_PED_TASKS(self::ped);
		});

		ImGui::SliderInt("Top Speed", &g->vehicle.auto_drive_speed, 1, 200);

		if (ImGui::ListBox("Driving Style", &g->vehicle.driving_style_id, vehicle::driving_style_names, 2))
		{
			g->vehicle.driving_style_flags = vehicle::driving_styles[g->vehicle.driving_style_id];
			g_notification_service->push_warning("Auto Drive", fmt::format("Driving style set to {}.", vehicle::driving_style_names[g->vehicle.driving_style_id]));
		}
	}
}
