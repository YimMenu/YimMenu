#include "backend/looped/looped.hpp"
#include "util/teleport.hpp"

namespace big
{
    void looped::hotkeys_teleport_waypoint()
    {
        static int once = 0;
        if (g->settings.hotkeys.teleport_waypoint_triggered)
        {
            if (once == 0)
            {
                teleport::to_waypoint();
                once = 1;
            }
        }
        else once = 0;
    }
}