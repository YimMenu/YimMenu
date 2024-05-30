#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class vehicle_fly : looped_command
	{
		using looped_command::looped_command;

		Vehicle last_vehicle = 0;

		void cleanup(Vehicle vehicle)
		{
			VEHICLE::SET_VEHICLE_GRAVITY(vehicle, true);
			ENTITY::SET_ENTITY_COLLISION(vehicle, true, true);
			if (g.vehicle.fly.stop_on_exit)
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.0);
			}
		}

		virtual void on_tick() override
		{
			Vehicle vehicle               = self::veh;
			static bool player_fpv_warned = false;

			if (!vehicle)
				return;

			if (last_vehicle != vehicle)
			{
				if (last_vehicle)
					cleanup(last_vehicle);

				last_vehicle = vehicle;
			}

			if (CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() == CameraMode::FIRST_PERSON)
			{
				if (!player_fpv_warned)
				{
					g_notification_service.push_warning("BACKEND_FLYING_VEHICLE"_T.data(),
					    "BACKEND_FLYING_VEHICLE_FPV_DISABLED"_T.data());
					player_fpv_warned = true;
				}

				// Kick us out of FPV when in fly mode
				CAM::SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(CameraMode::THIRD_PERSON_NEAR);

				return;
			}
			else
			{
				// Reset the warning, so it only shows up once each time the player enters FPV mode
				player_fpv_warned = false;
			}

			Vector3 cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);

			/*
			* Leaving this for experimentation in the future, but vehicle flying in first person needs fixing
				
			Vector3 car_rot;
			Vector3 rotation_delta;
 
			if (CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == CameraMode::FIRST_PERSON)
			{

				car_rot = ENTITY::GET_ENTITY_ROTATION(vehicle, 0);
				rotation_delta.x = (cam_rot.x - car_rot.x) / 360.0f;
				rotation_delta.y = (cam_rot.y - car_rot.y) / 360.0f;
				rotation_delta.z = (cam_rot.z - car_rot.z) / 360.0f;

				Vector3 new_rot = {car_rot.x + rotation_delta.x, car_rot.y + rotation_delta.y, car_rot.z + rotation_delta.z};

				ENTITY::SET_ENTITY_ROTATION(vehicle, new_rot.x, new_rot.y, new_rot.z, 0, true);
			}
			else
			{
				ENTITY::SET_ENTITY_ROTATION(vehicle, cam_rot.x, cam_rot.y, cam_rot.z, 0, true);
			}*/

			ENTITY::SET_ENTITY_ROTATION(vehicle, cam_rot.x, cam_rot.y, cam_rot.z, 0, true);
			ENTITY::SET_ENTITY_COLLISION(vehicle, !g.vehicle.fly.no_collision, true);

			float locspeed = g.vehicle.fly.speed;

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
			{
				locspeed *= 2;
			}

			if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_ACCELERATE))
			{
				if (g.vehicle.fly.dont_stop)
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0, g.vehicle.fly.speed, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
				}
				else
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, locspeed);
				}
			}

			if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_BRAKE))
			{
				float lsp = g.vehicle.fly.speed;
				if (!PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
				{
					lsp = (g.vehicle.fly.speed * 2);
				}
				if (g.vehicle.fly.dont_stop)
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0, 0 - (lsp), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
				}
				else
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, (0 - locspeed));
				}
			}

			if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_MOVE_LEFT_ONLY))
			{
				float lsp = ((0 - g.vehicle.fly.speed) * 2);
				if (!PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
				{
					lsp = (0 - g.vehicle.fly.speed);
				}
				if (g.vehicle.fly.dont_stop)
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, (lsp), 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
				}
				else
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, (0 - (locspeed)), 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
				}
			}

			if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_MOVE_RIGHT_ONLY))
			{
				float lsp = g.vehicle.fly.speed;
				if (!PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_MOVE_UP_ONLY))
				{
					lsp = (g.vehicle.fly.speed * 2);
				}
				if (g.vehicle.fly.dont_stop)
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, lsp, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
				}
				else
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, locspeed, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
				}
			}

			if (!g.vehicle.fly.dont_stop && !PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_ACCELERATE) && !PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_BRAKE))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.0);
			}

			VEHICLE::SET_VEHICLE_GRAVITY(vehicle, false);
		}

		virtual void on_disable() override
		{
			if (self::veh)
				cleanup(self::veh);
		}
	};

	vehicle_fly g_vehicle_fly("vehiclefly", "VEHICLE_FLY", "VEHICLE_FLY_DESC", g.vehicle.fly.enabled);
}
