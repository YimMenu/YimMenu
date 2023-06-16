#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{

	class increased_damage : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g.weapons.increased_damage != 1)
			{
				Hash weapon{};
				WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
				WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, g.weapons.increased_damage);
			}
		}
	};

	increased_damage
	    g_increased_damage("incrdamage", "Damage Override", "Sets your damage to whatever you want", g.weapons.increase_damage);
}
