#include "backend/looped/looped.hpp"

namespace big
{
	static bool bLastSeatBelt = false;

	void looped::self_seat_belt()
	{
		if (g_local_player == nullptr) return;

		bool bSeatBelt = g->self.seat_belt;

		if (bSeatBelt)
		{
			g_local_player->m_seatbelt = 201;
			bLastSeatBelt = bSeatBelt;
		}
		else if (bSeatBelt != bLastSeatBelt)
		{
			g_local_player->m_seatbelt = 200;
			bLastSeatBelt = bSeatBelt;
		}
	}
}
