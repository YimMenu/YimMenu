#include "infinite_ammo.hpp"

#include "natives.hpp"

namespace big
{
	void infinite_ammo::on_tick()
	{
		WEAPON::SET_PED_INFINITE_AMMO(self::ped, TRUE, NULL);
	}

	void infinite_ammo::on_disable()
	{
		WEAPON::SET_PED_INFINITE_AMMO(self::ped, FALSE, NULL);
	}
}
