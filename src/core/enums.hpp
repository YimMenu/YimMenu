#pragma once

namespace big
{
	enum class eBoostBehaviors
	{
		DEFAULT,
		INSTANT_REFIL,
		INFINITE_BOOST
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(eBoostBehaviors, {
		{ eBoostBehaviors::DEFAULT, "default" },
		{ eBoostBehaviors::INSTANT_REFIL, "instant" },
		{ eBoostBehaviors::INFINITE_BOOST, "infinite" }
	})

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
	NLOHMANN_JSON_SERIALIZE_ENUM(CustomWeapon, {
		{ CustomWeapon::NONE, "none" },
		{ CustomWeapon::CAGE_GUN, "cage" },
		{ CustomWeapon::DELETE_GUN, "delete" },
		{ CustomWeapon::GRAVITY_GUN, "gravity" },
		{ CustomWeapon::STEAL_VEHICLE_GUN, "steal" },
		{ CustomWeapon::REPAIR_GUN, "repair" },
		{ CustomWeapon::VEHICLE_GUN, "vehicle" },
	})

	enum class ContextEntityType : uint8_t
	{
		NONE = 0,
		PED = 1 << 0,
		PLAYER = 1 << 1,
		VEHICLE = 1 << 2,
		OBJECT = 1 << 3,
		SHARED = 1 << 4
	};

	enum class eEntityType
	{
		UNK_0,
		UNK_1,
		UNK_2,
		UNK_3,
		UNK_4,
		VEHICLE,
		PED,
	};

	enum class eTransitionState
	{
		TRANSITION_STATE_EMPTY,
		TRANSITION_STATE_SP_SWOOP_UP,
		TRANSITION_STATE_MP_SWOOP_UP,
		TRANSITION_STATE_CREATOR_SWOOP_UP,
		TRANSITION_STATE_PRE_HUD_CHECKS,
		TRANSITION_STATE_WAIT_HUD_EXIT,
		TRANSITION_STATE_WAIT_FOR_SUMMON,
		TRANSITION_STATE_SP_SWOOP_DOWN,
		TRANSITION_STATE_MP_SWOOP_DOWN,
		TRANSITION_STATE_CANCEL_JOINING,
		TRANSITION_STATE_RETRY_LOADING,
		TRANSITION_STATE_RETRY_LOADING_SLOT_1,
		TRANSITION_STATE_RETRY_LOADING_SLOT_2,
		TRANSITION_STATE_RETRY_LOADING_SLOT_3,
		TRANSITION_STATE_RETRY_LOADING_SLOT_4,
		TRANSITION_STATE_WAIT_ON_INVITE,
		TRANSITION_STATE_PREJOINING_FM_SESSION_CHECKS,
		TRANSITION_STATE_LOOK_FOR_FRESH_JOIN_FM,
		TRANSITION_STATE_LOOK_TO_JOIN_ANOTHER_SESSION_FM,
		TRANSITION_STATE_CONFIRM_FM_SESSION_JOINING,
		TRANSITION_STATE_WAIT_JOIN_FM_SESSION,
		TRANSITION_STATE_CREATION_ENTER_SESSION,
		TRANSITION_STATE_PRE_FM_LAUNCH_SCRIPT,
		TRANSITION_STATE_FM_TEAMFULL_CHECK,
		TRANSITION_STATE_START_FM_LAUNCH_SCRIPT,
		TRANSITION_STATE_FM_TRANSITION_CREATE_PLAYER,
		TRANSITION_STATE_IS_FM_AND_TRANSITION_READY,
		TRANSITION_STATE_FM_SWOOP_DOWN,
		TRANSITION_STATE_POST_BINK_VIDEO_WARP,
		TRANSITION_STATE_FM_FINAL_SETUP_PLAYER,
		TRANSITION_STATE_MOVE_FM_TO_RUNNING_STATE,
		TRANSITION_STATE_FM_HOW_TO_TERMINATE,
		TRANSITION_STATE_START_CREATOR_PRE_LAUNCH_SCRIPT_CHECK,
		TRANSITION_STATE_START_CREATOR_LAUNCH_SCRIPT,
		TRANSITION_STATE_CREATOR_TRANSITION_CREATE_PLAYER,
		TRANSITION_STATE_IS_CREATOR_AND_TRANSITION_READY,
		TRANSITION_STATE_CREATOR_SWOOP_DOWN,
		TRANSITION_STATE_CREATOR_FINAL_SETUP_PLAYER,
		TRANSITION_STATE_MOVE_CREATOR_TO_RUNNING_STATE,
		TRANSITION_STATE_PREJOINING_TESTBED_SESSION_CHECKS,
		TRANSITION_STATE_LOOK_FOR_FRESH_JOIN_TESTBED,
		TRANSITION_STATE_LOOK_FOR_FRESH_HOST_TESTBED,
		TRANSITION_STATE_LOOK_TO_JOIN_ANOTHER_SESSION_TESTBED,
		TRANSITION_STATE_LOOK_TO_HOST_SESSION_TESTBED,
		TRANSITION_STATE_CONFIRM_TESTBED_SESSION_JOINING,
		TRANSITION_STATE_WAIT_JOIN_TESTBED_SESSION,
		TRANSITION_STATE_START_TESTBED_LAUNCH_SCRIPT,
		TRANSITION_STATE_TESTBED_TRANSITION_CREATE_PLAYER,
		TRANSITION_STATE_IS_TESTBED_AND_TRANSITION_READY,
		TRANSITION_STATE_TESTBED_SWOOP_DOWN,
		TRANSITION_STATE_TESTBED_FINAL_SETUP_PLAYER,
		TRANSITION_STATE_MOVE_TESTBED_TO_RUNNING_STATE,
		TRANSITION_STATE_TESTBED_HOW_TO_TERMINATE,
		TRANSITION_STATE_QUIT_CURRENT_SESSION_PROMPT,
		TRANSITION_STATE_WAIT_FOR_TRANSITION_SESSION_TO_SETUP,
		TRANSITION_STATE_TERMINATE_SP,
		TRANSITION_STATE_WAIT_TERMINATE_SP,
		TRANSITION_STATE_KICK_TERMINATE_SESSION,
		TRANSITION_STATE_TERMINATE_SESSION,
		TRANSITION_STATE_WAIT_TERMINATE_SESSION,
		TRANSITION_STATE_TERMINATE_SESSION_AND_HOLD,
		TRANSITION_STATE_TERMINATE_SESSION_AND_MOVE_INTO_HOLDING_STATE,
		TRANSITION_STATE_TEAM_SWAPPING_CHECKS,
		TRANSITION_STATE_RETURN_TO_SINGLEPLAYER,
		TRANSITION_STATE_WAIT_FOR_SINGLEPLAYER_TO_START,
		TRANSITION_STATE_WAITING_FOR_EXTERNAL_TERMINATION_CALL,
		TRANSITION_STATE_TERMINATE_MAINTRANSITION,
		TRANSITION_STATE_WAIT_FOR_DIRTY_LOAD_CONFIRM,
		TRANSITION_STATE_DLC_INTRO_BINK,
		TRANSITION_STATE_SPAWN_INTO_PERSONAL_VEHICLE
	};

	enum eVehicleFlags
	{
		TRIGGER_SPAWN_TOGGLE = 1 << 0,
		DESTROYED = 1 << 1,
		HAS_INSURANCE = 1 << 2,
		UNK0 = 1 << 3,
		IMPOUNDED = 1 << 6,
		UNK1 = 1 << 10,
		SPAWN_AT_MORS_MUTUAL = 1 << 11,
		UNK2 = 1 << 16
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
		Bounty = 1370461707, // (137, "FM_TXT_BNTY0", iVar1, PLAYER::GET_PLAYER_NAME(Var2.f_1), "", 5000, Var2.f_6);
		CeoBan = 316066012, // mpply_vipgameplaydisabledtimer
		CeoKick = -1831959078, // BGDISMISSED
		CeoMoney = 245065909, // Goon_Paid_Large
		ClearWantedLevel = 2080651008,
		ForceMission = 1858712297, // ), Var0.f_2, 1))
		ForceMission2 = -1578682814, // TICK_PH_INVA
		GiveCollectible = 697566862, // DLC_SUM20_HIDDEN_COLLECTIBLES xref
		GtaBanner = -795380017, // NETWORK::NETWORK_IS_SCRIPT_ACTIVE("BUSINESS_BATTLES", -1, true, 0) second one
		NetworkBail = 915462795, // NETWORK::NETWORK_BAIL(16, 0, 0); xref func
		PersonalVehicleDestroyed = -964882004, // PLYVEH_INS_DES1
		RemoteOffradar = -162943635, // NETWORK::GET_TIME_DIFFERENCE(NETWORK::GET_NETWORK_TIME(), Var0.f_2)
		SendToCutscene = 392606458, // (bVar3, bVar4, 125f, 1)
		SendToCayoPerico = -910497748, // CELL_HI_INV
		SendToLocation = 1214823473, // &Var222, 11);
		SoundSpam = -1891171016, // CELL_APTINVYACHT
		Spectate = -1903870031, // SPEC_TCK1
		Teleport = -168599209, // Mission_Pass_Notify
		TeleportToWarehouse = 434937615, // .f_4 == 50
		TransactionError = -768108950, // NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH
		VehicleKick = -852914485, // PIM_RFMOC
		MCTeleport = 879177392, // NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()) == (first one)
		StartActivity = 243072129, // (Var0.f_2, -1); first match
		MarkPlayerAsBeast = -2001677186, // GB_BOSSBST xref == PLAYER... global (sadly doesn't actually turn people into the beast)
		KickFromInterior = 1454834612, // ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), PED::GET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), false)
		InteriorControl = 1268038438, // eventData.f_3 != _INVALID_PLAYER_INDEX_0()

		Crash = -904555865, // SET_NO_LOADING_SCREEN, xref it
		Crash2 = 1775863255,

		TSECommand = 113023613, // CnCTG_IN_BF
		TSECommandRotateCam = 0x69979fea /*joaat("pats_horse_right") in script*/, // != 29) && f

		Notification = 548471420,
		NotificationMoneyBanked = -1032040118, // TICK_TC_BANK
		NotificationMoneyRemoved = -1197151915, // TICK_TC_REMO
		NotificationMoneyStolen = -28878294, // TICK_TC_STOL
	};

	enum class eCollectibleType
	{
		MovieProp = 0,
		CacheShard = 1,
		ChestShard = 2,
		RadioTowerShard = 3,
		AudioPlayerShard = 4,
		ShipwreckShard = 5,
		BuriedStashShard = 6,
		Treat = 8,
		Organics = 9,
		Skydive = 10
	};

	enum class eActivityType
	{
		HeistPrep = 233,
		Gunrunning = 180,
		Sightseer = 142,
		HeadHunter = 166,
		BuySpecialCargo = 167,
		SellSpecialCargo = 168,
		DefendSpecialCargo = 169,
		StealVehicle = 178,
		ExportVehicle = 188,
		Gunrunning2 = 225,
		GunrunningSell = 226,
		GunrunningDefend = 227,
		BikerSell = 190,
		BikerDefend = 191,
		BusinessResupply = 192,
		Survival = 3,
		Darts = 14,
		ArmWresling = 15,
		GangAttack = 6,
		PilotSchool = 122,
		Golf = 11,
		ShootingRange = 13,
		Tennis = 12,
		BaseJump = 8,
		Deathmatch = 1,
		ImpromptuDeathmatch = 5,
		Mission = 0,
		Race = 2,
		ExecutiveDeathmatch = 148,
		MarkedForDeath = 151,
		PiracyPrevention = 152,
		MostWanted = 153,
		AssetRecovery = 157,
		HostileTakeover = 159,
		Point2Point = 162,
		AmphibiousAssault = 216,
		Velocity = 219,
		GunsForHire = 185,
		ByThePound = 182,
		RippingItUp = 194,
		RaceToPoint = 189,
		HitAndRide = 193,
		CriminalMischief = 205,
		WeaponOfChoice = 186,
		FragileGoods = 207,
		Torched = 208,
		Outrider = 209,
		WheelieRider = 210,
		POW = 183,
		ExecutiveSearch = 199,
		StandYourGround = 201,
		AutoBuyout = 163,
		DueDiligence = 160,
		MarketManipulation = 154,
		CourierService = 155,
		Skydive = 267
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
		SC_TV,
		LEAVE_ONLINE = -1
	};

	enum class SpeedUnit
	{
		KMPH,
		MIPH,
		MPS
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(SpeedUnit, {
		{ SpeedUnit::KMPH, "kmph" },
		{ SpeedUnit::MIPH, "miph" },
		{ SpeedUnit::MPS, "mps" },
	})

	enum class RainbowPaintType
	{
		Off,
		Fade,
		Spasm
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(RainbowPaintType, {
		{ RainbowPaintType::Off, "off" },
		{ RainbowPaintType::Fade, "fade" },
		{ RainbowPaintType::Spasm, "spasm" },
	})

	enum class AutoDriveDestination
	{
		STOPPED,
		OBJECTITVE,
		WAYPOINT,
		WANDER,
		EMERGENCY_STOP
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(AutoDriveDestination, {
		{ AutoDriveDestination::STOPPED, "stopped" },
		{ AutoDriveDestination::OBJECTITVE, "objective" },
		{ AutoDriveDestination::WAYPOINT, "waypoint" },
		{ AutoDriveDestination::WANDER, "wander" },
		{ AutoDriveDestination::EMERGENCY_STOP, "emergency_stop" },
	})

	enum class AutoDriveStyle
	{
		LAW_ABIDING,
		THE_ROAD_IS_YOURS
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(AutoDriveStyle, {
		{ AutoDriveStyle::LAW_ABIDING, "law_abiding" },
		{ AutoDriveStyle::THE_ROAD_IS_YOURS, "the_road_is_yours" },
	})

	enum class eEntityProofs : uint32_t
	{
		BULLET     = 1 << 4,
		FIRE       = 1 << 5,
		COLLISION  = 1 << 6,
		MELEE      = 1 << 7,
		GOD        = 1 << 8,
		EXPLOSION  = 1 << 11,
		STEAM      = 1 << 15,
		DROWN      = 1 << 16,
		WATER      = 1 << 24,
	};
	enum ePedType : uint32_t
	{
		PED_TYPE_PLAYER_0,
		PED_TYPE_PLAYER_1,
		PED_TYPE_NETWORK_PLAYER,
		PED_TYPE_PLAYER_2,
		PED_TYPE_CIVMALE,
		PED_TYPE_CIVFEMALE,
		PED_TYPE_COP,
		PED_TYPE_GANG_ALBANIAN,
		PED_TYPE_GANG_BIKER_1,
		PED_TYPE_GANG_BIKER_2,
		PED_TYPE_GANG_ITALIAN,
		PED_TYPE_GANG_RUSSIAN,
		PED_TYPE_GANG_RUSSIAN_2,
		PED_TYPE_GANG_IRISH,
		PED_TYPE_GANG_JAMAICAN,
		PED_TYPE_GANG_AFRICAN_AMERICAN,
		PED_TYPE_GANG_KOREAN,
		PED_TYPE_GANG_CHINESE_JAPANESE,
		PED_TYPE_GANG_PUERTO_RICAN,
		PED_TYPE_DEALER,
		PED_TYPE_MEDIC,
		PED_TYPE_FIREMAN,
		PED_TYPE_CRIMINAL,
		PED_TYPE_BUM,
		PED_TYPE_PROSTITUTE,
		PED_TYPE_SPECIAL,
		PED_TYPE_MISSION,
		PED_TYPE_SWAT,
		PED_TYPE_ANIMAL,
		PED_TYPE_ARMY
	};

	enum class HudComponents {
		WANTED_STARS = 1,
		WEAPON_ICON,
		CASH,
		MP_CASH,
		MP_MESSAGE,
		VEHICLE_NAME,
		AREA_NAME,
		VEHICLE_CLASS,
		STREET_NAME,
		HELP_TEXT,
		FLOATING_HELP_TEXT_1,
		FLOATING_HELP_TEXT_2,
		CASH_CHANGE,
		RETICLE,
		SUBTITLE_TEXT,
		RADIO_STATIONS,
		SAVING_GAME,
		GAME_STREAM,
		WEAPON_WHEEL,
		WEAPON_WHEEL_STATS,
		HUD_COMPONENTS,
		HUD_WEAPONS
	};

	enum class CommandAccessLevel
	{
		NONE,
		FRIENDLY, // heal, semi godmode...
		AGGRESSIVE, // kick from vehicle, send to apartment...
		TOXIC, // kicks
		ADMIN // full access
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(CommandAccessLevel, {
		{ CommandAccessLevel::NONE, "none" },
		{ CommandAccessLevel::FRIENDLY, "friendly" },
		{ CommandAccessLevel::AGGRESSIVE, "aggressive" },
		{ CommandAccessLevel::TOXIC, "toxic" },
		{ CommandAccessLevel::ADMIN, "admin" }
	})
}
