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
			Vehicle vehicle = self::veh;

			if (last_vehicle != vehicle)
			{
				if (last_vehicle)
					cleanup(last_vehicle);

				last_vehicle = vehicle;
			}

			if (vehicle)
			{
				Vector3 cam_pos = CAM::GET_GAMEPLAY_CAM_ROT(0);
				ENTITY::SET_ENTITY_ROTATION(vehicle, cam_pos.x, cam_pos.y, cam_pos.z, 1, true);
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
		}

		virtual void on_disable() override
		{
			if (self::veh)
				cleanup(self::veh);
		}
	};

	vehicle_fly g_vehicle_fly("vehiclefly", "VEHICLE_FLY", "VEHICLE_FLY_DESC", g.vehicle.fly.enabled);
}
