#include "hooking.hpp"
#include "pointers.hpp"
#include "services/chat/chat_service.hpp"

namespace big
{
    __int64* hooks::chat_receive(__int64 a1, __int64 a2, __int64 sender, const char* msg, char is_team)
    {
        CNetGamePlayer* Player = g_pointers->m_get_net_player_from_unk(sender);

        if (Player != nullptr)
        {
            g_chat_service->add_msg(Player, msg, (bool)is_team);
            LOG(INFO) << Player->get_name() << ((bool)is_team ? " [LOCAL] " : " [ALL] ") << msg;
        }

        return g_hooking->m_chat_message_received_hook.get_original<decltype(&chat_receive)>()(a1, a2, sender, msg, is_team);
    }
}
