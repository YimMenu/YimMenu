#include "features.hpp"

namespace big
{
	void features::no_bike_fall()
	{
		bool bNoBikeFall = g_settings.options["no_bike_fall"].get<bool>();

		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), bNoBikeFall);
	}
}