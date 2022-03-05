#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_increased_damage()
	{
		auto const player_ped = PLAYER::PLAYER_PED_ID();

		if (g->weapons.increased_damage != 1) {
			Hash weapon{}; 
			WEAPON::GET_CURRENT_PED_WEAPON(player_ped, &weapon, 0);
			WEAPON::SET_WEAPON_DAMAGE_MODIFIER_THIS_FRAME_(weapon, g->weapons.increased_damage);
		}
	}
}