#include "gta/joaat.hpp"
#include "hooking.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void hooks::set_warning_message_with_header(
		const char* entryHeader,
		const char* entryLine1,
		int instructionalKey,
		const char* entryLine2,
		bool p4,
		Any p5,
		Any* showBackground,
		Any* p7,
		bool p8,
		Any p9
	)
	{
		if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("shop_controller") && strcmp(entryLine1, "CTALERT_F_2") == 0)
		{
			if (g->notifications.transaction_rate_limit.log)
				LOG(WARNING) << "Received transaction rate limit";
			if (g->notifications.transaction_rate_limit.notify)
				g_notification_service->push_warning("Transaction Rate Limit", "You're receiving transaction rate limits, whatever you're doing do it less.");

			// dismisses popup instead of killing it silently
			*script_global(4529830).as<int*>() = 0;

			// we still return to prevent our original call from rendering a single frame
			return;
		}

		return g_hooking->m_error_screen_hook.get_original<decltype(&hooks::set_warning_message_with_header)>()(
			entryHeader,
			entryLine1,
			instructionalKey,
			entryLine2,
			p4,
			p5,
			showBackground,
			p7,
			p8,
			p9
		);
	}
}