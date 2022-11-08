#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::system_self_globals()
	{
		self::id = PLAYER::PLAYER_ID();

		self::ped = PLAYER::PLAYER_PED_ID();

		self::pos = ENTITY::GET_ENTITY_COORDS(self::ped, false /*Unused*/);

		if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, 0))
		{
			self::veh = PED::GET_VEHICLE_PED_IS_IN(self::ped, false);
		}
		else
		{
			self::veh = 0;
		}
	}
}
