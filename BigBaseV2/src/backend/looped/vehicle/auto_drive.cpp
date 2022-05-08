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

		if (g->vehicle.auto_drive_to_waypoint)
		{
			running = false;

			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint))
			{
				if (!self::veh)
				{
					g_notification_service->push_warning("Warning", "Please be in a car first then try again.");
				}
				else
				{
					g_notification_service->push_warning("Warning", "No Waypoint found please set one first.");
				}
				g->vehicle.auto_drive_to_waypoint = false;
			}
			else if (self::veh)
			{
				blip::get_blip_location(location, (int)BlipIcons::Waypoint);

				g_notification_service->push_warning("Auto Drive", "Starting Route To Destination");

				TASK::TASK_VEHICLE_DRIVE_TO_COORD(self::ped, self::veh, location.x, location.x, location.x, 30.f, 1, ENTITY::GET_ENTITY_MODEL(self::veh), 525244, 1, true);
				
				g->vehicle.auto_drive_to_waypoint = false;

				running = true;
			}
		}

		if (running)
		{
			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint) || PAD::IS_CONTROL_PRESSED(0, 75) || PAD::IS_CONTROL_PRESSED(0, 63) || PAD::IS_CONTROL_PRESSED(0, 64))
			{
				g->vehicle.auto_drive_to_waypoint = false;

				g_notification_service->push_warning("Warning", "Drive Cancled");

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);

				running = false;
			}
		}
	}
}