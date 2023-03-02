#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_increased_damage()
	{
		if (g.weapons.increased_damage != 1)
		{
			Hash weapon{};
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
			WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, g.weapons.increased_damage);
		}
	}
}