#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::vehicle_auto_drive()
	{
		static constexpr int driving_styles[] = { 443, 524861 };

		static int changing_driving_styles = false;
		static int current_driving_style = 443;
		static float current_speed = 8;
		static Vector3 waypoint;

		static bool driving_to_wp = false;
		static bool wandering = false;

		if (g->vehicle.auto_drive_to_waypoint || g->vehicle.auto_drive_wander)
		{
			driving_to_wp = g->vehicle.auto_drive_to_waypoint;
			wandering = g->vehicle.auto_drive_wander;

			changing_driving_styles = true;
			g->vehicle.auto_drive_wander = false;
			g->vehicle.auto_drive_to_waypoint = false;
		}

		if (!self::veh && (driving_to_wp || wandering))
		{
			wandering = false;
			driving_to_wp = false;
			changing_driving_styles = false;
			g_notification_service->push_warning("Warning", "Please be in a car first then try again.");
		}
		else if (
			current_driving_style != driving_styles[g->vehicle.driving_style_id] || 
			current_speed != g->vehicle.auto_drive_speed
		) {
			changing_driving_styles = true;
		}

		if (driving_to_wp || wandering)
		{
			Vector3 last_waypoint = waypoint;
			bool is_waypoint_exist = blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);

			if (
				driving_to_wp && 
				(
					last_waypoint.x != waypoint.x || 
					last_waypoint.y != waypoint.y || 
					last_waypoint.z != waypoint.z
				)
			) {
				changing_driving_styles = true;
			}

			if (
				((driving_to_wp && !is_waypoint_exist) || wandering) &&
				(
					PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) ||
					PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) ||
					PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) ||
					PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) ||
					PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT) ||
					PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE)
					)
				) {
				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);

				if (driving_to_wp)
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 8);
				}

				driving_to_wp = false;
				wandering = false;
				g_notification_service->push_warning("Warning", "Auto Drive Stopped");
			}
			else if (changing_driving_styles)
			{
				current_speed = g->vehicle.auto_drive_speed;
				current_driving_style = driving_styles[g->vehicle.driving_style_id];
				changing_driving_styles = false;


				if (driving_to_wp)
				{
					if (!is_waypoint_exist)
					{
						g_notification_service->push_warning("Warning", "No Waypoint found please set one first.");
						driving_to_wp = false;
					}
				}

				if (driving_to_wp || wandering)
				{
					TASK::CLEAR_VEHICLE_TASKS_(self::veh);
					TASK::CLEAR_PED_TASKS(self::ped);

					if (driving_to_wp)
					{
						TASK::TASK_VEHICLE_DRIVE_TO_COORD(
							self::ped, self::veh,
							waypoint.x, waypoint.y, waypoint.z, current_speed,
							5, ENTITY::GET_ENTITY_MODEL(self::veh),
							current_driving_style, 20, true
						);
					}
					else if (wandering)
					{
						TASK::TASK_VEHICLE_DRIVE_WANDER(self::ped, self::veh, current_speed, current_driving_style);
					}
				}
			}
		}
	}
}
