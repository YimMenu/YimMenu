#include "hooking.hpp"
#include "network/Network.hpp"

#include <stats/CPlayerCardStats.hpp>

namespace big
{
	rage::netGameEvent* hooks::send_player_card_stats(rage::netGameEvent* a1, CPlayerCardStats* stats)
	{
		return g_hooking->get_original<hooks::send_player_card_stats>()(a1, stats);
	}
}