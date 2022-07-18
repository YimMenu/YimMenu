#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::vehicle_auto_drive_to_waypoint()
	{
		static Vector3 location;
		static bool driving_to_wp = true;
		static bool ran_once = false;
		static int changing_driving_styles = false;
		static int current_driving_style = false;
		static float current_speed;

		if (g->vehicle.auto_drive_to_waypoint)
		{
			ran_once = true;
			driving_to_wp = false;

			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint))
			{
				g_notification_service->push_warning("Warning", "No Waypoint found please set one first.");
				g->vehicle.auto_drive_to_waypoint = false;
			}
			else if (!self::veh)
			{
				g_notification_service->push_warning("Warning", "Please be in a car first then try again.");
				g->vehicle.auto_drive_to_waypoint = false;
			}
			else
			{
				blip::get_blip_location(location, (int)BlipIcons::Waypoint);

				if (!changing_driving_styles)
				{
					g_notification_service->push_warning("Auto Drive", "Starting Route To Destination");
					g_notification_service->push_warning("Auto Drive", "Start driving or leave car to take back control.");
				}

				current_speed = g->vehicle.auto_drive_speed;
				current_driving_style = g->vehicle.driving_style_flags;

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);
				TASK::TASK_VEHICLE_DRIVE_TO_COORD(
					self::ped, self::veh, 
					location.x, location.y, location.z, current_speed, 
					5, ENTITY::GET_ENTITY_MODEL(self::veh), 
					current_driving_style, 20, true
				);

				g->vehicle.auto_drive_to_waypoint = false;

				driving_to_wp = true;
			}
		}

		if (driving_to_wp)
		{
			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			{
				if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint))
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 8);
				}

				g->vehicle.auto_drive_to_waypoint = false;

				if (ran_once)
				{
					g_notification_service->push_warning("Warning", "Autodrive Stopped");
				}

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);

				driving_to_wp = false;
			}

			if (!ran_once)
			{
				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);
				driving_to_wp = false;
			}
			else
			{
				if ((current_driving_style != g->vehicle.driving_style_flags) || (current_speed != g->vehicle.auto_drive_speed))
				{
					changing_driving_styles = true;
					g->vehicle.auto_drive_to_waypoint = true;
				}
			}
		}
	}
}
