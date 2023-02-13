#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{

	class increased_damage : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_damage = 0.0f;

		virtual void on_tick() override
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
						p_modified_weapon->m_damage = og_damage;

					og_damage = g_local_player->m_weapon_manager->m_weapon_info->m_damage;
					p_modified_weapon = g_local_player->m_weapon_manager->m_weapon_info;
					g_local_player->m_weapon_manager->m_weapon_info->m_damage = 0.0f;
				}
			}
		}
		virtual void on_disable() override
		{
			if (g_local_player && p_modified_weapon)
			{
				p_modified_weapon->m_damage = og_damage;
				p_modified_weapon = nullptr;
			}
		}
	};

	increased_damage g_increased_damage("incrdamage", "Damage Override", "Sets your damage to whatever you want", g.weapons.increase_damage);
}
