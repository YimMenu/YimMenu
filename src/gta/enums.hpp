#pragma once
#include <cstdint>

constexpr auto MAX_PLAYERS = 32;

enum class ControllerInputs : std::uint32_t
{
	INPUT_NEXT_CAMERA,
	INPUT_LOOK_LR,
	INPUT_LOOK_UD,
	INPUT_LOOK_UP_ONLY,
	INPUT_LOOK_DOWN_ONLY,
	INPUT_LOOK_LEFT_ONLY,
	INPUT_LOOK_RIGHT_ONLY,
	INPUT_CINEMATIC_SLOWMO,
	INPUT_SCRIPTED_FLY_UD,
	INPUT_SCRIPTED_FLY_LR,
	INPUT_SCRIPTED_FLY_ZUP,
	INPUT_SCRIPTED_FLY_ZDOWN,
	INPUT_WEAPON_WHEEL_UD,
	INPUT_WEAPON_WHEEL_LR,
	INPUT_WEAPON_WHEEL_NEXT,
	INPUT_WEAPON_WHEEL_PREV,
	INPUT_SELECT_NEXT_WEAPON,
	INPUT_SELECT_PREV_WEAPON,
	INPUT_SKIP_CUTSCENE,
	INPUT_CHARACTER_WHEEL,
	INPUT_MULTIPLAYER_INFO,
	INPUT_SPRINT,
	INPUT_JUMP,
	INPUT_ENTER,
	INPUT_ATTACK,
	INPUT_AIM,
	INPUT_LOOK_BEHIND,
	INPUT_PHONE,
	INPUT_SPECIAL_ABILITY,
	INPUT_SPECIAL_ABILITY_SECONDARY,
	INPUT_MOVE_LR,
	INPUT_MOVE_UD,
	INPUT_MOVE_UP_ONLY,
	INPUT_MOVE_DOWN_ONLY,
	INPUT_MOVE_LEFT_ONLY,
	INPUT_MOVE_RIGHT_ONLY,
	INPUT_DUCK,
	INPUT_SELECT_WEAPON,
	INPUT_PICKUP,
	INPUT_SNIPER_ZOOM,
	INPUT_SNIPER_ZOOM_IN_ONLY,
	INPUT_SNIPER_ZOOM_OUT_ONLY,
	INPUT_SNIPER_ZOOM_IN_SECONDARY,
	INPUT_SNIPER_ZOOM_OUT_SECONDARY,
	INPUT_COVER,
	INPUT_RELOAD,
	INPUT_TALK,
	INPUT_DETONATE,
	INPUT_HUD_SPECIAL,
	INPUT_ARREST,
	INPUT_ACCURATE_AIM,
	INPUT_CONTEXT,
	INPUT_CONTEXT_SECONDARY,
	INPUT_WEAPON_SPECIAL,
	INPUT_WEAPON_SPECIAL_TWO,
	INPUT_DIVE,
	INPUT_DROP_WEAPON,
	INPUT_DROP_AMMO,
	INPUT_THROW_GRENADE,
	INPUT_VEH_MOVE_LR,
	INPUT_VEH_MOVE_UD,
	INPUT_VEH_MOVE_UP_ONLY,
	INPUT_VEH_MOVE_DOWN_ONLY,
	INPUT_VEH_MOVE_LEFT_ONLY,
	INPUT_VEH_MOVE_RIGHT_ONLY,
	INPUT_VEH_SPECIAL,
	INPUT_VEH_GUN_LR,
	INPUT_VEH_GUN_UD,
	INPUT_VEH_AIM,
	INPUT_VEH_ATTACK,
	INPUT_VEH_ATTACK2,
	INPUT_VEH_ACCELERATE,
	INPUT_VEH_BRAKE,
	INPUT_VEH_DUCK,
	INPUT_VEH_HEADLIGHT,
	INPUT_VEH_EXIT,
	INPUT_VEH_HANDBRAKE,
	INPUT_VEH_HOTWIRE_LEFT,
	INPUT_VEH_HOTWIRE_RIGHT,
	INPUT_VEH_LOOK_BEHIND,
	INPUT_VEH_CIN_CAM,
	INPUT_VEH_NEXT_RADIO,
	INPUT_VEH_PREV_RADIO,
	INPUT_VEH_NEXT_RADIO_TRACK,
	INPUT_VEH_PREV_RADIO_TRACK,
	INPUT_VEH_RADIO_WHEEL,
	INPUT_VEH_HORN,
	INPUT_VEH_FLY_THROTTLE_UP,
	INPUT_VEH_FLY_THROTTLE_DOWN,
	INPUT_VEH_FLY_YAW_LEFT,
	INPUT_VEH_FLY_YAW_RIGHT,
	INPUT_VEH_PASSENGER_AIM,
	INPUT_VEH_PASSENGER_ATTACK,
	INPUT_VEH_SPECIAL_ABILITY_FRANKLIN,
	INPUT_VEH_STUNT_UD,
	INPUT_VEH_CINEMATIC_UD,
	INPUT_VEH_CINEMATIC_UP_ONLY,
	INPUT_VEH_CINEMATIC_DOWN_ONLY,
	INPUT_VEH_CINEMATIC_LR,
	INPUT_VEH_SELECT_NEXT_WEAPON,
	INPUT_VEH_SELECT_PREV_WEAPON,
	INPUT_VEH_ROOF,
	INPUT_VEH_JUMP,
	INPUT_VEH_GRAPPLING_HOOK,
	INPUT_VEH_SHUFFLE,
	INPUT_VEH_DROP_PROJECTILE,
	INPUT_VEH_MOUSE_CONTROL_OVERRIDE,
	INPUT_VEH_FLY_ROLL_LR,
	INPUT_VEH_FLY_ROLL_LEFT_ONLY,
	INPUT_VEH_FLY_ROLL_RIGHT_ONLY,
	INPUT_VEH_FLY_PITCH_UD,
	INPUT_VEH_FLY_PITCH_UP_ONLY,
	INPUT_VEH_FLY_PITCH_DOWN_ONLY,
	INPUT_VEH_FLY_UNDERCARRIAGE,
	INPUT_VEH_FLY_ATTACK,
	INPUT_VEH_FLY_SELECT_NEXT_WEAPON,
	INPUT_VEH_FLY_SELECT_PREV_WEAPON,
	INPUT_VEH_FLY_SELECT_TARGET_LEFT,
	INPUT_VEH_FLY_SELECT_TARGET_RIGHT,
	INPUT_VEH_FLY_VERTICAL_FLIGHT_MODE,
	INPUT_VEH_FLY_DUCK,
	INPUT_VEH_FLY_ATTACK_CAMERA,
	INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE,
	INPUT_VEH_SUB_TURN_LR,
	INPUT_VEH_SUB_TURN_LEFT_ONLY,
	INPUT_VEH_SUB_TURN_RIGHT_ONLY,
	INPUT_VEH_SUB_PITCH_UD,
	INPUT_VEH_SUB_PITCH_UP_ONLY,
	INPUT_VEH_SUB_PITCH_DOWN_ONLY,
	INPUT_VEH_SUB_THROTTLE_UP,
	INPUT_VEH_SUB_THROTTLE_DOWN,
	INPUT_VEH_SUB_ASCEND,
	INPUT_VEH_SUB_DESCEND,
	INPUT_VEH_SUB_TURN_HARD_LEFT,
	INPUT_VEH_SUB_TURN_HARD_RIGHT,
	INPUT_VEH_SUB_MOUSE_CONTROL_OVERRIDE,
	INPUT_VEH_PUSHBIKE_PEDAL,
	INPUT_VEH_PUSHBIKE_SPRINT,
	INPUT_VEH_PUSHBIKE_FRONT_BRAKE,
	INPUT_VEH_PUSHBIKE_REAR_BRAKE,
	INPUT_MELEE_ATTACK_LIGHT,
	INPUT_MELEE_ATTACK_HEAVY,
	INPUT_MELEE_ATTACK_ALTERNATE,
	INPUT_MELEE_BLOCK,
	INPUT_PARACHUTE_DEPLOY,
	INPUT_PARACHUTE_DETACH,
	INPUT_PARACHUTE_TURN_LR,
	INPUT_PARACHUTE_TURN_LEFT_ONLY,
	INPUT_PARACHUTE_TURN_RIGHT_ONLY,
	INPUT_PARACHUTE_PITCH_UD,
	INPUT_PARACHUTE_PITCH_UP_ONLY,
	INPUT_PARACHUTE_PITCH_DOWN_ONLY,
	INPUT_PARACHUTE_BRAKE_LEFT,
	INPUT_PARACHUTE_BRAKE_RIGHT,
	INPUT_PARACHUTE_SMOKE,
	INPUT_PARACHUTE_PRECISION_LANDING,
	INPUT_MAP,
	INPUT_SELECT_WEAPON_UNARMED,
	INPUT_SELECT_WEAPON_MELEE,
	INPUT_SELECT_WEAPON_HANDGUN,
	INPUT_SELECT_WEAPON_SHOTGUN,
	INPUT_SELECT_WEAPON_SMG,
	INPUT_SELECT_WEAPON_AUTO_RIFLE,
	INPUT_SELECT_WEAPON_SNIPER,
	INPUT_SELECT_WEAPON_HEAVY,
	INPUT_SELECT_WEAPON_SPECIAL,
	INPUT_SELECT_CHARACTER_MICHAEL,
	INPUT_SELECT_CHARACTER_FRANKLIN,
	INPUT_SELECT_CHARACTER_TREVOR,
	INPUT_SELECT_CHARACTER_MULTIPLAYER,
	INPUT_SAVE_REPLAY_CLIP,
	INPUT_SPECIAL_ABILITY_PC,
	INPUT_CELLPHONE_UP,
	INPUT_CELLPHONE_DOWN,
	INPUT_CELLPHONE_LEFT,
	INPUT_CELLPHONE_RIGHT,
	INPUT_CELLPHONE_SELECT,
	INPUT_CELLPHONE_CANCEL,
	INPUT_CELLPHONE_OPTION,
	INPUT_CELLPHONE_EXTRA_OPTION,
	INPUT_CELLPHONE_SCROLL_FORWARD,
	INPUT_CELLPHONE_SCROLL_BACKWARD,
	INPUT_CELLPHONE_CAMERA_FOCUS_LOCK,
	INPUT_CELLPHONE_CAMERA_GRID,
	INPUT_CELLPHONE_CAMERA_SELFIE,
	INPUT_CELLPHONE_CAMERA_DOF,
	INPUT_CELLPHONE_CAMERA_EXPRESSION,
	INPUT_FRONTEND_DOWN,
	INPUT_FRONTEND_UP,
	INPUT_FRONTEND_LEFT,
	INPUT_FRONTEND_RIGHT,
	INPUT_FRONTEND_RDOWN,
	INPUT_FRONTEND_RUP,
	INPUT_FRONTEND_RLEFT,
	INPUT_FRONTEND_RRIGHT,
	INPUT_FRONTEND_AXIS_X,
	INPUT_FRONTEND_AXIS_Y,
	INPUT_FRONTEND_RIGHT_AXIS_X,
	INPUT_FRONTEND_RIGHT_AXIS_Y,
	INPUT_FRONTEND_PAUSE,
	INPUT_FRONTEND_PAUSE_ALTERNATE,
	INPUT_FRONTEND_ACCEPT,
	INPUT_FRONTEND_CANCEL,
	INPUT_FRONTEND_X,
	INPUT_FRONTEND_Y,
	INPUT_FRONTEND_LB,
	INPUT_FRONTEND_RB,
	INPUT_FRONTEND_LT,
	INPUT_FRONTEND_RT,
	INPUT_FRONTEND_LS,
	INPUT_FRONTEND_RS,
	INPUT_FRONTEND_LEADERBOARD,
	INPUT_FRONTEND_SOCIAL_CLUB,
	INPUT_FRONTEND_SOCIAL_CLUB_SECONDARY,
	INPUT_FRONTEND_DELETE,
	INPUT_FRONTEND_ENDSCREEN_ACCEPT,
	INPUT_FRONTEND_ENDSCREEN_EXPAND,
	INPUT_FRONTEND_SELECT,
	INPUT_SCRIPT_LEFT_AXIS_X,
	INPUT_SCRIPT_LEFT_AXIS_Y,
	INPUT_SCRIPT_RIGHT_AXIS_X,
	INPUT_SCRIPT_RIGHT_AXIS_Y,
	INPUT_SCRIPT_RUP,
	INPUT_SCRIPT_RDOWN,
	INPUT_SCRIPT_RLEFT,
	INPUT_SCRIPT_RRIGHT,
	INPUT_SCRIPT_LB,
	INPUT_SCRIPT_RB,
	INPUT_SCRIPT_LT,
	INPUT_SCRIPT_RT,
	INPUT_SCRIPT_LS,
	INPUT_SCRIPT_RS,
	INPUT_SCRIPT_PAD_UP,
	INPUT_SCRIPT_PAD_DOWN,
	INPUT_SCRIPT_PAD_LEFT,
	INPUT_SCRIPT_PAD_RIGHT,
	INPUT_SCRIPT_SELECT,
	INPUT_CURSOR_ACCEPT,
	INPUT_CURSOR_CANCEL,
	INPUT_CURSOR_X,
	INPUT_CURSOR_Y,
	INPUT_CURSOR_SCROLL_UP,
	INPUT_CURSOR_SCROLL_DOWN,
	INPUT_ENTER_CHEAT_CODE,
	INPUT_INTERACTION_MENU,
	INPUT_MP_TEXT_CHAT_ALL,
	INPUT_MP_TEXT_CHAT_TEAM,
	INPUT_MP_TEXT_CHAT_FRIENDS,
	INPUT_MP_TEXT_CHAT_CREW,
	INPUT_PUSH_TO_TALK,
	INPUT_CREATOR_LS,
	INPUT_CREATOR_RS,
	INPUT_CREATOR_LT,
	INPUT_CREATOR_RT,
	INPUT_CREATOR_MENU_TOGGLE,
	INPUT_CREATOR_ACCEPT,
	INPUT_CREATOR_DELETE,
	INPUT_ATTACK2,
	INPUT_RAPPEL_JUMP,
	INPUT_RAPPEL_LONG_JUMP,
	INPUT_RAPPEL_SMASH_WINDOW,
	INPUT_PREV_WEAPON,
	INPUT_NEXT_WEAPON,
	INPUT_MELEE_ATTACK1,
	INPUT_MELEE_ATTACK2,
	INPUT_WHISTLE,
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,
	INPUT_LOOK_LEFT,
	INPUT_LOOK_RIGHT,
	INPUT_LOOK_UP,
	INPUT_LOOK_DOWN,
	INPUT_SNIPER_ZOOM_IN,
	INPUT_SNIPER_ZOOM_OUT,
	INPUT_SNIPER_ZOOM_IN_ALTERNATE,
	INPUT_SNIPER_ZOOM_OUT_ALTERNATE,
	INPUT_VEH_MOVE_LEFT,
	INPUT_VEH_MOVE_RIGHT,
	INPUT_VEH_MOVE_UP,
	INPUT_VEH_MOVE_DOWN,
	INPUT_VEH_GUN_LEFT,
	INPUT_VEH_GUN_RIGHT,
	INPUT_VEH_GUN_UP,
	INPUT_VEH_GUN_DOWN,
	INPUT_VEH_LOOK_LEFT,
	INPUT_VEH_LOOK_RIGHT,
	INPUT_REPLAY_START_STOP_RECORDING,
	INPUT_REPLAY_START_STOP_RECORDING_SECONDARY,
	INPUT_SCALED_LOOK_LR,
	INPUT_SCALED_LOOK_UD,
	INPUT_SCALED_LOOK_UP_ONLY,
	INPUT_SCALED_LOOK_DOWN_ONLY,
	INPUT_SCALED_LOOK_LEFT_ONLY,
	INPUT_SCALED_LOOK_RIGHT_ONLY,
	INPUT_REPLAY_MARKER_DELETE,
	INPUT_REPLAY_CLIP_DELETE,
	INPUT_REPLAY_PAUSE,
	INPUT_REPLAY_REWIND,
	INPUT_REPLAY_FFWD,
	INPUT_REPLAY_NEWMARKER,
	INPUT_REPLAY_RECORD,
	INPUT_REPLAY_SCREENSHOT,
	INPUT_REPLAY_HIDEHUD,
	INPUT_REPLAY_STARTPOINT,
	INPUT_REPLAY_ENDPOINT,
	INPUT_REPLAY_ADVANCE,
	INPUT_REPLAY_BACK,
	INPUT_REPLAY_TOOLS,
	INPUT_REPLAY_RESTART,
	INPUT_REPLAY_SHOWHOTKEY,
	INPUT_REPLAY_CYCLEMARKERLEFT,
	INPUT_REPLAY_CYCLEMARKERRIGHT,
	INPUT_REPLAY_FOVINCREASE,
	INPUT_REPLAY_FOVDECREASE,
	INPUT_REPLAY_CAMERAUP,
	INPUT_REPLAY_CAMERADOWN,
	INPUT_REPLAY_SAVE,
	INPUT_REPLAY_TOGGLETIME,
	INPUT_REPLAY_TOGGLETIPS,
	INPUT_REPLAY_PREVIEW,
	INPUT_REPLAY_TOGGLE_TIMELINE,
	INPUT_REPLAY_TIMELINE_PICKUP_CLIP,
	INPUT_REPLAY_TIMELINE_DUPLICATE_CLIP,
	INPUT_REPLAY_TIMELINE_PLACE_CLIP,
	INPUT_REPLAY_CTRL,
	INPUT_REPLAY_TIMELINE_SAVE,
	INPUT_REPLAY_PREVIEW_AUDIO,
	INPUT_VEH_DRIVE_LOOK,
	INPUT_VEH_DRIVE_LOOK2,
	INPUT_VEH_FLY_ATTACK2,
	INPUT_RADIO_WHEEL_UD,
	INPUT_RADIO_WHEEL_LR,
	INPUT_VEH_SLOWMO_UD,
	INPUT_VEH_SLOWMO_UP_ONLY,
	INPUT_VEH_SLOWMO_DOWN_ONLY,
	INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE,
	INPUT_VEH_HYDRAULICS_CONTROL_LEFT,
	INPUT_VEH_HYDRAULICS_CONTROL_RIGHT,
	INPUT_VEH_HYDRAULICS_CONTROL_UP,
	INPUT_VEH_HYDRAULICS_CONTROL_DOWN,
	INPUT_VEH_HYDRAULICS_CONTROL_LR,
	INPUT_VEH_HYDRAULICS_CONTROL_UD,
	INPUT_SWITCH_VISOR,
	INPUT_VEH_MELEE_HOLD,
	INPUT_VEH_MELEE_LEFT,
	INPUT_VEH_MELEE_RIGHT,
	INPUT_MAP_POI,
	INPUT_REPLAY_SNAPMATIC_PHOTO,
	INPUT_VEH_CAR_JUMP,
	INPUT_VEH_ROCKET_BOOST,
	INPUT_VEH_FLY_BOOST,
	INPUT_VEH_PARACHUTE,
	INPUT_VEH_BIKE_WINGS,
	INPUT_VEH_FLY_BOMB_BAY,
	INPUT_VEH_FLY_COUNTER,
	INPUT_VEH_TRANSFORM,
	MAX_INPUTS,
	UNDEFINED_INPUT,
	DYNAMIC_MAPPING_MOUSE_X,
	DYNAMIC_MAPPING_MOUSE_Y,
	FIRST_INPUT,
	SCRIPTED_INPUT_FIRST,
	SCRIPTED_INPUT_LAST
};

enum class RadioStationIndexes : std::uint32_t
{
	RADIO_LSROCKRADIO,
	RADIO_NONSTOPPOPFM,
	RADIO_RADIOLOSSANTOS,
	RADIO_CHANNELX,
	RADIO_WCTR,
	RADIO_REBELRADIO,
	RADIO_SOULWAX,
	RADIO_EASTLOSFM,
	RADIO_WESTCOASTCLASSICS,
	RADIO_BLUEARK,
	RADIO_WORLDWIDEFM,
	RADIO_FLYLO,
	RADIO_THELOWDOWN,
	RADIO_THELAB,
	RADIO_RADIOMIRRORPARK,
	RADIO_SPACE1032,
	RADIO_VINEWOODBOULEVARD,
	RADIO_BLONDEDLOSSANDOS,
	RADIO_SELFRADIO,
	RADIO_BLANECOUNTYTALK,
	RADIO_LOSSANTOSUNDERGROUNDRADIO,
	RADIO_OFF
};

enum class NetObjEntityType : uint16_t
{
	NetObjEntityType_Automobile,
	NetObjEntityType_Bike,
	NetObjEntityType_Boat,
	NetObjEntityType_Door,
	NetObjEntityType_Heli,
	NetObjEntityType_Object,
	NetObjEntityType_Ped,
	NetObjEntityType_Pickup,
	NetObjEntityType_PickupPlacement,
	NetObjEntityType_Plane,
	NetObjEntityType_Submarine,
	NetObjEntityType_Player,
	NetObjEntityType_Trailer,
	NetObjEntityType_Train,
	NetObjEntityType_Max
};

enum class eNetworkEvents : uint16_t
{
	OBJECT_ID_FREED_EVENT,
	OBJECT_ID_REQUEST_EVENT,
	ARRAY_DATA_VERIFY_EVENT,
	SCRIPT_ARRAY_DATA_VERIFY_EVENT,
	REQUEST_CONTROL_EVENT,
	GIVE_CONTROL_EVENT,
	WEAPON_DAMAGE_EVENT,
	REQUEST_PICKUP_EVENT,
	REQUEST_MAP_PICKUP_EVENT,
	GAME_CLOCK_EVENT,
	GAME_WEATHER_EVENT,
	RESPAWN_PLAYER_PED_EVENT,
	GIVE_WEAPON_EVENT,
	REMOVE_WEAPON_EVENT,
	REMOVE_ALL_WEAPONS_EVENT,
	VEHICLE_COMPONENT_CONTROL_EVENT,
	FIRE_EVENT,
	EXPLOSION_EVENT,
	START_PROJECTILE_EVENT,
	UPDATE_PROJECTILE_TARGET_EVENT,
	REMOVE_PROJECTILE_ENTITY_EVENT,
	BREAK_PROJECTILE_TARGET_LOCK_EVENT,
	ALTER_WANTED_LEVEL_EVENT,
	CHANGE_RADIO_STATION_EVENT,
	RAGDOLL_REQUEST_EVENT,
	PLAYER_TAUNT_EVENT,
	PLAYER_CARD_STAT_EVENT,
	DOOR_BREAK_EVENT,
	SCRIPTED_GAME_EVENT,
	REMOTE_SCRIPT_INFO_EVENT,
	REMOTE_SCRIPT_LEAVE_EVENT,
	MARK_AS_NO_LONGER_NEEDED_EVENT,
	CONVERT_TO_SCRIPT_ENTITY_EVENT,
	SCRIPT_WORLD_STATE_EVENT,
	CLEAR_AREA_EVENT,
	CLEAR_RECTANGLE_AREA_EVENT,
	NETWORK_REQUEST_SYNCED_SCENE_EVENT,
	NETWORK_START_SYNCED_SCENE_EVENT,
	NETWORK_STOP_SYNCED_SCENE_EVENT,
	NETWORK_UPDATE_SYNCED_SCENE_EVENT,
	INCIDENT_ENTITY_EVENT,
	GIVE_PED_SCRIPTED_TASK_EVENT,
	GIVE_PED_SEQUENCE_TASK_EVENT,
	NETWORK_CLEAR_PED_TASKS_EVENT,
	NETWORK_START_PED_ARREST_EVENT,
	NETWORK_START_PED_UNCUFF_EVENT,
	NETWORK_SOUND_CAR_HORN_EVENT,
	NETWORK_ENTITY_AREA_STATUS_EVENT,
	NETWORK_GARAGE_OCCUPIED_STATUS_EVENT,
	PED_CONVERSATION_LINE_EVENT,
	SCRIPT_ENTITY_STATE_CHANGE_EVENT,
	NETWORK_PLAY_SOUND_EVENT,
	NETWORK_STOP_SOUND_EVENT,
	NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT,
	NETWORK_BANK_REQUEST_EVENT,
	NETWORK_AUDIO_BARK_EVENT,
	REQUEST_DOOR_EVENT,
	NETWORK_TRAIN_REPORT_EVENT,
	NETWORK_TRAIN_REQUEST_EVENT,
	NETWORK_INCREMENT_STAT_EVENT,
	MODIFY_VEHICLE_LOCK_WORD_STATE_DATA,
	MODIFY_PTFX_WORD_STATE_DATA_SCRIPTED_EVOLVE_EVENT,
	REQUEST_PHONE_EXPLOSION_EVENT,
	REQUEST_DETACHMENT_EVENT,
	KICK_VOTES_EVENT,
	GIVE_PICKUP_REWARDS_EVENT,
	NETWORK_CRC_HASH_CHECK_EVENT,
	BLOW_UP_VEHICLE_EVENT,
	NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON,
	NETWORK_RESPONDED_TO_THREAT_EVENT,
	NETWORK_SHOUT_TARGET_POSITION,
	VOICE_DRIVEN_MOUTH_MOVEMENT_FINISHED_EVENT,
	PICKUP_DESTROYED_EVENT,
	UPDATE_PLAYER_SCARS_EVENT,
	NETWORK_CHECK_EXE_SIZE_EVENT,
	NETWORK_PTFX_EVENT,
	NETWORK_PED_SEEN_DEAD_PED_EVENT,
	REMOVE_STICKY_BOMB_EVENT,
	NETWORK_CHECK_CODE_CRCS_EVENT,
	INFORM_SILENCED_GUNSHOT_EVENT,
	PED_PLAY_PAIN_EVENT,
	CACHE_PLAYER_HEAD_BLEND_DATA_EVENT,
	REMOVE_PED_FROM_PEDGROUP_EVENT,
	REPORT_MYSELF_EVENT,
	REPORT_CASH_SPAWN_EVENT,
	ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT,
	BLOCK_WEAPON_SELECTION,
	NETWORK_CHECK_CATALOG_CRC
};

enum class ScriptEntityChangeType
{
	BlockingOfNonTemporaryEvents,
	SettingOfPedRelationshipGroupHash,
	SettingOfDriveTaskCruiseSpeed,
	SettingOfLookAtEntity,
	SettingOfPlaneMinHeightAboveTerrain,
	SetPedRagdollBlockFlag,
	SettingOfTaskVehicleTempAction,
	SetPedFacialIdleAnimOverride,
	SetVehicleLockState,
	SetVehicleExclusiveDriver
};

enum class WorldStateDataType
{
	CarGen,
	EntityArea,
	PopGroupOverride,
	PopMultiplierArea,
	PTFX,
	RoadNode,
	Rope,
	ScenarioBlockingArea,
	VehiclePlayerLocking
};

enum class BlipIcons
{
	Null,
	Circle,
	Empty,
	Cop,
	CopSearchZone,
	Square,
	PlayerArrow,
	North,
	Waypoint,
	BigCircle,
	BigCircleOutline,
	ArrowUpOutlined,
	ArrowDownOutlined,
	ArrowUp,
	ArrowDown,
	PoliceHelicopter,
	Jet,
	Number1,
	Number2,
	Number3,
	Number4,
	Number5,
	Number6,
	Number7,
	Number8,
	Number9,
	Number10,
	GTAOCrew,
	GTAOFriend,
	CableCar   = 36,
	RaceFinish = 38,
	Safehouse  = 40,
	Cop2,
	CopCar,
	Helicopter,
	ChatBubble = 47,
	Garage     = 50,
	Drugs,
	ConvenienceStore,
	PoliceCar = 56,
	Circle2,
	CircleWithStar,
	ConvenienceStore2,
	ShieldWithStar,
	Asterisk,
	Helicopter2        = 64,
	StrangersAndFreaks = 66,
	ArmoredTruck,
	TowTruck,
	Barber = 71,
	LosSantosCustoms,
	Clothes,
	TattooParlor = 75,
	Simeon,
	Lester,
	Michael,
	Trevor,
	Heist1,
	Rampage = 84,
	VinewoodTours,
	Franklin,
	Franklin2 = 88,
	Chinese,
	FlightSchool,
	Bar = 93,
	ParachuteJump,
	Heist2     = 96,
	CarWash    = 100,
	ComedyClub = 102,
	Darts,
	FIB = 106,
	Heist3,
	DollarSign,
	Golf,
	AmmuNation,
	Exile         = 112,
	ShootingRange = 119,
	Solomon,
	StripClub,
	Tennis,
	Triathlon = 126,
	OffRoadRaceFinish,
	Key = 134,
	MovieTheater,
	Music,
	Marijuana = 140,
	Hunting,
	ArmsTraffickingGround = 147,
	Nigel                 = 149,
	AssaultRifle,
	Bat,
	Grenade,
	Health,
	Knife,
	Molotov,
	Pistol,
	RPG,
	Shotgun,
	SMG,
	Sniper,
	SonicWave,
	PointOfInterest,
	GTAOPassive,
	GTAOUsingMenu,
	Link    = 171,
	Minigun = 173,
	GrenadeLauncher,
	Armor,
	Castle,
	CameraIcon = 184,
	Handcuffs  = 188,
	Yoga       = 197,
	Cab,
	Number11,
	Number12,
	Number13,
	Number14,
	Number15,
	Number16,
	Shrink,
	Epsilon,
	PersonalVehicleCar = 225,
	PersonalVehicleBike,
	Custody            = 237,
	ArmsTraffickingAir = 251,
	Fairground         = 266,
	PropertyManagement,
	Altruist = 269,
	Enemy,
	Chop = 273,
	Dead,
	Hooker = 279,
	Friend,
	BountyHit = 303,
	GTAOMission,
	GTAOSurvival,
	CrateDrop,
	PlaneDrop,
	Sub,
	Race,
	Deathmatch,
	ArmWrestling,
	AmmuNationShootingRange = 313,
	RaceAir,
	RaceCar,
	RaceSea,
	GarbageTruck     = 318,
	Motorcycle       = 348,
	SafehouseForSale = 350,
	Package,
	MartinMadrazo,
	EnemyHelicopter,
	Boost,
	Devin,
	Marina,
	Garage2,
	GolfFlag,
	Hangar,
	Helipad,
	JerryCan,
	Masks,
	HeistSetup,
	Incapacitated,
	PickupSpawn,
	BoilerSuit,
	Completed,
	Rockets,
	GarageForSale,
	HelipadForSale,
	MarinaForSale,
	HangarForSale,
	Business = 374,
	BusinessForSale,
	RaceBike,
	Parachute,
	TeamDeathmatch,
	RaceFoot,
	VehicleDeathmatch,
	Barry,
	Dom,
	MaryAnn,
	Cletus,
	Josh,
	Minute,
	Omega,
	Tonya,
	Paparazzo,
	Crosshair,
	Creator = 398,
	CreatorDirection,
	Abigail,
	Blimp,
	Repair,
	Testosterone,
	Dinghy,
	Fanatic,
	GangAttack,
	Information,
	CaptureBriefcase,
	LastTeamStanding,
	Boat,
	CaptureHouse,
	JerryCan2 = 415,
	RPLogo,
	GTAOPlayerSafehouse,
	GTAOPlayerSafehouseBounty,
	CaptureAmericanFlag,
	CaptureFlag,
	Tank,
	PlayerHelicopter,
	PlayerPlane,
	PlayerJet,
	PlayerArrowNoColor,
	PlayerLAPV,
	PlayerBoat,
	HeistRoom,
	Stopwatch = 430,
	DollarSignCircled,
	Crosshair2,
	Crosshair3,
	DollarSignSquared,
	RaceFlagWithArrow,
	Fire,
	DoubleDeathmatchSkulls,
	CastleIcon,
	Crown,
	SupplyBag,
	QuadirectionalArrows,
	Fox,
	Triangle,
	ThreeBars,
	LamarDavis,
	Mechanic,
	LamarDavisOne,
	LamarDavisTwo,
	LamarDavisThree,
	LamarDavisFour,
	LamarDavisFive,
	LamarDavisSix,
	LamarDavisSeven,
	LamarDavisEight,
	Yacht,
	SmallQuestionMark,
	GymBag,
	CrosshairWithPersonInMiddle,
	PlayerSpeaking,
	Taxi,
	ShieldWithX,
	YachtMinimap,
	Fox2,
	Hourglass,
	SmallQuestionMark2,
	Stopwatch2,
	Restart,
	SunWithEye,
	Marijuana2,
	Shotgun2,
	Jetski,
	EyeWithLineThroughIt,
	Garage3,
	GarageForSale2,
	Building,
	BuildingForSale,
	Truck,
	Crate,
	Trailer,
	Person,
	Cargobob,
	BigOutlineSquare,
	Speedometer,
	Ghost,
	RemoteControl,
	Bomb,
	Shield,
	StuntRace,
	Heart,
	StuntRaceMoney,
	TeamDeathMatch2,
	HouseWithGarage,
	QuadirectionalArrowsWithMotorcycle,
	CircleWithMotorcycle,
	MotorcycleRace,
	Weed,
	Cocaine,
	ForgedDocuments,
	Meth,
	CounterfeitMoney,
	DrugPickup,
	BigOne,
	BigTwo,
	BigThree,
	BigFour,
	BigFive,
	BigSix,
	BigSeven,
	BigEight,
	BigNine,
	BigTen,
	ATVQuad,
	Bus,
	BagMaybe,
	UpArrowOnSquare,
	FourPlayers,
	EightPlayers,
	TenPlayers,
	TwelvePlayers,
	SixteenPlayers,
	Laptop,
	Supercycle,
	Supercar,
	GarageWithCar,
	PaperDocument,
	ShieldWithBlackStar,
	CraneClaw,
	PhantomWedge,
	BoxvilleArmored,
	Ruiner2000,
	RampBuggy,
	Wastelander,
	RocketVoltic,
	TechnicalAqua,
	LetterA,
	LetterB,
	LetterC,
	LetterD,
	LetterE,
	LetterF,
	LetterG,
	LetterH,
	SkullWithTriangleTop,
	Wrench,
	SteeringWheel,
	Trolphy,
	Rocket,
	Missile,
	Bullets,
	Parachute2,
	Number5WithCircle,
	Number10WithCircle,
	Number15WithCircle,
	Number20WithCircle,
	Number30WithCircle,
	Bullets2,
	Bunker,
	InsurgentPickup,
	Opressor,
	TechnicalCustom,
	DuneFAV,
	HalfTrack,
	AntiAircraftTrailer,
	Satelite,
	BunkerWithPeople,
	ScrewdriverAndHammer,
	UpgradedWeaponWorkbench,
	CrateWithStraps,
	AircraftHanger,
	Icosikaitetragon,
	RaceflagWithQuestionmark,
	AlphaZ1,
	Bombushka,
	Havok,
	HowardNX25,
	Hunter,
	Ultralight,
	Mogul,
	Molotok,
	Nokota,
	Pyro,
	Rogue,
	Starling,
	Starbreeze,
	Tula,
	GymBagWithLetterH,
	LockedCrate,
	SateliteIcon,
	Avenger,
	IAAFacility,
	DoomsdayHeist,
	SAMTurret,
	HackingPuzzleRed,
	HackingPuzzleDiode,
	Stromburg,
	Deluxo,
	ThrusterJetpack,
	TM02KhanjaliTank,
	RCV,
	Volatol,
	Barrage,
	Akula,
	Chernobog,
	SpeakerMaybe,
	YellowishBrownMoneySign,
	ComputerTerminal,
	HackingPuzzleMirror,
	HackingPuzzleReflector,
	HackingPuzzleRotator,
	RaceFlagWithCrosshair,
	RaceFlagWithSteeringWheel,
	SeaSparrow,
	Caracara,
	Nightclub,
	CrateB,
	VanB,
	Diamond,
	BullionStacks,
	CalculatorMaybe,
	CarWithLightningBolt,
	HeartIcon,
	StarWithAdd,
	StarWithSubtract,
	BombWithAdd,
	BombWithSubtract,
	CrosshairDJ,
	Drone,
	Cashregister,
	SpeakerMaybeBigger,
	Skull,
	FestivalBus,
	Terrorbyte,
	Menacer,
	Scramjet,
	PounderCustom,
	MuleCustom,
	SpeedoCustom,
	BlimpIcon,
	OpressorMKII,
	B11StrikeForce,
	GearWithCar,
	GearWithMoney,
	GearWithWrench,
	RaceFlagWithGear,
	CrosshairOnCar,
	RCBandito,
	RCRemote,
	FlameSign,
	ArrowSign,
	GearSign,
	RepeatSign,
	DownArrowSign,
	ExplosionSign,
	WheelExplosionSign,
	ElevatorSign,
	ElevatorSign2,
	EjectorPlatformSign,
	Bruiser,
	Brutus,
	Cerberus,
	Deathbike,
	Dominator,
	Impaler,
	Imperator,
	Issi,
	Sasquatch,
	Scarab,
	Slamvan,
	ZR380
};

enum class BlipColors
{
	None,
	Red,
	Green,
	Blue,
	PlayerColor,
	YellowMission,
	FriendlyVehicle = 0x26,
	MichaelColor    = 0x2A,
	FranklinColor,
	TravorColor,
	BlipColorEnemy = 0x31,
	MissionVehicle = 0x36,
	RedMission     = 0x3B,
	YellowMission2 = 0x3C,
	Mission        = 0x42,
	WaypointColor  = 0x54
};

enum class BlipDisplayBits
{
	BlipIsBright                 = (1 << 1),
	BlipEngageFlashing           = (1 << 3),
	BlipFlashForRoute            = (1 << 5),
	BlipIsOnMinimap              = (1 << 6),
	BlipIsHighDetail             = (1 << 8),
	BlipUseBlipColorForDirection = (1 << 9),
	BlipIsSmall                  = (1 << 10),
	BlipShowCone                 = (1 << 11),
	BlipIsMissionCreatorBlip     = (1 << 12),
	BlipShowCheckmark            = (1 << 15),
	BlipShowDollarSign           = (1 << 16),
	BlipShowHeadingIndicator     = (1 << 17),
	BlipShowFullCircle           = (1 << 18),
	BlipIsFriend                 = (1 << 19),
	BlipIsCrew                   = (1 << 20),
	BlipIsSelected               = (1 << 22),
};

enum class BlipRenderBits
{
	BlipIsOnScreen = (1 << 6)
};

enum class eFrameFlags : std::uint32_t
{
	eFrameFlagExplosiveAmmo  = 1 << 11,
	eFrameFlagFireAmmo       = 1 << 12,
	eFrameFlagExplosiveMelee = 1 << 13,
	eFrameFlagSuperJump      = 1 << 14,
};

enum class eNetObjType
{
	NET_OBJ_TYPE_AUTOMOBILE,
	NET_OBJ_TYPE_BIKE,
	NET_OBJ_TYPE_BOAT,
	NET_OBJ_TYPE_DOOR,
	NET_OBJ_TYPE_HELI,
	NET_OBJ_TYPE_OBJECT,
	NET_OBJ_TYPE_PED,
	NET_OBJ_TYPE_PICKUP,
	NET_OBJ_TYPE_PICKUP_PLACEMENT,
	NET_OBJ_TYPE_PLANE,
	NET_OBJ_TYPE_SUBMARINE,
	NET_OBJ_TYPE_PLAYER,
	NET_OBJ_TYPE_TRAILER,
	NET_OBJ_TYPE_TRAIN
};

enum class eNetObjectFlags : std::uint16_t
{
	NET_OBJ_FLAGS_FROM_SCRIPT = 1 << 2,
	NET_OBJ_FLAGS_SCRIPTED    = 1 << 6,
};

enum class eAckCode : std::uint32_t
{
	ACKCODE_SUCCESS,
	ACKCODE_FAIL,
	ACKCODE_WRONG_OWNER,
	ACKCODE_OUT_OF_SEQUENCE,
	ACKCODE_NO_OBJECT,
	ACKCODE_TOO_MANY_OBJECTS,
	ACKCODE_CANT_APPLY_DATA,
	ACKCODE_MATCH_NOT_STARTED,
	ACKCODE_NONE
};

enum class PedBones : std::uint32_t
{
	SKEL_ROOT                        = 0x0,
	SKEL_Pelvis                      = 0x2E28,
	SKEL_L_Thigh                     = 0xE39F,
	SKEL_L_Calf                      = 0xF9BB,
	SKEL_L_Foot                      = 0x3779,
	SKEL_L_Toe0                      = 0x83C,
	EO_L_Foot                        = 0x84C5,
	EO_L_Toe                         = 0x68BD,
	IK_L_Foot                        = 0xFEDD,
	PH_L_Foot                        = 0xE175,
	MH_L_Knee                        = 0xB3FE,
	SKEL_R_Thigh                     = 0xCA72,
	SKEL_R_Calf                      = 0x9000,
	SKEL_R_Foot                      = 0xCC4D,
	SKEL_R_Toe0                      = 0x512D,
	EO_R_Foot                        = 0x1096,
	EO_R_Toe                         = 0x7163,
	IK_R_Foot                        = 0x8AAE,
	PH_R_Foot                        = 0x60E6,
	MH_R_Knee                        = 0x3FCF,
	RB_L_ThighRoll                   = 0x5C57,
	RB_R_ThighRoll                   = 0x192A,
	SKEL_Spine_Root                  = 0xE0FD,
	SKEL_Spine0                      = 0x5C01,
	SKEL_Spine1                      = 0x60F0,
	SKEL_Spine2                      = 0x60F1,
	SKEL_Spine3                      = 0x60F2,
	SKEL_L_Clavicle                  = 0xFCD9,
	SKEL_L_UpperArm                  = 0xB1C5,
	SKEL_L_Forearm                   = 0xEEEB,
	SKEL_L_Hand                      = 0x49D9,
	SKEL_L_Finger00                  = 0x67F2,
	SKEL_L_Finger01                  = 0xFF9,
	SKEL_L_Finger02                  = 0xFFA,
	SKEL_L_Finger10                  = 0x67F3,
	SKEL_L_Finger11                  = 0x1049,
	SKEL_L_Finger12                  = 0x104A,
	SKEL_L_Finger20                  = 0x67F4,
	SKEL_L_Finger21                  = 0x1059,
	SKEL_L_Finger22                  = 0x105A,
	SKEL_L_Finger30                  = 0x67F5,
	SKEL_L_Finger31                  = 0x1029,
	SKEL_L_Finger32                  = 0x102A,
	SKEL_L_Finger40                  = 0x67F6,
	SKEL_L_Finger41                  = 0x1039,
	SKEL_L_Finger42                  = 0x103A,
	PH_L_Hand                        = 0xEB95,
	IK_L_Hand                        = 0x8CBD,
	RB_L_ForeArmRoll                 = 0xEE4F,
	RB_L_ArmRoll                     = 0x1470,
	MH_L_Elbow                       = 0x58B7,
	SKEL_R_Clavicle                  = 0x29D2,
	SKEL_R_UpperArm                  = 0x9D4D,
	SKEL_R_Forearm                   = 0x6E5C,
	SKEL_R_Hand                      = 0xDEAD,
	SKEL_R_Finger00                  = 0xE5F2,
	SKEL_R_Finger01                  = 0xFA10,
	SKEL_R_Finger02                  = 0xFA11,
	SKEL_R_Finger10                  = 0xE5F3,
	SKEL_R_Finger11                  = 0xFA60,
	SKEL_R_Finger12                  = 0xFA61,
	SKEL_R_Finger20                  = 0xE5F4,
	SKEL_R_Finger21                  = 0xFA70,
	SKEL_R_Finger22                  = 0xFA71,
	SKEL_R_Finger30                  = 0xE5F5,
	SKEL_R_Finger31                  = 0xFA40,
	SKEL_R_Finger32                  = 0xFA41,
	SKEL_R_Finger40                  = 0xE5F6,
	SKEL_R_Finger41                  = 0xFA50,
	SKEL_R_Finger42                  = 0xFA51,
	PH_R_Hand                        = 0x6F06,
	IK_R_Hand                        = 0x188E,
	RB_R_ForeArmRoll                 = 0xAB22,
	RB_R_ArmRoll                     = 0x90FF,
	MH_R_Elbow                       = 0xBB0,
	SKEL_Neck_1                      = 0x9995,
	SKEL_Head                        = 0x796E,
	IK_Head                          = 0x322C,
	FACIAL_facialRoot                = 0xFE2C,
	FB_L_Brow_Out_000                = 0xE3DB,
	FB_L_Lid_Upper_000               = 0xB2B6,
	FB_L_Eye_000                     = 0x62AC,
	FB_L_CheekBone_000               = 0x542E,
	FB_L_Lip_Corner_000              = 0x74AC,
	FB_R_Lid_Upper_000               = 0xAA10,
	FB_R_Eye_000                     = 0x6B52,
	FB_R_CheekBone_000               = 0x4B88,
	FB_R_Brow_Out_000                = 0x54C,
	FB_R_Lip_Corner_000              = 0x2BA6,
	FB_Brow_Centre_000               = 0x9149,
	FB_UpperLipRoot_000              = 0x4ED2,
	FB_UpperLip_000                  = 0xF18F,
	FB_L_Lip_Top_000                 = 0x4F37,
	FB_R_Lip_Top_000                 = 0x4537,
	FB_Jaw_000                       = 0xB4A0,
	FB_LowerLipRoot_000              = 0x4324,
	FB_LowerLip_000                  = 0x508F,
	FB_L_Lip_Bot_000                 = 0xB93B,
	FB_R_Lip_Bot_000                 = 0xC33B,
	FB_Tongue_000                    = 0xB987,
	RB_Neck_1                        = 0x8B93,
	SPR_L_Breast                     = 0xFC8E,
	SPR_R_Breast                     = 0x885F,
	IK_Root                          = 0xDD1C,
	SKEL_Neck_2                      = 0x5FD4,
	SKEL_Pelvis1                     = 0xD003,
	SKEL_PelvisRoot                  = 0x45FC,
	SKEL_SADDLE                      = 0x9524,
	MH_L_CalfBack                    = 0x1013,
	MH_L_ThighBack                   = 0x600D,
	SM_L_Skirt                       = 0xC419,
	MH_R_CalfBack                    = 0xB013,
	MH_R_ThighBack                   = 0x51A3,
	SM_R_Skirt                       = 0x7712,
	SM_M_BackSkirtRoll               = 0xDBB,
	SM_L_BackSkirtRoll               = 0x40B2,
	SM_R_BackSkirtRoll               = 0xC141,
	SM_M_FrontSkirtRoll              = 0xCDBB,
	SM_L_FrontSkirtRoll              = 0x9B69,
	SM_R_FrontSkirtRoll              = 0x86F1,
	SM_CockNBalls_ROOT               = 0xC67D,
	SM_CockNBalls                    = 0x9D34,
	MH_L_Finger00                    = 0x8C63,
	MH_L_FingerBulge00               = 0x5FB8,
	MH_L_Finger10                    = 0x8C53,
	MH_L_FingerTop00                 = 0xA244,
	MH_L_HandSide                    = 0xC78A,
	MH_Watch                         = 0x2738,
	MH_L_Sleeve                      = 0x933C,
	MH_R_Finger00                    = 0x2C63,
	MH_R_FingerBulge00               = 0x69B8,
	MH_R_Finger10                    = 0x2C53,
	MH_R_FingerTop00                 = 0xEF4B,
	MH_R_HandSide                    = 0x68FB,
	MH_R_Sleeve                      = 0x92DC,
	FACIAL_jaw                       = 0xB21,
	FACIAL_underChin                 = 0x8A95,
	FACIAL_L_underChin               = 0x234E,
	FACIAL_chin                      = 0xB578,
	FACIAL_chinSkinBottom            = 0x98BC,
	FACIAL_L_chinSkinBottom          = 0x3E8F,
	FACIAL_R_chinSkinBottom          = 0x9E8F,
	FACIAL_tongueA                   = 0x4A7C,
	FACIAL_tongueB                   = 0x4A7D,
	FACIAL_tongueC                   = 0x4A7E,
	FACIAL_tongueD                   = 0x4A7F,
	FACIAL_tongueE                   = 0x4A80,
	FACIAL_L_tongueE                 = 0x35F2,
	FACIAL_R_tongueE                 = 0x2FF2,
	FACIAL_L_tongueD                 = 0x35F1,
	FACIAL_R_tongueD                 = 0x2FF1,
	FACIAL_L_tongueC                 = 0x35F0,
	FACIAL_R_tongueC                 = 0x2FF0,
	FACIAL_L_tongueB                 = 0x35EF,
	FACIAL_R_tongueB                 = 0x2FEF,
	FACIAL_L_tongueA                 = 0x35EE,
	FACIAL_R_tongueA                 = 0x2FEE,
	FACIAL_chinSkinTop               = 0x7226,
	FACIAL_L_chinSkinTop             = 0x3EB3,
	FACIAL_chinSkinMid               = 0x899A,
	FACIAL_L_chinSkinMid             = 0x4427,
	FACIAL_L_chinSide                = 0x4A5E,
	FACIAL_R_chinSkinMid             = 0xF5AF,
	FACIAL_R_chinSkinTop             = 0xF03B,
	FACIAL_R_chinSide                = 0xAA5E,
	FACIAL_R_underChin               = 0x2BF4,
	FACIAL_L_lipLowerSDK             = 0xB9E1,
	FACIAL_L_lipLowerAnalog          = 0x244A,
	FACIAL_L_lipLowerThicknessV      = 0xC749,
	FACIAL_L_lipLowerThicknessH      = 0xC67B,
	FACIAL_lipLowerSDK               = 0x7285,
	FACIAL_lipLowerAnalog            = 0xD97B,
	FACIAL_lipLowerThicknessV        = 0xC5BB,
	FACIAL_lipLowerThicknessH        = 0xC5ED,
	FACIAL_R_lipLowerSDK             = 0xA034,
	FACIAL_R_lipLowerAnalog          = 0xC2D9,
	FACIAL_R_lipLowerThicknessV      = 0xC6E9,
	FACIAL_R_lipLowerThicknessH      = 0xC6DB,
	FACIAL_nose                      = 0x20F1,
	FACIAL_L_nostril                 = 0x7322,
	FACIAL_L_nostrilThickness        = 0xC15F,
	FACIAL_noseLower                 = 0xE05A,
	FACIAL_L_noseLowerThickness      = 0x79D5,
	FACIAL_R_noseLowerThickness      = 0x7975,
	FACIAL_noseTip                   = 0x6A60,
	FACIAL_R_nostril                 = 0x7922,
	FACIAL_R_nostrilThickness        = 0x36FF,
	FACIAL_noseUpper                 = 0xA04F,
	FACIAL_L_noseUpper               = 0x1FB8,
	FACIAL_noseBridge                = 0x9BA3,
	FACIAL_L_nasolabialFurrow        = 0x5ACA,
	FACIAL_L_nasolabialBulge         = 0xCD78,
	FACIAL_L_cheekLower              = 0x6907,
	FACIAL_L_cheekLowerBulge1        = 0xE3FB,
	FACIAL_L_cheekLowerBulge2        = 0xE3FC,
	FACIAL_L_cheekInner              = 0xE7AB,
	FACIAL_L_cheekOuter              = 0x8161,
	FACIAL_L_eyesackLower            = 0x771B,
	FACIAL_L_eyeball                 = 0x1744,
	FACIAL_L_eyelidLower             = 0x998C,
	FACIAL_L_eyelidLowerOuterSDK     = 0xFE4C,
	FACIAL_L_eyelidLowerOuterAnalog  = 0xB9AA,
	FACIAL_L_eyelashLowerOuter       = 0xD7F6,
	FACIAL_L_eyelidLowerInnerSDK     = 0xF151,
	FACIAL_L_eyelidLowerInnerAnalog  = 0x8242,
	FACIAL_L_eyelashLowerInner       = 0x4CCF,
	FACIAL_L_eyelidUpper             = 0x97C1,
	FACIAL_L_eyelidUpperOuterSDK     = 0xAF15,
	FACIAL_L_eyelidUpperOuterAnalog  = 0x67FA,
	FACIAL_L_eyelashUpperOuter       = 0x27B7,
	FACIAL_L_eyelidUpperInnerSDK     = 0xD341,
	FACIAL_L_eyelidUpperInnerAnalog  = 0xF092,
	FACIAL_L_eyelashUpperInner       = 0x9B1F,
	FACIAL_L_eyesackUpperOuterBulge  = 0xA559,
	FACIAL_L_eyesackUpperInnerBulge  = 0x2F2A,
	FACIAL_L_eyesackUpperOuterFurrow = 0xC597,
	FACIAL_L_eyesackUpperInnerFurrow = 0x52A7,
	FACIAL_forehead                  = 0x9218,
	FACIAL_L_foreheadInner           = 0x843,
	FACIAL_L_foreheadInnerBulge      = 0x767C,
	FACIAL_L_foreheadOuter           = 0x8DCB,
	FACIAL_skull                     = 0x4221,
	FACIAL_foreheadUpper             = 0xF7D6,
	FACIAL_L_foreheadUpperInner      = 0xCF13,
	FACIAL_L_foreheadUpperOuter      = 0x509B,
	FACIAL_R_foreheadUpperInner      = 0xCEF3,
	FACIAL_R_foreheadUpperOuter      = 0x507B,
	FACIAL_L_temple                  = 0xAF79,
	FACIAL_L_ear                     = 0x19DD,
	FACIAL_L_earLower                = 0x6031,
	FACIAL_L_masseter                = 0x2810,
	FACIAL_L_jawRecess               = 0x9C7A,
	FACIAL_L_cheekOuterSkin          = 0x14A5,
	FACIAL_R_cheekLower              = 0xF367,
	FACIAL_R_cheekLowerBulge1        = 0x599B,
	FACIAL_R_cheekLowerBulge2        = 0x599C,
	FACIAL_R_masseter                = 0x810,
	FACIAL_R_jawRecess               = 0x93D4,
	FACIAL_R_ear                     = 0x1137,
	FACIAL_R_earLower                = 0x8031,
	FACIAL_R_eyesackLower            = 0x777B,
	FACIAL_R_nasolabialBulge         = 0xD61E,
	FACIAL_R_cheekOuter              = 0xD32,
	FACIAL_R_cheekInner              = 0x737C,
	FACIAL_R_noseUpper               = 0x1CD6,
	FACIAL_R_foreheadInner           = 0xE43,
	FACIAL_R_foreheadInnerBulge      = 0x769C,
	FACIAL_R_foreheadOuter           = 0x8FCB,
	FACIAL_R_cheekOuterSkin          = 0xB334,
	FACIAL_R_eyesackUpperInnerFurrow = 0x9FAE,
	FACIAL_R_eyesackUpperOuterFurrow = 0x140F,
	FACIAL_R_eyesackUpperInnerBulge  = 0xA359,
	FACIAL_R_eyesackUpperOuterBulge  = 0x1AF9,
	FACIAL_R_nasolabialFurrow        = 0x2CAA,
	FACIAL_R_temple                  = 0xAF19,
	FACIAL_R_eyeball                 = 0x1944,
	FACIAL_R_eyelidUpper             = 0x7E14,
	FACIAL_R_eyelidUpperOuterSDK     = 0xB115,
	FACIAL_R_eyelidUpperOuterAnalog  = 0xF25A,
	FACIAL_R_eyelashUpperOuter       = 0xE0A,
	FACIAL_R_eyelidUpperInnerSDK     = 0xD541,
	FACIAL_R_eyelidUpperInnerAnalog  = 0x7C63,
	FACIAL_R_eyelashUpperInner       = 0x8172,
	FACIAL_R_eyelidLower             = 0x7FDF,
	FACIAL_R_eyelidLowerOuterSDK     = 0x1BD,
	FACIAL_R_eyelidLowerOuterAnalog  = 0x457B,
	FACIAL_R_eyelashLowerOuter       = 0xBE49,
	FACIAL_R_eyelidLowerInnerSDK     = 0xF351,
	FACIAL_R_eyelidLowerInnerAnalog  = 0xE13,
	FACIAL_R_eyelashLowerInner       = 0x3322,
	FACIAL_L_lipUpperSDK             = 0x8F30,
	FACIAL_L_lipUpperAnalog          = 0xB1CF,
	FACIAL_L_lipUpperThicknessH      = 0x37CE,
	FACIAL_L_lipUpperThicknessV      = 0x38BC,
	FACIAL_lipUpperSDK               = 0x1774,
	FACIAL_lipUpperAnalog            = 0xE064,
	FACIAL_lipUpperThicknessH        = 0x7993,
	FACIAL_lipUpperThicknessV        = 0x7981,
	FACIAL_L_lipCornerSDK            = 0xB1C,
	FACIAL_L_lipCornerAnalog         = 0xE568,
	FACIAL_L_lipCornerThicknessUpper = 0x7BC,
	FACIAL_L_lipCornerThicknessLower = 0xDD42,
	FACIAL_R_lipUpperSDK             = 0x7583,
	FACIAL_R_lipUpperAnalog          = 0x51CF,
	FACIAL_R_lipUpperThicknessH      = 0x382E,
	FACIAL_R_lipUpperThicknessV      = 0x385C,
	FACIAL_R_lipCornerSDK            = 0xB3C,
	FACIAL_R_lipCornerAnalog         = 0xEE0E,
	FACIAL_R_lipCornerThicknessUpper = 0x54C3,
	FACIAL_R_lipCornerThicknessLower = 0x2BBA,
	MH_MulletRoot                    = 0x3E73,
	MH_MulletScaler                  = 0xA1C2,
	MH_Hair_Scale                    = 0xC664,
	MH_Hair_Crown                    = 0x1675,
	SM_Torch                         = 0x8D6,
	FX_Light                         = 0x8959,
	FX_Light_Scale                   = 0x5038,
	FX_Light_Switch                  = 0xE18E,
	BagRoot                          = 0xAD09,
	BagPivotROOT                     = 0xB836,
	BagPivot                         = 0x4D11,
	BagBody                          = 0xAB6D,
	BagBone_R                        = 0x937,
	BagBone_L                        = 0x991,
	SM_LifeSaver_Front               = 0x9420,
	SM_R_Pouches_ROOT                = 0x2962,
	SM_R_Pouches                     = 0x4141,
	SM_L_Pouches_ROOT                = 0x2A02,
	SM_L_Pouches                     = 0x4B41,
	SM_Suit_Back_Flapper             = 0xDA2D,
	SPR_CopRadio                     = 0x8245,
	SM_LifeSaver_Back                = 0x2127,
	MH_BlushSlider                   = 0xA0CE,
	SKEL_Tail_01                     = 0x347,
	SKEL_Tail_02                     = 0x348,
	MH_L_Concertina_B                = 0xC988,
	MH_L_Concertina_A                = 0xC987,
	MH_R_Concertina_B                = 0xC8E8,
	MH_R_Concertina_A                = 0xC8E7,
	MH_L_ShoulderBladeRoot           = 0x8711,
	MH_L_ShoulderBlade               = 0x4EAF,
	MH_R_ShoulderBladeRoot           = 0x3A0A,
	MH_R_ShoulderBlade               = 0x54AF,
	FB_R_Ear_000                     = 0x6CDF,
	SPR_R_Ear                        = 0x63B6,
	FB_L_Ear_000                     = 0x6439,
	SPR_L_Ear                        = 0x5B10,
	FB_TongueA_000                   = 0x4206,
	FB_TongueB_000                   = 0x4207,
	FB_TongueC_000                   = 0x4208,
	SKEL_L_Toe1                      = 0x1D6B,
	SKEL_R_Toe1                      = 0xB23F,
	SKEL_Tail_03                     = 0x349,
	SKEL_Tail_04                     = 0x34A,
	SKEL_Tail_05                     = 0x34B,
	SPR_Gonads_ROOT                  = 0xBFDE,
	SPR_Gonads                       = 0x1C00,
	FB_L_Brow_Out_001                = 0xE3DB,
	FB_L_Lid_Upper_001               = 0xB2B6,
	FB_L_Eye_001                     = 0x62AC,
	FB_L_CheekBone_001               = 0x542E,
	FB_L_Lip_Corner_001              = 0x74AC,
	FB_R_Lid_Upper_001               = 0xAA10,
	FB_R_Eye_001                     = 0x6B52,
	FB_R_CheekBone_001               = 0x4B88,
	FB_R_Brow_Out_001                = 0x54C,
	FB_R_Lip_Corner_001              = 0x2BA6,
	FB_Brow_Centre_001               = 0x9149,
	FB_UpperLipRoot_001              = 0x4ED2,
	FB_UpperLip_001                  = 0xF18F,
	FB_L_Lip_Top_001                 = 0x4F37,
	FB_R_Lip_Top_001                 = 0x4537,
	FB_Jaw_001                       = 0xB4A0,
	FB_LowerLipRoot_001              = 0x4324,
	FB_LowerLip_001                  = 0x508F,
	FB_L_Lip_Bot_001                 = 0xB93B,
	FB_R_Lip_Bot_001                 = 0xC33B,
	FB_Tongue_001                    = 0xB987
};

enum class eVehicleLockState
{
	VEHICLELOCK_NONE,
	VEHICLELOCK_UNLOCKED,
	VEHICLELOCK_LOCKED,
	VEHICLELOCK_LOCKOUT_PLAYER_ONLY,
	VEHICLELOCK_LOCKED_PLAYER_INSIDE,
	VEHICLELOCK_LOCKED_INITIALLY,
	VEHICLELOCK_FORCE_SHUT_DOORS,
	VEHICLELOCK_LOCKED_BUT_CAN_BE_DAMAGED,
	VEHICLELOCK_LOCKED_BUT_BOOT_UNLOCKED,
	VEHICLELOCK_LOCKED_NO_PASSENGERS,
	VEHICLELOCK_CANNOT_ENTER
};

enum class eCombatAttributes
{
	CA_INVALID        = -1,
	CA_USE_COVER      = 0, // AI will only use cover if this is set
	CA_USE_VEHICLE    = 1, // AI will only use vehicles if this is set
	CA_DO_DRIVEBYS    = 2, // AI will only driveby from a vehicle if this is set
	CA_LEAVE_VEHICLES = 3, // Will be forced to stay in a ny vehicel if this isn't set
	CA_CAN_USE_DYNAMIC_STRAFE_DECISIONS = 4, // This ped can make decisions on whether to strafe or not based on distance to destination, recent bullet events, etc.
	CA_ALWAYS_FIGHT           = 5, // Ped will always fight upon getting threat response task
	CA_FLEE_WHILST_IN_VEHICLE = 6, // If in combat and in a vehicle, the ped will flee rather than attacking
	CA_JUST_FOLLOW_VEHICLE = 7, // If in combat and chasing in a vehicle, the ped will keep a distance behind rather than ramming
	CA_PLAY_REACTION_ANIMS     = 8,  // Deprecated
	CA_WILL_SCAN_FOR_DEAD_PEDS = 9,  // Peds will scan for and react to dead peds found
	CA_IS_A_GUARD              = 10, // Deprecated
	CA_JUST_SEEK_COVER         = 11, // The ped will seek cover only
	CA_BLIND_FIRE_IN_COVER     = 12, // Ped will only blind fire when in cover
	CA_AGGRESSIVE              = 13, // Ped may advance
	CA_CAN_INVESTIGATE         = 14, // Ped can investigate events such as distant gunfire, footsteps, explosions etc
	CA_CAN_USE_RADIO           = 15, // Ped can use a radio to call for backup (happens after a reaction)
	CA_CAN_CAPTURE_ENEMY_PEDS  = 16, // Deprecated
	CA_ALWAYS_FLEE             = 17, // Ped will always flee upon getting threat response task
	CA_CAN_TAUNT_IN_VEHICLE    = 20, // Ped can do unarmed taunts in vehicle
	CA_CAN_CHASE_TARGET_ON_FOOT = 21, // Ped will be able to chase their targets if both are on foot and the target is running away
	CA_WILL_DRAG_INJURED_PEDS_TO_SAFETY = 22, // Ped can drag injured peds to safety
	CA_REQUIRES_LOS_TO_SHOOT            = 23, // Ped will require LOS to the target it is aiming at before shooting
	CA_USE_PROXIMITY_FIRING_RATE = 24, // Ped is allowed to use proximity based fire rate (increasing fire rate at closer distances)
	CA_DISABLE_SECONDARY_TARGET = 25, // Normally peds can switch briefly to a secondary target in combat, setting this will prevent that
	CA_DISABLE_ENTRY_REACTIONS = 26, // This will disable the flinching combat entry reactions for peds, instead only playing the turn and aim anims
	CA_PERFECT_ACCURACY = 27, // Force ped to be 100% accurate in all situations (added by Jay Reinebold)
	CA_CAN_USE_FRUSTRATED_ADVANCE = 28, // If we don't have cover and can't see our target it's possible we will advance, even if the target is in cover
	CA_MOVE_TO_LOCATION_BEFORE_COVER_SEARCH = 29, // This will have the ped move to defensive areas and within attack windows before performing the cover search
	CA_CAN_SHOOT_WITHOUT_LOS = 30, // Allow shooting of our weapon even if we don't have LOS (this isn't X-ray vision as it only affects weapon firing)
	CA_MAINTAIN_MIN_DISTANCE_TO_TARGET = 31, // Ped will try to maintain a min distance to the target, even if using defensive areas (currently only for cover finding + usage)
	CA_CAN_USE_PEEKING_VARIATIONS = 34,      // Allows ped to use steamed variations of peeking anims
	CA_DISABLE_PINNED_DOWN        = 35,      // Disables pinned down behaviors
	CA_DISABLE_PIN_DOWN_OTHERS    = 36,      // Disables pinning down others
	CA_OPEN_COMBAT_WHEN_DEFENSIVE_AREA_IS_REACHED = 37, // When defensive area is reached the area is cleared and the ped is set to use defensive combat movement
	CA_DISABLE_BULLET_REACTIONS          = 38, // Disables bullet reactions
	CA_CAN_BUST                          = 39, // Allows ped to bust the player
	CA_IGNORED_BY_OTHER_PEDS_WHEN_WANTED = 40, // This ped is ignored by other peds when wanted
	CA_CAN_COMMANDEER_VEHICLES = 41, // Ped is allowed to "jack" vehicles when needing to chase a target in combat
	CA_CAN_FLANK               = 42, // Ped is allowed to flank
	CA_SWITCH_TO_ADVANCE_IF_CANT_FIND_COVER      = 43, // Ped will switch to advance if they can't find cover
	CA_SWITCH_TO_DEFENSIVE_IF_IN_COVER           = 44, // Ped will switch to defensive if they are in cover
	CA_CLEAR_PRIMARY_DEFENSIVE_AREA_WHEN_REACHED = 45, // Ped will clear their primary defensive area when it is reached
	CA_CAN_FIGHT_ARMED_PEDS_WHEN_NOT_ARMED       = 46, // Ped is allowed to fight armed peds when not armed
	CA_ENABLE_TACTICAL_POINTS_WHEN_DEFENSIVE = 47, // Ped is not allowed to use tactical points if set to use defensive movement (will only use cover)
	CA_DISABLE_COVER_ARC_ADJUSTMENTS = 48, // Ped cannot adjust cover arcs when testing cover safety (atm done on corner cover points when  ped usingdefensive area + no LOS)
	CA_USE_ENEMY_ACCURACY_SCALING = 49, // Ped may use reduced accuracy with large number of enemies attacking the same local player target
	CA_CAN_CHARGE = 50, // Ped is allowed to charge the enemy position
	CA_REMOVE_AREA_SET_WILL_ADVANCE_WHEN_DEFENSIVE_AREA_REACHED = 51, // When defensive area is reached the area is cleared and the ped is set to use will advance movement
	CA_USE_VEHICLE_ATTACK = 52, // Use the vehicle attack mission during combat (only works on driver)
	CA_USE_VEHICLE_ATTACK_IF_VEHICLE_HAS_MOUNTED_GUNS = 53, // Use the vehicle attack mission during combat if the vehicle has mounted guns (only works on driver)
	CA_ALWAYS_EQUIP_BEST_WEAPON = 54,           // Always equip best weapon in combat
	CA_CAN_SEE_UNDERWATER_PEDS  = 55,           // Ignores in water at depth visibility check
	CA_DISABLE_AIM_AT_AI_TARGETS_IN_HELIS = 56, // Will prevent this ped from aiming at any AI targets that are in helicopters
	CA_DISABLE_SEEK_DUE_TO_LINE_OF_SIGHT = 57, // Disables peds seeking due to no clear line of sight
	CA_DISABLE_FLEE_FROM_COMBAT = 58, // To be used when releasing missions peds if we don't want them fleeing from combat (mission peds already prevent flee)
	CA_DISABLE_TARGET_CHANGES_DURING_VEHICLE_PURSUIT = 59, // Disables target changes during vehicle pursuit
	CA_CAN_THROW_SMOKE_GRENADE = 60, // Ped may throw a smoke grenade at player loitering in combat
	CA_CLEAR_AREA_SET_DEFENSIVE_IF_DEFENSIVE_CANNOT_BE_REACHED = 62, // Will clear a set defensive area if that area cannot be reached
	CA_DISABLE_BLOCK_FROM_PURSUE_DURING_VEHICLE_CHASE = 64, // Disable block from pursue during vehicle chases
	CA_DISABLE_SPIN_OUT_DURING_VEHICLE_CHASE          = 65, // Disable spin out during vehicle chases
	CA_DISABLE_CRUISE_IN_FRONT_DURING_BLOCK_DURING_VEHICLE_CHASE = 66, // Disable cruise in front during block during vehicle chases
	CA_CAN_IGNORE_BLOCKED_LOS_WEIGHTING = 67, // Makes it more likely that the ped will continue targeting a target with blocked los for a few seconds
	CA_DISABLE_REACT_TO_BUDDY_SHOT                   = 68, // Disables the react to buddy shot behaviour.
	CA_PREFER_NAVMESH_DURING_VEHICLE_CHASE           = 69, // Prefer pathing using navmesh over road nodes
	CA_ALLOWED_TO_AVOID_OFFROAD_DURING_VEHICLE_CHASE = 70, // Ignore road edges when avoiding
	CA_PERMIT_CHARGE_BEYOND_DEFENSIVE_AREA = 71, // Permits ped to charge a target outside the assigned defensive area.
	CA_USE_ROCKETS_AGAINST_VEHICLES_ONLY = 72, // This ped will switch to an RPG if target is in a vehicle, otherwise will use alternate weapon.
	CA_DISABLE_TACTICAL_POINTS_WITHOUT_CLEAR_LOS   = 73, // Disables peds moving to a tactical point without clear los
	CA_DISABLE_PULL_ALONGSIDE_DURING_VEHICLE_CHASE = 74, // Disables pull alongside during vehicle chase
	CA_DISABLE_ALL_RANDOMS_FLEE = 78, // If set on a ped, they will not flee when all random peds flee is set to TRUE (they are still able to flee due to other reasons)
	CA_WILL_GENERATE_DEAD_PED_SEEN_SCRIPT_EVENTS = 79, // This ped will send out a script DeadPedSeenEvent when they see a dead ped
	CA_USE_MAX_SENSE_RANGE_WHEN_RECEIVING_EVENTS = 80, // This will use the receiving peds sense range rather than the range supplied to the communicate event
	CA_RESTRICT_IN_VEHICLE_AIMING_TO_CURRENT_SIDE = 81, // When aiming from a vehicle the ped will only aim at targets on his side of the vehicle
	CA_USE_DEFAULT_BLOCKED_LOS_POSITION_AND_DIRECTION = 82, // LOS to the target is blocked we return to our default position and direction until we have LOS (no aiming)
	CA_REQUIRES_LOS_TO_AIM = 83, // LOS to the target is blocked we return to our default position and direction until we have LOS (no aiming)
	CA_CAN_CRUISE_AND_BLOCK_IN_VEHICLE = 84, // Allow vehicles spawned infront of target facing away to enter cruise and wait to block approaching target
	CA_PREFER_AIR_COMBAT_WHEN_IN_AIRCRAFT = 85, // Peds flying aircraft will prefer to target other aircraft over entities on the ground
	CA_ALLOW_DOG_FIGHTING = 86,                 //Allow peds flying aircraft to use dog fighting behaviours
	CA_PREFER_NON_AIRCRAFT_TARGETS = 87, // This will make the weight of targets who aircraft vehicles be reduced greatly compared to targets on foot or in ground based vehicles
	CA_PREFER_KNOWN_TARGETS_WHEN_COMBAT_CLOSEST_TARGET = 88, //When peds are tasked to go to combat, they keep searching for a known target for a while before forcing an unknown one
	CA_FORCE_CHECK_ATTACK_ANGLE_FOR_MOUNTED_GUNS = 89, // Only allow mounted weapons to fire if within the correct attack angle (default 25-degree cone). On a flag in order to keep exiting behaviour and only fix in specific cases.
	CA_BLOCK_FIRE_FOR_VEHICLE_PASSENGER_MOUNTED_GUNS = 90 // Blocks the firing state for passenger-controlled mounted weapons. Existing flags CA_USE_VEHICLE_ATTACK and CA_USE_VEHICLE_ATTACK_IF_VEHICLE_HAS_MOUNTED_GUNS only work for drivers.
};

enum class ePedConfigFlags
{
	PCF_AllowMedicsToAttend = 20, // If this ped dies medics will be dispatched, false by default for mission peds, the ped wont be revived
	PCF_DontAllowToBeDraggedOutOfVehicle = 26, // Prevents a ped from being able to be dragged out of a car
	PCF_GetOutUndriveableVehicle = 29, // Script can stop peds automatically getting out of car when it's upside down or undrivable, defaults to true
	PCF_WillFlyThroughWindscreen = 32, // Ped will fly through the vehicle windscreen upon a forward impact at high velocity
	PCF_HasHelmet = 34, // Ped has a helmet (/ The PedHelmetComponent has put the helmet on the ped via "put on" animations)
	PCF_DontTakeOffHelmet = 36, // Disable the ped taking off his helmet automatically
	PCF_DontInfluenceWantedLevel = 42, // Can do any crime against this character and the cops turn a blind eye (no crime reported)
	PCF_DisableLockonToRandomPeds    = 44, // Disable lockon to random ambient peds
	PCF_AllowLockonToFriendlyPlayers = 45,
	PCF_DisableHornAudioWhenDead = 46, // Disable horn audio when the ped dies and rests his head on top of the steering wheel
	PCF_IsAimingGun = 78,              // Is set when a ped is performing an aim task
	PCF_ForcedAim = 101, // If set, we will always behave like we have the aim trigger pressed, also works for AI in cars
	PCF_OpenDoorArmIK                        = 104, // Set if the ped should enable open door arm IK
	PCF_DontActivateRagdollFromVehicleImpact = 106, // Blocks ragdoll activation when hit by a vehicle
	PCF_DontActivateRagdollFromBulletImpact  = 107, // Blocks ragdoll activation when hit by a bullet
	PCF_DontActivateRagdollFromExplosions    = 108, // Blocks ragdoll activation when hit by an explosive
	PCF_DontActivateRagdollFromFire          = 109, // Blocks ragdoll activation when set on fire
	PCF_DontActivateRagdollFromElectrocution = 110, // Blocks ragdoll activation when electrocuted
	PCF_KeepWeaponHolsteredUnlessFired = 113, // Will keep the peds weapon holstered until they shoot or change weapons
	PCF_ForceControlledKnockout        = 114, // Forces a melee knockout state for the victim ped
	PCF_FallsOutOfVehicleWhenKilled = 115, // Forces a ped in a vehicle to collapse out onto the floor (TaskDyingDead launches TaskExitVehicle)
	PCF_GetOutBurningVehicle = 116, // If set, a ped will escape a burning vehicle they are inside, defaults to true
	PCF_RunFromFiresAndExplosions = 118, // If set, a ped will escape a burning vehicle they are inside, defaults to true
	PCF_TreatAsPlayerDuringTargeting = 119, // If set, the ped will be given the same boost a player gets in the targeting scoring system
	PCF_DisableMelee           = 122,            // Disable melee for a ped (only supported for player right now)
	PCF_DisableUnarmedDrivebys = 123,            // Disable unarmed driveby taunts for a ped
	PCF_JustGetsPulledOutWhenElectrocuted = 124, // MP only - if this ped is tased or rubber bulleted in a vehicle and a ped jacks them, the jacker will only pull the ped out
	PCF_WillNotHotwireLawEnforcementVehicle = 126, // If set, the ped won't hotwire a lawenforcement vehicle
	PCF_WillCommandeerRatherThanJack = 127, // If set, the ped will play commandeering anims rather than jacking if available
	PCF_CanBeAgitated              = 128, // If set, the ped can be agitated
	PCF_ForcePedToFaceLeftInCover  = 129, // If set ped will turn to face left in cover
	PCF_ForcePedToFaceRightInCover = 130, // If set ped will turn to face right in cover
	PCF_BlockPedFromTurningInCover = 131, // If set ped will not turn in cover, unless one of the force flags is set
	PCF_KeepRelationshipGroupAfterCleanUp = 132, // Ped keeps their relationship group when the mission is cleaned up or they are marked as no longer needed
	PCF_ForcePedToBeDragged = 133, // Ped will loop the try locked door anim when they get to the door in order for them to automatically be dragged along
	PCF_PreventPedFromReactingToBeingJacked = 134, // Ped doesn't react when being jacked
	PCF_RemoveDeadExtraFarAway = 137, // We must be further away before ped polulation remove this ped when it is dead
	PCF_ArrestResult           = 139, // If set, the ped arrest task completed successfully
	PCF_CanAttackFriendly      = 140, // True allows this ped to attack peds they are friendly with
	PCF_WillJackAnyPlayer = 141, // MP only, if set this ped will be allowed to jack any player peds, regardless of relationship
	PCF_WillJackWantedPlayersRatherThanStealCar = 144, //MP only, True if this player will jack hated players rather than try to steal a car (cops arresting crims)
	PCF_DisableLadderClimbing = 146, // If this flag is set on a ped it will not scan for or climb ladders
	PCF_CowerInsteadOfFlee    = 150, // If set the ped should cower instead of fleeing
	PCF_CanActivateRagdollWhenVehicleUpsideDown = 151, //If set the ped will be allowed to ragdoll when the vehicle they are in gets turned upside down if the seat supports it
	PCF_AlwaysRespondToCriesForHelp = 152, // If set the ped will respond to cries for help even if not friends with the injured ped.
	PCF_DisableBloodPoolCreation = 153, // If set the ped will not create a blood pool when dead
	PCF_ShouldFixIfNoCollision   = 154, // If set, the ped will be fixed if there is no collision around.
	PCF_CanPerformArrest         = 155, // If set, the ped can perform arrests on peds that can be arrested
	PCF_CanPerformUncuff         = 156, // If set, the ped can uncuff peds that are handcuffed
	PCF_CanBeArrested            = 157, // If set, the ped can be arrested
	PCF_PlayerPreferFrontSeatMP  = 159, // When true, Prefer the front seat when getting in a car with buddies.
	PCF_DontEnterVehiclesInPlayersGroup = 167, // When true, will follow the player around if in their group but wont enter vehicles.
	PCF_CannotBeTargeted      = 169, // DEPRECATED - Use the reset flag instead
	PCF_PreventAllMeleeTaunts = 169, // Disable all melee taunts for this particular ped
	PCF_ForceDirectEntry = 170, // Will force this ped to use the direct entry point for any vehicle they try to enter, or warp in
	PCF_AlwaysSeeApproachingVehicles       = 171, // This ped will always see approaching vehicles (even from behind).
	PCF_CanDiveAwayFromApproachingVehicles = 172, // This ped can dive away from approaching vehicles.
	PCF_AllowPlayerToInterruptVehicleEntryExit = 173, // Will allow player to interrupt a peds scripted entry/exit task as if they had triggered it themselves
	PCF_OnlyAttackLawIfPlayerIsWanted = 174, // This ped will only attack cops if the player is wanted
	PCF_PedsJackingMeDontGetIn        = 177, // If set the ped will not get in as part of the jack
	PCF_PedIgnoresAnimInterruptEvents = 179, // AI peds only, will not early out of anims, default behaviour is to exit as early as possible
	PCF_IsInCustody = 180, // Any targeting LoS checks will fail if any materials with 'see through' materials found.
	PCF_ForceStandardBumpReactionThresholds = 181, // Setting this on an armed or buddy ped will make him more likely to perform an nm reaction when bumped by a player, friendly vehicle or ragdolling ped.
	PCF_LawWillOnlyAttackIfPlayerIsWanted = 182, // If set on a ped, law peds will only attack if the local player is wanted
	PCF_PreventAutoShuffleToDriversSeat = 184, // Prevents passenger from auto shuffling over to drivers seat if it becomes free
	PCF_UseKinematicModeWhenStationary = 185, // When enabled, the ped will continually set the kinematic mode reset flag when stationary.
	PCF_DisableHurt   = 188, // Set to disable the combat hurt mode
	PCF_PlayerIsWeird = 189, // Should this player ped periodically generate shocking events for being weird
	PCF_DoNothingWhenOnFootByDefault = 193, // Do nothing when on foot, by default
	PCF_DontReactivateRagdollOnPedCollisionWhenDead = 198, // Peds with this flag set won't be allowed to reactivate their ragdoll when hit by another ragdoll.
	PCF_DontActivateRagdollOnVehicleCollisionWhenDead = 199, // Peds with this flag set won't be allowed to reactivate their ragdoll when hit by a vehicle.
	PCF_HasBeenInArmedCombat       = 200, // True if we've ever been in non-melee combat
	PCF_Avoidance_Ignore_All       = 202, // True if we never steer around peds
	PCF_Avoidance_Ignored_by_All   = 203, // True if peds never steer around us
	PCF_Avoidance_Ignore_Group1    = 204, // True if we steer around peds that are members of group 1
	PCF_Avoidance_Member_of_Group1 = 205, // True if we are members of avoidance group 1
	PCF_ForcedToUseSpecificGroupSeatIndex = 206, // Ped is forced to use specific seat index set by SET_PED_GROUP_MEMBER_PASSENGER_INDEX
	PCF_DisableExplosionReactions = 208,        // If set, ped will ignore explosion events
	PCF_WaitingForPlayerControlInterrupt = 210, // Set when player switches to an ai ped and keeps the scripted task of the ai ped, if unset we won't check for interrupts or time out
	PCF_ForcedToStayInCover  = 211, // If set, ped will stay in cover (won't come out to fire or move out during combat)
	PCF_GeneratesSoundEvents = 212, // Does this ped generate sound events?
	PCF_ListensToSoundEvents = 213, // Does this ped have the ability to respond to sound events?
	PCF_AllowToBeTargetedInAVehicle = 214, // Ped can be targeting inside a vehicle
	PCF_WaitForDirectEntryPointToBeFreeWhenExiting = 215, // When exiting a vehicle, the ped will wait for the direct entry point to be clear before exiting
	PCF_OnlyRequireOnePressToExitVehicle = 216, // Player doesn't need to hold exit button to exit vehicles
	PCF_ForceExitToSkyDive               = 217, // Force the skydive exit if we're exiting the vehicle
	PCF_DisableExitToSkyDive             = 221, // Disable the skydive exit if we're exiting the vehicle
	PCF_DisablePedAvoidance              = 226, // This ped will not avoid other peds whilst navigating
	PCF_ForceRagdollUponDeath = 227, // When the ped dies, it will ragdoll instead of potentially choosing an animated death
	PCF_DisablePanicInVehicle            = 229, // Disable panic in vehicle
	PCF_AllowedToDetachTrailer           = 230, // Allow this ped to detach trailers from vehicles
	PCF_ForceSkinCharacterCloth          = 240, // ForceSkin character cloth on creation when flag is set
	PCF_LeaveEngineOnWhenExitingVehicles = 241, // Player will leave the engine on when exiting a vehicle normally
	PCF_PhoneDisableTextingAnimations = 242, // tells taskmobile phone to not texting animations.  Currently don't play these in MP
	PCF_PhoneDisableTalkingAnimations = 243, // tells taskmobile phone to not talking animations.  Currently don't play these in MP
	PCF_PhoneDisableCameraAnimations = 244, // tells taskmobile phone to not camera animations.  Currently don't play these in SP
	PCF_DisableBlindFiringInShotReactions = 245, // Stops the ped from accidentally firing his weapon when shot.
	PCF_AllowNearbyCoverUsage = 246, // This makes it so that OTHER peds are allowed to take cover at points that would otherwise be rejected due to proximity
	PCF_CanAttackNonWantedPlayerAsLaw = 249, // If this ped is a law enforcement ped then we will NOT quit combat due to a target player no longer having a wanted level
	PCF_WillTakeDamageWhenVehicleCrashes = 250, // If set, this ped will take damage if the car they are in crashes
	PCF_AICanDrivePlayerAsRearPassenger = 251, // If this ai ped is driving the vehicle, if the player taps to enter, they will enter as a rear passenger, if they hold, they'll jack the driver
	PCF_PlayerCanJackFriendlyPlayers = 252, // If a friendly player is driving the vehicle, if the player taps to enter, they will enter as a passenger, if they hold, they'll jack the driver
	PCF_AIDriverAllowFriendlyPassengerSeatEntry = 255, // If this ai ped is driving the vehicle, allow players to get in passenger seats
	PCF_AllowMissionPedToUseInjuredMovement = 259, // Set the target ped to be allowed to use Injured movement clips
	PCF_PreventUsingLowerPrioritySeats      = 261, // Don't use certain seats (like hanging on the side of a vehicle)
	PCF_TeleportToLeaderVehicle = 268, // If set, teleport if ped is not in the leader's vehicle before TaskEnterVehicle::m_SecondsBeforeWarpToLeader.
	PCF_Avoidance_Ignore_WeirdPedBuffer = 269, // Don't walk extra far around weird peds like trevor
	PCF_DontBlipCop                     = 272, // Don't add a blip for this cop
	PCF_KillWhenTrapped                 = 275, // Kill this ped if it becomes trapped and cannot get up
	PCF_AvoidTearGas                    = 279, // If set, this ped will avoid tear gas
	PCF_DisableGoToWritheWhenInjured = 281, // If set, CPed::DAMAGED_GOTOWRITHE will no longer get set.  In particular, tazer hits wil no longer kill this ped in one hit
	PCF_OnlyUseForcedSeatWhenEnteringHeliInGroup = 282, // If set this ped will only use their forced seat index if the vehicle they're entering is a heli as part of a group
	PCF_DisableWeirdPedEvents = 285, // Disables weird ped events
	PCF_ShouldChargeNow = 286, // This ped should charge if in combat right away, for use by scripts, cleared once ped charges
	PCF_DisableShockingEvents                  = 294, // This ped should ignore shocking events.
	PCF_NeverReactToPedOnRoof                  = 296, // If true, this ped will not react to a ped standing on the roof
	PCF_DisableShockingDrivingOnPavementEvents = 299, // If true, this ped will not react to peds driving on pavement
	PCF_ShouldThrowSmokeGrenadeNow = 300, // This ped should throw a smoke grenade in combat right away, for use by scripts, cleared once ped throws
	PCF_ForceInitialPeekInCover = 302, // If set, ped will peek once before firing in cover. Cleared upon peeking.
	PCF_DisableJumpingFromVehiclesAfterLeader = 305, // If true, disable followers jumping out of cars after their group leader
	PCF_ShoutToGroupOnPlayerMelee = 311, // If set, ped will shout target position when melee attacked by a player
	PCF_IgnoredByAutoOpenDoors = 312, // Set this for a ped to be ignored by the auto opened doors when checking to see if the door should be opened.
	PCF_ForceIgnoreMeleeActiveCombatant = 314, // Purposely ignore the melee active combatant role and push them into a support or inactive combatant role
	PCF_CheckLoSForSoundEvents      = 315, // If set, ped will ignore sound events generated by entites it can't see.
	PCF_CanSayFollowedByPlayerAudio = 317, // If set, ped can play FRIEND_FOLLOWED_BY_PLAYER lines.
	PCF_ActivateRagdollFromMinorPlayerContact = 318, // If set, the ped will activate ragdoll much more easily on contact with the player
	PCF_ForcePoseCharacterCloth = 320, // Default cloth pose will be applied if is available in the character cloth when the cloth is created
	PCF_HasClothCollisionBounds = 321, // Ped has cloth collision bounds
	PCF_DontBehaveLikeLaw = 324, // If set on a non-law ped that has law like behavior (i.e. security) then that ped will not use the law like behaviors/logic
	PCF_DisablePoliceInvestigatingBody = 326, // If set, police will not perform the CTaskShockingPoliceInvestigate behavior on the ped
	PCF_DisableWritheShootFromGround = 327, // If set, the ped will no longer shoot while writhing
	PCF_LowerPriorityOfWarpSeats = 328, // If set the ped will only just the warp entry points if there are no animated entry points available
	PCF_DisableTalkTo           = 329, // If set the ped can't be talked to
	PCF_DontBlip                = 330, // If set the ped will not be blipped by the wanted system
	PCF_IgnoreLegIkRestrictions = 332, // If set, the ped will ignore leg IK request restrictions for non-player peds
	PCF_ForceNoTimesliceIntelligenceUpdate = 333, // If set, the ped will never have their intelligence update time sliced across frames.
	PCF_AllowTaskDoNothingTimeslicing = 339, // If set, this ped will timeslice it's DoNothing Task when computing default task.
	PCF_NotAllowedToJackAnyPlayers = 342, // If set, this ped will not be allowed to jack any other players (not synced)
	PCF_AlwaysLeaveTrainUponArrival = 345, // If set, this ped will always exit the train when it stops at a station.
	PCF_OnlyWritheFromWeaponDamage = 347, // If set, Only allow ped to wrothe from weapon damage, not from other stuff, like small vehicle impacts
	PCF_UseSloMoBloodVfx = 348, // If set, this ped will use slo mo blood vfx instead of the normal ones (these effects must be included in the script particle asset)
	PCF_PreventDraggedOutOfCarThreatResponse = 350, // Don't do threat response when dragged out of a car
	PCF_ForceDeepSurfaceCheck = 356, // Don't do distance from camera culling of the deep surface check, needed for detecting snow, mud, etc.
	PCF_DisableDeepSurfaceAnims = 357, // Disable deep surface anims to prevent them slowing ped down.
	PCF_DontBlipNotSynced = 358, // If set the ped will not be blipped by the wanted system, this will not be synced and be set on clones so the behaviour can be changed per player
	PCF_IsDuckingInVehicle = 359, // Query only, see if the ped is ducking in a vehicle
	PCF_PreventAutoShuffleToTurretSeat = 360, // If set the ped will not automatically shuffle to the turret seat when it becomes free
	PCF_DisableEventInteriorStatusCheck = 361, // Disables the ignore events based on interior status check which normally has peds inside ignore events from outside
	PCF_TreatDislikeAsHateWhenInCombat = 364, // If the ped this is set on is in combat then any dislike feeling they have towards other peds will be treated as a hate feeling
	PCF_OnlyUpdateTargetWantedIfSeen = 365, // Law with this set will only update the WL is the target player is seen. This includes on combat initialization as well as during normal LOS checks (ignoring "last known position" reports)
	PCF_AllowAutoShuffleToDriversSeat = 366, // Allows this ped to auto shuffle to the driver seat of a vehicle if the driver is dead (law and MP peds would do this normally)
	PCF_PreventReactingToSilencedCloneBullets = 372, // If set prevents the ped from reacting to silenced bullets fired from network clone peds (use for peds where stealth kills are important)
	PCF_DisableInjuredCryForHelpEvents = 373, // Blocks ped from creating the injured cry for help events (run over, tazed or melee would usually do this)
	PCF_NeverLeaveTrain        = 374, // Prevents peds riding trains from getting off them
	PCF_DontDropJetpackOnDeath = 375, // Prevents ped dropping jetpack when they die
	PCF_DisableAutoEquipHelmetsInBikes = 380, // Prevents ped from auto-equipping helmets when entering a bike (includes quadbikes)
	PCF_DisableAutoEquipHelmetsInAicraft = 381, // Prevents ped from auto-equipping helmets when entering an aircraft
	PCF_HasBareFeet         = 389, // Flag to indicate that player has no shoes(used for first person aiming camera)
	PCF_UNUSED_REPLACE_ME_2 = 390, //
	PCF_GoOnWithoutVehicleIfItIsUnableToGetBackToRoad = 391, // It will force the ped to abandon its vehicle (when using TaskGoToPointAnyMeans) if it is unable to get back to road
	PCF_BlockDroppingHealthSnacksOnDeath = 392, // This will block health pickups from being created when the ped dies.
	PCF_ForceThreatResponseToNonFriendToFriendMeleeActions = 394, // Forces threat response to melee actions from non friend to friend peds.
	PCF_DontRespondToRandomPedsDamage = 395,                      // Do not respond to random peds damage.
	PCF_AllowContinuousThreatResponseWantedLevelUpdates = 396, // Shares the same logic of PCF_OnlyUpdateTargetWantedIfSeen but will continue to check even after the initial WL is set
	PCF_KeepTargetLossResponseOnCleanup = 397, // The target loss response will not be reset to exit task on cleanup if this is set
	PCF_PlayersDontDragMeOutOfCar = 398, // Similar to DontDragMeOutCar except it will still allow AI to drag the ped out of a vehicle
	PCF_BroadcastRepondedToThreatWhenGoingToPointShooting = 399, // Whenever the ped starts shooting while going to a point, it trigger a responded to threat broadcast
	PCF_IgnorePedTypeForIsFriendlyWith = 400, // If this is set then IsFriendlyWith will ignore the ped type checks (i.e. two PEDTYPE_COP peds are not automatically friendly)
	PCF_TreatNonFriendlyAsHateWhenInCombat = 401, // Any non friendly ped will be considered as hated instead when in combat
	PCF_DontLeaveVehicleIfLeaderNotInVehicle = 402, // Supresses "LeaderExistedCarAsDriver" events. Ped won't exit vehicle if leader isn't in it as well.
	PCF_AllowMeleeReactionIfMeleeProofIsOn = 404,           //Allow melee reaction to come through even if proof is on
	PCF_UseNormalExplosionDamageWhenBlownUpInVehicle = 407, // If this is set, ped won't be instantly killed if vehicle is blown up. Instead, they will take normal explosive damage and be forced to exit the vehicle if they're still alive.
	PCF_DisableHomingMissileLockForVehiclePedInside = 408,  // Blocks locking on of the vehicle that the ped is inside.
	PCF_DisableTakeOffScubaGear = 409, // Disable taking off the scuba gear. Same as PRF_DisableTakeOffScubaGear but on a config flag.
	PCF_IgnoreMeleeFistWeaponDamageMult = 410, // Melee fist weapons (ie knuckle duster) won't apply relative health damage scaler (MeleeRightFistTargetHealthDamageScaler in weapon info).
	PCF_LawPedsCanFleeFromNonWantedPlayer = 411, // Law peds will be triggered to flee if player triggers an appropriate event (even if ped is not wanted) instead of entering combat. NB: Only synced over the network when set on players.
	PCF_ForceBlipSecurityPedsIfPlayerIsWanted = 412, // Forces security peds (not cop peds) to be blipped on the minimap if the player is wanted. Set this on the local player.
	PCF_UseGoToPointForScenarioNavigation = 414, // Don't use nav mesh for navigating to scenario points. DLC Hack for yachts
	PCF_DontClearLocalPassengersWantedLevel = 415, // Don't clear local ped's wanted level when remote ped in the same car has his wanted level cleared by script.
	PCF_BlockAutoSwapOnWeaponPickups  = 416, // Block auto weapon swaps for weapon pickups.
	PCF_ThisPedIsATargetPriorityForAI = 417, // Increase AI targeting score for peds with this flag.
	PCF_IsSwitchingHelmetVisor        = 418, // Indicates ped is using switch helmet visor up/down anim
	PCF_ForceHelmetVisorSwitch        = 419, // Indicates ped is using switch helmet visor up/down anim
	PCF_UseOverrideFootstepPtFx = 421, // Overrides ped footstep particle effects with the overriden footstep effect
	PCF_DisableVehicleCombat    = 422, // Disables vehicle combat.
	PCF_AllowBikeAlternateAnimations      = 424, // Allows transition into bike alternate animations (PI menu option)
	PCF_UseLockpickVehicleEntryAnimations = 426, // Use Franklin's alternate lockpicking animations for forced entry
	PCF_IgnoreInteriorCheckForSprinting = 427, // When set, player will be able to sprint inside interriors even if it is tagged to prevent it.
	PCF_SwatHeliSpawnWithinLastSpottedLocation = 428, // When set, swat helicopters will spawn within last spotted location instead of actual ped location (and target is a player)
	PCF_DisableStartEngine = 429, // Prevents ped from playing start engine anims (and turning engine on)
	PCF_IgnoreBeingOnFire  = 430, // Makes ped ignore being on fire (fleeing, reacting to CEventOnFire event)
	PCF_DisableTurretOrRearSeatPreference = 431, // Disables turret seat and activity seat preference for vehicle entry for local player
	PCF_DisableWantedHelicopterSpawning = 432, // Will not spawn wanted helicopters to chase after this target
	PCF_UseTargetPerceptionForCreatingAimedAtEvents = 433, // Will only create aimed at events if player is within normal perception of the target
	PCF_DisableHomingMissileLockon = 434,                 // Will prevent homing lockon on this ped
	PCF_ForceIgnoreMaxMeleeActiveSupportCombatants = 435, //Ignore max number of active support combatants and let ped join them as such
	PCF_StayInDefensiveAreaWhenInVehicle = 436, // Will try to stay within set defensive area while driving a vehicle
	PCF_DontShoutTargetPosition = 437, // Will prevent the ped from communicating target position to all other friendly peds
	PCF_DisableHelmetArmor = 438, // Will apply full headshot damage, regardless if ped has a helmet (or armored one)
	PCF_PreventVehExitDueToInvalidWeapon = 441, // Will prevent ped from automatically being forced out of vehicle due to weapon being invalid (e.g. turret seats after going into water)
	PCF_IgnoreNetSessionFriendlyFireCheckForAllowDamage = 442, // Will ignore the friendly fire setting set by NETWORK_SET_FRIENDLY_FIRE_OPTION when checking if ped can be damaged
	PCF_DontLeaveCombatIfTargetPlayerIsAttackedByPolice = 443, // Will make ped stay in combat even if the player hes targeting starts being attacked by cops
	PCF_CheckLockedBeforeWarp = 444, // Will check when entering a vehicle if it is locked before warping
	PCF_DontShuffleInVehicleToMakeRoom = 445, // Will prevent a player from shuffling across to make room if another player is entering from the same side
	PCF_GiveWeaponOnGetup = 446, // Will give the ped a weapon to use once their weapon is removed for getups
	PCF_DontHitVehicleWithProjectiles = 447, // Ped fired projectiles will ignore the vehicle they are in
	PCF_DisableForcedEntryForOpenVehiclesFromTryLockedDoor = 448, // Will prevent ped from forcing entry into cars that are open from TryLockedDoor state
	PCF_FiresDummyRockets = 449, // his ped will fire rockets that explode when close to its target, and won't affect it
	PCF_DecoyPed          = 451, // Will make this ped a decoy ped that will focus targeting
	PCF_HasEstablishedDecoy = 452,                   // This ped has created a decoy
	PCF_BlockDispatchedHelicoptersFromLanding = 453, // Will prevent dispatched helicopters from landing and dropping off peds
	PCF_DontCryForHelpOnStun      = 454, // Will prevent peds from crying for help when shot with the stun gun
	PCF_CanBeIncapacitated        = 456, // If set, the ped may be incapacitated
	PCF_DontChangeTargetFromMelee = 458, // If set, we wont set a new target after a melee attack
	PCF_RagdollFloatsIndefinitely = 460, // Prevents a dead ped from sinking
	PCF_BlockElectricWeaponDamage = 461  // Blocks electric weapon damage
};

enum class eDrivingMode
{
	DF_StopForCars               = 1,
	DF_StopForPeds               = 2,
	DF_SwerveAroundAllCars       = 4,
	DF_SteerAroundStationaryCars = 8,
	DF_SteerAroundPeds           = 16,
	DF_SteerAroundObjects        = 32,
	DF_DontSteerAroundPlayerPed  = 64,
	DF_StopAtLights              = 128,
	DF_GoOffRoadWhenAvoiding     = 256,
	DF_DriveIntoOncomingTraffic  = 512,
	DF_DriveInReverse            = 1024,

	//if pathfinding fails, cruise randomly instead of going on a straight line
	DF_UseWanderFallbackInsteadOfStraightLine = 2048,

	DF_AvoidRestrictedAreas = 4096,

	// These only work on MISSION_CRUISE
	DF_PreventBackgroundPathfinding      = 8192,
	DF_AdjustCruiseSpeedBasedOnRoadSpeed = 16384,

	DF_UseShortCutLinks              = 262144,
	DF_ChangeLanesAroundObstructions = 524288,
	DF_UseSwitchedOffNodes           = 2097152, //cruise tasks ignore this anyway--only used for goto's
	DF_PreferNavmeshRoute            = 4194304, //if you're going to be primarily driving off road

	// Only works for planes using MISSION_GOTO, will cause them to drive along the ground instead of fly
	DF_PlaneTaxiMode = 8388608,

	DF_ForceStraightLine           = 16777216,
	DF_UseStringPullingAtJunctions = 33554432,

	DF_AvoidHighways            = 536870912,
	DF_ForceJoinInRoadDirection = 1073741824,

	//standard driving mode. stops for cars, peds, and lights, goes around stationary obstructions
	DRIVINGMODE_STOPFORCARS = 786603, //DF_StopForCars|DF_StopForPeds|DF_SteerAroundObjects|DF_SteerAroundStationaryCars|DF_StopAtLights|DF_UseShortCutLinks|DF_ChangeLanesAroundObstructions,		// Obey lights too

	//like the above, but doesn't steer around anything in its way--will only wait instead.
	DRIVINGMODE_STOPFORCARS_STRICT = 262275, //DF_StopForCars|DF_StopForPeds|DF_StopAtLights|DF_UseShortCutLinks,		// Doesn't deviate an inch.

	//default "alerted" driving mode. drives around everything, doesn't obey lights
	DRIVINGMODE_AVOIDCARS = 786469, //DF_SwerveAroundAllCars|DF_SteerAroundObjects|DF_UseShortCutLinks|DF_ChangeLanesAroundObstructions|DF_StopForCars,

	//very erratic driving. difference between this and AvoidCars is that it doesn't use the brakes at ALL to help with steering
	DRIVINGMODE_AVOIDCARS_RECKLESS = 786468, //DF_SwerveAroundAllCars|DF_SteerAroundObjects|DF_UseShortCutLinks|DF_ChangeLanesAroundObstructions,

	//smashes through everything
	DRIVINGMODE_PLOUGHTHROUGH = 262144, //DF_UseShortCutLinks

	//drives normally except for the fact that it ignores lights
	DRIVINGMODE_STOPFORCARS_IGNORELIGHTS = 786475, //DF_StopForCars|DF_SteerAroundStationaryCars|DF_StopForPeds|DF_SteerAroundObjects|DF_UseShortCutLinks|DF_ChangeLanesAroundObstructions

	//try to swerve around everything, but stop for lights if necessary
	DRIVINGMODE_AVOIDCARS_OBEYLIGHTS = 786597, //DF_SwerveAroundAllCars|DF_StopAtLights|DF_SteerAroundObjects|DF_UseShortCutLinks|DF_ChangeLanesAroundObstructions|DF_StopForCars

	//swerve around cars, be careful around peds, and stop for lights
	DRIVINGMODE_AVOIDCARS_STOPFORPEDS_OBEYLIGHTS = 786599 //DF_SwerveAroundAllCars|DF_StopAtLights|DF_StopForPeds|DF_SteerAroundObjects|DF_UseShortCutLinks|DF_ChangeLanesAroundObstructions|DF_StopForCars,
};

enum class eDrivingStyle
{
	DRIVINGSTYLE_NORMAL       = 0,
	DRIVINGSTYLE_ACCURATE     = 0, // will be removed eventually
	DRIVINGSTYLE_STRAIGHTLINE = 0, // will be removed eventually
	DRIVINGSTYLE_RACING       = 1,
	DRIVINGSTYLE_REVERSING    = 2
};

enum class eDoorId
{
	VEH_EXT_DOOR_INVALID_ID = -1,
	VEH_EXT_DOOR_DSIDE_F,
	VEH_EXT_DOOR_DSIDE_R,
	VEH_EXT_DOOR_PSIDE_F,
	VEH_EXT_DOOR_PSIDE_R,
	VEH_EXT_BONNET,
	VEH_EXT_BOOT
};

enum class eVehicleSeats
{
	DRIVER = -1,
	PASSENGER,
	LEFT_BACK,
	RIGHT_BACK,
	OUTSIDE_LEFT,
	OUTSIDE_RIGHT,
};

enum class eGetSafeCoordFlags
{
	GSC_FLAG_DEFAULT,
	GSC_FLAG_ONLY_PAVEMENT,
	GSC_FLAG_NOT_ISOLATED,
	GSC_FLAG_NOT_INTERIOR = 4,
	GSC_FLAG_NOT_WATER = 8,
	GSC_FLAG_ONLY_NETWORK_SPAWN = 16,
	GSC_FLAG_USE_FLOOD_FILL = 32 //// Specify whether to use a flood-fill from the starting position, as opposed to scanning all polygons within the search volume
};

enum class eNodeFlags
{
	NF_NONE                       = 0,  // No flags
	NF_INCLUDE_SWITCHED_OFF_NODES = 1,  // Include switched off nodes in any search
	NF_INCLUDE_BOAT_NODES         = 2,  // Include boat nodes
	NF_IGNORE_SLIPLANES           = 4,  // Ignore sliplanes
	NF_IGNORE_SWITCHED_OFF_DEADENDS = 8 // Ignore dead-ends, only if they're switched off. If NF_INCLUDE_SWITCHED_OFF_NODES is false this won't find anything to ignore
};
