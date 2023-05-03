#include "no_spread.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void no_spread::on_tick()
	{
		if (!g_local_player)
		{
			return;
		}

		auto* const weapon_mgr = g_local_player->m_weapon_manager;
		if (weapon_mgr)
		{
			if (p_modified_weapon != weapon_mgr->m_weapon_info && weapon_mgr->m_weapon_info)
			{
				if (p_modified_weapon)
					p_modified_weapon->m_accuracy_spread = og_spread_value;

				og_spread_value                              = weapon_mgr->m_weapon_info->m_accuracy_spread;
				p_modified_weapon                            = weapon_mgr->m_weapon_info;
				weapon_mgr->m_weapon_info->m_accuracy_spread = 0.0f;
			}
		}
	}

	void no_spread::on_disable()
	{
		if (g_local_player && p_modified_weapon)
		{
			p_modified_weapon->m_accuracy_spread = og_spread_value;
			p_modified_weapon                    = nullptr;
		}
	}
}
