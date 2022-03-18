#include "hooking.hpp"

namespace big
{
	// in this hook we rebuild how the game reads data from the datBitBuffer
	// we specifically recreate what the game uses to "detect" the NET_ARRAY_ERROR
	// then if we find such a crash we just return false;
	bool hooks::net_array_handler(long long netArrayHandlerBaseMgr, unsigned char* a2, rage::datBitBuffer* datbitbuffer, unsigned int bytes_to_read, short a5)
	{
		if (g_running)
		{
			DWORD test = 0;

			const auto bytes_start = datbitbuffer->m_bitsRead;
			for (unsigned int i = datbitbuffer->m_bitsRead - bytes_start;
				i < bytes_to_read;
				i = datbitbuffer->m_bitsRead - bytes_start)
			{
				const auto bytes_read_before = datbitbuffer->m_bitsRead;
				g_pointers->m_read_bitbuf_dword(datbitbuffer, &test, 1u);

				if (bytes_read_before == datbitbuffer->m_bitsRead)
				{
					LOG(INFO) << "NET_ARRAY_ERROR caught, someones probably trying to crash us.";

					return false;
				}
			}

			datbitbuffer->Seek(bytes_start);
		}

		return g_hooking->m_net_array_handler_hook.get_original<decltype(&hooks::net_array_handler)>()(netArrayHandlerBaseMgr, a2, datbitbuffer, bytes_to_read, a5);
	}
}