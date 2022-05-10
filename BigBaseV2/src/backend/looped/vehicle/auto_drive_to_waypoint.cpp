#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"
#include "gta/enums.hpp"

namespace big
{
	void looped::vehicle_auto_drive_to_waypoint()
	{
		static Vector3 location;
		static bool driving_to_wp = true;
		static bool ran_once = false;
		static int changing_driving_styles = false;
		static int current_driving_style = false;
		static int current_speed;

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

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);
				TASK::TASK_VEHICLE_DRIVE_TO_COORD(self::ped, self::veh, location.x, location.y, location.z, static_cast<float>(g->vehicle.auto_drive_speed), 5, ENTITY::GET_ENTITY_MODEL(self::veh), g->vehicle.driving_style_flags, 20, true);

				current_driving_style = g->vehicle.driving_style_flags;
				current_speed = g->vehicle.auto_drive_speed;

				g->vehicle.auto_drive_to_waypoint = false;

				driving_to_wp = true;
			}
		}

		if (driving_to_wp)
		{
			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint) || PAD::IS_CONTROL_PRESSED(0, 63) || PAD::IS_CONTROL_PRESSED(0, 64) || PAD::IS_CONTROL_PRESSED(0, 71) || PAD::IS_CONTROL_PRESSED(0, 72) || PAD::IS_CONTROL_PRESSED(0, 75) || PAD::IS_CONTROL_PRESSED(0, 76))
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
