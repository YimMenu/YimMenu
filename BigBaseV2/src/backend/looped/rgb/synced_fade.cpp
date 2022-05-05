#include "backend/looped/looped.hpp"
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

    void looped::rgb_synced_fade()
    {
        if (g->rgb.fade)
        {
            static int rgb_controller_v = rgb_controller_green_up;

            switch (rgb_controller_v)
            {
            case rgb_controller_green_up:
                g->rgb.g += g->rgb.speed;
                if (g->rgb.g >= 255)
                {
                    g->rgb.g = 255;
                    rgb_controller_v = rgb_controller_red_down;
                }
                break;

            case rgb_controller_red_down:
                g->rgb.r -= g->rgb.speed;
                if (g->rgb.r < 0)
                {
                    g->rgb.r = 0;
                    rgb_controller_v = rgb_controller_blue_up;
                }
                break;

            case rgb_controller_blue_up:
                g->rgb.b += g->rgb.speed;
                if (g->rgb.b >= 255)
                {
                    g->rgb.b = 255;
                    rgb_controller_v = rgb_controller_green_down;
                }
                break;

            case rgb_controller_green_down:
                g->rgb.g -= g->rgb.speed;
                if (g->rgb.g < 0)
                {
                    g->rgb.g = 0;
                    rgb_controller_v = rgb_controller_red_up;
                }
                break;

            case rgb_controller_red_up:
                g->rgb.r += g->rgb.speed;
                if (g->rgb.r >= 255)
                {
                    g->rgb.r = 255;
                    rgb_controller_v = rgb_controller_blue_down;
                }
                break;

            case rgb_controller_blue_down:
                g->rgb.b -= g->rgb.speed;
                if (g->rgb.b < 0)
                {
                    g->rgb.b = 0;
                    rgb_controller_v = rgb_controller_green_up;
                }
                break;

            default:
                throw std::runtime_error("Invalid case provided to RGB controller!");
            }
        }
    }
}
