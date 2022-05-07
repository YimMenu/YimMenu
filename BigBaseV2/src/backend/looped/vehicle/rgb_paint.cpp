#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_rainbow_paint()
	{

		if (self::veh && g->vehicle.rainbow_paint)
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

			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(self::veh, g->rgb.r, g->rgb.g, g->rgb.b);
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(self::veh, g->rgb.r, g->rgb.g, g->rgb.b);
		}
	}
}