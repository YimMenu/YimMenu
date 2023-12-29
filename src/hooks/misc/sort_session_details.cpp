#include "hooking/hooking.hpp"

#include <network/Network.hpp>

namespace big
{
	// true => e1 > e2
	// false => e1 < e2
	bool hooks::sort_session_details(SessionSortEntry* e1, SessionSortEntry* e2)
	{
		if (g.session.player_magnet_enabled)
		{
			return std::abs((int)e1->m_session_detail->m_player_count - g.session.player_magnet_count)
			    < std::abs((int)e2->m_session_detail->m_player_count - g.session.player_magnet_count);
		}
		else
		{
			return g_hooking->get_original<hooks::sort_session_details>()(e1, e2);
		}
	}
}