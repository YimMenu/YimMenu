#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::player_plane_chase()
	{
		static bool chasing = true;
		static bool ran_once = false;
		Ped PlayerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id());
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

		if (g->player.plane_chase)
		{
			ran_once = true;
			chasing = false;

			if (!self::veh)
			{
				g_notification_service->push_warning("Warning", "Please be in a Plane first then try again.");

				g->player.plane_chase = false;

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
			}

			else
			{
				g->player.plane_chase = false;

				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);
				TASK::TASK_PLANE_CHASE(self::ped, PlayerPed, 0.0, 0.0, 20.0);

				chasing = true;


				g_notification_service->push_warning("Starting to Chase", "Start flying or leave Plane to take back control.");
			}
		}

		if (chasing && ran_once)
		{
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT))
			{
				TASK::CLEAR_VEHICLE_TASKS_(self::veh);
				TASK::CLEAR_PED_TASKS(self::ped);

				g_notification_service->push_warning("Warning", "Chasing Stopped");
				chasing = false;
			}
		}
	}
}