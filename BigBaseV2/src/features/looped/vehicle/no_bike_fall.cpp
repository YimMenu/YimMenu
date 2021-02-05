#include "features/vehicle.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastNoBikeFall = false;

	void vehicle::no_bike_fall()
	{
		bool bNoBikeFall = g_settings.options["no_bike_fall"].get<bool>();

		if (bNoBikeFall || bLastNoBikeFall != bNoBikeFall)
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), bNoBikeFall);

		bLastNoBikeFall = bNoBikeFall;
	}
}