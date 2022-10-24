#include "hooking.hpp"
#include "pointers.hpp"
#include "services/chat/chat_service.hpp"

namespace big
{
    __int64* hooks::chat_receive(__int64 a1, __int64 a2, __int64 sender, const char* msg, bool is_team)
    {
        CNetGamePlayer* net_player = g_pointers->m_get_net_player_from_unk(sender);
        std::string previous_message = "";

        if (net_player != nullptr)
        {
            if (msg == previous_message)
            {
                std::string message = std::format("Duplicate message purged: {}", msg);

                if (g->notifications.chat_receive.log)
                    LOG(WARNING) << message;

                if (g->notifications.chat_receive.notify)
                    g_notification_service->push_warning("Protections", message);

                return nullptr; //Blocks the message from appearing in chat
            }
            previous_message = msg;

            g_chat_service->add_msg(net_player, msg, is_team);
            LOG(INFO) << net_player->get_name() << (is_team ? " [LOCAL] " : " [ALL] ") << msg;
        }

        return g_hooking->m_chat_message_received_hook.get_original<decltype(&chat_receive)>()(a1, a2, sender, msg, is_team);
    }
}
