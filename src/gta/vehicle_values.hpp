#pragma once

#include "vehicles.hpp"

enum SeatPositions
{
	SEAT_DRIVER        = -1,
	SEAT_PASSENGER     = 0,
	SEAT_BACKDRIVER    = 1,
	SEAT_BACKPASSENGER = 2
};

enum WheelTypes
{
	WHEEL_TYPE_STOCK = -1,
	WHEEL_TYPE_SPORT,
	WHEEL_TYPE_MUSCLE,
	WHEEL_TYPE_LOWRIDER,
	WHEEL_TYPE_SUV,
	WHEEL_TYPE_OFFROAD,
	WHEEL_TYPE_TUNER,
	WHEEL_TYPE_BIKEWHEELS,
	WHEEL_TYPE_HIGHEND,
	WHEEL_TYPE_BENNYS_ORIGINAL,
	WHEEL_TYPE_BENNYS_BESPOKE,
	WHEEL_TYPE_OPEN_WHEEL,
	WHEEL_TYPE_STREET,
	WHEEL_TYPE_TRACK
};

enum VehicleWeapons
{
	VEHICLE_WEAPON_AKULA_BARRAGE         = 0x880D14F2,
	VEHICLE_WEAPON_AKULA_MINIGUN         = 0x19B95679,
	VEHICLE_WEAPON_AKULA_MISSILE         = 0x7CBE304C,
	VEHICLE_WEAPON_AKULA_TURRET_DUAL     = 0x1C6D0842,
	VEHICLE_WEAPON_AKULA_TURRET_SINGLE   = 0xB5B3B9AD,
	VEHICLE_WEAPON_APC_CANNON            = 0x138F71D8,
	VEHICLE_WEAPON_APC_MG                = 0xB56E4E4,
	VEHICLE_WEAPON_APC_MISSILE           = 0x44A56189,
	VEHICLE_WEAPON_ARDENT_MG             = 0xC44E4341,
	VEHICLE_WEAPON_AVENGER_CANNON        = 0x9867203B,
	VEHICLE_WEAPON_BARRAGE_REAR_GL       = 0xA44C228D,
	VEHICLE_WEAPON_BARRAGE_REAR_MG       = 0x47894765,
	VEHICLE_WEAPON_BARRAGE_REAR_MINIGUN  = 0x1F545F65,
	VEHICLE_WEAPON_BARRAGE_TOP_MG        = 0xF7498994,
	VEHICLE_WEAPON_BARRAGE_TOP_MINIGUN   = 0x3B9EBD01,
	VEHICLE_WEAPON_BOMBUSHKA_CANNON      = 0xD8443A59,
	VEHICLE_WEAPON_BOMBUSHKA_DUALMG      = 0x2C2B2D58,
	VEHICLE_WEAPON_CANNON_BLAZER         = 0xEBF9FF3E,
	VEHICLE_WEAPON_CARACARA_MG           = 0x6C516BA8,
	VEHICLE_WEAPON_CARACARA_MINIGUN      = 0x4FCBDC7B,
	VEHICLE_WEAPON_CHERNO_MISSILE        = 0xA247D03E,
	VEHICLE_WEAPON_COMET_MG              = 0xEAA835F3,
	VEHICLE_WEAPON_DELUXO_MG             = 0x9AFF6376,
	VEHICLE_WEAPON_DELUXO_MISSILE        = 0xB4F96934,
	VEHICLE_WEAPON_DOGFIGHTER_MG         = 0x5F1834E2,
	VEHICLE_WEAPON_DOGFIGHTER_MISSILE    = 0xCA46F87D,
	VEHICLE_WEAPON_DUNE_GRENADELAUNCHER  = 0xA0FC710D,
	VEHICLE_WEAPON_DUNE_MG               = 0xD11507CF,
	VEHICLE_WEAPON_DUNE_MINIGUN          = 0x54672A71,
	VEHICLE_WEAPON_ENEMY_LASER           = 0x5D6660AB,
	VEHICLE_WEAPON_HACKER_MISSILE        = 0x766FF7B1,
	VEHICLE_WEAPON_HACKER_MISSILE_HOMING = 0x77EACF96,
	VEHICLE_WEAPON_HALFTRACK_DUALMG      = 0x4F6384FB,
	VEHICLE_WEAPON_HALFTRACK_QUADMG      = 0x491B2E74,
	VEHICLE_WEAPON_HAVOK_MINIGUN         = 0x32FE9EEF,
	VEHICLE_WEAPON_HUNTER_BARRAGE        = 0x2ED14835,
	VEHICLE_WEAPON_HUNTER_CANNON         = 0x2A00AB1A,
	VEHICLE_WEAPON_HUNTER_MG             = 0x42BA80A7,
	VEHICLE_WEAPON_HUNTER_MISSILE        = 0x924A5F5,
	VEHICLE_WEAPON_INSURGENT_MINIGUN     = 0xAA886DF8,
	VEHICLE_WEAPON_KHANJALI_CANNON       = 0x1E3ACFA0,
	VEHICLE_WEAPON_KHANJALI_CANNON_HEAVY = 0x838B716D,
	VEHICLE_WEAPON_KHANJALI_GL           = 0x178605E2,
	VEHICLE_WEAPON_KHANJALI_MG           = 0x2A6F8E1D,
	VEHICLE_WEAPON_MENACER_MG            = 0xDFCAF8A4,
	VEHICLE_WEAPON_MICROLIGHT_MG         = 0xC4E0216C,
	VEHICLE_WEAPON_MOBILEOPS_CANNON      = 0xE53E69A4,
	VEHICLE_WEAPON_MOGUL_DUALNOSE        = 0xE5F3AE2F,
	VEHICLE_WEAPON_MOGUL_DUALTURRET      = 0xBA277C01,
	VEHICLE_WEAPON_MOGUL_NOSE            = 0xF6189F4A,
	VEHICLE_WEAPON_MOGUL_TURRET          = 0xE2FD135E,
	VEHICLE_WEAPON_MULE4_MG              = 0x84558727,
	VEHICLE_WEAPON_MULE4_MISSILE         = 0x4772F84B,
	VEHICLE_WEAPON_MULE4_TURRET_GL       = 0xDD124A65,
	VEHICLE_WEAPON_NIGHTSHARK_MG         = 0xA61AC574,
	VEHICLE_WEAPON_NOSE_TURRET_VALKYRIE  = 0x4170E491,
	VEHICLE_WEAPON_OPPRESSOR_MG          = 0xD9322EDD,
	VEHICLE_WEAPON_OPPRESSOR_MISSILE     = 0x8BB7C63E,
	VEHICLE_WEAPON_OPPRESSOR2_CANNON     = 0xD64D3469,
	VEHICLE_WEAPON_OPPRESSOR2_MG         = 0xE2451DD6,
	VEHICLE_WEAPON_OPPRESSOR2_MISSILE    = 0x753A78F1,
	VEHICLE_WEAPON_PLANE_ROCKET          = 0xCF0896E0,
	VEHICLE_WEAPON_PLAYER_BUZZARD        = 0x46B89C8E,
	VEHICLE_WEAPON_PLAYER_LAZER          = 0xE2822A29,
	VEHICLE_WEAPON_PLAYER_SAVAGE         = 0x61A31349,
	VEHICLE_WEAPON_POUNDER2_BARRAGE      = 0x926B8CE4,
	VEHICLE_WEAPON_POUNDER2_GL           = 0x9318FF16,
	VEHICLE_WEAPON_POUNDER2_MINI         = 0x86E6F84E,
	VEHICLE_WEAPON_POUNDER2_MISSILE      = 0x9A8EA9A,
	VEHICLE_WEAPON_RADAR                 = 0xD276317E,
	VEHICLE_WEAPON_REVOLTER_MG           = 0xBD5E626A,
	VEHICLE_WEAPON_ROGUE_CANNON          = 0xE72ABBC2,
	VEHICLE_WEAPON_ROGUE_MG              = 0x97273CD,
	VEHICLE_WEAPON_ROGUE_MISSILE         = 0x6C88E47D,
	VEHICLE_WEAPON_RUINER_BULLET         = 0x2FCC0F9,
	VEHICLE_WEAPON_RUINER_ROCKET         = 0x50DC6AB,
	VEHICLE_WEAPON_SAVESTRA_MG           = 0xEB41E84E,
	VEHICLE_WEAPON_SCRAMJET_MG           = 0xDCE6112,
	VEHICLE_WEAPON_SCRAMJET_MISSILE      = 0xBCE908DB,
	VEHICLE_WEAPON_SEABREEZE_MG          = 0x51B8D4E8,
	VEHICLE_WEAPON_SEARCHLIGHT           = 0xCDAC517D,
	VEHICLE_WEAPON_SPACE_ROCKET          = 0xF8A3939F,
	VEHICLE_WEAPON_SPEEDO4_MG            = 0xC7FCF93C,
	VEHICLE_WEAPON_SPEEDO4_TURRET_MG     = 0xD6561141,
	VEHICLE_WEAPON_SPEEDO4_TURRET_MINI   = 0x9EFE3EBA,
	VEHICLE_WEAPON_STRIKEFORCE_BARRAGE   = 0x39BC6683,
	VEHICLE_WEAPON_STRIKEFORCE_CANNON    = 0x38F41EAB,
	VEHICLE_WEAPON_STRIKEFORCE_MISSILE   = 0x1EF01D8A,
	VEHICLE_WEAPON_SUBCAR_MG             = 0x461DDDB0,
	VEHICLE_WEAPON_SUBCAR_MISSILE        = 0xD4897C0E,
	VEHICLE_WEAPON_SUBCAR_TORPEDO        = 0xE783C3BA,
	VEHICLE_WEAPON_TAMPA_DUALMINIGUN     = 0x67FDCFE4,
	VEHICLE_WEAPON_TAMPA_FIXEDMINIGUN    = 0xDAC57AAD,
	VEHICLE_WEAPON_TAMPA_MISSILE         = 0x9E5840A2,
	VEHICLE_WEAPON_TAMPA_MORTAR          = 0x3C83C410,
	VEHICLE_WEAPON_TANK                  = 0x73F7C04B,
	VEHICLE_WEAPON_TECHNICAL_MINIGUN     = 0xDB894608,
	VEHICLE_WEAPON_THRUSTER_MG           = 0x652E1D9D,
	VEHICLE_WEAPON_THRUSTER_MISSILE      = 0x4635DD15,
	VEHICLE_WEAPON_TRAILER_DUALAA        = 0x808C4D4C,
	VEHICLE_WEAPON_TRAILER_MISSILE       = 0x145599F7,
	VEHICLE_WEAPON_TRAILER_QUADMG        = 0x4711B02C,
	VEHICLE_WEAPON_TULA_DUALMG           = 0xB0D15C0B,
	VEHICLE_WEAPON_TULA_MG               = 0x488BD081,
	VEHICLE_WEAPON_TULA_MINIGUN          = 0x1670C4A8,
	VEHICLE_WEAPON_TULA_NOSEMG           = 0x419D8E15,
	VEHICLE_WEAPON_TURRET_BOXVILLE       = 0xB54F4918,
	VEHICLE_WEAPON_TURRET_INSURGENT      = 0x44DB5498,
	VEHICLE_WEAPON_TURRET_LIMO           = 0x2B796481,
	VEHICLE_WEAPON_TURRET_TECHNICAL      = 0x7FD2EA0B,
	VEHICLE_WEAPON_TURRET_VALKYRIE       = 0xA4513E35,
	VEHICLE_WEAPON_VIGILANTE_MG          = 0xF4077EE7,
	VEHICLE_WEAPON_VIGILANTE_MISSILE     = 0x504DA665,
	VEHICLE_WEAPON_VISERIS_MG            = 0x87A02E06,
	VEHICLE_WEAPON_VOLATOL_DUALMG        = 0x4497AC40,
	VEHICLE_WEAPON_WATER_CANNON          = 0x67D18297
};

enum TunerTypes
{
	WHEEL_TUNER_STOCK = -1,
	WHEEL_TUNER_COSMO,
	WHEEL_TUNER_SUPERMESH,
	WHEEL_TUNER_OUTSIDER,
	WHEEL_TUNER_ROLLAS,
	WHEEL_TUNER_DRIFFMEISTER,
	WHEEL_TUNER_SLICER,
	WHEEL_TUNER_ELQUATRO,
	WHEEL_TUNER_DUBBED,
	WHEEL_TUNER_FIVESTAR,
	WHEEL_TUNER_SLIDEWAYS,
	WHEEL_TUNER_APEX,
	WHEEL_TUNER_STANCEDEG,
	WHEEL_TUNER_COUNTERSTEER,
	WHEEL_TUNER_ENDOV1,
	WHEEL_TUNER_ENDOV2DISH,
	WHEEL_TUNER_GUPPEZ,
	WHEEL_TUNER_CHOKADORI,
	WHEEL_TUNER_CHICANE,
	WHEEL_TUNER_SAISOKU,
	WHEEL_TUNER_DISHEDEIGHT,
	WHEEL_TUNER_FUJIWARA,
	WHEEL_TUNER_ZOKUSHA,
	WHEEL_TUNER_BATTLEVLLL,
	WHEEL_TUNER_RALLYMASTER
};

enum HighEndWheels
{
	WHEEL_HIGHEND_STOCK = -1,
	WHEEL_HIGHEND_SHADOW,
	WHEEL_HIGHEND_HYPHER,
	WHEEL_HIGHEND_BLADE,
	WHEEL_HIGHEND_DIAMOND,
	WHEEL_HIGHEND_SUPAGEE,
	WHEEL_HIGHEND_CHROMATICZ,
	WHEEL_HIGHEND_MERCIECHLIP,
	WHEEL_HIGHEND_OBEYRS,
	WHEEL_HIGHEND_GTCHROME,
	WHEEL_HIGHEND_CHEETAHR,
	WHEEL_HIGHEND_SOLAR,
	WHEEL_HIGHEND_SPLITTEN,
	WHEEL_HIGHEND_DASHVIP,
	WHEEL_HIGHEND_LOZSPEEDTEN,
	WHEEL_HIGHEND_CARBONINFERNO,
	WHEEL_HIGHEND_CARBONSHADOW,
	WHEEL_HIGHEND_CARBONZ,
	WHEEL_HIGHEND_CARBONSOLAR,
	WHEEL_HIGHEND_CARBONCHEETAHR,
	WHEEL_HIGHEND_CARBONSRACER
};

enum LowriderWheels
{
	WHEEL_LOWRIDER_STOCK = -1,
	WHEEL_LOWRIDER_FLARE,
	WHEEL_LOWRIDER_WIRED,
	WHEEL_LOWRIDER_TRIPLEGOLDS,
	WHEEL_LOWRIDER_BIGWORM,
	WHEEL_LOWRIDER_SEVENFIVES,
	WHEEL_LOWRIDER_SPLITSIX,
	WHEEL_LOWRIDER_FRESHMESH,
	WHEEL_LOWRIDER_LEADSLED,
	WHEEL_LOWRIDER_TURBINE,
	WHEEL_LOWRIDER_SUPERFIN,
	WHEEL_LOWRIDER_CLASSICROD,
	WHEEL_LOWRIDER_DOLLAR,
	WHEEL_LOWRIDER_DUKES,
	WHEEL_LOWRIDER_LOWFIVE,
	WHEEL_LOWRIDER_GOOCH,
};

enum MuscleWheels
{
	WHEEL_MUSCLE_STOCK = -1,
	WHEEL_MUSCLE_CLASSICFIVE,
	WHEEL_MUSCLE_DUKES,
	WHEEL_MUSCLE_MUSCLEFREAK,
	WHEEL_MUSCLE_KRACKA,
	WHEEL_MUSCLE_AZREA,
	WHEEL_MUSCLE_MECHA,
	WHEEL_MUSCLE_BLACKTOP,
	WHEEL_MUSCLE_DRAGSPL,
	WHEEL_MUSCLE_REVOLVER,
	WHEEL_MUSCLE_CLASSICROD,
	WHEEL_MUSCLE_FAIRLRE,
	WHEEL_MUSCLE_SPOONER,
	WHEEL_MUSCLE_FIVESTAR,
	WHEEL_MUSCLE_OLDSCHOOL,
	WHEEL_MUSCLE_ELJEFE,
	WHEEL_MUSCLE_DODMAN,
	WHEEL_MUSCLE_SIXGUN,
	WHEEL_MUSCLE_MERCENARY
};

enum OffroadWheels
{
	WHEEL_OFFROAD_STOCK = -1,
	WHEEL_OFFROAD_RAIDER,
	WHEEL_OFFROAD_MUDSLINGER,
	WHEEL_OFFROAD_NEVIS,
	WHEEL_OFFROAD_CAIRNGORM,
	WHEEL_OFFROAD_AMAZON,
	WHEEL_OFFROAD_CHALLENGER,
	WHEEL_OFFROAD_DUNEBASHER,
	WHEEL_OFFROAD_FIVESTAR,
	WHEEL_OFFROAD_ROCKCRAWLER,
	WHEEL_OFFROAD_MILSPECSTEELIE
};

enum SportWheels
{
	WHEEL_SPORT_STOCK = -1,
	WHEEL_SPORT_INFERNO,
	WHEEL_SPORT_DEEPFIVE,
	WHEEL_SPORT_LOZSPEED,
	WHEEL_SPORT_DIAMONDCUT,
	WHEEL_SPORT_CHRONO,
	WHEEL_SPORT_FEROCCIRR,
	WHEEL_SPORT_FIFTYNINE,
	WHEEL_SPORT_MERCIE,
	WHEEL_SPORT_SYNTHETICZ,
	WHEEL_SPORT_ORGANICTYPED,
	WHEEL_SPORT_ENDOV1,
	WHEEL_SPORT_DUPER7,
	WHEEL_SPORT_UZER,
	WHEEL_SPORT_GROUNDRIDE,
	WHEEL_SPORT_SRACER,
	WHEEL_SPORT_VENUM,
	WHEEL_SPORT_COSMO,
	WHEEL_SPORT_DASHVIP,
	WHEEL_SPORT_ICEKID,
	WHEEL_SPORT_RUFFWELD,
	WHEEL_SPORT_WANGENMASTER,
	WHEEL_SPORT_SUPERFIVE,
	WHEEL_SPORT_ENDOV2,
	WHEEL_SPORT_SLITSIX
};

enum SUVWheels
{
	WHEEL_SUV_STOCK = -1,
	WHEEL_SUV_VIP,
	WHEEL_SUV_BENEFACTOR,
	WHEEL_SUV_COSMO,
	WHEEL_SUV_BIPPU,
	WHEEL_SUV_ROYALSIX,
	WHEEL_SUV_FAGORME,
	WHEEL_SUV_DELUXE,
	WHEEL_SUV_ICEDOUT,
	WHEEL_SUV_COGNSCENTI,
	WHEEL_SUV_LOZSPEEDTEN,
	WHEEL_SUV_SUPERNOVA,
	WHEEL_SUV_OBEYRS,
	WHEEL_SUV_LOZSPEEDBALLER,
	WHEEL_SUV_EXTRAVAGANZO,
	WHEEL_SUV_SPLITSIX,
	WHEEL_SUV_EMPOWERED,
	WHEEL_SUV_SUNRISE,
	WHEEL_SUV_DASHVIP,
	WHEEL_SUV_CUTTER
};

enum BikeWheels
{
	WHEEL_BIKE_STOCK = -1,
	WHEEL_BIKE_SPEEDWAY,
	WHEEL_BIKE_STREETSPECIAL,
	WHEEL_BIKE_RACER,
	WHEEL_BIKE_TRACKSTAR,
	WHEEL_BIKE_OVERLORD,
	WHEEL_BIKE_TRIDENT,
	WHEEL_BIKE_TRIPLETHREAT,
	WHEEL_BIKE_STILLETO,
	WHEEL_BIKE_WIRES,
	WHEEL_BIKE_BOBBER,
	WHEEL_BIKE_SOLIDUS,
	WHEEL_BIKE_ICESHIELD,
	WHEEL_BIKE_LOOPS
};

enum VehicleModType
{
	MOD_SPOILERS,
	MOD_FRONTBUMPER,
	MOD_REARBUMPER,
	MOD_SIDESKIRT,
	MOD_EXHAUST,
	MOD_FRAME,
	MOD_GRILLE,
	MOD_HOOD,
	MOD_FENDER,
	MOD_RIGHTFENDER,
	MOD_ROOF,
	MOD_ENGINE,
	MOD_BRAKES,
	MOD_TRANSMISSION,
	MOD_HORNS,
	MOD_SUSPENSION,
	MOD_ARMOR,
	MOD_NITROUS      = 17,
	MOD_TURBO        = 18,
	MOD_SUBWOOFER    = 19,
	MOD_TYRE_SMOKE   = 20,
	MOD_HYDRAULICS   = 21,
	MOD_XENON_LIGHTS = 22,
	MOD_FRONTWHEEL   = 23,
	MOD_REARWHEEL,
	MOD_PLATEHOLDER,
	MOD_VANITYPLATES,
	MOD_TRIMDESIGN,
	MOD_ORNAMENTS,
	MOD_DASHBOARD,
	MOD_DIALDESIGN,
	MOD_DOORSPEAKERS,
	MOD_SEATS,
	MOD_STEERINGWHEELS,
	MOD_COLUMNSHIFTERLEVERS,
	MOD_PLAQUES,
	MOD_SPEAKERS,
	MOD_TRUNK,
	MOD_HYDRO,
	MOD_ENGINEBLOCK,
	MOD_AIRFILTER,
	MOD_STRUTS,
	MOD_ARCHCOVER,
	MOD_AERIALS,
	MOD_TRIM,
	MOD_TANK,
	MOD_WINDOWS,
	MOD_DOORS,
	MOD_LIVERY,
	MOD_LIGHTBAR,
};

enum CustomVehicleModType
{
	MOD_MODEL_HASH = -100,

	MOD_WHEEL_TYPE  = -101,
	MOD_PLATE_STYLE = -102,
	MOD_WINDOW_TINT = -103,

	MOD_FRONTWHEEL_VAR = -104,
	MOD_REARWHEEL_VAR  = -105,

	MOD_NEON_FRONT_ON  = -106,
	MOD_NEON_BACK_ON   = -107,
	MOD_NEON_LEFT_ON   = -108,
	MOD_NEON_RIGHT_ON  = -109,
	MOD_TIRE_CAN_BURST = -110,
	MOD_DRIFT_TIRE     = -111,

	MOD_PRIMARY_COL     = -112,
	MOD_SECONDARY_COL   = -113,
	MOD_PEARLESCENT_COL = -114,
	MOD_WHEEL_COL       = -115,
	MOD_INTERIOR_COL    = -116,
	MOD_DASHBOARD_COL   = -117,
	MOD_XENON_COL       = -118,

	MOD_PRIMARY_COL_R = -119,
	MOD_PRIMARY_COL_G = -120,
	MOD_PRIMARY_COL_B = -121,

	MOD_SECONDARY_COL_R = -122,
	MOD_SECONDARY_COL_G = -123,
	MOD_SECONDARY_COL_B = -124,

	MOD_TIRESMOKE_COL_R = -125,
	MOD_TIRESMOKE_COL_G = -126,
	MOD_TIRESMOKE_COL_B = -127,

	MOD_NEON_COL_R = -128,
	MOD_NEON_COL_G = -129,
	MOD_NEON_COL_B = -130,

	MOD_PRIMARY_CUSTOM   = -131,
	MOD_SECONDARY_CUSTOM = -132,

	MOD_EXTRA_0  = -200,
	MOD_EXTRA_1  = -201,
	MOD_EXTRA_2  = -202,
	MOD_EXTRA_3  = -203,
	MOD_EXTRA_4  = -204,
	MOD_EXTRA_5  = -205,
	MOD_EXTRA_6  = -206,
	MOD_EXTRA_7  = -207,
	MOD_EXTRA_8  = -208,
	MOD_EXTRA_9  = -209,
	MOD_EXTRA_10 = -210,
	MOD_EXTRA_11 = -211,
	MOD_EXTRA_12 = -212,
	MOD_EXTRA_13 = -213,
	MOD_EXTRA_14 = -214
};


static const char* mod_names[] = {"MOD_SPOILERS", "MOD_FRONTBUMPER", "MOD_REARBUMPER", "MOD_SIDESKIRT", "MOD_EXHAUST", "MOD_FRAME", "MOD_GRILLE", "MOD_HOOD", "MOD_FENDER", "MOD_RIGHTFENDER", "MOD_ROOF", "MOD_ENGINE", "MOD_BRAKES", "MOD_TRANSMISSION", "MOD_HORNS", "MOD_SUSPENSION", "MOD_ARMOR", "", "MOD_TURBO", "", "MOD_TIRESMOKE", "", "MOD_XENONHEADLIGHTS", "MOD_FRONTWHEEL", "MOD_REARWHEEL", "MOD_PLATEHOLDER", "MOD_VANITYPLATES", "MOD_TRIMDESIGN", "MOD_ORNAMENTS", "MOD_DASHBOARD", "MOD_DIALDESIGN", "MOD_DOORSPEAKERS", "MOD_SEATS", "MOD_STEERINGWHEELS", "MOD_COLUMNSHIFTERLEVERS", "MOD_PLAQUES", "MOD_SPEAKERS", "MOD_TRUNK", "MOD_HYDRAULICS", "MOD_ENGINEBLOCK", "MOD_AIRFILTER", "MOD_STRUTS", "MOD_ARCHCOVER", "MOD_AERIALS", "MOD_TRIM", "MOD_TANK", "MOD_WINDOWS", "", "MOD_LIVERY"};

enum VehicleModHorns
{
	HORN_STOCK = -1,
	HORN_TRUCK,
	HORN_POLICE,
	HORN_CLOWN,
	HORN_MUSICAL1,
	HORN_MUSICAL2,
	HORN_MUSICAL3,
	HORN_MUSICAL4,
	HORN_MUSICAL5,
	HORN_SADTROMBONE,
	HORN_CLASSICAL1,
	HORN_CLASSICAL2,
	HORN_CLASSICAL3,
	HORN_CLASSICAL4,
	HORN_CLASSICAL5,
	HORN_CLASSICAL6,
	HORN_CLASSICAL7,
	HORN_SCALEDO,
	HORN_SCALERE,
	HORN_SCALEMI,
	HORN_SCALEFA,
	HORN_SCALESOL,
	HORN_SCALELA,
	HORN_SCALETI,
	HORN_SCALEDO_HIGH,
	HORN_JAZZ1,
	HORN_JAZZ2,
	HORN_JAZZ3,
	HORN_JAZZLOOP,
	HORN_STARSPANGBAN1,
	HORN_STARSPANGBAN2,
	HORN_STARSPANGBAN3,
	HORN_STARSPANGBAN4,
	HORN_CLASSICAL_LOOP,
	HORN_CLASSICAL,
	HORN_CLASSICAL_LOOP2,
	HORN_CLASSICAL_HORN_LOOP,
	HORN_CLASSICAL_HORN_LOOP2,
	HORN_CLASSICAL_HORN_LOOP3,
	HORN_HALLOWEEN_LOOP,
	HORN_HALLOWEEN,
	HORN_HALLOWEEN2_LOOP,
	HORN_HALLOWEEN2,
	HORN_SANANDREAS_LOOP,
	HORN_SANANDREAS,
	HORN_LIBERTYCITY_LOOP,
	HORN_LIBERTYCITY,
	HORN_XMAS,
	HORN_XMAS_BACKGROUND,
	HORN_XMAS2,
	HORN_XMAS2_BACKGROUND,
	HORN_XMAS3,
	HORN_XMAS3_BACKGROUND,
	HORN_LOW_LONG,
	HORN_LOW_SHORT,
	HORN_MID_LONG,
	HORN_MID_SHORT,
	HORN_HIGH_LONG,
	HORN_HIGH_SHORT
};

enum VehicleAddonLevel
{
	MOD_INDEX_OFF = -1,
	MOD_INDEX_ONE,//To determine mod index, look at the mod menu in LSC, the first item is MOD_INDEX_ONE. Count down to the item you want. Stock counts as OFF.
	MOD_INDEX_TWO,
	MOD_INDEX_THREE,
	MOD_INDEX_FOUR,
	MOD_INDEX_FIVE,
	MOD_INDEX_SIX,
	MOD_INDEX_SEVEN,
	MOD_INDEX_EIGHT,
	MOD_INDEX_NINE
};

enum NeonLightLocations
{
	NEON_LEFT,
	NEON_RIGHT,
	NEON_FRONT,
	NEON_BACK
};

enum VehicleColorsChrome
{
	COLOR_CHROME = 120
};

enum VehicleColorsClassic
{
	COLOR_CLASSIC_BLACK            = 0,
	COLOR_CLASSIC_CARBON_BLACK     = 147,
	COLOR_CLASSIC_GRAPHITE         = 1,
	COLOR_CLASSIC_ANHRACITE_BLACK  = 11,
	COLOR_CLASSIC_BLACK_STEEL      = 2,
	COLOR_CLASSIC_DARK_STEEL       = 3,
	COLOR_CLASSIC_SILVER           = 4,
	COLOR_CLASSIC_BLUISH_SILVER    = 5,
	COLOR_CLASSIC_ROLLED_STEEL     = 6,
	COLOR_CLASSIC_SHADOW_SILVER    = 7,
	COLOR_CLASSIC_STONE_SILVER     = 8,
	COLOR_CLASSIC_MIDNIGHT_SILVER  = 9,
	COLOR_CLASSIC_CAST_IRON_SILVER = 10,
	COLOR_CLASSIC_RED              = 27,
	COLOR_CLASSIC_TORINO_RED       = 28,
	COLOR_CLASSIC_FORMULA_RED      = 29,
	COLOR_CLASSIC_LAVA_RED         = 150,
	COLOR_CLASSIC_BLAZE_RED        = 30,
	COLOR_CLASSIC_GRACE_RED        = 31,
	COLOR_CLASSIC_GARNET_RED       = 32,
	COLOR_CLASSIC_SUNSET_RED       = 33,
	COLOR_CLASSIC_CABERNET_RED     = 34,
	COLOR_CLASSIC_WINE_RED         = 143,
	COLOR_CLASSIC_CANDY_RED        = 35,
	COLOR_CLASSIC_HOT_PINK         = 135,
	COLOR_CLASSIC_PFSITER_PINK     = 137,
	COLOR_CLASSIC_SALMON_PINK      = 136,
	COLOR_CLASSIC_SUNRISE_ORANGE   = 36,
	COLOR_CLASSIC_ORANGE           = 38,
	COLOR_CLASSIC_BRIGHT_ORANGE    = 138,
	COLOR_CLASSIC_GOLD             = 99,
	COLOR_CLASSIC_BRONZE           = 90,
	COLOR_CLASSIC_YELLOW           = 88,
	COLOR_CLASSIC_RACE_YELLOW      = 89,
	COLOR_CLASSIC_DEW_YELLOW       = 91,
	COLOR_CLASSIC_DARK_GREEN       = 49,
	COLOR_CLASSIC_RACING_GREEN     = 50,
	COLOR_CLASSIC_SEA_GREEN        = 51,
	COLOR_CLASSIC_OLIVE_GREEN      = 52,
	COLOR_CLASSIC_BRIGHT_GREEN     = 53,
	COLOR_CLASSIC_GASOLINE_GREEN   = 54,
	COLOR_CLASSIC_LIME_GREEN       = 92,
	COLOR_CLASSIC_MIDNIGHT_BLUE    = 141,
	COLOR_CLASSIC_GALAXY_BLUE      = 61,
	COLOR_CLASSIC_DARK_BLUE        = 62,
	COLOR_CLASSIC_SAXON_BLUE       = 63,
	COLOR_CLASSIC_BLUE             = 64,
	COLOR_CLASSIC_MARINER_BLUE     = 65,
	COLOR_CLASSIC_HARBOR_BLUE      = 66,
	COLOR_CLASSIC_DIAMOND_BLUE     = 67,
	COLOR_CLASSIC_SURF_BLUE        = 68,
	COLOR_CLASSIC_NAUTICAL_BLUE    = 69,
	COLOR_CLASSIC_RACING_BLUE      = 73,
	COLOR_CLASSIC_ULTRA_BLUE       = 70,
	COLOR_CLASSIC_LIGHT_BLUE       = 74,
	COLOR_CLASSIC_CHOCOLATE_BROWN  = 96,
	COLOR_CLASSIC_BISON_BROWN      = 101,
	COLOR_CLASSIC_CREEEN_BROWN     = 95,
	COLOR_CLASSIC_FELTZER_BROWN    = 94,
	COLOR_CLASSIC_MAPLE_BROWN      = 97,
	COLOR_CLASSIC_BEECHWOOD_BROWN  = 103,
	COLOR_CLASSIC_SIENNA_BROWN     = 104,
	COLOR_CLASSIC_SADDLE_BROWN     = 98,
	COLOR_CLASSIC_MOSS_BROWN       = 100,
	COLOR_CLASSIC_WOODBEECH_BROWN  = 102,
	COLOR_CLASSIC_STRAW_BROWN      = 99,
	COLOR_CLASSIC_SANDY_BROWN      = 105,
	COLOR_CLASSIC_BLEACHED_BROWN   = 106,
	COLOR_CLASSIC_SCHAFTER_PURPLE  = 71,
	COLOR_CLASSIC_SPINNAKER_PURPLE = 72,
	COLOR_CLASSIC_MIDNIGHT_PURPLE  = 142,
	COLOR_CLASSIC_BRIGHT_PURPLE    = 145,
	COLOR_CLASSIC_CREAM            = 107,
	COLOR_CLASSIC_ICE_WHITE        = 111,
	COLOR_CLASSIC_FROST_WHITE      = 112
};

enum VehicleColorsMatte
{
	COLOR_MATTE_BLACK           = 12,
	COLOR_MATTE_GRAY            = 13,
	COLOR_MATTE_LIGHT_GRAY      = 14,
	COLOR_MATTE_ICE_WHITE       = 131,
	COLOR_MATTE_BLUE            = 83,
	COLOR_MATTE_DARK_BLUE       = 82,
	COLOR_MATTE_MIDNIGHT_BLUE   = 84,
	COLOR_MATTE_MIDNIGHT_PURPLE = 149,
	COLOR_MATTE_SCHAFTER_PURPLE = 148,
	COLOR_MATTE_RED             = 39,
	COLOR_MATTE_DARK_RED        = 40,
	COLOR_MATTE_ORANGE          = 41,
	COLOR_MATTE_YELLOW          = 42,
	COLOR_MATTE_LIME_GREEN      = 55,
	COLOR_MATTE_GREEN           = 128,
	COLOR_MATTE_FOREST_GREEN    = 151,
	COLOR_MATTE_FOLIAGE_GREEN   = 155,
	COLOR_MATTE_OLIVE_DARB      = 152,
	COLOR_MATTE_DARK_EARTH      = 153,
	COLOR_MATTE_DESERT_TAN      = 154
};

enum VehicleColorsMetals
{
	//COLOR_METALS_PEARLESCENT_STEEL = 18,
	COLOR_METALS_BRUSHED_STEEL       = 117,
	COLOR_METALS_BRUSHED_BLACK_STEEL = 118,
	COLOR_METALS_BRUSHED_ALUMINUM    = 119,
	COLOR_METALS_PURE_GOLD           = 158,
	COLOR_METALS_BRUSHED_GOLD        = 159,
	//COLOR_METALS_PEARLESCENT_GOLD = 160
};

enum PlateTextIndexs
{
	PLATE_BLUEONWHITE1,
	PLATE_YELLOWONBLACK,
	PLATE_YELLOWONBLUE,
	PLATE_BLUEONWHITE2,
	PLATE_BLUEONWHITE3,
	PLATE_YANKTON
};

enum WindowTints//m8 do you even int tint?
{
	WINDOWTINT_NONE,
	WINDOWTINT_BLACK,
	WINDOWTINT_DARKSMOKE,
	WINDOWTINT_LIGHTSMOKE,
	WINDOWTINT_STOCK,
	WINDOWTINT_LIMO,
	WINDOWTINT_GREEN
};

enum HeadlightColors
{
	XENON_DEFAULT = -1,
	XENON_WHITE,
	XENON_BLUE,
	XENON_ELECTRIC_BLUE,
	XENON_MINT_GREEN,
	XENON_LIME_GREEN,
	XENON_YELLOW,
	XENON_GOLDEN_SHOWER,
	XENON_ORANGE,
	XENON_RED,
	XENON_PONY_PINK,
	XENON_HOT_PINK,
	XENON_PURPLE,
	XENON_BACKLIGHT
};

#define NEON_COLOR_WHITE 222, 222, 255
#define NEON_COLOR_BLUE 2, 21, 255
#define NEON_COLOR_ELECTRICBLUE 3, 83, 255
#define NEON_COLOR_MINTGREEN 0, 255, 140
#define NEON_COLOR_LIMEGREEN 94, 255, 1
#define NEON_COLOR_YELLOW 255, 255, 0
#define NEON_COLOR_GOLDENSHOWER 255, 150, 5
#define NEON_COLOR_ORANGE 255, 62, 0
#define NEON_COLOR_RED 255, 1, 1
#define NEON_COLOR_PONYPINK 255, 50, 100//Fag
#define NEON_COLOR_HOTPINK 255, 5, 190
#define NEON_COLOR_PURPLE 35, 1, 255
#define NEON_COLOR_BACKLIGHT 15, 3, 255

#define TIRESMOKE_COLOR_WHITE 255, 255, 255
#define TIRESMOKE_COLOR_BLACK 20, 20, 20
#define TIRESMOKE_COLOR_BLUE 0, 174, 239
#define TIRESMOKE_COLOR_YELLOW 252, 238, 0
#define TIRESMOKE_COLOR_PURPLE 100, 79, 142
#define TIRESMOKE_COLOR_ORANGE 255, 127, 0
#define TIRESMOKE_COLOR_GREEN 114, 204, 114
#define TIRESMOKE_COLOR_RED 226, 6, 6
#define TIRESMOKE_COLOR_PINK 203, 54, 148
#define TIRESMOKE_COLOR_BROWN 180, 130, 97
#define TIRESMOKE_COLOR_PATRIOT 0, 0, 0

static bool GetVehicleInfoForClanLogo(Hash vehicleModel, rage::fvector3& x, rage::fvector3& y, rage::fvector3& z, float& scale)
{
	switch (vehicleModel)
	{
	case VEHICLE_DOMINATOR:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_FELTZER2:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ADDER:
		x     = {0.0f, 1.54f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_AKUMA:
		x     = {0.0f, 0.06f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.18f;
		return true;
	case VEHICLE_ASEA:
		x     = {0.0f, 1.5f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ASTEROPE:
		x     = {0.0f, 1.7f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BAGGER:
		x     = {-1.0f, 0.16f, 0.283f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.09f;
		return true;
	case VEHICLE_BALLER:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BALLER2:
		x     = {0.0f, 1.55f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BANSHEE:
		x     = {0.0f, 0.94f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_BATI:
		x     = {0.0f, 0.2f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_BATI2:
		x     = {0.0f, 0.2f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_BFINJECTION:
		x     = {-1.0f, 0.08f, 0.19f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BISON:
		x     = {0.0f, 1.99f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BJXL:
		x     = {0.0f, 1.2f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_BLISTA:
		x     = {0.0f, 1.49f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.29f;
		return true;
	case VEHICLE_BOBCATXL:
		x     = {0.0f, 1.68f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.65f;
		return true;
	case VEHICLE_BODHI2:
		x     = {0.0f, 1.95f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BUCCANEER:
		x     = {0.0f, 2.01f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.37f;
		return true;
	case VEHICLE_BUFFALO:
		x     = {0.0f, 1.6f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BUFFALO2:
		x     = {0.0f, 2.24f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_BULLETGT:
		x     = {-1.57f, 0.07f, 0.16f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_CARBONRS:
		x     = {0.0f, 0.09f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.18f;
		return true;
	case VEHICLE_CARBONIZZARE:
		x     = {0.0f, 1.45f, 1.0f};
		y     = {0.0f, -0.11f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_CAVALCADE:
		x     = {0.0f, 1.51f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.55f;
		return true;
	case VEHICLE_CAVALCADE2:
		x     = {0.0f, 1.59f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_CHEETAH:
		x     = {-1.61f, 0.26f, 0.17f};
		y     = {0.9f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_COGCABRIO:
		x     = {0.0f, 1.42f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_COMET2:
		x     = {0.0f, 1.35f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_COQUETTE:
		x     = {0.0f, 0.96f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.22f;
		return true;
	case VEHICLE_DAEMON:
		x     = {0.0f, 0.06f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_DILETTANTE:
		x     = {0.0f, 1.59f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_DLOADER:
		x     = {0.0f, 1.52f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_DOUBLE:
		x     = {0.0f, 0.08f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_DUBSTA:
		x     = {-1.71f, 0.31f, 0.27f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_DUBSTA2:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.75f;
		return true;
	case VEHICLE_ELEGY2:
		x     = {0.0f, 1.14f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_EMPEROR:
		x     = {0.0f, 1.31f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_EMPEROR2:
		x     = {0.0f, 1.31f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ENTITYXF:
		x     = {-1.52f, 0.41f, 0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_EXEMPLAR:
		x     = {0.0f, 1.32f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_F620:
		x     = {0.0f, 1.28f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_FAGGIO2:
		x     = {-1.0f, -0.48f, -0.11f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_FELON:
		x     = {0.0f, 1.24f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_FELON2:
		x     = {0.0f, 1.24f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_FQ2:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_FUGITIVE:
		x     = {0.0f, 1.62f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_FUSILADE:
		x     = {0.0f, 0.98f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_FUTO:
		x     = {0.0f, 1.28f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_GAUNTLET:
		x     = {0.0f, 1.735f, 1.05f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.33f;
		return true;
	case VEHICLE_GRANGER:
		x     = {0.0f, 2.07f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_GRESLEY:
		x     = {0.0f, 1.75f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_HABANERO:
		x     = {0.0f, 1.69f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_HEXER:
		x     = {0.0f, -0.46f, 1.0f};
		y     = {0.0f, 1.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.14f;
		return true;
	case VEHICLE_HOTKNIFE:
		x     = {-1.43f, -0.14f, 0.18f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_INFERNUS:
		x     = {-1.0f, 0.33f, 0.08f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.06f};
		scale = 0.25f;
		return true;
	case VEHICLE_INGOT:
		x     = {0.0f, 1.58f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_INTRUDER:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ISSI2:
		x     = {0.0f, 1.21f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_JACKAL:
		x     = {0.0f, 1.36f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_JB700:
		x     = {0.0f, 1.2f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.37f;
		return true;
	case VEHICLE_KHAMELION:
		x     = {0.0f, 1.46f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.475f;
		return true;
	case VEHICLE_LANDSTALKER:
		x     = {0.0f, 1.83f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_MANANA:
		x     = {0.0f, 0.86f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.37f;
		return true;
	case VEHICLE_MESA:
		x     = {0.0f, 1.47f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_MESA3:
		x     = {0.0f, 1.47f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_MINIVAN:
		x     = {0.0f, 1.95f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_MONROE:
		x     = {0.0f, 1.23f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.43f;
		return true;
	case VEHICLE_NEMESIS:
		x     = {0.0f, 0.14f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_NINEF:
		x     = {0.0f, 1.7f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_NINEF2:
		x     = {0.0f, 1.7f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ORACLE:
		x     = {0.0f, 1.6f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ORACLE2:
		x     = {0.0f, 1.7f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PATRIOT:
		x     = {0.0f, 1.75f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PCJ:
		x     = {0.0f, 0.02f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_PENUMBRA:
		x     = {0.0f, 1.46f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PEYOTE:
		x     = {-1.0f, -0.36f, 0.2125f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PHOENIX:
		x     = {0.0f, 1.833f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.44f;
		return true;
	case VEHICLE_PICADOR:
		x     = {0.0f, 1.43f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.515f;
		return true;
	case VEHICLE_PRAIRIE:
		x     = {0.0f, 1.41f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.31f;
		return true;
	case VEHICLE_PREMIER:
		x     = {0.0f, 1.6f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PRIMO:
		x     = {0.0f, 1.62f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_RADI:
		x     = {0.0f, 1.74f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_RANCHERXL:
		x     = {0.0f, 1.54f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_RAPIDGT:
		x     = {0.0f, 1.263f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_RAPIDGT2:
		x     = {0.0f, 1.263f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_RATLOADER:
		x     = {-1.78f, 0.52f, 0.52f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_REBEL:
		x     = {-1.22f, 0.6f, 0.44f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_REBEL2:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_REGINA:
		x     = {0.0f, 1.473f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ROCOTO:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ROMERO:
		x     = {0.0f, 1.83f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_RUFFIAN:
		x     = {0.0f, -0.02f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.19f;
		return true;
	case VEHICLE_RUINER:
		x     = {0.0f, 1.34f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SABREGT:
		x     = {-1.0f, 0.0f, 0.14f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.015f};
		scale = 0.35f;
		return true;
	case VEHICLE_SADLER:
		x     = {0.0f, 2.26f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SANDKING:
		x     = {0.0f, 2.496f, 1.55f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SANDKING2:
		x     = {0.0f, 2.286f, 1.55f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SCHAFTER2:
		x     = {0.0f, 1.56f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.28f;
		return true;
	case VEHICLE_SCHWARZER:
		x     = {0.0f, 1.43f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.28f;
		return true;
	case VEHICLE_SEMINOLE:
		x     = {0.0f, 1.45f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SENTINEL:
		x     = {0.0f, 1.52f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SENTINEL2:
		x     = {0.0f, 1.52f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SERRANO:
		x     = {0.0f, 1.68f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.49f;
		return true;
	case VEHICLE_STANIER:
		x     = {0.0f, 1.55f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_STINGER:
		x     = {0.0f, 1.3f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_STINGERGT:
		x     = {-1.0f, -0.17f, 0.12f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_STRATUM:
		x     = {0.0f, 1.52f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SULTAN:
		x     = {0.0f, 1.77f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.33f;
		return true;
	case VEHICLE_SUPERD:
		x     = {0.0f, 1.62f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SURANO:
		x     = {0.0f, 1.38f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SURFER:
		x     = {0.0f, 2.48f, 0.26f};
		y     = {0.0f, -1.0f, -0.212f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.32f;
		return true;
	case VEHICLE_SURFER2:
		x     = {0.0f, 2.48f, 0.26f};
		y     = {0.0f, -1.0f, -0.212f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.32f;
		return true;
	case VEHICLE_SURGE:
		x     = {0.0f, 1.69f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_TAILGATER:
		x     = {0.0f, 1.783f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_TORNADO:
		x     = {-1.23f, 0.11f, -0.21f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_TORNADO2:
		x     = {0.0f, 1.44f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_TORNADO3:
		x     = {0.0f, 1.44f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_VACCA:
		x     = {0.0f, 1.76f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_VADER:
		x     = {0.0f, 0.08f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_VIGERO:
		x     = {-1.0f, 0.11f, -0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_VOLTIC:
		x     = {0.0f, 1.763f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.29f;
		return true;
	case VEHICLE_VOODOO2:
		x     = {0.0f, 1.48f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_WASHINGTON:
		x     = {0.0f, 1.61f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_YOUGA:
		x     = {0.0f, 2.352f, 1.003f};
		y     = {0.0f, -1.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.175f;
		return true;
	case VEHICLE_ZION:
		x     = {0.0f, 1.48f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_ZION2:
		x     = {0.0f, 1.48f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_ZTYPE:
		x     = {-0.96f, -0.69f, 0.35f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_KALAHARI:
		x     = {-1.0f, 0.18f, 0.1f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PARADISE:
		x     = {0.0f, 2.23f, 1.0f};
		y     = {0.0f, -0.22f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_ALPHA:
		x     = {-1.0f, 0.18f, -0.05f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_HUNTLEY:
		x     = {0.0f, 1.52f, 0.99f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_ZENTORNO:
		x     = {-1.24f, 0.42f, -0.14f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.035f};
		scale = 0.3f;
		return true;
	case VEHICLE_JESTER:
		x     = {-1.0f, 0.17f, 0.22f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.05f};
		scale = 0.33f;
		return true;
	case VEHICLE_MASSACRO:
		x     = {0.0f, 1.37f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.33f;
		return true;
	case VEHICLE_TURISMOR:
		x     = {-1.0f, 0.3f, 0.27f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_THRUST:
		x     = {-1.0f, 0.405f, 0.4625f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1625f;
		return true;
	case VEHICLE_BTYPE:
		x     = {0.0f, 1.143f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.7125f;
		return true;
	case VEHICLE_RHAPSODY:
		x     = {-1.0f, -0.47f, -0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2625f;
		return true;
	case VEHICLE_GLENDALE:
		x     = {0.0f, 1.683f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.775f;
		return true;
	case VEHICLE_WARRENER:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.775f;
		return true;
	case VEHICLE_BLADE:
		x     = {-1.0f, 0.445f, 0.2075f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.325f;
		return true;
	case VEHICLE_PANTO:
		x     = {-1.0f, 0.0f, 0.335f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_DUBSTA3:
		x     = {-1.0f, 0.34f, 0.2975f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PIGALLE:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_COQUETTE2:
		x     = {-1.0f, -0.1775f, 0.195f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_INNOVATION:
		x     = {0.0f, 0.15f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.18f;
		return true;
	case VEHICLE_HAKUCHOU:
		x     = {0.0f, 0.27f, 0.845f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.16f;
		return true;
	case VEHICLE_FUROREGT:
		x     = {-1.0f, 0.0f, 0.2075f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_RATLOADER2:
		x     = {-1.78f, 0.52f, 0.52f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_SLAMVAN:
		x     = {-1.0f, 0.275f, 0.195f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_DUKES2:
		x     = {-1.0f, 0.0f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.375f;
		return true;
	case VEHICLE_DUKES:
		x     = {-1.0f, 0.0f, 0.0375f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3875f;
		return true;
	case VEHICLE_STALION:
		x     = {-1.0f, 0.0f, 0.0925f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4375f;
		return true;
	case VEHICLE_BLISTA2:
		x     = {-1.0f, 0.5325f, 0.245f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2875f;
		return true;
	case VEHICLE_CASCO:
		x     = {0.0f, 0.94f, 1.03f};
		y     = {0.0f, -0.03f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_ENDURO:
		x     = {0.0f, -0.17f, 1.0f};
		y     = {0.0f, 0.34f, -0.786f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_GBURRITO2:
		x     = {0.0f, 2.32f, 0.94f};
		y     = {0.0f, -0.182f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_GUARDIAN:
		x     = {-1.94f, 1.07f, 0.38f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_KURUMA:
	case VEHICLE_KURUMA2:
		x     = {-1.0f, 0.2475f, -0.175f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.435f;
		return true;
	case VEHICLE_LECTRO:
		x     = {0.0f, 0.3f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.09f;
		return true;
	case VEHICLE_FELTZER3:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_OSIRIS:
		x     = {-1.0f, 0.27f, -0.03f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_VIRGO:
		x     = {-1.05f, 0.0f, 0.075f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_WINDSOR:
		x     = {-1.2f, -0.39f, 0.12f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.55f;
		return true;
	case VEHICLE_BRAWLER:
		x     = {-1.0f, -0.21f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_CHINO:
		x     = {-1.05f, 0.0f, 0.075f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_COQUETTE3:
		x     = {-1.0f, -0.1775f, 0.195f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_T20:
		x     = {-1.0f, 0.4f, -0.12f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_VINDICATOR:
		x     = {-1.0f, 0.21f, 0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_FACTION:
		x     = {-1.0f, 0.0f, 0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_FACTION2:
		x     = {-1.0f, 0.0f, 0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BUCCANEER2:
		x     = {0.0f, 2.01f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.37f;
		return true;
	case VEHICLE_CHINO2:
		x     = {-1.05f, 0.0f, 0.075f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_MOONBEAM:
		x     = {0.0f, 1.713f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_MOONBEAM2:
		x     = {0.0f, 1.713f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_PRIMO2:
		x     = {-1.0f, 0.42f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_VOODOO:
		x     = {-1.12f, 0.0f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_FACTION3:
		x     = {-1.0f, 0.0f, 0.5f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SABREGT2:
		x     = {-1.0f, 0.0f, 0.14f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.015f};
		scale = 0.35f;
		return true;
	case VEHICLE_TORNADO5:
		x     = {-1.0f, 0.15f, -0.09f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_VIRGO2:
		x     = {-1.0f, 0.0f, 0.1225f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.375f;
		return true;
	case VEHICLE_VIRGO3:
		x     = {-1.0f, 0.0f, 0.1225f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.375f;
		return true;
	case VEHICLE_MINIVAN2:
		x     = {0.0f, 1.95f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_SLAMVAN3:
		x     = {-1.0f, 0.275f, 0.195f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BTYPE2:
		x     = {-1.0f, -0.1f, 0.4f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_LURCHER:
		x     = {-1.0f, 0.0f, 0.3f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_BALLER3:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BALLER4:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BALLER5:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BALLER6:
		x     = {0.0f, 1.4f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_COG55:
		x     = {-1.0f, 0.37f, 0.13f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_COG552:
		x     = {-1.0f, 0.37f, 0.13f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_COGNOSCENTI:
		x     = {-1.0f, 0.37f, 0.13f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_COGNOSCENTI2:
		x     = {-1.0f, 0.37f, 0.13f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_MAMBA:
		x     = {-1.0f, -0.18f, 0.21f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_NIGHTSHADE:
		x     = {-1.0f, -0.2f, 0.17f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_SCHAFTER3:
		x     = {0.0f, 1.56f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.28f;
		return true;
	case VEHICLE_SCHAFTER4:
		x     = {0.0f, 1.56f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.28f;
		return true;
	case VEHICLE_SCHAFTER5:
		x     = {0.0f, 1.56f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.28f;
		return true;
	case VEHICLE_SCHAFTER6:
		x     = {0.0f, 1.56f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.28f;
		return true;
	case VEHICLE_VERLIERER2:
		x     = {-1.0f, -0.21f, 0.03f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_TAMPA:
		x     = {-1.0f, 0.0f, 0.12f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_BANSHEE2:
		x     = {-1.0f, -0.4f, 0.075f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SULTANRS:
		x     = {0.0f, 1.77f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.33f;
		return true;
	case VEHICLE_BTYPE3:
		x     = {-1.0f, -0.1f, 0.4f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_BESTIAGTS:
		x     = {-1.0f, -0.06f, 0.4f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SEVEN70:
		x     = {-1.0f, -0.21f, 0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_FMJ:
		x     = {-1.0f, -0.06f, 0.21f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_PFISTER811:
		x     = {-1.0f, 0.06f, 0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_PROTOTIPO:
		x     = {-1.0f, 0.3f, 0.27f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_REAPER:
		x     = {-1.0f, 0.48f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_RUMPO3:
		x     = {0.0f, 2.103f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_WINDSOR2:
		x     = {-1.2f, 0.03f, 0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.55f;
		return true;
	case VEHICLE_XLS:
		x     = {-1.0f, 0.36f, -0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_XLS2:
		x     = {-1.0f, 0.36f, -0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_BRIOSO:
		x     = {-1.0f, -0.06f, 0.565f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_CONTENDER:
		x     = {0.0f, 2.33f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_LE7B:
		x     = {-1.0f, -0.12f, 0.235f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_OMNIS:
		x     = {-1.0f, 0.03f, 0.18f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_TROPOS:
		x     = {-1.0f, 0.0f, 0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_AVARUS:
		x     = {-1.0f, 0.27f, 0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_DAEMON2:
		x     = {-1.0f, 0.27f, 0.29f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_DEFILER:
		x     = {-1.0f, 0.0f, 0.34f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.125f;
		return true;
	case VEHICLE_ESSKEY:
		x     = {-1.0f, 0.335f, 0.31f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.09f;
		return true;
	case VEHICLE_HAKUCHOU2:
		x     = {0.0f, 0.27f, 0.845f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_NIGHTBLADE:
		x     = {0.0f, -0.133f, 0.61f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.125f;
		return true;
	case VEHICLE_RATBIKE:
		x     = {-1.0f, 0.31f, 0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_SHOTARO:
		x     = {-1.0f, 0.06f, 0.325f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_ZOMBIEA:
		x     = {-1.0f, 0.3f, 0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_ZOMBIEB:
		x     = {-1.0f, 0.2f, 0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_VORTEX:
		x     = {-1.0f, 0.18f, 0.37f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.095f;
		return true;
	case VEHICLE_TORNADO6:
		x     = {-1.0f, -0.03f, -0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_YOUGA2:
		x     = {0.0f, 2.352f, 0.253f};
		y     = {0.0f, -1.0f, -0.256f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.175f;
		return true;
	case VEHICLE_WOLFSBANE:
		x     = {-1.0f, 0.33f, 0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_FAGGIO3:
		x     = {-1.0f, -0.54f, -0.11f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_FAGGIO:
		x     = {-0.9875f, -0.0175f, -0.01f};
		y     = {0.8975f, -0.26f, -0.0725f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1625f;
		return true;
	case VEHICLE_COMET3:
		x     = {-1.0f, 0.0f, 0.295f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_DIABLOUS:
		x     = {-1.0f, 0.006f, 0.382f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_DIABLOUS2:
		x     = {-1.0f, 0.225f, 0.541f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_ELEGY:
		x     = {0.0f, 1.14f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_FCR:
		x     = {-1.0f, 0.234f, 0.376f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_FCR2:
		x     = {-1.0f, 0.234f, 0.376f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_ITALIGTB:
		x     = {-1.0f, -0.024f, 0.187f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_ITALIGTB2:
		x     = {-1.0f, -0.024f, 0.187f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_NERO:
		x     = {-1.0f, 0.237f, 0.09f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_NERO2:
		x     = {-1.0f, 0.237f, 0.09f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_PENETRATOR:
		x     = {-1.0f, 0.153f, 0.295f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_RUINER2:
		x     = {0.363f, 1.34f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_RUINER3:
		x     = {0.363f, 1.34f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SPECTER:
		x     = {-1.0f, -0.273f, -0.02f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_SPECTER2:
		x     = {-1.0f, -0.273f, 0.286f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_TECHNICAL2:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_TEMPESTA:
		x     = {-1.0f, 0.0f, 0.253f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_VOLTIC2:
		x     = {0.0f, 1.763f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.29f;
		return true;
	case VEHICLE_INFERNUS2:
		x     = {-1.0f, 0.33f, 0.06f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.06f};
		scale = 0.2f;
		return true;
	case VEHICLE_RUSTON:
		x     = {-1.0f, -0.273f, 0.084f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_TURISMO2:
		x     = {-1.0f, 0.159f, -0.193f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_ARDENT:
		x     = {-1.0f, 0.309f, 0.276f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_CHEETAH2:
		x     = {-1.0f, 0.159f, -0.127f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_HALFTRACK:
		x     = {-1.0f, 0.501f, 0.531f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_NIGHTSHARK:
		x     = {-1.5f, 0.42f, 0.584f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_OPPRESSOR:
		x     = {-1.0f, 0.306f, 0.355f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.08f;
		return true;
	case VEHICLE_TAMPA3:
		x     = {0.0f, 1.515f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.275f;
		return true;
	case VEHICLE_TECHNICAL3:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.43f;
		return true;
	case VEHICLE_TORERO:
		x     = {-1.0f, 0.201f, 0.114f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_VAGNER:
		x     = {-1.5f, 0.906f, 0.071f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_XA21:
		x     = {-1.0f, 0.441f, 0.13f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_PHANTOM3:
		x     = {-1.3f, 2.045f, 0.802f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_HAULER2:
		x     = {-1.627f, 2.456f, 0.745f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_CYCLONE:
		x     = {-1.0f, 0.186f, 0.382f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_VISIONE:
		x     = {-1.0f, 0.432f, 0.031f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_VIGILANTE:
		x     = {-1.0f, 0.232f, 0.24f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.175f;
		return true;
	case VEHICLE_RETINUE:
		x     = {-1.0f, -0.018f, 0.253f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_RAPIDGT3:
		x     = {0.0f, 1.972f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.18f;
		return true;
	case VEHICLE_AVENGER:
		x     = {-2.02f, 6.45f, -0.716f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_DELUXO:
		x     = {-1.0f, -0.291f, 0.247f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_STROMBERG:
		x     = {-1.0f, 0.23f, 0.247f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_RIOT2:
		x     = {-1.891f, 2.144f, 0.657f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_CHERNOBOG:
		x     = {-2.127f, 5.413f, 1.132f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.34f;
		return true;
	case VEHICLE_KHANJALI:
		x     = {-0.897f, 1.391f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_BARRAGE:
		x     = {-1.51f, 0.71f, 0.451f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_COMET4:
		x     = {-1.0f, 0.298f, 0.257f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.36f;
		return true;
	case VEHICLE_NEON:
		x     = {-1.0f, 0.181f, -0.066f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_STREITER:
		x     = {-1.0f, 0.301f, 0.295f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SENTINEL3:
		x     = {0.0f, 1.52f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_YOSEMITE:
		x     = {-1.0f, 0.252f, 0.201f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_SC1:
		x     = {-1.0f, 0.616f, -0.131f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_AUTARCH:
		x     = {-1.0f, 0.0f, 0.116f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_GT500:
		x     = {-1.0f, 0.0f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_HUSTLER:
		x     = {-1.0f, -0.228f, 0.321f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_REVOLTER:
		x     = {-1.0f, 0.203f, 0.126f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_PARIAH:
		x     = {-1.0f, -0.126f, 0.208f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_RAIDEN:
		x     = {-1.0f, 0.252f, -0.095f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_SAVESTRA:
		x     = {-1.0f, 0.0f, 0.25f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_RIATA:
		x     = {-1.3f, 0.18f, 0.511f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_HERMES:
		x     = {-1.0f, -0.134f, 0.158f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_COMET5:
		x     = {-1.0f, 0.002f, 0.031f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_Z190:
		x     = {-1.0f, -0.175f, 0.242f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_VISERIS:
		x     = {-1.0f, 0.0f, 0.244f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.275f;
		return true;
	case VEHICLE_KAMACHO:
		x     = {0.0f, 1.623f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_GB200:
		x     = {-1.0f, 0.0f, 0.407f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.225f;
		return true;
	case VEHICLE_FAGALOA:
		x     = {-1.0f, 0.0f, 0.225f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_ELLIE:
		x     = {-1.0f, 0.441f, -0.128f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_ISSI3:
		x     = {-1.0f, 0.195f, 0.246f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_MICHELLI:
		x     = {-1.0f, 0.0f, 0.0805f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_FLASHGT:
		x     = {0.0f, 1.592f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_HOTRING:
		x     = {-1.0f, 0.0f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_TEZERACT:
		x     = {-1.0f, 0.679f, 0.514f};
		y     = {1.0f, 0.0f, -0.75f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.175f;
		return true;
	case VEHICLE_TYRANT:
		x     = {-1.588f, 0.315f, 0.337f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_DOMINATOR3:
		x     = {-1.0f, 0.0f, 0.221f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_TAIPAN:
		x     = {-1.0f, 0.0f, 0.219f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_ENTITY2:
		x     = {-1.52f, 0.41f, 0.15f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_JESTER3:
		x     = {-1.0f, 0.0f, 0.297f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_CHEBUREK:
		x     = {-1.0f, 0.393f, 0.162f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.375f;
		return true;
	case VEHICLE_CARACARA:
		x     = {-1.0f, 1.266f, 0.4115f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SPEEDO4:
		x     = {-1.5f, 0.833f, 0.391f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_MULE4:
		x     = {-1.125f, 2.691f, 0.318f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_POUNDER2:
		x     = {-1.5f, 1.853f, 0.779f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.38f;
		return true;
	case VEHICLE_SWINGER:
		x     = {-1.0f, 0.195f, 0.105f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_MENACER:
		x     = {-1.73f, 0.159f, 0.61f};
		y     = {1.0f, 0.12f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SCRAMJET:
		x     = {-1.0f, -0.188f, 0.0f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_PATRIOT2:
		x     = {-1.213f, 1.546f, 0.511f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_STAFFORD:
		x     = {-1.0f, 0.036f, 0.096f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_FREECRAWLER:
		x     = {-1.0f, 0.249f, 0.511f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_OPPRESSOR2:
		x     = {-1.0f, 0.306f, 0.355f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.08f;
		return true;
	case VEHICLE_TERBYTE:
		x     = {-1.73f, 3.397f, 0.724f};
		y     = {1.0f, 0.12f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_BRUISER:
	case VEHICLE_BRUISER2:
	case VEHICLE_BRUISER3:
		x     = {0.0f, 2.12f, 1.241f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.084f};
		scale = 0.775f;
		return true;
	case VEHICLE_BRUTUS:
	case VEHICLE_BRUTUS2:
	case VEHICLE_BRUTUS3:
		x     = {-1.0f, 0.446f, 0.247f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_CERBERUS:
	case VEHICLE_CERBERUS2:
	case VEHICLE_CERBERUS3:
		x     = {-1.432f, 1.443f, 1.292f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_CLIQUE:
		x     = {-1.0f, 0.167f, 0.159f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_DEVESTE:
		x     = {-1.5f, 1.066f, 0.13f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.15f;
		return true;
	case VEHICLE_DEVIANT:
		x     = {-1.0f, 0.111f, 0.123f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_DOMINATOR4:
	case VEHICLE_DOMINATOR5:
	case VEHICLE_DOMINATOR6:
		x     = {-1.0f, 0.0f, 0.417f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_IMPALER:
	case VEHICLE_IMPALER2:
	case VEHICLE_IMPALER3:
	case VEHICLE_IMPALER4:
		x     = {-1.0f, 0.0f, 0.137f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_IMPERATOR:
	case VEHICLE_IMPERATOR2:
	case VEHICLE_IMPERATOR3:
		x     = {-1.0f, 0.0f, 0.295f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_ISSI4:
	case VEHICLE_ISSI5:
	case VEHICLE_ISSI6:
		x     = {-1.0f, 0.195f, 0.246f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_ITALIGTO:
		x     = {-1.0f, -0.091f, 0.207f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_MONSTER3:
	case VEHICLE_MONSTER4:
	case VEHICLE_MONSTER5:
		x     = {-1.78f, 0.445f, 0.81f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_SCHLAGEN:
		x     = {-1.0f, -0.105f, 0.262f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SLAMVAN4:
	case VEHICLE_SLAMVAN5:
	case VEHICLE_SLAMVAN6:
		x     = {-1.0f, 0.152f, 0.537f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_TOROS:
		x     = {-1.0f, 0.415f, 0.394f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_TULIP:
		x     = {-1.0f, 0.171f, 0.223f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_VAMOS:
		x     = {-1.0f, 0.0f, 0.163f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_ZR380:
	case VEHICLE_ZR3802:
	case VEHICLE_ZR3803:
		x     = {-1.0f, 0.0f, 0.286f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_CARACARA2:
		x     = {-1.0f, 0.687f, 0.4115f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_DRAFTER:
		x     = {-1.045f, 0.15f, 0.09f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_DYNASTY:
		x     = {-1.0f, 0.12f, 0.334f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_EMERUS:
		x     = {-1.0f, 0.372f, 0.439f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.1f;
		return true;
	case VEHICLE_GAUNTLET3:
		x     = {-1.0f, 0.0f, 0.222f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.33f;
		return true;
	case VEHICLE_GAUNTLET4:
		x     = {-1.0f, 0.0f, 0.222f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.33f;
		return true;
	case VEHICLE_HELLION:
		x     = {-1.0f, 0.27f, 0.246f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_ISSI7:
		x     = {-1.0f, 0.195f, -0.063f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_JUGULAR:
		x     = {-1.0f, 0.213f, 0.213f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_KRIEGER:
		x     = {-1.0f, 0.576f, -0.123f};
		y     = {0.997f, -0.105f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_LOCUST:
		x     = {-1.0f, -0.207f, 0.042f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_NEBULA:
		x     = {-1.0f, 0.012f, 0.147f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_NEO:
		x     = {-1.0f, 0.216f, 0.216f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_NOVAK:
		x     = {-1.0f, 0.24f, 0.255f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_PARAGON:
	case VEHICLE_PARAGON2:
		x     = {-1.0f, 0.0f, 0.156f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_PEYOTE2:
		x     = {-1.0f, -0.36f, 0.2125f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_S80:
		x     = {-1.0f, 0.357f, 0.256f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.2f;
		return true;
	case VEHICLE_THRAX:
		x     = {-1.0f, 0.426f, 0.339f};
		y     = {1.0f, 0.06f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_ZION3:
		x     = {-1.0f, 0.108f, 0.234f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_ZORRUSSO:
		x     = {-1.0f, 0.273f, -0.06f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_SLAMVAN2:
		x     = {-1.0f, 0.35f, 0.456f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.25f;
		return true;
	case VEHICLE_REBLA:
		x     = {0.0f, 1.9002f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_ASBO:
		x     = {-1.0f, 0.104f, 0.339f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_SUGOI:
		x     = {-1.0f, 0.104f, 0.223f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_KOMODA:
		x     = {-1.0f, 0.104f, 0.155f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_VSTR:
		x     = {-1.0f, 0.104f, 0.155f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_SULTAN2:
		x     = {-1.0f, 0.313f, 0.16f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_KANJO:
		x     = {-1.0f, 0.313f, 0.16f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.35f;
		return true;
	case VEHICLE_JB7002:
		x     = {0.0f, 1.2f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.37f;
		return true;
	case VEHICLE_YOSEMITE2:
		x     = {-1.0f, 0.252f, 0.201f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_RETINUE2:
		x     = {-1.0f, -0.018f, 0.253f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.3f;
		return true;
	case VEHICLE_FURIA:
		x     = {-1.0f, 0.0965f, 0.149f};
		y     = {1.0f, 0.0f, 0.0f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_EVERON:
		x     = {0.0f, 2.019f, 1.0f};
		y     = {0.0f, 0.0f, -1.0f};
		z     = {-1.0f, 0.0f, 0.0f};
		scale = 0.5f;
		return true;
	case VEHICLE_IMORGON:
		x     = {-1.5f, 0.42f, -0.2f};
		y     = {1.0f, -0.0997f, 0.0415f};
		z     = {0.0f, -1.0f, 0.0f};
		scale = 0.45f;
		return true;
	case VEHICLE_ZHABA:
		x     = {-1.202f, 0.034f, 0.6635f};
		y     = {1.0f, -0.002f, 0.0f};
		z     = {0.0f, -0.7398f, 0.0f};
		scale = 0.4f;
		return true;
	case VEHICLE_GAUNTLET5:
		x     = {-1.5f, 0.379f, 0.297f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.24f;
		return true;
	case VEHICLE_DUKES3:
		x     = {-1.f, 0.f, 0.f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.375f;
		return true;
	case VEHICLE_MANANA2:
		x     = {-1.76f, 0.105f, 0.009f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.22f;
		return true;
	case VEHICLE_CLUB:
		x     = {0.f, 1.252f, 1.f};
		y     = {0.f, 0.f, -1.f};
		z     = {-1.f, 0.f, 0.f};
		scale = 0.31f;
		return true;
	case VEHICLE_GLENDALE2:
		x     = {0.f, 2.135f, 1.f};
		y     = {0.f, 0.f, -1.f};
		z     = {-1.f, 0.f, 0.f};
		scale = 0.205f;
		return true;
	case VEHICLE_YOUGA3:
		x     = {0.f, 2.352f, 0.3f};
		y     = {0.f, -1.f, -0.256f};
		z     = {-1.f, 0.f, 0.f};
		scale = 0.135f;
		return true;
	case VEHICLE_YOSEMITE3:
		x     = {-1.f, 0.252f, 0.203f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.21f;
		return true;
	case VEHICLE_SEMINOLE2:
		x     = {0.f, 1.654f, 1.f};
		y     = {0.f, 0.f, -1.f};
		z     = {-1.f, 0.f, 0.f};
		scale = 0.25f;
		return true;
	case VEHICLE_PENUMBRA2:
		x     = {-1.08f, 0.28f, -0.093f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.4f;
		return true;
	case VEHICLE_LANDSTALKER2:
		x     = {-1.64f, 0.7f, 0.f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.35f;
		return true;
	case VEHICLE_COQUETTE4:
		x     = {-1.f, -0.021f, 0.273f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.25f;
		return true;
	case VEHICLE_TIGON:
		x     = {-1.f, 0.156f, 0.099f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.3f;
		return true;
	case VEHICLE_PEYOTE3:
		x     = {-1.5f, -0.36f, 0.2125f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.35f;
		return true;
	case VEHICLE_BRIOSO2:
		x     = {-1.f, 0.275f, 0.215f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.3f;
		return true;
	case VEHICLE_SLAMTRUCK:
		x     = {-1.f, 1.454f, 0.485f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.3f;
		return true;
	case VEHICLE_ITALIRSX:
		x     = {-1.f, 0.109f, 0.129f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.3f;
		return true;
	case VEHICLE_TOREADOR:
		x     = {-1.f, 0.194f, 0.342f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.15f;
		return true;
	case VEHICLE_WEEVIL:
		x     = {-1.f, 0.111f, 0.168f};
		y     = {1.f, 0.f, 0.f};
		z     = {0.f, -1.f, 0.f};
		scale = 0.3f;
		return true;
	default: return false;
	}
}