#include "seatbelt.hpp"

#include "natives.hpp"

namespace big
{
	void seatbelt::on_tick()
	{
		PED::SET_PED_CONFIG_FLAG(self::ped, 32, true);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, true);
	}

	void seatbelt::on_disable()
	{
		PED::SET_PED_CONFIG_FLAG(self::ped, 32, false);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, false);
	}
}
