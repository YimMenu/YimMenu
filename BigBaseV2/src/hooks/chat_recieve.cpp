#include "hooking.hpp"

namespace big 
{
	std::string previous_message = "";

	__int64* hooks::chat_receive(__int64 chat_pointer, __int64 unk2, __int64 peerId, const char* msg, char IsTeam)
	{
		if (msg == previous_message)
		{
			std::string message = fmt::format("Duplicate message purged: {}", msg);

			if (g->notifications.chat_receive.log)
				LOG(WARNING) << message;

			if (g->notifications.chat_receive.notify)
				g_notification_service->push_warning("Protections", message);

			return nullptr; //Blocks the message from appearing in chat
		}
		
		previous_message = msg;

		//Displays the message in chat as normal
		return g_hooking->m_chat_receive_hook.get_original<decltype(&chat_receive)>()(chat_pointer, unk2, peerId, msg, IsTeam);
	}
}