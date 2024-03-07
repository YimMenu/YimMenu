#include "gta/net_game_event.hpp"
#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"

#include <network/CNetGamePlayer.hpp>

namespace big
{
	bool hooks::increment_stat_event(CNetworkIncrementStatEvent* net_event, CNetGamePlayer* sender)
	{
		switch (net_event->m_stat)
		{
		case "MPPLY_BAD_CREW_STATUS"_J:
		case "MPPLY_BAD_CREW_MOTTO"_J:
		case "MPPLY_BAD_CREW_NAME"_J:
		case "MPPLY_BAD_CREW_EMBLEM"_J:
		case "MPPLY_EXPLOITS"_J:
		case "MPPLY_GAME_EXPLOITS"_J:
		case "MPPLY_TC_ANNOYINGME"_J:
		case "MPPLY_TC_HATE"_J:
		case "MPPLY_VC_ANNOYINGME"_J:
		case "MPPLY_VC_HATE"_J:
			g.reactions.report.process(g_player_service->get_by_id(sender->m_player_id));
			return true;
		}

		return false;
	}
}
