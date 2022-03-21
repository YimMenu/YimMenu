#include "hooking.hpp"

namespace big
{
	// in this hook we rebuild how the game reads data from the datBitBuffer
	// we specifically recreate what the game uses to "detect" the NET_ARRAY_ERROR
	// then if we find such a crash we just return false;
	bool hooks::net_array_handler(long long netArrayHandlerBaseMgr, CNetGamePlayer* a2, rage::datBitBuffer* datbitbuffer, unsigned int bytes_to_read, short a5)
	{
		if (datbitbuffer->m_bitsRead + bytes_to_read > datbitbuffer->m_curBit)
		{
			if (g->notifications.net_array_error.log)
				LOG(WARNING) << "Received NET_ARRAY_ERROR crash from " << a2->get_name();

			if (g->notifications.net_array_error.notify)
				g_notification_service->push_warning("Protections", fmt::format("Detected NET_ARRAY_ERROR crash from {}", a2->get_name()));
      
			return false;
		}

		return g_hooking->m_net_array_handler_hook.get_original<decltype(&hooks::net_array_handler)>()(netArrayHandlerBaseMgr, a2, datbitbuffer, bytes_to_read, a5);
	}
}