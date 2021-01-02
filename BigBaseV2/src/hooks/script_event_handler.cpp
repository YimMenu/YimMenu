#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::script_event_handler(std::int64_t NetEventStruct, std::int64_t CNetGamePlayer)
	{
		auto args = reinterpret_cast<std::int64_t*>(NetEventStruct + 0x70);
		Player SenderID = *reinterpret_cast<std::int8_t*>(CNetGamePlayer + 0x2D);

		const auto ScriptEventHash = args[0];

		if (g_settings.options["settings"]["logging"]["script_events"])
			LOG(INFO) << "Received Script Event " << ScriptEventHash << " from Player " << PLAYER::GET_PLAYER_NAME(SenderID);

		return g_hooking->m_script_event_hook.get_original<decltype(&script_event_handler)>()(NetEventStruct, CNetGamePlayer);
	}
}