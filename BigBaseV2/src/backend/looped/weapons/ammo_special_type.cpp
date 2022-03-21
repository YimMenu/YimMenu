#include "backend/looped/looped.hpp"

namespace big
{
	static bool bLastState = false;
	void looped::weapons_ammo_special_type()
	{
		if (g_local_player == nullptr ||
			g_local_player->m_weapon_manager == nullptr ||
			g_local_player->m_weapon_manager->m_weapon_info == nullptr ||
			g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info == nullptr)
			return;

		if (g->weapons.ammo_special.toggle)
			g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info->m_ammo_special_type = g->weapons.ammo_special.type;
		else if (bLastState)
			g_local_player->m_weapon_manager->m_weapon_info->m_ammo_info->m_ammo_special_type = eAmmoSpecialType::None;

		bLastState = g->weapons.ammo_special.toggle;
	}
}