#include "hooking.hpp"

namespace big
{
	int hooks::censor_chat(int64_t chat_menu, const char* user_text, const char** output_text)
	{
		if (g_settings.options["disable_chat_censoring"].get<bool>()) return -1;

		return g_hooking->m_censor_chat.get_original<decltype(&hooks::censor_chat)>()(chat_menu, user_text, output_text);
	}
}