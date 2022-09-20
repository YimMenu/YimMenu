#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_boost_behavior()
	{
		auto* const vehicle = g_local_player->m_vehicle;

		if (vehicle && VEHICLE::GET_HAS_ROCKET_BOOST(self::veh))
		{
			if (g->vehicle.boost_behavior == eBoostBehaviors::INSTANT_REFIL && vehicle->m_boost == 0.f) // No Boost Refil Time
			{
				vehicle->m_boost = 1.f;
			}
			else if (g->vehicle.boost_behavior == eBoostBehaviors::INFINITE_BOOST) // Infinite Boost
			{
				if (vehicle->m_boost_state)
				{
					vehicle->m_boost_allow_recharge = true;
					vehicle->m_boost = 1.f;
				}
			}
		}
	}
}
