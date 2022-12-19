#include "backend/looped/looped.hpp"

namespace big
{
	static bool bLastSelfNoWaterCollsion = false;

	void looped::self_no_water_collision()
	{
		if (g_local_player == nullptr) return;

		bool bNoWaterCollsion = g.self.no_water_collision;

		if (bNoWaterCollsion)
		{
			g_local_player->m_navigation->m_damp->m_water_collision = 0;
			bLastSelfNoWaterCollsion = bNoWaterCollsion;
		}
		else if (bNoWaterCollsion != bLastSelfNoWaterCollsion)
		{
			g_local_player->m_navigation->m_damp->m_water_collision = 1;
			bLastSelfNoWaterCollsion = bNoWaterCollsion;
		}
	}
}