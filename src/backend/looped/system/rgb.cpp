#include "backend/looped/looped.hpp"
#include "core/data/color.hpp"

namespace big
{
	void looped::system_rainbow()
	{
		static std::chrono::system_clock::time_point last_rgb_run_time;
		static std::chrono::milliseconds delay = 0s;

		enum rgb_controller_t
		{
			rgb_controller_green_up,
			rgb_controller_red_down,
			rgb_controller_blue_up,
			rgb_controller_green_down,
			rgb_controller_red_up,
			rgb_controller_blue_down,
		};


		if (last_rgb_run_time + delay < std::chrono::system_clock::now())
		{
			int delay_step = 100;
			if (g.settings.rainbow.spasm)
			{
				rgb.red   = rand() % 256;
				rgb.green = rand() % 256;
				rgb.blue  = rand() % 256;
			}
			else if (g.settings.rainbow.fade)
			{
				int delay_step = 10;

				static int rgb_controller_v = rgb_controller_green_up;

				switch (rgb_controller_v)
				{
				case rgb_controller_green_up:
					rgb.green += 5;
					if (rgb.green >= 255)
					{
						rgb.green        = 255;
						rgb_controller_v = rgb_controller_red_down;
					}
					break;

				case rgb_controller_red_down:
					rgb.red -= 5;
					if (rgb.red < 0)
					{
						rgb.red          = 0;
						rgb_controller_v = rgb_controller_blue_up;
					}
					break;

				case rgb_controller_blue_up:
					rgb.blue += 5;
					if (rgb.blue >= 255)
					{
						rgb.blue         = 255;
						rgb_controller_v = rgb_controller_green_down;
					}
					break;

				case rgb_controller_green_down:
					rgb.green -= 5;
					if (rgb.green < 0)
					{
						rgb.green        = 0;
						rgb_controller_v = rgb_controller_red_up;
					}
					break;

				case rgb_controller_red_up:
					rgb.red += 5;
					if (rgb.red >= 255)
					{
						rgb.red          = 255;
						rgb_controller_v = rgb_controller_blue_down;
					}
					break;

				case rgb_controller_blue_down:
					rgb.blue -= 5;
					if (rgb.blue < 0)
					{
						rgb.blue         = 0;
						rgb_controller_v = rgb_controller_green_up;
					}
					break;

				default: break;
				}
			}

			delay = std::chrono::milliseconds(((delay_step * 10) + 10) - (g.settings.rainbow.speed * delay_step));
			last_rgb_run_time = std::chrono::system_clock::now();
		}
	}
}