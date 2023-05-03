#include "unlimited_oxygen.hpp"

#include "natives.hpp"

#include <ped/CPedIntelligence.hpp>

namespace big
{
	void unlimited_oxygen::on_tick()
	{
		if (g_local_player)
			g_local_player->m_ped_intelligence->m_oxygen_time = 0;
	}
}
