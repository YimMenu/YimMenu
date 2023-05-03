#include "infinite_mag.hpp"

#include "natives.hpp"

namespace big
{
	void infinite_mag::on_tick()
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, TRUE);
	}

	void infinite_mag::on_disable()
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(self::ped, FALSE);
	}
}
