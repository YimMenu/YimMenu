#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{

	class infinite_range : looped_command
	{
		using looped_command::looped_command;

		CWeaponInfo* p_modified_weapon = nullptr;
		float og_range                 = 0.0f;

		virtual void on_tick() override
		{
			if (!g_local_player)
			{
				return;
			}

			if (g_local_player->m_weapon_manager)
			{
				if (p_modified_weapon != g_local_player->m_weapon_manager->m_weapon_info)
				{
					if (p_modified_weapon)
						p_modified_weapon->m_weapon_range = og_range;

					p_modified_weapon = g_local_player->m_weapon_manager->m_weapon_info;

					if (g_local_player->m_weapon_manager->m_weapon_info)
					{
						og_range = g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range;
						g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range = 1000.0f;
					}
				}
			}
		}

		virtual void on_disable() override
		{
			if (g_local_player && p_modified_weapon)
			{
				p_modified_weapon->m_weapon_range = og_range;
				p_modified_weapon                 = nullptr;
			}
		}
	};

	infinite_range g_infinite_range("infrange", "BACKEND_LOOPED_WEAPONS_INFINITE_RANGE", "BACKEND_LOOPED_WEAPONS_INFINITE_RANGE_DESC", g.weapons.infinite_range);
}