#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::self_bulletproof()
	{
		if (g->self.bulletproof) {
			ENTITY::SET_ENTITY_HEALTH(self::ped, PED::GET_PED_MAX_HEALTH(self::ped), 0);
			PED::SET_PED_ARMOUR(self::ped, PLAYER::GET_PLAYER_MAX_ARMOUR(self::id));
		}
	}
}