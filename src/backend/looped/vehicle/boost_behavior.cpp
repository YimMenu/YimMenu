#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_boost_behavior()
	{
		if (g_local_player == nullptr)
			return;

		auto* const vehicle = g_local_player->m_vehicle;

		bool is_rocket = VEHICLE::GET_HAS_ROCKET_BOOST(self::veh);
		bool is_kers   = VEHICLE::GET_VEHICLE_HAS_KERS(self::veh);

		if (vehicle && (is_rocket || is_kers))
		{
			if (g.vehicle.boost_behavior == eBoostBehaviors::INSTANT_REFIL) // Instant Refill
			{
				if (is_rocket && (vehicle->m_boost == 0.f || !vehicle->m_boosting))
				{
					vehicle->m_boost_allow_recharge = true;
					vehicle->m_boost                = 10.f;
				}
				else if (is_kers && vehicle->m_kers_boost == 0.f)
				{
					vehicle->m_kers_boost = vehicle->m_kers_boost_max;
				}
			}
			else if (g.vehicle.boost_behavior == eBoostBehaviors::INFINITE_BOOST) // Infinite
			{
				vehicle->m_boost_allow_recharge = true;
				vehicle->m_boost                = 10.f;
				vehicle->m_kers_boost           = vehicle->m_kers_boost_max - 0.01f;
			}
			else if (g.vehicle.boost_behavior == eBoostBehaviors::HOLD_FOR_INFINITE) //Hold for Boost
			{
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ROCKET_BOOST) || PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_FLY_BOOST))
				{
					if (is_rocket && vehicle->m_boosting)
					{
						vehicle->m_boost_allow_recharge = true;
						vehicle->m_boost                = 10.f;
					}
					else if (is_kers)
					{
						vehicle->m_kers_boost = vehicle->m_kers_boost_max - 0.01f;
					}
				}
				else if (is_rocket && vehicle->m_boosting)
				{
					vehicle->m_boosting = false;
				}
			}
		}
	}
}
