#pragma once

namespace big
{
	enum class CustomWeapon
	{
		NONE,
		CAGE_GUN,
		DELETE_GUN,
		GRAVITY_GUN,
		STEAL_VEHICLE_GUN,
		REPAIR_GUN,
		VEHICLE_GUN
	};

	enum class RemoteEvent : int64_t
	{
		Bounty = -1906146218,
		CeoBan = 1355230914,
		CeoKick = -316948135,
		CeoMoney = 1152266822,
		ClearWantedLevel = 1187364773,
		FakeDeposit = 153488394,
		ForceMission = -1147284669,
		GtaBanner = 1659915470,
		PersonalVehicleDestroyed = 299217086,
		RemoteOffradar = -397188359,
		RotateCam = -1320260596,
		SendToCutscene = 1889984715,
		SendToIsland = -1479371259,
		SoundSpam = 1537221257,
		Spectate = -148441291,
		Teleport = 1249026189,
		TransactionError = -2041535807,
		VehicleKick = -1005623606
	};

	enum class SpeedoMeter
	{
		DISABLED,
		KMH,
		MPH
	};
}