#include "hooking.hpp"
#include "network/Network.hpp"

namespace big
{
	bool hooks::send_session_matchmaking_attributes(void* a1, rage::rlSessionInfo* info, std::uint64_t session_id, bool use_session_id, MatchmakingAttributes* attributes)
	{
		if (g.spoofing.spoof_session_region_type)
			attributes->m_param_values[4] = g.spoofing.session_region_type;

		if (g.spoofing.spoof_session_language)
			attributes->m_param_values[3] = g.spoofing.session_language;

		if (g.spoofing.spoof_session_player_count)
			attributes->m_param_values[7] = g.spoofing.session_player_count;

		if (g.spoofing.spoof_session_bad_sport_status)
		{
			if (g.spoofing.session_bad_sport)
				attributes->m_param_values[0] |= (1 << 14);
			else
				attributes->m_param_values[0] &= ~(1 << 14);
		}

		return g_hooking->get_original<hooks::send_session_matchmaking_attributes>()(a1, info, session_id, use_session_id, attributes);
	}
}