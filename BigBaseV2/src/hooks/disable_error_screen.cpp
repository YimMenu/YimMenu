#include "gta/joaat.hpp"
#include "hooking.hpp"
#include "natives.hpp"

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
		if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("shop_controller")) return;

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