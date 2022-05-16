#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{

    static bool last_fly_tick = false;

    void do_vehicle_fly()
    {
        Vector3 cam_pos = CAM::GET_GAMEPLAY_CAM_ROT(0);
        ENTITY::SET_ENTITY_ROTATION(self::veh, cam_pos.x, cam_pos.y, cam_pos.z, 1, true);
        ENTITY::SET_ENTITY_COLLISION(self::veh, !g->vehicle.fly.no_collision, true);

        float locspeed = (g->vehicle.fly.speed * 10);
        float locspeed2 = g->vehicle.fly.speed;

        if (PAD::IS_CONTROL_PRESSED(0, 61))
        {
            locspeed = (locspeed * 2);
            locspeed2 = (locspeed2 * 2);
        }


        if (PAD::IS_CONTROL_PRESSED(2, 71))
        {
            if (g->vehicle.fly.dont_stop)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, 0.0, g->vehicle.fly.speed, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
            }
            else
            {
                VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, locspeed);
            }
        }

        if (PAD::IS_CONTROL_PRESSED(2, 72))
        {
            float lsp = g->vehicle.fly.speed;
            if (!PAD::IS_CONTROL_PRESSED(0, 61))
            {
                lsp = (g->vehicle.fly.speed * 2);
            }
            if (g->vehicle.fly.dont_stop)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, 0.0, 0 - (lsp), 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
            }
            else
            {
                VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, (0 - locspeed));
            }
        }

        if (PAD::IS_CONTROL_PRESSED(2, 63))
        {
            float lsp = ((0 - g->vehicle.fly.speed) * 2);
            if (!PAD::IS_CONTROL_PRESSED(0, 61))
            {
                lsp = (0 - g->vehicle.fly.speed);
            }
            if (g->vehicle.fly.dont_stop)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, (lsp), 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
            }
            else
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, (0 - (locspeed)), 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
            }
        }

        if (PAD::IS_CONTROL_PRESSED(2, 64))
        {
            float lsp = g->vehicle.fly.speed;
            if (!PAD::IS_CONTROL_PRESSED(0, 61))
            {
                lsp = (g->vehicle.fly.speed * 2);
            }
            if (g->vehicle.fly.dont_stop)
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, lsp, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
            }
            else
            {
                ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, locspeed, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
            }
        }

        if (!g->vehicle.fly.dont_stop && !PAD::IS_CONTROL_PRESSED(2, 71) && !PAD::IS_CONTROL_PRESSED(2, 72))
        {
            VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0.0);
        }

        if (TASK::GET_IS_TASK_ACTIVE(self::ped, 2))
        {
            g->vehicle.fly.enabled = false;
            VEHICLE::SET_VEHICLE_GRAVITY(self::veh, true);
            ENTITY::SET_ENTITY_COLLISION(self::veh, true, true);
            if (g->vehicle.fly.stop_on_exit)
            {
                VEHICLE::SET_VEHICLE_FORWARD_SPEED(self::veh, 0.0);
            }
        }
    }

	void looped::vehicle_fly()
	{
		if (g->vehicle.fly.enabled)
		{

            last_fly_tick = true;

            if (!self::veh)
            {
                g_notification_service->push_warning("Warning", "Please be in a vehicle before enabling vehicle fly.");
                g->vehicle.fly.enabled = false;
                return;
            }
            else 
            {
                if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(self::veh))
                {
                    do_vehicle_fly();
                    VEHICLE::SET_VEHICLE_GRAVITY(self::veh, false);
                }
                else
                {
                    for (int i = 0; i < 5; i++) 
                    {
                        entity::take_control_of(self::veh);
                        g_notification_service->push_warning("Warning", "Failed to take control of the vehicle.");
                    }

                }
            }
		}
        else
        {
            if (last_fly_tick)
            {
                ENTITY::SET_ENTITY_COLLISION(self::veh, true, true);
                VEHICLE::SET_VEHICLE_GRAVITY(self::veh, true);
                last_fly_tick = false;
            }
        }
	}
}
