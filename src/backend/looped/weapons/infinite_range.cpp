#include "infinite_range.hpp"

#include "natives.hpp"

namespace big
{
	void infinite_range::on_tick()
	{
		if (!g_local_player)
		{
			return;
		}

		if (g_local_player->m_weapon_manager)
		{
			if (p_modified_weapon != g_local_player->m_weapon_manager->m_weapon_info && g_local_player->m_weapon_manager->m_weapon_info)
			{
				if (p_modified_weapon)
					p_modified_weapon->m_weapon_range = og_range;

				og_range          = g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range;
				p_modified_weapon = g_local_player->m_weapon_manager->m_weapon_info;
				g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range = 1000.0f;
			}
		}
	}

	void infinite_range::on_disable()
	{
		if (g_local_player && p_modified_weapon)
		{
			p_modified_weapon->m_weapon_range = og_range;
			p_modified_weapon                 = nullptr;
		}
	}
}
