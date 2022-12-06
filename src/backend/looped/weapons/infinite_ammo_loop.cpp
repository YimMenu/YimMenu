#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_infinite_ammo_loop()
	{
		if (g->weapons.infinite_ammo_loop)
		{
            if (
		    	g_local_player == nullptr ||
		    	g_local_player->m_weapon_manager == nullptr ||
		    	g_local_player->m_weapon_manager->m_weapon_info == nullptr ||
		    	g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info == nullptr
		    ) 
            {
                return;
            }

			Hash current_weapon = g_local_player->m_weapon_manager->m_selected_weapon_hash;
            int max_ammo = g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info->m_ammo_max_100;

            WEAPON::SET_PED_AMMO(self::ped, current_weapon, max_ammo, false);
		}
	}
}