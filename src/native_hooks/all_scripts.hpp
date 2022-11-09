#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
    namespace all_scripts
    {
        void IS_DLC_PRESENT(rage::scrNativeCallContext* src)
        {
            const auto hash = src->get_arg<rage::joaat_t>(0);
            
            bool return_value = DLC::IS_DLC_PRESENT(hash);
            if (hash == 0x96F02EE6)
                return_value = return_value || g->settings.dev_dlc;

            src->set_return_value(return_value);
        }

        inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
        {
            if (g->tunables.fast_join)
            {
                LOG(G3LOG_DEBUG) << "NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA skipped";
                src->set_return_value<BOOL>(TRUE);
            }
            else
            {
                src->set_return_value<BOOL>(NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA());
            }
        }

        inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
        {
            if (RAGE_JOAAT("freemode") == SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME())
            {
                std::string text = std::format("NETWORK_BAIL({}, {}, {})", src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
                LOG(WARNING) << "Prevented freemode " << text;
                g_notification_service->push_warning("freemode", text);
            }
            else
            {
                std::string text = std::format("NETWORK_BAIL({}, {}, {})", src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
                LOG(G3LOG_DEBUG) << text;
                g_notification_service->push("NETWORK_BAIL", text);
                NETWORK::NETWORK_BAIL(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
            }
        }
    }
}