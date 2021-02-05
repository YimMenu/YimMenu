#include "features/vehicle.hpp"
#include "features/functions.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void vehicle::sticky_tyres()
	{
		if (g_settings.options["sticky_tyres"].get<bool>())
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			if (veh)
			{
				func::take_control_of_entity(veh);

				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 5.f);
			}
		}
	}
}