#include "features.hpp"

namespace big
{
	void features::sticky_tyres()
	{
		if (g_settings.options["sticky_tyres"].get<bool>())
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{

				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

				if (veh)
				{
					while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh))
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);

						script::get_current()->yield();
					}

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 5.f);
				}
			}QUEUE_JOB_END_CLAUSE
		}
	}
}