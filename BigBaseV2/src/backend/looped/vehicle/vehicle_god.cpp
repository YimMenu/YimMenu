#include "backend/looped/looped.hpp"

namespace big
{
	void looped::vehicle_god_mode()
	{
		if (!g.vehicle.god_mode || g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			return;

		if (g_local_player->m_in_vehicle == 0x0)
		{
			g_local_player->m_vehicle->m_deform_god = 0x8C;
			g_local_player->m_vehicle->m_godmode = 0x1;
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;
			g_local_player->m_vehicle->m_godmode = 0x0;
		}
	}
}