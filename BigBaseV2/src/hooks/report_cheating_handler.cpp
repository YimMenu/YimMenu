#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	void hooks::report_cheating_handler(__int64 a1, unsigned int a2, unsigned int a3, unsigned int a4)
	{
		LOG(INFO) << "Caught game trying to report self.";
		notify::above_map("Game tried to snitch.");

		return;

		//return g_hooking->m_report_cheating_hook.get_original<decltype(&hooks::report_cheating_handler)>()(a1, a2, a3, a4);
	}
}