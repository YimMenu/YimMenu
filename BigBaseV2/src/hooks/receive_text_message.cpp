#include "hooking.hpp"
#include "pointers.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "util/toxic.hpp"
#include "file_manager.hpp"

namespace big
{
	constexpr static const char* spam[] =
	{
		"QQ",
		"WWW.",
		"GTA",
		"www.",
		".cn",
		".CN",
		".TOP",
		".COM",
		".me",
		"666",
		".gg",
		"TRUSTED",
		"VX",
		"\xE3\x80\x90",
		"\xE9\x87\x91",
	};

	static uint64_t gamerHandle[13];
	static char buffer[160]{};

	void hooks::text_message_received(void* a1, char* message, void* something)
	{
		bool found = false;
		if (strlen(message) > 20)
		{
			for (auto v : spam)
			{
				if (strstr(message, v) != NULL)
				{
					found = true;
					break;
				}
			}
		}

		LOG(INFO) << "Chat," << message;

		g_hooking->m_text_message_received_hook.get_original<decltype(&hooks::text_message_received)>()(a1, message, something);
		return;
	}
}