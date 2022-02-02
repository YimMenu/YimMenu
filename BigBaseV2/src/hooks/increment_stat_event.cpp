#include "hooking.hpp"
#include "natives.hpp"
#include "util/notify.hpp"

namespace big
{
	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender, int64_t a3)
	{
		switch (net_event->m_stat)
		{
		case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_VC_HATE"):
		case RAGE_JOAAT("MPPLY_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_TC_HATE"):
			std::string report = fmt::format("~g~BLOCKED REPORT~s~\nFrom: <C>{}</C>", sender->get_name());

			notify::above_map(report);

			return true;
		}

		return g_hooking->m_increment_stat_hook.get_original<decltype(&increment_stat_event)>()(net_event, sender, a3);
	}
}