#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_infinite_mag()
	{
		if (g->weapons.infinite_mag) {
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), g->weapons.infinite_mag);
		}
	}
}