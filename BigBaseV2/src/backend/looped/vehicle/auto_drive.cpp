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
		static std::map<AutoDriveStyle, int> driving_style_flags = {
			{AutoDriveStyle::LAW_ABIDING, 443},
			{AutoDriveStyle::THE_ROAD_IS_YOURS, 787004}
		};

		static int changing_driving_styles = false;
		static AutoDriveDestination current_destination = AutoDriveDestination::STOPPED;
		static int current_driving_flag = driving_style_flags[AutoDriveStyle::LAW_ABIDING];
		static float current_speed = 8;
		static bool started = false;
		static Vector3 waypoint;
		static bool does_waypoint_exist = false;
		static bool to_waypoint = false;
		static int update_ticks = 0;

		if (g->vehicle.auto_drive_destination != AutoDriveDestination::STOPPED)
		{
			current_destination = g->vehicle.auto_drive_destination;
			g->vehicle.auto_drive_destination = AutoDriveDestination::STOPPED;
			changing_driving_styles = true;
			does_waypoint_exist = false;
			to_waypoint = false;
			update_ticks = 0;
		}

		if (!self::veh && current_destination != AutoDriveDestination::STOPPED)
		{
			current_destination = AutoDriveDestination::STOPPED;
			changing_driving_styles = false;
			does_waypoint_exist = false;
			to_waypoint = false;
			update_ticks = 0;
			g_notification_service->push_warning("Warning", "Please be in a car first then try again.");
		}
		else if (
			current_driving_flag != driving_style_flags[g->vehicle.auto_drive_style] ||
			current_speed != g->vehicle.auto_drive_speed
		) {
			current_driving_flag = driving_style_flags[g->vehicle.auto_drive_style];
			current_speed = g->vehicle.auto_drive_speed;
			changing_driving_styles = true;
			does_waypoint_exist = false;
			to_waypoint = false;
			update_ticks = 0;
		}

		if (current_destination != AutoDriveDestination::STOPPED)
		{
			Vector3 last_waypoint = waypoint;

			if (update_ticks == 0)
			{
				does_waypoint_exist = false;
				to_waypoint = false;

				if (current_destination == AutoDriveDestination::OBJECTITVE)
				{
					to_waypoint = true;
					does_waypoint_exist = blip::get_objective_location(waypoint);
				}
				else if (current_destination == AutoDriveDestination::WAYPOINT)
				{
					to_waypoint = true;

					const std::map<BlipIcons, std::vector<BlipColors>> checkpoints = {
						{BlipIcons::WAYPOINT, {  } }
					};

					does_waypoint_exist = blip::get_blip_location(checkpoints, waypoint);
				}

				if (
					does_waypoint_exist &&
					(
						last_waypoint.x != waypoint.x ||
						last_waypoint.y != waypoint.y ||
						last_waypoint.z != waypoint.z
						)
					) {
					changing_driving_styles = true;
				}
			}

			update_ticks++;

			if (update_ticks > 1200)
			{
				update_ticks = 0;
			}

			bool interupted = (
				PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) ||
				PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) ||
				PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) ||
				PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) ||
				PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT) ||
				PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE)
			);

			if (
				current_destination == AutoDriveDestination::EMERGENCY_STOP ||
				(to_waypoint && !does_waypoint_exist) ||
				interupted
			) {
				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);

				if (!interupted && started)
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0);
				}

				current_destination = AutoDriveDestination::STOPPED;

				if (to_waypoint && !does_waypoint_exist)
				{
					g_notification_service->push_warning("Warning", "No Waypoint found please set one first.");
				}
				else
				{
					g_notification_service->push_warning("Warning", "Auto Drive Stopped");
				}

				started = false;
			}
			else if (changing_driving_styles)
			{
				changing_driving_styles = false;

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);

				if (to_waypoint)
				{
					TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(
						self::ped, self::veh,
						waypoint.x, waypoint.y, waypoint.z, current_speed,
						current_driving_flag, 20
					);
				}
				else
				{
					TASK::TASK_VEHICLE_DRIVE_WANDER(self::ped, self::veh, current_speed, current_driving_flag);
				}

				started = true;
			}
		}
	}
}
