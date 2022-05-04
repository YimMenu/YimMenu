#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_rainbow_paint()
	{
		const Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		if (veh && g->vehicle.rainbow_paint)
		{
			if (g->vehicle.rainbow_paint == 1)
			{
				g->rgb.fade = true;
				g->rgb.spasm = false;
			}
			else if (g->vehicle.rainbow_paint == 2)
			{
				g->rgb.spasm = true;
				g->rgb.fade = false;
			}

			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, g->rgb.r, g->rgb.g, g->rgb.b);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, g->rgb.r, g->rgb.g, g->rgb.b);
		}
	}
}