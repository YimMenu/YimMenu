#include "hooking/hooking.hpp"

namespace big
{
	int hooks::netfilter_handle_message(__int64 filter, char* message, int flags)
	{
		int* features = (int*)(filter + 0x24);
		int old       = *features;
		*features     = 0;
		auto id       = g_hooking->get_original<netfilter_handle_message>()(filter, message, flags);
		*features     = old;
		return id;
	}
}
