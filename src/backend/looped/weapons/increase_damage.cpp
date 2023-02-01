#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{

	class increased_damage : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			g_local_player->m_weapon_manager->m_weapon_info->m_damage = g.weapons.increased_damage;
		}
		virtual void on_disable() override
		{
			g_local_player->m_weapon_manager->m_weapon_info->m_damage = 100.0f;
		}
	};

	increased_damage g_increased_damage("incrdamage", "Damage Override", "Sets your damage to whatever you want", g.weapons.increase_damage);
}
