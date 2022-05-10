#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"
#include "gta/enums.hpp"

namespace big
{
	void looped::vehicle_auto_drive_wander()
	{
		static Vector3 location;
		static bool wandering = true;
		static bool ran_once = false;
		static int changing_driving_styles = false;
		static int current_driving_style = false;
		static int current_speed;

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
				TASK::TASK_VEHICLE_DRIVE_WANDER(self::ped, self::veh, (float)g->vehicle.auto_drive_speed, g->vehicle.driving_style_flags);

				current_driving_style = g->vehicle.driving_style_flags;
				current_speed = g->vehicle.auto_drive_speed;

				wandering = true;

				if (!changing_driving_styles)
				{
					g_notification_service->push_warning("Starting Wondering", "Start driving or leave car to take back control.");
				}
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
			if ((current_driving_style != g->vehicle.driving_style_flags) || (current_speed != g->vehicle.auto_drive_speed))
			{
				changing_driving_styles = true;
				g->vehicle.auto_drive_wander = true;
			}
		}
	}
}