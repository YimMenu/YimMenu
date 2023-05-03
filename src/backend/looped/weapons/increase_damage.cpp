#include "increase_damage.hpp"

#include "natives.hpp"

namespace big
{
	void increased_damage::on_tick()
	{
		if (g.weapons.increased_damage != 1)
		{
			Hash weapon{};

			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
			WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, g.weapons.increased_damage);
		}
	}

	void increased_damage::on_disable()
	{
		Hash weapon{};

		WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
		WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, 1);
	}
}
