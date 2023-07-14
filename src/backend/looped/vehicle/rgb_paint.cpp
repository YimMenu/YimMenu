#include "backend/bool_command.hpp"
#include "backend/int_command.hpp"
#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "core/data/color.hpp"

namespace big
{
	void looped::vehicle_rainbow_paint()
	{
		static std::chrono::system_clock::time_point last_rgb_run_time;
		static std::chrono::milliseconds delay = 0s;

		static int red   = 255;
		static int green = 0;
		static int blue  = 0;

		if (self::veh && g.vehicle.rainbow_paint.type != RainbowPaintType::Off && last_rgb_run_time + delay < std::chrono::system_clock::now())
		{
			int delay_step = 100;

			if (g.vehicle.rainbow_paint.type == RainbowPaintType::Spasm)
			{
				red   = rand() % 256;
				green = rand() % 256;
				blue  = rand() % 256;
			}
			else if (g.vehicle.rainbow_paint.type == RainbowPaintType::Fade)
			{
				red   = rgb.red;
				blue  = rgb.blue;
				green = rgb.green;
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
				VEHICLE::SET_VEHICLE_NEON_ENABLED(self::veh, 0, 1);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(self::veh, 1, 1);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(self::veh, 2, 1);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(self::veh, 3, 1);
				VEHICLE::SET_VEHICLE_NEON_COLOUR(self::veh, red, green, blue);
			}
			if (g.vehicle.rainbow_paint.smoke)
			{
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(self::veh, red, green, blue);
			}

			delay = std::chrono::milliseconds(((delay_step * 10) + 10) - (g.vehicle.rainbow_paint.speed * delay_step));
			last_rgb_run_time = std::chrono::system_clock::now();
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