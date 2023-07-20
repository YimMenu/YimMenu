#include "backend/bool_command.hpp"
#include "backend/int_command.hpp"
#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	float red = 255.f, green = 0.f, blue = 0.f;
	void looped::vehicle_rainbow_paint()
	{
		if (g.vehicle.rainbow_paint.type == RainbowPaintType::Spasm)
		{
				red   = rand() % 255;
				green = rand() % 255;
				blue  = rand() % 255;
		}
		if (g.vehicle.rainbow_paint.type == RainbowPaintType::Fade) //messy but gets job done
		{
			if (red > 0 && blue == 0)
			{
				green += g.vehicle.rainbow_paint.speed;
				red -= g.vehicle.rainbow_paint.speed;
			}
			if (green > 0 && red == 0)
			{
				blue += g.vehicle.rainbow_paint.speed;
				green -= g.vehicle.rainbow_paint.speed;
			}
			if (blue > 0 && green == 0)
			{
				red += g.vehicle.rainbow_paint.speed;
				blue -= g.vehicle.rainbow_paint.speed;
			}
			if (red > 255) {red = 255;} //checks
			if (green > 255) {green = 255;}
			if (blue > 255) {blue = 255;}
			if (red < 0) {red = 0;}
			if (green < 0) {green = 0;}
			if (blue < 0) {blue = 0;}
		}

		if (g.vehicle.rainbow_paint.primary)
		{
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(self::veh, red, green, blue);
		}
		if (g.vehicle.rainbow_paint.secondary)
		{
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(self::veh, red, green, blue);
		}
		if (g.vehicle.rainbow_paint.neon)
		{
			VEHICLE::SET_VEHICLE_NEON_COLOUR(self::veh, red, green, blue);
		}
		if (g.vehicle.rainbow_paint.smoke)
		{
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(self::veh, red, green, blue);
		}
	}

	bool_command g_rainbow_paint_primary("rainbowpri", "Rainbow Paint: Apply to Primary", "Applies active rainbow effect to the current vehicle's primary color",
	    g.vehicle.rainbow_paint.primary);
	bool_command g_rainbow_paint_secondary("rainbowsec", "Rainbow Paint: Apply to Secondary", "Applies active rainbow effect to the current vehicle's secondary color",
	    g.vehicle.rainbow_paint.secondary);
	bool_command g_rainbow_paint_neon("rainbowneons", "Rainbow Paint: Apply to Neons", "Applies active rainbow effect to the current vehicle's neon color",
	    g.vehicle.rainbow_paint.neon);
	bool_command g_rainbow_paint_smoke("rainbowsmoke", "Rainbow Paint: Apply to Tire Smoke", "Applies active rainbow effect to the current vehicle's tire smoke color",
	    g.vehicle.rainbow_paint.smoke);
	int_command g_rainbow_paint_speed("rainbowspeed", "Rainbow Paint: Speed", "Speed of the rainbow paint effect",
	    g.vehicle.rainbow_paint.speed, 1, 10);

}