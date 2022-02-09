#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"
#include "util/notify.hpp"

namespace big
{
	void looped::weapons_infinite_mag()
	{
		if (g.weapons.infinite_mag) {
			auto const ped = PLAYER::PLAYER_PED_ID();
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, g.weapons.infinite_mag);
		}
	}
}