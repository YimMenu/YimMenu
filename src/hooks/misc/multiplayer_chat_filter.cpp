#include "hooking.hpp"

namespace big
{
	int hooks::multiplayer_chat_filter(__int64 chat_type, const char* input, const char** output)
	{
		if (g.session.disable_chat_filter)
		{
			return -1;
		}
		return g_hooking->get_original<hooks::multiplayer_chat_filter>()(chat_type, input, output);
	}
}
