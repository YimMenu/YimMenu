#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::player_remote_control_vehicle() 
	{
		if (g.m_remote_controller_vehicle == -1)
			return;

		if (!ENTITY::DOES_ENTITY_EXIST(g.m_remote_controlled_vehicle))
		{
			g.m_remote_controlled_vehicle = -1;
			g.m_remote_controlled_vehicle = -1;
			return;
		}

		if (!ENTITY::DOES_ENTITY_EXIST(g.m_remote_controller_vehicle))
		{
			g.m_remote_controlled_vehicle = -1;
			g.m_remote_controlled_vehicle = -1;
			return;
		}

		if (VEHICLE::IS_VEHICLE_SEAT_FREE(g.m_remote_controller_vehicle, -1, TRUE))
		{
			auto controlled = g.m_remote_controlled_vehicle;
			auto controller = g.m_remote_controller_vehicle;
			g_fiber_pool->queue_job([controlled, &controller] {
				if (entity::take_control_of(controlled))
				{
					ENTITY::SET_ENTITY_COLLISION(g.m_remote_controlled_vehicle, TRUE, TRUE);
					ENTITY::DETACH_ENTITY(controlled, TRUE, TRUE);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(controlled, 0);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(controlled, FALSE);
					ENTITY::SET_ENTITY_INVINCIBLE(controlled, FALSE);
					entity::delete_entity(controller);
				}
			});


			g.m_remote_controller_vehicle = -1;
			g.m_remote_controlled_vehicle = -1;
		}
	}
};