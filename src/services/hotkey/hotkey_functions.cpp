#include "common.hpp"
#include "hotkey_functions.hpp"
#include "services/notifications/notification_service.hpp"

namespace big::hotkey_funcs
{
    void toggle_noclip()
    {
        const auto state = !g.self.noclip;
        g_notification_service->push("Noclip", std::format("Noclip has been {}.", state ? "enabled" : "disabled"));

        g.self.noclip = state;
    }
}