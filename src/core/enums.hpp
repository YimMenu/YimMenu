#pragma once

namespace big
{
	enum class eBoostBehaviors
	{
		DEFAULT,
		INSTANT_REFIL,
		INFINITE_BOOST,
		HOLD_FOR_INFINITE
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(eBoostBehaviors, {{eBoostBehaviors::DEFAULT, "default"}, {eBoostBehaviors::INSTANT_REFIL, "instant"}, {eBoostBehaviors::INFINITE_BOOST, "infinite"}, {eBoostBehaviors::HOLD_FOR_INFINITE, "hold"}})

	enum class CustomWeapon
	{
		NONE,
		CAGE_GUN,
		DELETE_GUN,
		GRAVITY_GUN,
		STEAL_VEHICLE_GUN,
		REPAIR_GUN,
		VEHICLE_GUN,
		TP_GUN,
		PAINT_GUN
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(CustomWeapon,
	    {
	        {CustomWeapon::NONE, "none"},
	        {CustomWeapon::CAGE_GUN, "cage"},
	        {CustomWeapon::DELETE_GUN, "delete"},
	        {CustomWeapon::GRAVITY_GUN, "gravity"},
	        {CustomWeapon::STEAL_VEHICLE_GUN, "steal"},
	        {CustomWeapon::REPAIR_GUN, "repair"},
	        {CustomWeapon::VEHICLE_GUN, "vehicle"},
	        {CustomWeapon::TP_GUN, "tp"},
	        {CustomWeapon::PAINT_GUN, "paint"},
	    })

	enum class ContextEntityType : uint8_t
	{
		NONE    = 0,
		PED     = 1 << 0,
		PLAYER  = 1 << 1,
		VEHICLE = 1 << 2,
		OBJECT  = 1 << 3,
		SHARED  = 1 << 4
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
		DESTROYED            = 1 << 1,
		HAS_INSURANCE        = 1 << 2,
		UNK0                 = 1 << 3,
		IMPOUNDED            = 1 << 6,
		UNK1                 = 1 << 10,
		SPAWN_AT_MORS_MUTUAL = 1 << 11,
		UNK2                 = 1 << 16
	};

	enum class ePedTask
	{
		TASK_NONE,
		TASK_FOOT    = 1 << 4,
		TASK_UNK     = 1 << 5,
		TASK_DRIVING = 1 << 6
	};

	enum class eRemoteEvent
	{
		Bounty   = 1517551547, // (137, "FM_TXT_BNTY0", iVar1, PLAYER::GET_PLAYER_NAME(Var2.f_1), "", 5000, Var2.f_6);
		CeoBan   = 1531565154, // mpply_vipgameplaydisabledtimer
		CeoKick  = -11681548,
		CeoMoney = -337848027, // Goon_Paid_Large
		ClearWantedLevel = -1704545346,
		ForceMission     = 259469385,  // ), Var0.f_2, 1))
		GiveCollectible  = 968269233,  // DLC_SUM20_HIDDEN_COLLECTIBLES xref
		GtaBanner        = -330501227, // NETWORK::NETWORK_IS_SCRIPT_ACTIVE("BUSINESS_BATTLES", -1, true, 0) second one
		NetworkBail      = -901348601, // NETWORK::NETWORK_BAIL(16, 0, 0); xref func
		PersonalVehicleDestroyed = 1655503526,  // PLYVEH_INS_DES1
		RemoteOffradar           = 57493695,    // NETWORK::GET_TIME_DIFFERENCE(NETWORK::GET_NETWORK_TIME(), Var0.f_2)
		SendToCutscene           = -1951335381, // (bVar3, bVar4, 125f, 1)
		SendToCayoPerico         = 373376135,   // CELL_HI_INV
		SendToLocation           = 1669592503,  // &Var222, 11);
		SoundSpam                = 996099702,   // CELL_APTINVYACHT
		Spectate                 = 1840946429,  // SPEC_TCK1
		Teleport                 = -1321657966, // Mission_Pass_Notify
		TeleportToWarehouse      = -1253241415, // .f_4 == 50
		TransactionError         = -830063381,  // NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH
		VehicleKick              = -503325966,  // PIM_RFMOC
		MCTeleport    = 1103127469, // NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()) == (first one)
		StartActivity = 1450115979, // (Var0.f_2, -1); first match
		MarkPlayerAsBeast = 1649541577, // GB_BOSSBST xref == PLAYER... global (sadly doesn't actually turn people into the beast)
		KickFromInterior = -1496371358, // ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), PED::GET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), false)
		InteriorControl  = -1638522928, // eventData.f_3 != _INVALID_PLAYER_INDEX_0()
		SendTextLabelSMS = -1773335296,

		Crash  = -1604421397, // SET_NO_LOADING_SCREEN, xref it
		Crash2 = -375628860,
		Crash3 = 323285304,

		TSECommand          = 800157557, // CnCTG_IN_BF
		TSECommandRotateCam = 225624744, // != 29) && f
		TSECommandSound     = 385726943,

		Notification             = -642704387,
		NotificationMoneyBanked  = 94410750,   // TICK_TC_BANK
		NotificationMoneyRemoved = -242911964, // TICK_TC_REMO
		NotificationMoneyStolen  = -295926414, // TICK_TC_STOL
		NotificationCrash1       = -994541138, // AMCH_ATTEMPT2
		NotificationCrash2       = 782258655,  // GBSAL_COLL

		DestroyPersonalVehicle = 109434679, // CnC_PV_THEFT
		TriggerCEORaid         = -1906536929,

		StartScriptBegin   = -366707054,
		StartScriptProceed = 1757622014
	};

	enum class eCollectibleType
	{
		MovieProp        = 0,
		CacheShard       = 1,
		ChestShard       = 2,
		RadioTowerShard  = 3,
		AudioPlayerShard = 4,
		ShipwreckShard   = 5,
		BuriedStashShard = 6,
		Treat            = 8,
		Organics         = 9,
		Skydive          = 10
	};

	enum class eSessionType
	{
		JOIN_PUBLIC,
		NEW_PUBLIC,
		CLOSED_CREW,
		CREW,
		CLOSED_FRIENDS = 6,
		FIND_FRIEND    = 9,
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
	NLOHMANN_JSON_SERIALIZE_ENUM(SpeedUnit,
	    {
	        {SpeedUnit::KMPH, "kmph"},
	        {SpeedUnit::MIPH, "mph"},
	        {SpeedUnit::MPS, "mps"},
	    })

	enum class RainbowPaintType
	{
		Off,
		Fade,
		Spasm
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(RainbowPaintType,
	    {
	        {RainbowPaintType::Off, "off"},
	        {RainbowPaintType::Fade, "fade"},
	        {RainbowPaintType::Spasm, "spasm"},
	    })

	enum class AutoDriveDestination
	{
		STOPPED,
		OBJECTITVE,
		WAYPOINT,
		WANDER,
		EMERGENCY_STOP
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(AutoDriveDestination,
	    {
	        {AutoDriveDestination::STOPPED, "stopped"},
	        {AutoDriveDestination::OBJECTITVE, "objective"},
	        {AutoDriveDestination::WAYPOINT, "waypoint"},
	        {AutoDriveDestination::WANDER, "wander"},
	        {AutoDriveDestination::EMERGENCY_STOP, "emergency_stop"},
	    })

	enum class AutoDriveStyle
	{
		LAW_ABIDING,
		THE_ROAD_IS_YOURS
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(AutoDriveStyle,
	    {
	        {AutoDriveStyle::LAW_ABIDING, "law_abiding"},
	        {AutoDriveStyle::THE_ROAD_IS_YOURS, "the_road_is_yours"},
	    })

	enum class eEntityProofs : uint32_t
	{
		BULLET    = 1 << 4,
		FIRE      = 1 << 5,
		COLLISION = 1 << 6,
		MELEE     = 1 << 7,
		GOD       = 1 << 8,
		EXPLOSION = 1 << 11,
		STEAM     = 1 << 15,
		WATER     = 1 << 16,
	};

	enum class ePedTypeFlag : int64_t
	{
		PED_TYPE_PLAYER_0              = 1 << 0,
		PED_TYPE_PLAYER_1              = 1 << 1,
		PED_TYPE_NETWORK_PLAYER        = 1 << 2,
		PED_TYPE_PLAYER_2              = 1 << 3,
		PED_TYPE_CIVMALE               = 1 << 4,
		PED_TYPE_CIVFEMALE             = 1 << 5,
		PED_TYPE_COP                   = 1 << 6,
		PED_TYPE_GANG_ALBANIAN         = 1 << 7,
		PED_TYPE_GANG_BIKER_1          = 1 << 8,
		PED_TYPE_GANG_BIKER_2          = 1 << 9,
		PED_TYPE_GANG_ITALIAN          = 1 << 10,
		PED_TYPE_GANG_RUSSIAN          = 1 << 11,
		PED_TYPE_GANG_RUSSIAN_2        = 1 << 12,
		PED_TYPE_GANG_IRISH            = 1 << 13,
		PED_TYPE_GANG_JAMAICAN         = 1 << 14,
		PED_TYPE_GANG_AFRICAN_AMERICAN = 1 << 15,
		PED_TYPE_GANG_KOREAN           = 1 << 16,
		PED_TYPE_GANG_CHINESE_JAPANESE = 1 << 17,
		PED_TYPE_GANG_PUERTO_RICAN     = 1 << 18,
		PED_TYPE_DEALER                = 1 << 19,
		PED_TYPE_MEDIC                 = 1 << 20,
		PED_TYPE_FIREMAN               = 1 << 21,
		PED_TYPE_CRIMINAL              = 1 << 22,
		PED_TYPE_BUM                   = 1 << 23,
		PED_TYPE_PROSTITUTE            = 1 << 24,
		PED_TYPE_SPECIAL               = 1 << 25,
		PED_TYPE_MISSION               = 1 << 26,
		PED_TYPE_SWAT                  = 1 << 27,
		PED_TYPE_ANIMAL                = 1 << 28,
		PED_TYPE_ARMY                  = 1 << 29,
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

	enum class HudComponents
	{
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
		FRIENDLY,   // heal, semi godmode...
		AGGRESSIVE, // kick from vehicle, send to apartment...
		TOXIC,      // kicks
		ADMIN       // full access
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(CommandAccessLevel,
	    {
	        {CommandAccessLevel::NONE, "none"},
	        {CommandAccessLevel::FRIENDLY, "friendly"},
	        {CommandAccessLevel::AGGRESSIVE, "aggressive"},
	        {CommandAccessLevel::TOXIC, "toxic"},
	        {CommandAccessLevel::ADMIN, "admin"},
	    })

	enum eKeyState : unsigned int
	{
		RELEASE = WM_KEYUP,
		DOWN    = WM_KEYDOWN
	};

	enum SpamReason : int
	{
		NOT_A_SPAMMER,
		STATIC_DETECTION,
		TIMER_DETECTION
	};

	enum eTraceFlags : uint32_t
	{
		IntersectNone               = 0,
		IntersectWorld              = 1 << 0,
		IntersectVehicle            = 1 << 1,
		IntersectPedSimpleCollision = 1 << 2,
		IntersectPed                = 1 << 3,
		IntersectObject             = 1 << 4,
		IntersectPickup             = 1 << 5,
		IntersectGlass              = 1 << 6,
		IntersectWater              = 1 << 7,
		IntersectFoliage            = 1 << 8,
		IntersectEverything         = eTraceFlags(-1),
	};
}
