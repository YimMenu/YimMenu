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

    enum class ePedTask
    {
        TASK_NONE,
        TASK_FOOT = 1 << 4,
        TASK_UNK = 1 << 5,
        TASK_DRIVING = 1 << 6
    };

	enum class eRemoteEvent
	{
		Bounty = 1294995624,
		CeoBan = -764524031,
		CeoKick = 248967238,
		CeoMoney = 1890277845,
		ClearWantedLevel = -91354030,
		FakeDeposit = 677240627,
		ForceMission = 2020588206,
		GtaBanner = 1572255940,
		PersonalVehicleDestroyed = 802133775,
		RemoteOffradar = -391633760,
		RotateCam = 801199324,
		SendToCutscene = 1068259786,
		SendToIsland = -621279188,
		SoundSpam = 1132878564,
		Spectate = -1113591308,
		Teleport = 603406648,
		TransactionError = -1704141512,
		VehicleKick = 578856274
	};

	enum class eSessionType
	{
		JOIN_PUBLIC,
		NEW_PUBLIC,
		CLOSED_CREW,
		CREW,
		CLOSED_FRIENDS = 6,
		FIND_FRIEND = 9,
		SOLO,
		INVITE_ONLY,
		JOIN_CREW,
		LEAVE_ONLINE = -1
	};

	enum class SpeedoMeter
	{
		DISABLED,
		KMH,
		MPH
	};
}