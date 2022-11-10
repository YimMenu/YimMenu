#include "hooking.hpp"

namespace big
{
    void hooks::add_message(int64_t a1, int64_t a2, int64_t a3, const char* message, bool is_team_chat)
	{
        if(g->session.log_chat_message)
        {
            if(CNetGamePlayer* net_game_player = g_pointers->m_get_net_game_player(a3); net_game_player)
                LOG(INFO) << "[CHAT MESSAGE] " << net_game_player->m_player_info->m_net_player_data.m_name << ": " << message;
            else
                LOG(INFO) << "[CHAT MESSAGE] " << "unknown: " << message;
        }
		
		return g_hooking->get_original<add_message>()(a1, a2, a3, message, is_team_chat);
	}
}