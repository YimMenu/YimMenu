#pragma once
#include "gta_util.hpp"
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

        void GET_PLAYER_NAME(rage::scrNativeCallContext* src)
        {
            const auto playerId = src->get_arg<Player>(0);
            src->set_return_value(PLAYER::GET_PLAYER_NAME(playerId));
            if (g->spoofing.spoof_username)
            {
                const auto network_player_mgr = gta_util::get_network_player_mgr();
                if (network_player_mgr && network_player_mgr->m_local_net_player && playerId == network_player_mgr->m_local_net_player->m_player_id)
                {
                    src->set_return_value(g->spoofing.username.c_str());
                }
            }
        }
    }
}