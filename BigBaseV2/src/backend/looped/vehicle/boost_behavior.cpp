#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_boost_behavior()
	{
		auto* const vehicle = g_local_player->m_vehicle;

		if (vehicle && VEHICLE::GET_HAS_ROCKET_BOOST_(self::veh))
		{
			if (g->vehicle.boost_behavior == 1 && vehicle->m_boost == 0.f) // No Boost Refil Time
			{
				vehicle->m_boost = 1.f;
			}
			else if (g->vehicle.boost_behavior == 2) // Infinite Boost
			{
				if (vehicle->m_boost_state)
				{
					vehicle->m_boost = 1.f;
				}
			}
		}
	}
}
