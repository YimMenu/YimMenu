#include "hooking.hpp"
#include "gta/net_game_event.hpp"
#include <network/CNetGamePlayer.hpp>

namespace big
{
	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender)
	{
		switch (net_event->m_stat)
		{
		case RAGE_JOAAT("MPPLY_BAD_CREW_STATUS"):
		case RAGE_JOAAT("MPPLY_BAD_CREW_MOTTO"):
		case RAGE_JOAAT("MPPLY_BAD_CREW_NAME"):
		case RAGE_JOAAT("MPPLY_BAD_CREW_EMBLEM"):
		case RAGE_JOAAT("MPPLY_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_TC_HATE"):
		case RAGE_JOAAT("MPPLY_VC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_VC_HATE"):
			const auto report = std::format("From: {}", sender->get_name());

			if (g.notifications.reports.log)
				LOG(INFO) << "Blocked report; " << report;

			if (g.notifications.reports.notify)
				g_notification_service->push_warning("BLOCKED REPORT", report);

			return true;
		}

		return false;
	}
}