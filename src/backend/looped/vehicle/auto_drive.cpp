#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "core/settings/vehicle.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/vehicle.hpp"

namespace big
{
	inline std::unordered_map<AutoDriveStyle, int> driving_style_flags = {{AutoDriveStyle::LAW_ABIDING, 443}, {AutoDriveStyle::THE_ROAD_IS_YOURS, 787004}};

	void looped::vehicle_auto_drive()
	{
		static int current_driving_flag = driving_style_flags[AutoDriveStyle::LAW_ABIDING];
		static float current_speed      = 8;

		static bool has_driving_settings_changed = false;
		static Vector3 waypoint;

		// start driving if destination is there
		if (g_vehicle.auto_drive_destination != AutoDriveDestination::STOPPED)
		{
			if (!self::veh)
			{
				g_vehicle.auto_drive_destination = AutoDriveDestination::STOPPED;
				has_driving_settings_changed     = false;
				g_vehicle.is_auto_driving        = false;
			}

			// check for changing driving settings
			if (current_driving_flag != driving_style_flags[g_vehicle.auto_drive_style] || current_speed != g_vehicle.auto_drive_speed)
			{
				current_driving_flag         = driving_style_flags[g_vehicle.auto_drive_style];
				current_speed                = g_vehicle.auto_drive_speed;
				has_driving_settings_changed = true;
			}

			if (!g_vehicle.is_auto_driving)
			{
				bool does_waypoint_exist = g_vehicle.auto_drive_destination == AutoDriveDestination::OBJECTITVE ? blip::get_objective_location(waypoint) : blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);

				if (does_waypoint_exist)
				{
					TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(self::ped, self::veh, waypoint.x, waypoint.y, waypoint.z, current_speed, current_driving_flag, 20);
					g_vehicle.is_auto_driving = true;
				}
				else
				{
					g_vehicle.auto_drive_destination = AutoDriveDestination::STOPPED;
					has_driving_settings_changed     = false;
				}
			}
			else
			{
				bool interupted = (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE));

				if (has_driving_settings_changed || interupted)
				{
					TASK::CLEAR_PRIMARY_VEHICLE_TASK(self::veh);
					TASK::CLEAR_PED_TASKS(self::ped);

					has_driving_settings_changed = false;
					g_vehicle.is_auto_driving    = false; // start driving again in next tick if !interupted
				}

				if (interupted)
					g_vehicle.auto_drive_destination = AutoDriveDestination::STOPPED;
			}
		}
	}
}
