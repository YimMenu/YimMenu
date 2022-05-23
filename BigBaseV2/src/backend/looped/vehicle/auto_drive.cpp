#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "gta/enums.hpp"

namespace big
{
	void looped::vehicle_auto_drive()
	{
		Vehicle vehicle = self::veh;
		Ped ped = self::ped;
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
			else if (!vehicle)
			{
				g_notification_service->push_warning("Warning", "Please be in a car first then try again.");
			}
			else
			{
				blip::get_blip_location(location, (int)BlipIcons::Waypoint);

				g_notification_service->push_warning("Auto Drive", "Starting Route To Destination");

				g_notification_service->push_warning("Auto Drive", "Start driving or leave car to take back control.");

				TASK::CLEAR_VEHICLE_TASKS_(vehicle);

				TASK::TASK_VEHICLE_DRIVE_TO_COORD(ped, vehicle, location.x, location.y, location.z,
												  static_cast<float>(g->vehicle.auto_drive_speed), 5, ENTITY::GET_ENTITY_MODEL(vehicle), g->vehicle.driving_style_flags, 20, true);

				g->vehicle.auto_drive_to_waypoint = false;

				running = true;
			}
		}

		if (g->vehicle.auto_drive_wander)
		{
			ran_once = true;
			wandering = false;

			if (!vehicle)
			{
				g_notification_service->push_warning("Warning", "Please be in a car first then try again.");

				g->vehicle.auto_drive_wander = false;

				TASK::CLEAR_VEHICLE_TASKS_(vehicle);
			}
			else
			{
				g->vehicle.auto_drive_wander = false;

				TASK::CLEAR_VEHICLE_TASKS_(vehicle);

				TASK::CLEAR_PED_TASKS(ped);

				TASK::TASK_VEHICLE_DRIVE_WANDER(ped, vehicle, static_cast<float>(g->vehicle.auto_drive_speed), g->vehicle.driving_style_flags);

				wandering = true;

				g_notification_service->push_warning("Starting Wondering", "Start driving or leave car to take back control.");
			}
		}

		if (wandering && ran_once)
		{
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			{
				TASK::CLEAR_VEHICLE_TASKS_(vehicle);
				TASK::CLEAR_PED_TASKS(ped);
				g_notification_service->push_warning("Warning", "Wandering Stopped");
				g->vehicle.auto_drive_wander = false;
				wandering = false;
			}
		}

		if (running)
		{
			if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			{
				if (!blip::get_blip_location(location, (int)BlipIcons::Waypoint))
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 8);
				}

				g->vehicle.auto_drive_to_waypoint = false;

				if (ran_once)
				{
					g_notification_service->push_warning("Warning", "Autodrive Stopped");
				}

				TASK::CLEAR_VEHICLE_TASKS_(vehicle);
				TASK::CLEAR_PED_TASKS(ped);

				running = false;
			}
		}
	}
}