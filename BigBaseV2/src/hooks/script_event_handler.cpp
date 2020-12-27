#include "hooking.hpp"

namespace big
{
	bool hooks::script_event_handler(std::int64_t NetEventStruct, std::int64_t CNetGamePlayer)
	{
		return g_hooking->m_script_event_hook.get_original<decltype(&script_event_handler)>()(NetEventStruct, CNetGamePlayer);
	}
}