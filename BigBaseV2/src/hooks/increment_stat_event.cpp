#include "hooking.hpp"

namespace big
{
	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender, int64_t a3)
	{
		switch (net_event->m_stat)
		{
		case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_VC_HATE"):
		case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_TC_HATE"):
			const std::string report = fmt::format("From: {}", sender->get_name());

			if (g->notifications.reports.log)
				LOG(INFO) << "Blocked report; " << report;

			if (g->notifications.reports.notify)
				g_notification_service->push_warning("BLOCKED REPORT", report);

			return true;
		}

		return g_hooking->m_increment_stat_hook.get_original<decltype(&increment_stat_event)>()(net_event, sender, a3);
	}
}