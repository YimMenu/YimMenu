#include "block_homing.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void block_homing::on_tick()
	{
		if (g_local_player && g_local_player->m_vehicle)
			g_local_player->m_vehicle->m_is_targetable = false;
	}

	void block_homing::on_disable()
	{
		if (g_local_player && g_local_player->m_vehicle)
			g_local_player->m_vehicle->m_is_targetable = true;
	}
}
