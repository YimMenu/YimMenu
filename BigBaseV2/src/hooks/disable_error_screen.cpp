#include "gta/joaat.hpp"
#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	void hooks::set_warning_message_with_header_and_substring_flags(
		char* entryHeader,
		char* entryLine1,
		int instructionalKey,
		char* entryLine2,
		BOOL p4,
		Any p5,
		Any* additionalIntInfo,
		const char* additionalTextInfoLine1,
		const char* additionalTextInfoLine2,
		BOOL background,
		int errorCode
	)
	{
		if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("shop_controller")) return;

		return g_hooking->m_error_screen_hook.get_original<decltype(&hooks::set_warning_message_with_header_and_substring_flags)>()(
			entryHeader,
			entryLine1,
			instructionalKey,
			entryLine2,
			p4,
			p5,
			additionalIntInfo,
			additionalTextInfoLine1,
			additionalTextInfoLine2,
			background,
			errorCode
		);
	}
}