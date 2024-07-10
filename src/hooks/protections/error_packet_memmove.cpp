#include "hooking/hooking.hpp"

namespace big
{
	void hooks::error_packet_memmove(void* dst, void* src, int size)
	{
		if (!src || !dst) [[unlikely]]
			return;

		// remote crash
		if (size > 0x80) [[unlikely]]
		{
			LOG(INFO) << "remote crash blocked";
			return;
		}

		return g_hooking->m_error_packet_memmove_hook.get_original<decltype(&hooks::error_packet_memmove)>()(dst, src, size);
	}
}