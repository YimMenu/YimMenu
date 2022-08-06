#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_rainbow_paint()
	{
		if (g->vehicle.rainbow_paint)
		{
			Vehicle vehicle = self::veh;

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
			if (g->vehicle.rainbow_primary) {
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, g->rgb.r, g->rgb.g, g->rgb.b);
			}
			if (g->vehicle.rainbow_secondary) {
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, g->rgb.r, g->rgb.g, g->rgb.b);
			}
			if (g->vehicle.rainbow_neon) {
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehicle, 0, 1);
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehicle, 1, 1);
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehicle, 2, 1);
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehicle, 3, 1);
				VEHICLE::SET_VEHICLE_NEON_LIGHTS_COLOUR_(vehicle, g->rgb.r, g->rgb.g, g->rgb.b);
			}
			if (g->vehicle.rainbow_smoke) {
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, g->rgb.r, g->rgb.g, g->rgb.b);
			}
		}
	}
}