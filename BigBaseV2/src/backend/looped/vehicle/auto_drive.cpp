#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "gta/enums.hpp"

namespace big
{
	void looped::vehicle_auto_drive()
	{
		static Vector3 location;
		static bool running = true;
		static bool wandering = true;
		static bool ran_once = false;

		if (g->vehicle.auto_drive_to_waypoint)
		{
			running = false;
			ran_once = true;

			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint))
			{
				g_notification_service->push_warning("Warning", "No Waypoint found please set one first.");
				g->vehicle.auto_drive_to_waypoint = false;
			}
			else if (!self::veh)
			{
				g_notification_service->push_warning("Warning", "Please be in a car first then try again.");
			}
			else
			{
				blip::get_blip_location(location, (int)BlipIcons::Waypoint);

				g_notification_service->push_warning("Auto Drive", "Starting Route To Destination");

				g_notification_service->push_warning("Auto Drive", "Start driving or leave car to take back control.");

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);

				TASK::TASK_VEHICLE_DRIVE_TO_COORD(self::ped, self::veh, location.x, location.y, location.z, (int)g->vehicle.auto_drive_speed, 5, ENTITY::GET_ENTITY_MODEL(self::veh), g->vehicle.driving_style_flags, 20, true);

				g->vehicle.auto_drive_to_waypoint = false;

				running = true;
			}
		}

		if (g->vehicle.auto_drive_wander)
		{
			ran_once = true;
			wandering = false;

			if (!self::veh)
			{
				g_notification_service->push_warning("Warning", "Please be in a car first then try again.");

				g->vehicle.auto_drive_wander = false;

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
			}
			else
			{
				g->vehicle.auto_drive_wander = false;

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);

				TASK::CLEAR_PED_TASKS(self::ped);

				TASK::TASK_VEHICLE_DRIVE_WANDER(self::ped, self::veh, (int)g->vehicle.auto_drive_speed, g->vehicle.driving_style_flags);

				wandering = true;

				g_notification_service->push_warning("Starting Wondering", "Start driving or leave car to take back control.");
			}
		}

		if (wandering && ran_once)
		{
			if (PAD::IS_CONTROL_PRESSED(0, 63) || PAD::IS_CONTROL_PRESSED(0, 64) || PAD::IS_CONTROL_PRESSED(0, 71) || PAD::IS_CONTROL_PRESSED(0, 72) || PAD::IS_CONTROL_PRESSED(0, 75) || PAD::IS_CONTROL_PRESSED(0, 76))
			{
				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);
				g_notification_service->push_warning("Warning", "Wandering Stopped");
				g->vehicle.auto_drive_wander = false;
				wandering = false;
			}
		}

		if (running)
		{
			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint) || PAD::IS_CONTROL_PRESSED(0, 75) || PAD::IS_CONTROL_PRESSED(0, 63) || PAD::IS_CONTROL_PRESSED(0, 64))
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

				running = false;
			}
		}
	}
}