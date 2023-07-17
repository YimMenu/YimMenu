#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_boost_behavior()
	{
		auto* const vehicle = g_local_player->m_vehicle;

		if (vehicle && VEHICLE::GET_HAS_ROCKET_BOOST(self::veh))
		{
			if (g.vehicle.boost_behavior == eBoostBehaviors::INSTANT_REFIL && (vehicle->m_boost == 0.f || !vehicle->m_boost_state))// Instant Refill
			{
				vehicle->m_boost_allow_recharge = true;
				vehicle->m_boost                = 3.f;
			}
			else if (g.vehicle.boost_behavior == eBoostBehaviors::INFINITE_BOOST)// Infinite Boost
			{
				vehicle->m_boost_allow_recharge = true;
				vehicle->m_boost                = 3.f;
			}
			else if (g.vehicle.boost_behavior == eBoostBehaviors::HOLD_FOR_INFINITE)
			{
				if (vehicle->m_boost_state && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ROCKET_BOOST))
				{
					vehicle->m_boost_allow_recharge = true;
					vehicle->m_boost                = 3.f;
				}
				else if (vehicle->m_boost_state)
				{
					vehicle->m_boost_state = false;
				}
			}
		}
	}
}
