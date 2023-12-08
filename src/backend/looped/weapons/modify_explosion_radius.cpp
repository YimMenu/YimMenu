#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class modify_explosion_radius : looped_command
	{
		using looped_command::looped_command;

		Hash ped_weapon;

		virtual void on_tick() override
		{
			Hash weapon{};
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);

			if (weapon != ped_weapon)
			{
				WEAPON::SET_WEAPON_AOE_MODIFIER(weapon, 1);
				ped_weapon = weapon;
			}

			WEAPON::SET_WEAPON_AOE_MODIFIER(weapon, g.weapons.set_explosion_radius);
		}
		virtual void on_disable() override
		{
			Hash weapon{};
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
			WEAPON::SET_WEAPON_AOE_MODIFIER(weapon, 1);
		}
	};

	modify_explosion_radius g_modify_explosion_radius("modifyexplosionradius", "BACKEND_LOOPED_WEAPONS_MODIFY_EXPLOSION_RADIUS", "BACKEND_LOOPED_WEAPONS_MODIFY_EXPLOSION_RADIUS_DESC", g.weapons.modify_explosion_radius);
}
