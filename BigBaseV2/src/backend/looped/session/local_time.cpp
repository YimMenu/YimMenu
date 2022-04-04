#include "backend/looped/looped.hpp"
#include "natives.hpp"
namespace big
{
    static bool toggled = true;

    void looped::session_local_time()
    {
        struct
        {
            int hour{ g->session.custom_time.hour }, minute{ g->session.custom_time.minute }, second{ g->session.custom_time.minute };
        } set_time;

        if (g->session.override_time)
        {

            if (toggled)
            {
                NETWORK::NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(&g->session.custom_time.hour, &g->session.custom_time.minute, &g->session.custom_time.second);
                toggled = false;
            }

            while (g->session.custom_time.hour > set_time.hour)
            {
                if (set_time.minute < 59)
                {
                    set_time.minute++;
                }
                else
                {
                    set_time.hour++;
                    set_time.minute = 0;
                }
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(set_time.hour, set_time.minute, g->session.custom_time.second);

            }

            while (g->session.custom_time.hour < set_time.hour)
            {
                if (set_time.minute > 0)
                {
                    set_time.minute--;
                }
                else
                {
                    set_time.hour--;
                    set_time.minute = 59;
                }
                NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(set_time.hour, set_time.minute, g->session.custom_time.second);

            }

        }
        else
        {
            NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
            toggled = true;
        }

    }
}