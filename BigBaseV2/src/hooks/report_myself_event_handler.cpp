#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	void hooks::report_myself_event_handler(__int64 a1, unsigned int a2, unsigned int a3, unsigned int a4)
	{
		LOG(INFO) << "Blocked REPORT_MYSELF_EVENT";

		return;
	}
}