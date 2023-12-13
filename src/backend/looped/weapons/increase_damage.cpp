#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class increased_damage : looped_command
	{
		using looped_command::looped_command;

		Hash ped_weapon;

		virtual void on_tick() override
		{
			if (g.weapons.increased_damage != 1)
			{
				Hash weapon{};
				WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);

				if (weapon != ped_weapon)
				{
					WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, 1);
					ped_weapon = weapon;
				}

				WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, g.weapons.increased_damage);
			}
		}
		virtual void on_disable() override
		{
			Hash weapon{};
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
			WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, 1);
		}
	};

	increased_damage
	    g_increased_damage("incrdamage", "BACKEND_LOOPED_WEAPONS_INCREASE_DAMAGE", "BACKEND_LOOPED_WEAPONS_INCREASE_DAMAGE_DESC", g.weapons.increase_damage);
}
