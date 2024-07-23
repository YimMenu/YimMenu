#include "hooking/hooking.hpp"

#include <stats/CPlayerCardStats.hpp>

namespace big
{
	rage::netGameEvent* hooks::send_player_card_stats(rage::netGameEvent* a1, CPlayerCardStats* stats)
	{
		if (g.spoofing.spoof_rank)
			stats->m_rank = g.spoofing.rank;

		if (g.spoofing.spoof_kd_ratio)
			stats->m_kd_ratio = g.spoofing.kd_ratio;

		if (g.spoofing.spoof_bad_sport)
		{
			switch (g.spoofing.badsport_type)
			{
			case 0: stats->m_overall_badsport = 0.0f; break;
			case 1: stats->m_overall_badsport = 46.0f; break;
			case 2: stats->m_overall_badsport = 1000.0f; break;
			}
		}

		return g_hooking->get_original<hooks::send_player_card_stats>()(a1, stats);
	}
}