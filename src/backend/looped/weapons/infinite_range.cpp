#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{

	class infinite_range : looped_command
	{
		using looped_command::looped_command;

		float blast = g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range && !bchanged;
		bool bchanged;

		virtual void on_tick() override
		{
			if (g_local_player)
			{
				bchanged = true;
				g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range = 99999999.0f;
			}
		}
		virtual void on_disable() override
		{
			if (g_local_player)
			{
				g_local_player->m_weapon_manager->m_weapon_info->m_weapon_range = blast;
				bchanged = false;
			}
		}
	};

	infinite_range g_infinite_range("infrange", "Infinite Range", "Kill anything at any distance.", g.weapons.infinite_range);
}
