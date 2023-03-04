#include "gta/net_game_event.hpp"
#include "hooking.hpp"
#include "services/players/player_service.hpp"

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
			g.reactions.report.process(g_player_service->get_by_id(sender->m_player_id));
			return true;
		}

		return false;
	}
}