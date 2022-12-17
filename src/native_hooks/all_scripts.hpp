#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "util/scripts.hpp"
#include "hooking.hpp"

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

        void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(rage::scrNativeCallContext* src)
        {
            if (rage::scrThread::get() && rage::scrThread::get()->m_handler)
            {
                if (auto hook = g_hooking->m_handler_hooks[(CGameScriptHandler*)rage::scrThread::get()->m_handler].get())
                {
                    hook->disable();
                    g_hooking->m_handler_hooks.erase((CGameScriptHandler*)rage::scrThread::get()->m_handler);
                }
            }

            NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
        }

        void NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(rage::scrNativeCallContext* src)
        {
            if (rage::scrThread::get() && rage::scrThread::get()->m_handler)
            {
                if (auto hook = g_hooking->m_handler_hooks[(CGameScriptHandler*)rage::scrThread::get()->m_handler].get())
                {
                    hook->disable();
                    g_hooking->m_handler_hooks.erase((CGameScriptHandler*)rage::scrThread::get()->m_handler);
                }
            }

            src->set_return_value<BOOL>(NETWORK::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2)));
        }
    }
}