#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool b_last_seatbelt = false;

	void looped::vehicle_seatbelt()
	{
		bool b_seatbelt = g->vehicle.seatbelt;

		if (b_seatbelt || (!b_seatbelt && b_seatbelt != b_last_seatbelt))
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 32, g->vehicle.seatbelt);

			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(self::ped, g->vehicle.seatbelt);

			b_last_seatbelt = g->vehicle.seatbelt;
		}
	}
}
