#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	enum rgb_controller_t
	{
		rgb_controller_green_up,
		rgb_controller_red_down,
		rgb_controller_blue_up,
		rgb_controller_green_down,
		rgb_controller_red_up,
		rgb_controller_blue_down,
	};

	std::chrono::system_clock::time_point last_rgb_run_time;
	std::chrono::milliseconds delay = 0s;

	void looped::vehicle_rainbow_paint()
	{
		static int rgb_controller_v = rgb_controller_green_up;

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
				delay_step = 10;

				switch (rgb_controller_v)
				{
				case rgb_controller_green_up:
					green += 5;
					if (green >= 255)
					{
						green            = 255;
						rgb_controller_v = rgb_controller_red_down;
					}
					break;

				case rgb_controller_red_down:
					red -= 5;
					if (red < 0)
					{
						red              = 0;
						rgb_controller_v = rgb_controller_blue_up;
					}
					break;

				case rgb_controller_blue_up:
					blue += 5;
					if (blue >= 255)
					{
						blue             = 255;
						rgb_controller_v = rgb_controller_green_down;
					}
					break;

				case rgb_controller_green_down:
					green -= 5;
					if (green < 0)
					{
						green            = 0;
						rgb_controller_v = rgb_controller_red_up;
					}
					break;

				case rgb_controller_red_up:
					red += 5;
					if (red >= 255)
					{
						red              = 255;
						rgb_controller_v = rgb_controller_blue_down;
					}
					break;

				case rgb_controller_blue_down:
					blue -= 5;
					if (blue < 0)
					{
						blue             = 0;
						rgb_controller_v = rgb_controller_green_up;
					}
					break;

				default: break;
				}
			}


			Vehicle vehicle = self::veh;

			if (g.vehicle.rainbow_paint.primary)
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, red, green, blue);
			}
			if (g.vehicle.rainbow_paint.secondary)
			{
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, red, green, blue);
			}
			if (g.vehicle.rainbow_paint.neon)
			{
				VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, 0, 1);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, 1, 1);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, 2, 1);
				VEHICLE::SET_VEHICLE_NEON_ENABLED(vehicle, 3, 1);
				VEHICLE::SET_VEHICLE_NEON_COLOUR(vehicle, red, green, blue);
			}
			if (g.vehicle.rainbow_paint.smoke)
			{
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, red, green, blue);
			}

			delay = std::chrono::milliseconds(((delay_step * 10) + 10) - (g.vehicle.rainbow_paint.speed * delay_step));
			last_rgb_run_time = std::chrono::system_clock::now();
		}
	}
}