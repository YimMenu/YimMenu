#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/teleport.hpp"

namespace big
{
    class auto_tp_to_waypoint : looped_command
    {
        using looped_command::looped_command;

        virtual void on_tick() override
        {
            //this is a hack to prevent the warning notify..
            if (!teleport::to_blip((int)BlipIcons::Waypoint))
                return;

            bool temp_disable_tp = (!*g_pointers->m_is_session_started) && CUTSCENE::IS_CUTSCENE_ACTIVE();
            if (!temp_disable_tp)
                teleport::to_waypoint();
        }
    };

    auto_tp_to_waypoint g_auto_tp_to_waypoint("autotptowp", "Auto-Teleport To Waypoint", "Automatically teleports you to a waypoint as soon as you set one.", g.self.auto_tp);
}
