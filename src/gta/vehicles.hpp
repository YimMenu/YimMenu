#pragma once

#include "gta/joaat.hpp"
#include "natives.hpp"

enum Boats : Hash
{
	VEHICLE_DINGHY = RAGE_JOAAT("DINGHY"),
	VEHICLE_DINGHY2 = RAGE_JOAAT("DINGHY2"),
	VEHICLE_DINGHY3 = RAGE_JOAAT("DINGHY3"),
	VEHICLE_DINGHY4 = RAGE_JOAAT("DINGHY4"),
	VEHICLE_JETMAX = RAGE_JOAAT("JETMAX"),
	VEHICLE_MARQUIS = RAGE_JOAAT("MARQUIS"),
	VEHICLE_SEASHARK = RAGE_JOAAT("SEASHARK"),
	VEHICLE_SEASHARK2 = RAGE_JOAAT("SEASHARK2"),
	VEHICLE_SEASHARK3 = RAGE_JOAAT("SEASHARK3"),
	VEHICLE_SPEEDER = RAGE_JOAAT("SPEEDER"),
	VEHICLE_SPEEDER2 = RAGE_JOAAT("SPEEDER2"),
	VEHICLE_SQUALO = RAGE_JOAAT("SQUALO"),
	VEHICLE_SUBMERSIBLE = RAGE_JOAAT("SUBMERSIBLE"),
	VEHICLE_SUBMERSIBLE2 = RAGE_JOAAT("SUBMERSIBLE2"),
	VEHICLE_SUNTRAP = RAGE_JOAAT("SUNTRAP"),
	VEHICLE_TORO = RAGE_JOAAT("TORO"),
	VEHICLE_TORO2 = RAGE_JOAAT("TORO2"),
	VEHICLE_TROPIC = RAGE_JOAAT("TROPIC"),
	VEHICLE_TROPIC2 = RAGE_JOAAT("TROPIC2"),
	VEHICLE_TUG = RAGE_JOAAT("TUG"),
};

enum Commericals : Hash
{
	VEHICLE_BENSON = RAGE_JOAAT("BENSON"),
	VEHICLE_BIFF = RAGE_JOAAT("BIFF"),
	VEHICLE_HAULER = RAGE_JOAAT("HAULER"),
	VEHICLE_HAULER2 = RAGE_JOAAT("HAULER2"),
	VEHICLE_MULE = RAGE_JOAAT("MULE"),
	VEHICLE_MULE2 = RAGE_JOAAT("MULE2"),
	VEHICLE_MULE3 = RAGE_JOAAT("MULE3"),
	VEHICLE_MULE4 = RAGE_JOAAT("MULE4"),
	VEHICLE_PACKER = RAGE_JOAAT("PACKER"),
	VEHICLE_PHANTOM = RAGE_JOAAT("PHANTOM"),
	VEHICLE_PHANTOM2 = RAGE_JOAAT("PHANTOM2"),
	VEHICLE_PHANTOM3 = RAGE_JOAAT("PHANTOM3"),
	VEHICLE_POUNDER = RAGE_JOAAT("POUNDER"),
	VEHICLE_POUNDER2 = RAGE_JOAAT("POUNDER2"),
	VEHICLE_STOCKADE = RAGE_JOAAT("STOCKADE"),
	VEHICLE_STOCKADE3 = RAGE_JOAAT("STOCKADE3"),
	VEHICLE_TERBYTE = RAGE_JOAAT("TERBYTE"),
};

enum Compacts : Hash
{
	VEHICLE_BLISTA = RAGE_JOAAT("BLISTA"),
	VEHICLE_BRIOSO = RAGE_JOAAT("BRIOSO"),
	VEHICLE_DILETTANTE = RAGE_JOAAT("DILETTANTE"),
	VEHICLE_DILETTANTE2 = RAGE_JOAAT("DILETTANTE2"),
	VEHICLE_ISSI2 = RAGE_JOAAT("ISSI2"),
	VEHICLE_ISSI3 = RAGE_JOAAT("ISSI3"),
	VEHICLE_PANTO = RAGE_JOAAT("PANTO"),
	VEHICLE_PRAIRIE = RAGE_JOAAT("PRAIRIE"),
	VEHICLE_RHAPSODY = RAGE_JOAAT("RHAPSODY"),
};

enum Coupes : Hash
{
	VEHICLE_COGCABRIO = RAGE_JOAAT("COGCABRIO"),
	VEHICLE_EXEMPLAR = RAGE_JOAAT("EXEMPLAR"),
	VEHICLE_F620 = RAGE_JOAAT("F620"),
	VEHICLE_FELON = RAGE_JOAAT("FELON"),
	VEHICLE_FELON2 = RAGE_JOAAT("FELON2"),
	VEHICLE_JACKAL = RAGE_JOAAT("JACKAL"),
	VEHICLE_ORACLE = RAGE_JOAAT("ORACLE"),
	VEHICLE_ORACLE2 = RAGE_JOAAT("ORACLE2"),
	VEHICLE_SENTINEL = RAGE_JOAAT("SENTINEL"),
	VEHICLE_SENTINEL2 = RAGE_JOAAT("SENTINEL2"),
	VEHICLE_WINDSOR = RAGE_JOAAT("WINDSOR"),
	VEHICLE_WINDSOR2 = RAGE_JOAAT("WINDSOR2"),
	VEHICLE_ZION = RAGE_JOAAT("ZION"),
	VEHICLE_ZION2 = RAGE_JOAAT("ZION2"),
};

enum Bikes : Hash
{
	VEHICLE_BMX = RAGE_JOAAT("BMX"),
	VEHICLE_CRUISER = RAGE_JOAAT("CRUISER"),
	VEHICLE_FIXTER = RAGE_JOAAT("FIXTER"),
	VEHICLE_SCORCHER = RAGE_JOAAT("SCORCHER"),
	VEHICLE_TRIBIKE = RAGE_JOAAT("TRIBIKE"),
	VEHICLE_TRIBIKE2 = RAGE_JOAAT("TRIBIKE2"),
	VEHICLE_TRIBIKE3 = RAGE_JOAAT("TRIBIKE3"),
};

enum Emergency : Hash
{
	VEHICLE_AMBULANCE = RAGE_JOAAT("AMBULANCE"),
	VEHICLE_FBI = RAGE_JOAAT("FBI"),
	VEHICLE_FBI2 = RAGE_JOAAT("FBI2"),
	VEHICLE_FIRETRUK = RAGE_JOAAT("FIRETRUK"),
	VEHICLE_LGUARD = RAGE_JOAAT("LGUARD"),
	VEHICLE_PBUS = RAGE_JOAAT("PBUS"),
	VEHICLE_POLICE = RAGE_JOAAT("POLICE"),
	VEHICLE_POLICE2 = RAGE_JOAAT("POLICE2"),
	VEHICLE_POLICE3 = RAGE_JOAAT("POLICE3"),
	VEHICLE_POLICE4 = RAGE_JOAAT("POLICE4"),
	VEHICLE_POLICEB = RAGE_JOAAT("POLICEB"),
	VEHICLE_POLMAV = RAGE_JOAAT("POLMAV"),
	VEHICLE_POLICEOLD1 = RAGE_JOAAT("POLICEOLD1"),
	VEHICLE_POLICEOLD2 = RAGE_JOAAT("POLICEOLD2"),
	VEHICLE_POLICET = RAGE_JOAAT("POLICET"),
	VEHICLE_PRANGER = RAGE_JOAAT("PRANGER"),
	VEHICLE_PREDATOR = RAGE_JOAAT("PREDATOR"),
	VEHICLE_RIOT = RAGE_JOAAT("RIOT"),
	VEHICLE_RIOT2 = RAGE_JOAAT("RIOT2"),
	VEHICLE_SHERIFF = RAGE_JOAAT("SHERIFF"),
	VEHICLE_SHERIFF2 = RAGE_JOAAT("SHERIFF2"),
};

enum Helicopters : Hash
{
	VEHICLE_AKULA = RAGE_JOAAT("AKULA"),
	VEHICLE_ANNIHILATOR = RAGE_JOAAT("ANNIHILATOR"),
	VEHICLE_BUZZARD = RAGE_JOAAT("BUZZARD"),
	VEHICLE_BUZZARD2 = RAGE_JOAAT("BUZZARD2"),
	VEHICLE_CARGOBOB = RAGE_JOAAT("CARGOBOB"),
	VEHICLE_CARGOBOB2 = RAGE_JOAAT("CARGOBOB2"),
	VEHICLE_CARGOBOB3 = RAGE_JOAAT("CARGOBOB3"),
	VEHICLE_CARGOBOB4 = RAGE_JOAAT("CARGOBOB4"),
	VEHICLE_FROGGER = RAGE_JOAAT("FROGGER"),
	VEHICLE_FROGGER2 = RAGE_JOAAT("FROGGER2"),
	VEHICLE_HAVOK = RAGE_JOAAT("HAVOK"),
	VEHICLE_HUNTER = RAGE_JOAAT("HUNTER"),
	VEHICLE_MAVERICK = RAGE_JOAAT("MAVERICK"),
	VEHICLE_SAVAGE = RAGE_JOAAT("SAVAGE"),
	VEHICLE_SKYLIFT = RAGE_JOAAT("SKYLIFT"),
	VEHICLE_SUPERVOLITO = RAGE_JOAAT("SUPERVOLITO"),
	VEHICLE_SUPERVOLITO2 = RAGE_JOAAT("SUPERVOLITO2"),
	VEHICLE_SWIFT = RAGE_JOAAT("SWIFT"),
	VEHICLE_SWIFT2 = RAGE_JOAAT("SWIFT2"),
	VEHICLE_VALKYRIE = RAGE_JOAAT("VALKYRIE"),
	VEHICLE_VALKYRIE2 = RAGE_JOAAT("VALKYRIE2"),
	VEHICLE_VOLATUS = RAGE_JOAAT("VOLATUS"),
};

enum Industrial : Hash
{
	VEHICLE_BULLDOZER = RAGE_JOAAT("BULLDOZER"),
	VEHICLE_CUTTER = RAGE_JOAAT("CUTTER"),
	VEHICLE_DUMP = RAGE_JOAAT("DUMP"),
	VEHICLE_FLATBED = RAGE_JOAAT("FLATBED"),
	VEHICLE_GUARDIAN = RAGE_JOAAT("GUARDIAN"),
	VEHICLE_HANDLER = RAGE_JOAAT("HANDLER"),
	VEHICLE_MIXER = RAGE_JOAAT("MIXER"),
	VEHICLE_MIXER2 = RAGE_JOAAT("MIXER2"),
	VEHICLE_RUBBLE = RAGE_JOAAT("RUBBLE"),
	VEHICLE_TIPTRUCK = RAGE_JOAAT("TIPTRUCK"),
	VEHICLE_TIPTRUCK2 = RAGE_JOAAT("TIPTRUCK2"),
};

enum Military : Hash
{
	VEHICLE_APC = RAGE_JOAAT("APC"),
	VEHICLE_BARRACKS = RAGE_JOAAT("BARRACKS"),
	VEHICLE_BARRACKS2 = RAGE_JOAAT("BARRACKS2"),
	VEHICLE_BARRACKS3 = RAGE_JOAAT("BARRACKS3"),
	VEHICLE_BARRAGE = RAGE_JOAAT("BARRAGE"),
	VEHICLE_CHERNOBOG = RAGE_JOAAT("CHERNOBOG"),
	VEHICLE_CRUSADER = RAGE_JOAAT("CRUSADER"),
	VEHICLE_HALFTRACK = RAGE_JOAAT("HALFTRACK"),
	VEHICLE_KHANJALI = RAGE_JOAAT("KHANJALI"),
	VEHICLE_RHINO = RAGE_JOAAT("RHINO"),
	VEHICLE_THRUSTER = RAGE_JOAAT("THRUSTER"),
	VEHICLE_TRAILERSMALL2 = RAGE_JOAAT("TRAILERSMALL2"),
};

enum Motorcycles : Hash
{
	VEHICLE_AKUMA = RAGE_JOAAT("AKUMA"),
	VEHICLE_AVARUS = RAGE_JOAAT("AVARUS"),
	VEHICLE_BAGGER = RAGE_JOAAT("BAGGER"),
	VEHICLE_BATI = RAGE_JOAAT("BATI"),
	VEHICLE_BATI2 = RAGE_JOAAT("BATI2"),
	VEHICLE_BF400 = RAGE_JOAAT("BF400"),
	VEHICLE_CARBONRS = RAGE_JOAAT("CARBONRS"),
	VEHICLE_CHIMERA = RAGE_JOAAT("CHIMERA"),
	VEHICLE_CLIFFHANGER = RAGE_JOAAT("CLIFFHANGER"),
	VEHICLE_DAEMON = RAGE_JOAAT("DAEMON"),
	VEHICLE_DAEMON2 = RAGE_JOAAT("DAEMON2"),
	VEHICLE_DEFILER = RAGE_JOAAT("DEFILER"),
	VEHICLE_DIABLOUS = RAGE_JOAAT("DIABLOUS"),
	VEHICLE_DIABLOUS2 = RAGE_JOAAT("DIABLOUS2"),
	VEHICLE_DOUBLE = RAGE_JOAAT("DOUBLE"),
	VEHICLE_ENDURO = RAGE_JOAAT("ENDURO"),
	VEHICLE_ESSKEY = RAGE_JOAAT("ESSKEY"),
	VEHICLE_FAGGIO = RAGE_JOAAT("FAGGIO"),
	VEHICLE_FAGGIO2 = RAGE_JOAAT("FAGGIO2"),
	VEHICLE_FAGGIO3 = RAGE_JOAAT("FAGGIO3"),
	VEHICLE_FCR = RAGE_JOAAT("FCR"),
	VEHICLE_FCR2 = RAGE_JOAAT("FCR2"),
	VEHICLE_GARGOYLE = RAGE_JOAAT("GARGOYLE"),
	VEHICLE_HAKUCHOU = RAGE_JOAAT("HAKUCHOU"),
	VEHICLE_HAKUCHOU2 = RAGE_JOAAT("HAKUCHOU2"),
	VEHICLE_HEXER = RAGE_JOAAT("HEXER"),
	VEHICLE_INNOVATION = RAGE_JOAAT("INNOVATION"),
	VEHICLE_LECTRO = RAGE_JOAAT("LECTRO"),
	VEHICLE_MANCHEZ = RAGE_JOAAT("MANCHEZ"),
	VEHICLE_NEMESIS = RAGE_JOAAT("NEMESIS"),
	VEHICLE_NIGHTBLADE = RAGE_JOAAT("NIGHTBLADE"),
	VEHICLE_OPPRESSOR = RAGE_JOAAT("OPPRESSOR"),
	VEHICLE_OPPRESSOR2 = RAGE_JOAAT("OPPRESSOR2"),
	VEHICLE_PCJ = RAGE_JOAAT("PCJ"),
	VEHICLE_RATBIKE = RAGE_JOAAT("RATBIKE"),
	VEHICLE_RUFFIAN = RAGE_JOAAT("RUFFIAN"),
	VEHICLE_SANCHEZ2 = RAGE_JOAAT("SANCHEZ2"),
	VEHICLE_SANCTUS = RAGE_JOAAT("SANCTUS"),
	VEHICLE_SHOTARO = RAGE_JOAAT("SHOTARO"),
	VEHICLE_SOVEREIGN = RAGE_JOAAT("SOVEREIGN"),
	VEHICLE_THRUST = RAGE_JOAAT("THRUST"),
	VEHICLE_VADER = RAGE_JOAAT("VADER"),
	VEHICLE_VINDICATOR = RAGE_JOAAT("VINDICATOR"),
	VEHICLE_VORTEX = RAGE_JOAAT("VORTEX"),
	VEHICLE_WOLFSBANE = RAGE_JOAAT("WOLFSBANE"),
	VEHICLE_ZOMBIEA = RAGE_JOAAT("ZOMBIEA"),
	VEHICLE_ZOMBIEB = RAGE_JOAAT("ZOMBIEB"),
};

enum Muscle : Hash
{
	VEHICLE_BLADE = RAGE_JOAAT("BLADE"),
	VEHICLE_BUCCANEER = RAGE_JOAAT("BUCCANEER"),
	VEHICLE_BUCCANEER2 = RAGE_JOAAT("BUCCANEER2"),
	VEHICLE_CHINO = RAGE_JOAAT("CHINO"),
	VEHICLE_CHINO2 = RAGE_JOAAT("CHINO2"),
	VEHICLE_COQUETTE3 = RAGE_JOAAT("COQUETTE3"),
	VEHICLE_DOMINATOR = RAGE_JOAAT("DOMINATOR"),
	VEHICLE_DOMINATOR2 = RAGE_JOAAT("DOMINATOR2"),
	VEHICLE_DOMINATOR3 = RAGE_JOAAT("DOMINATOR3"),
	VEHICLE_DUKES = RAGE_JOAAT("DUKES"),
	VEHICLE_DUKES2 = RAGE_JOAAT("DUKES2"),
	VEHICLE_ELLIE = RAGE_JOAAT("ELLIE"),
	VEHICLE_FACTION = RAGE_JOAAT("FACTION"),
	VEHICLE_FACTION2 = RAGE_JOAAT("FACTION2"),
	VEHICLE_FACTION3 = RAGE_JOAAT("FACTION3"),
	VEHICLE_GAUNTLET = RAGE_JOAAT("GAUNTLET"),
	VEHICLE_GAUNTLET2 = RAGE_JOAAT("GAUNTLET2"),
	VEHICLE_HERMES = RAGE_JOAAT("HERMES"),
	VEHICLE_HOTKNIFE = RAGE_JOAAT("HOTKNIFE"),
	VEHICLE_LURCHER = RAGE_JOAAT("LURCHER"),
	VEHICLE_MOONBEAM = RAGE_JOAAT("MOONBEAM"),
	VEHICLE_MOONBEAM2 = RAGE_JOAAT("MOONBEAM2"),
	VEHICLE_NIGHTSHADE = RAGE_JOAAT("NIGHTSHADE"),
	VEHICLE_PHOENIX = RAGE_JOAAT("PHOENIX"),
	VEHICLE_PICADOR = RAGE_JOAAT("PICADOR"),
	VEHICLE_RATLOADER = RAGE_JOAAT("RATLOADER"),
	VEHICLE_RATLOADER2 = RAGE_JOAAT("RATLOADER2"),
	VEHICLE_RUINER = RAGE_JOAAT("RUINER"),
	VEHICLE_RUINER2 = RAGE_JOAAT("RUINER2"),
	VEHICLE_RUINER3 = RAGE_JOAAT("RUINER3"),
	VEHICLE_SABREGT = RAGE_JOAAT("SABREGT"),
	VEHICLE_SABREGT2 = RAGE_JOAAT("SABREGT2"),
	VEHICLE_SLAMVAN = RAGE_JOAAT("SLAMVAN"),
	VEHICLE_SLAMVAN2 = RAGE_JOAAT("SLAMVAN2"),
	VEHICLE_SLAMVAN3 = RAGE_JOAAT("SLAMVAN3"),
	VEHICLE_STALION = RAGE_JOAAT("STALION"),
	VEHICLE_STALION2 = RAGE_JOAAT("STALION2"),
	VEHICLE_TAMPA = RAGE_JOAAT("TAMPA"),
	VEHICLE_TAMPA3 = RAGE_JOAAT("TAMPA3"),
	VEHICLE_VIGERO = RAGE_JOAAT("VIGERO"),
	VEHICLE_VIRGO = RAGE_JOAAT("VIRGO"),
	VEHICLE_VIRGO2 = RAGE_JOAAT("VIRGO2"),
	VEHICLE_VIRGO3 = RAGE_JOAAT("VIRGO3"),
	VEHICLE_VOODOO = RAGE_JOAAT("VOODOO"),
	VEHICLE_VOODOO2 = RAGE_JOAAT("VOODOO2"),
	VEHICLE_YOSEMITE = RAGE_JOAAT("YOSEMITE"),
};

enum OffRoad : Hash
{
	VEHICLE_BFINJECTION = RAGE_JOAAT("BFINJECTION"),
	VEHICLE_BIFTA = RAGE_JOAAT("BIFTA"),
	VEHICLE_BLAZER = RAGE_JOAAT("BLAZER"),
	VEHICLE_BLAZER2 = RAGE_JOAAT("BLAZER2"),
	VEHICLE_BLAZER3 = RAGE_JOAAT("BLAZER3"),
	VEHICLE_BLAZER4 = RAGE_JOAAT("BLAZER4"),
	VEHICLE_BLAZER5 = RAGE_JOAAT("BLAZER5"),
	VEHICLE_BODHI2 = RAGE_JOAAT("BODHI2"),
	VEHICLE_BRAWLER = RAGE_JOAAT("BRAWLER"),
	VEHICLE_DLOADER = RAGE_JOAAT("DLOADER"),
	VEHICLE_DUBSTA3 = RAGE_JOAAT("DUBSTA3"),
	VEHICLE_DUNE = RAGE_JOAAT("DUNE"),
	VEHICLE_DUNE2 = RAGE_JOAAT("DUNE2"),
	VEHICLE_DUNE3 = RAGE_JOAAT("DUNE3"),
	VEHICLE_DUNE4 = RAGE_JOAAT("DUNE4"),
	VEHICLE_DUNE5 = RAGE_JOAAT("DUNE5"),
	VEHICLE_FREECRAWLER = RAGE_JOAAT("FREECRAWLER"),
	VEHICLE_INSURGENT = RAGE_JOAAT("INSURGENT"),
	VEHICLE_INSURGENT2 = RAGE_JOAAT("INSURGENT2"),
	VEHICLE_INSURGENT3 = RAGE_JOAAT("INSURGENT3"),
	VEHICLE_KALAHARI = RAGE_JOAAT("KALAHARI"),
	VEHICLE_KAMACHO = RAGE_JOAAT("KAMACHO"),
	VEHICLE_MARSHALL = RAGE_JOAAT("MARSHALL"),
	VEHICLE_MESA3 = RAGE_JOAAT("MESA3"),
	VEHICLE_MONSTER = RAGE_JOAAT("MONSTER"),
	VEHICLE_MENACER = RAGE_JOAAT("MENACER"),
	VEHICLE_NIGHTSHARK = RAGE_JOAAT("NIGHTSHARK"),
	VEHICLE_RANCHERXL = RAGE_JOAAT("RANCHERXL"),
	VEHICLE_RANCHERXL2 = RAGE_JOAAT("RANCHERXL2"),
	VEHICLE_REBEL = RAGE_JOAAT("REBEL"),
	VEHICLE_REBEL2 = RAGE_JOAAT("REBEL2"),
	VEHICLE_RIATA = RAGE_JOAAT("RIATA"),
	VEHICLE_SANDKING = RAGE_JOAAT("SANDKING"),
	VEHICLE_SANDKING2 = RAGE_JOAAT("SANDKING2"),
	VEHICLE_TECHNICAL = RAGE_JOAAT("TECHNICAL"),
	VEHICLE_TECHNICAL2 = RAGE_JOAAT("TECHNICAL2"),
	VEHICLE_TECHNICAL3 = RAGE_JOAAT("TECHNICAL3"),
	VEHICLE_TROPHYTRUCK = RAGE_JOAAT("TROPHYTRUCK"),
	VEHICLE_TROPHYTRUCK2 = RAGE_JOAAT("TROPHYTRUCK2"),
};

enum Planes : Hash
{
	VEHICLE_ALPHAZ1 = RAGE_JOAAT("ALPHAZ1"),
	VEHICLE_AVENGER = RAGE_JOAAT("AVENGER"),
	VEHICLE_BESRA = RAGE_JOAAT("BESRA"),
	VEHICLE_BLIMP = RAGE_JOAAT("BLIMP"),
	VEHICLE_BLIMP2 = RAGE_JOAAT("BLIMP2"),
	VEHICLE_BLIMP3 = RAGE_JOAAT("BLIMP3"),
	VEHICLE_BOMBUSHKA = RAGE_JOAAT("BOMBUSHKA"),
	VEHICLE_CARGOPLANE = RAGE_JOAAT("CARGOPLANE"),
	VEHICLE_CUBAN800 = RAGE_JOAAT("CUBAN800"),
	VEHICLE_DODO = RAGE_JOAAT("DODO"),
	VEHICLE_DUSTER = RAGE_JOAAT("DUSTER"),
	VEHICLE_HOWARD = RAGE_JOAAT("HOWARD"),
	VEHICLE_HYDRA = RAGE_JOAAT("HYDRA"),
	VEHICLE_JET = RAGE_JOAAT("JET"),
	VEHICLE_LAZER = RAGE_JOAAT("LAZER"),
	VEHICLE_LUXOR = RAGE_JOAAT("LUXOR"),
	VEHICLE_LUXOR2 = RAGE_JOAAT("LUXOR2"),
	VEHICLE_MAMMATUS = RAGE_JOAAT("MAMMATUS"),
	VEHICLE_MICROLIGHT = RAGE_JOAAT("MICROLIGHT"),
	VEHICLE_MILJET = RAGE_JOAAT("MILJET"),
	VEHICLE_MOGUL = RAGE_JOAAT("MOGUL"),
	VEHICLE_MOLOTOK = RAGE_JOAAT("MOLOTOK"),
	VEHICLE_NIMBUS = RAGE_JOAAT("NIMBUS"),
	VEHICLE_NOKOTA = RAGE_JOAAT("NOKOTA"),
	VEHICLE_PYRO = RAGE_JOAAT("PYRO"),
	VEHICLE_ROGUE = RAGE_JOAAT("ROGUE"),
	VEHICLE_SEABREEZE = RAGE_JOAAT("SEABREEZE"),
	VEHICLE_SHAMAL = RAGE_JOAAT("SHAMAL"),
	VEHICLE_STARLING = RAGE_JOAAT("STARLING"),
	VEHICLE_STRIKEFORCE = RAGE_JOAAT("STRIKEFORCE"),
	VEHICLE_STUNT = RAGE_JOAAT("STUNT"),
	VEHICLE_TITAN = RAGE_JOAAT("TITAN"),
	VEHICLE_TULA = RAGE_JOAAT("TULA"),
	VEHICLE_VELUM = RAGE_JOAAT("VELUM"),
	VEHICLE_VELUM2 = RAGE_JOAAT("VELUM2"),
	VEHICLE_VESTRA = RAGE_JOAAT("VESTRA"),
	VEHICLE_VOLATOL = RAGE_JOAAT("VOLATOL"),
};

enum SUVs : Hash
{
	VEHICLE_BALLER = RAGE_JOAAT("BALLER"),
	VEHICLE_BALLER2 = RAGE_JOAAT("BALLER2"),
	VEHICLE_BALLER3 = RAGE_JOAAT("BALLER3"),
	VEHICLE_BALLER4 = RAGE_JOAAT("BALLER4"),
	VEHICLE_BALLER5 = RAGE_JOAAT("BALLER5"),
	VEHICLE_BALLER6 = RAGE_JOAAT("BALLER6"),
	VEHICLE_BJXL = RAGE_JOAAT("BJXL"),
	VEHICLE_CAVALCADE = RAGE_JOAAT("CAVALCADE"),
	VEHICLE_CAVALCADE2 = RAGE_JOAAT("CAVALCADE2"),
	VEHICLE_CONTENDER = RAGE_JOAAT("CONTENDER"),
	VEHICLE_DUBSTA = RAGE_JOAAT("DUBSTA"),
	VEHICLE_DUBSTA2 = RAGE_JOAAT("DUBSTA2"),
	VEHICLE_FQ2 = RAGE_JOAAT("FQ2"),
	VEHICLE_GRANGER = RAGE_JOAAT("GRANGER"),
	VEHICLE_GRESLEY = RAGE_JOAAT("GRESLEY"),
	VEHICLE_HABANERO = RAGE_JOAAT("HABANERO"),
	VEHICLE_HUNTLEY = RAGE_JOAAT("HUNTLEY"),
	VEHICLE_LANDSTALKER = RAGE_JOAAT("LANDSTALKER"),
	VEHICLE_MESA = RAGE_JOAAT("MESA"),
	VEHICLE_MESA2 = RAGE_JOAAT("MESA2"),
	VEHICLE_PATRIOT = RAGE_JOAAT("PATRIOT"),
	VEHICLE_PATRIOT2 = RAGE_JOAAT("PATRIOT2"),
	VEHICLE_RADI = RAGE_JOAAT("RADI"),
	VEHICLE_ROCOTO = RAGE_JOAAT("ROCOTO"),
	VEHICLE_SEMINOLE = RAGE_JOAAT("SEMINOLE"),
	VEHICLE_SERRANO = RAGE_JOAAT("SERRANO"),
	VEHICLE_XLS = RAGE_JOAAT("XLS"),
	VEHICLE_XLS2 = RAGE_JOAAT("XLS2"),
};

enum Sedans : Hash
{
	VEHICLE_ASEA = RAGE_JOAAT("ASEA"),
	VEHICLE_ASEA2 = RAGE_JOAAT("ASEA2"),
	VEHICLE_ASTEROPE = RAGE_JOAAT("ASTEROPE"),
	VEHICLE_CHEBUREK = RAGE_JOAAT("CHEBUREK"),
	VEHICLE_COG55 = RAGE_JOAAT("COG55"),
	VEHICLE_COG552 = RAGE_JOAAT("COG552"),
	VEHICLE_COGNOSCENTI = RAGE_JOAAT("COGNOSCENTI"),
	VEHICLE_COGNOSCENTI2 = RAGE_JOAAT("COGNOSCENTI2"),
	VEHICLE_EMPEROR = RAGE_JOAAT("EMPEROR"),
	VEHICLE_EMPEROR2 = RAGE_JOAAT("EMPEROR2"),
	VEHICLE_EMPEROR3 = RAGE_JOAAT("EMPEROR3"),
	VEHICLE_FUGITIVE = RAGE_JOAAT("FUGITIVE"),
	VEHICLE_GLENDALE = RAGE_JOAAT("GLENDALE"),
	VEHICLE_INGOT = RAGE_JOAAT("INGOT"),
	VEHICLE_INTRUDER = RAGE_JOAAT("INTRUDER"),
	VEHICLE_LIMO2 = RAGE_JOAAT("LIMO2"),
	VEHICLE_PREMIER = RAGE_JOAAT("PREMIER"),
	VEHICLE_PRIMO = RAGE_JOAAT("PRIMO"),
	VEHICLE_PRIMO2 = RAGE_JOAAT("PRIMO2"),
	VEHICLE_REGINA = RAGE_JOAAT("REGINA"),
	VEHICLE_ROMERO = RAGE_JOAAT("ROMERO"),
	VEHICLE_SCHAFTER2 = RAGE_JOAAT("SCHAFTER2"),
	VEHICLE_SCHAFTER5 = RAGE_JOAAT("SCHAFTER5"),
	VEHICLE_SCHAFTER6 = RAGE_JOAAT("SCHAFTER6"),
	VEHICLE_STAFFORD = RAGE_JOAAT("STAFFORD"),
	VEHICLE_STANIER = RAGE_JOAAT("STANIER"),
	VEHICLE_STRATUM = RAGE_JOAAT("STRATUM"),
	VEHICLE_STRETCH = RAGE_JOAAT("STRETCH"),
	VEHICLE_SUPERD = RAGE_JOAAT("SUPERD"),
	VEHICLE_SURGE = RAGE_JOAAT("SURGE"),
	VEHICLE_TAILGATER = RAGE_JOAAT("TAILGATER"),
	VEHICLE_WARRENER = RAGE_JOAAT("WARRENER"),
	VEHICLE_WASHINGTON = RAGE_JOAAT("WASHINGTON"),
};

enum Service : Hash
{
	VEHICLE_AIRBUS = RAGE_JOAAT("AIRBUS"),
	VEHICLE_BRICKADE = RAGE_JOAAT("BRICKADE"),
	VEHICLE_BUS = RAGE_JOAAT("BUS"),
	VEHICLE_COACH = RAGE_JOAAT("COACH"),
	VEHICLE_PBUS2 = RAGE_JOAAT("PBUS2"),
	VEHICLE_RALLYTRUCK = RAGE_JOAAT("RALLYTRUCK"),
	VEHICLE_RENTALBUS = RAGE_JOAAT("RENTALBUS"),
	VEHICLE_TAXI = RAGE_JOAAT("TAXI"),
	VEHICLE_TOURBUS = RAGE_JOAAT("TOURBUS"),
	VEHICLE_TRASH = RAGE_JOAAT("TRASH"),
	VEHICLE_TRASH2 = RAGE_JOAAT("TRASH2"),
	VEHICLE_WASTELANDER = RAGE_JOAAT("WASTELANDER"),
};

enum Sports : Hash
{
	VEHICLE_ALPHA = RAGE_JOAAT("ALPHA"),
	VEHICLE_BANSHEE = RAGE_JOAAT("BANSHEE"),
	VEHICLE_BESTIAGTS = RAGE_JOAAT("BESTIAGTS"),
	VEHICLE_BLISTA2 = RAGE_JOAAT("BLISTA2"),
	VEHICLE_BLISTA3 = RAGE_JOAAT("BLISTA3"),
	VEHICLE_BUFFALO = RAGE_JOAAT("BUFFALO"),
	VEHICLE_BUFFALO2 = RAGE_JOAAT("BUFFALO2"),
	VEHICLE_BUFFALO3 = RAGE_JOAAT("BUFFALO3"),
	VEHICLE_CARBONIZZARE = RAGE_JOAAT("CARBONIZZARE"),
	VEHICLE_COMET2 = RAGE_JOAAT("COMET2"),
	VEHICLE_COMET3 = RAGE_JOAAT("COMET3"),
	VEHICLE_COMET4 = RAGE_JOAAT("COMET4"),
	VEHICLE_COMET5 = RAGE_JOAAT("COMET5"),
	VEHICLE_COQUETTE = RAGE_JOAAT("COQUETTE"),
	VEHICLE_ELEGY = RAGE_JOAAT("ELEGY"),
	VEHICLE_ELEGY2 = RAGE_JOAAT("ELEGY2"),
	VEHICLE_FELTZER2 = RAGE_JOAAT("FELTZER2"),
	VEHICLE_FLASHGT = RAGE_JOAAT("FLASHGT"),
	VEHICLE_FUROREGT = RAGE_JOAAT("FUROREGT"),
	VEHICLE_FUSILADE = RAGE_JOAAT("FUSILADE"),
	VEHICLE_FUTO = RAGE_JOAAT("FUTO"),
	VEHICLE_GB200 = RAGE_JOAAT("GB200"),
	VEHICLE_HOTRING = RAGE_JOAAT("HOTRING"),
	VEHICLE_JESTER = RAGE_JOAAT("JESTER"),
	VEHICLE_JESTER2 = RAGE_JOAAT("JESTER2"),
	VEHICLE_JESTER3 = RAGE_JOAAT("JESTER3"),
	VEHICLE_KHAMELION = RAGE_JOAAT("KHAMELION"),
	VEHICLE_KURUMA = RAGE_JOAAT("KURUMA"),
	VEHICLE_KURUMA2 = RAGE_JOAAT("KURUMA2"),
	VEHICLE_LYNX2 = RAGE_JOAAT("LYNX2"),
	VEHICLE_MASSACRO = RAGE_JOAAT("MASSACRO"),
	VEHICLE_MASSACRO2 = RAGE_JOAAT("MASSACRO2"),
	VEHICLE_NEON = RAGE_JOAAT("NEON"),
	VEHICLE_NINEF = RAGE_JOAAT("NINEF"),
	VEHICLE_NINEF2 = RAGE_JOAAT("NINEF2"),
	VEHICLE_OMNIS = RAGE_JOAAT("OMNIS"),
	VEHICLE_PARIAH = RAGE_JOAAT("PARIAH"),
	VEHICLE_PENUMBRA = RAGE_JOAAT("PENUMBRA"),
	VEHICLE_RAIDEN = RAGE_JOAAT("RAIDEN"),
	VEHICLE_RAPIDGT = RAGE_JOAAT("RAPIDGT"),
	VEHICLE_RAPIDGT2 = RAGE_JOAAT("RAPIDGT2"),
	VEHICLE_RAPTOR = RAGE_JOAAT("RAPTOR"),
	VEHICLE_REVOLTER = RAGE_JOAAT("REVOLTER"),
	VEHICLE_RUSTON = RAGE_JOAAT("RUSTON"),
	VEHICLE_SCHAFTER3 = RAGE_JOAAT("SCHAFTER3"),
	VEHICLE_SCHAFTER4 = RAGE_JOAAT("SCHAFTER4"),
	VEHICLE_SCHWARZER = RAGE_JOAAT("SCHWARZER"),
	VEHICLE_SENTINEL3 = RAGE_JOAAT("SENTINEL3"),
	VEHICLE_SEVEN70 = RAGE_JOAAT("SEVEN70"),
	VEHICLE_SPECTER = RAGE_JOAAT("SPECTER"),
	VEHICLE_SPECTER2 = RAGE_JOAAT("SPECTER2"),
	VEHICLE_STREITER = RAGE_JOAAT("STREITER"),
	VEHICLE_SULTAN = RAGE_JOAAT("SULTAN"),
	VEHICLE_SURANO = RAGE_JOAAT("SURANO"),
	VEHICLE_TAMPA2 = RAGE_JOAAT("TAMPA2"),
	VEHICLE_TROPOS = RAGE_JOAAT("TROPOS"),
	VEHICLE_VERLIERER2 = RAGE_JOAAT("VERLIERER2"),
};

enum SportsClassic : Hash
{
	VEHICLE_ARDENT = RAGE_JOAAT("ARDENT"),
	VEHICLE_BTYPE = RAGE_JOAAT("BTYPE"),
	VEHICLE_BTYPE2 = RAGE_JOAAT("BTYPE2"),
	VEHICLE_BTYPE3 = RAGE_JOAAT("BTYPE3"),
	VEHICLE_CASCO = RAGE_JOAAT("CASCO"),
	VEHICLE_CHEETAH2 = RAGE_JOAAT("CHEETAH2"),
	VEHICLE_COQUETTE2 = RAGE_JOAAT("COQUETTE2"),
	VEHICLE_DELUXO = RAGE_JOAAT("DELUXO"),
	VEHICLE_FAGALOA = RAGE_JOAAT("FAGALOA"),
	VEHICLE_FELTZER3 = RAGE_JOAAT("FELTZER3"),
	VEHICLE_GT500 = RAGE_JOAAT("GT500"),
	VEHICLE_HUSTLER = RAGE_JOAAT("HUSTLER"),
	VEHICLE_INFERNUS2 = RAGE_JOAAT("INFERNUS2"),
	VEHICLE_JB700 = RAGE_JOAAT("JB700"),
	VEHICLE_MAMBA = RAGE_JOAAT("MAMBA"),
	VEHICLE_MANANA = RAGE_JOAAT("MANANA"),
	VEHICLE_MICHELLI = RAGE_JOAAT("MICHELLI"),
	VEHICLE_MONROE = RAGE_JOAAT("MONROE"),
	VEHICLE_PEYOTE = RAGE_JOAAT("PEYOTE"),
	VEHICLE_PIGALLE = RAGE_JOAAT("PIGALLE"),
	VEHICLE_RAPIDGT3 = RAGE_JOAAT("RAPIDGT3"),
	VEHICLE_RETINUE = RAGE_JOAAT("RETINUE"),
	VEHICLE_SAVESTRA = RAGE_JOAAT("SAVESTRA"),
	VEHICLE_STINGER = RAGE_JOAAT("STINGER"),
	VEHICLE_STINGERGT = RAGE_JOAAT("STINGERGT"),
	VEHICLE_STROMBERG = RAGE_JOAAT("STROMBERG"),
	VEHICLE_SWINGER = RAGE_JOAAT("SWINGER"),
	VEHICLE_TORERO = RAGE_JOAAT("TORERO"),
	VEHICLE_TORNADO = RAGE_JOAAT("TORNADO"),
	VEHICLE_TORNADO2 = RAGE_JOAAT("TORNADO2"),
	VEHICLE_TORNADO3 = RAGE_JOAAT("TORNADO3"),
	VEHICLE_TORNADO4 = RAGE_JOAAT("TORNADO4"),
	VEHICLE_TORNADO5 = RAGE_JOAAT("TORNADO5"),
	VEHICLE_TORNADO6 = RAGE_JOAAT("TORNADO6"),
	VEHICLE_TURISMO2 = RAGE_JOAAT("TURISMO2"),
	VEHICLE_VISERIS = RAGE_JOAAT("VISERIS"),
	VEHICLE_Z190 = RAGE_JOAAT("Z190"),
	VEHICLE_ZTYPE = RAGE_JOAAT("ZTYPE"),
};

enum Super : Hash
{
	VEHICLE_ADDER = RAGE_JOAAT("ADDER"),
	VEHICLE_AUTARCH = RAGE_JOAAT("AUTARCH"),
	VEHICLE_BANSHEE2 = RAGE_JOAAT("BANSHEE2"),
	VEHICLE_BULLETGT = RAGE_JOAAT("BULLET"),
	VEHICLE_CHEETAH = RAGE_JOAAT("CHEETAH"),
	VEHICLE_CYCLONE = RAGE_JOAAT("CYCLONE"),
	VEHICLE_ENTITYXF = RAGE_JOAAT("ENTITYXF"),
	VEHICLE_ENTITY2 = RAGE_JOAAT("ENTITY2"),
	VEHICLE_FMJ = RAGE_JOAAT("FMJ"),
	VEHICLE_GP1 = RAGE_JOAAT("GP1"),
	VEHICLE_INFERNUS = RAGE_JOAAT("INFERNUS"),
	VEHICLE_ITALIGTB = RAGE_JOAAT("ITALIGTB"),
	VEHICLE_ITALIGTB2 = RAGE_JOAAT("ITALIGTB2"),
	VEHICLE_LE7B = RAGE_JOAAT("LE7B"),
	VEHICLE_NERO = RAGE_JOAAT("NERO"),
	VEHICLE_NERO2 = RAGE_JOAAT("NERO2"),
	VEHICLE_OSIRIS = RAGE_JOAAT("OSIRIS"),
	VEHICLE_PENETRATOR = RAGE_JOAAT("PENETRATOR"),
	VEHICLE_PFISTER811 = RAGE_JOAAT("PFISTER811"),
	VEHICLE_PROTOTIPO = RAGE_JOAAT("PROTOTIPO"),
	VEHICLE_REAPER = RAGE_JOAAT("REAPER"),
	VEHICLE_SC1 = RAGE_JOAAT("SC1"),
	VEHICLE_SCRAMJET = RAGE_JOAAT("SCRAMJET"),
	VEHICLE_SHEAVA = RAGE_JOAAT("SHEAVA"),
	VEHICLE_SULTANRS = RAGE_JOAAT("SULTANRS"),
	VEHICLE_T20 = RAGE_JOAAT("T20"),
	VEHICLE_TAIPAN = RAGE_JOAAT("TAIPAN"),
	VEHICLE_TEMPESTA = RAGE_JOAAT("TEMPESTA"),
	VEHICLE_TEZERACT = RAGE_JOAAT("TEZERACT"),
	VEHICLE_TURISMOR = RAGE_JOAAT("TURISMOR"),
	VEHICLE_TYRANT = RAGE_JOAAT("TYRANT"),
	VEHICLE_TYRUS = RAGE_JOAAT("TYRUS"),
	VEHICLE_VACCA = RAGE_JOAAT("VACCA"),
	VEHICLE_VAGNER = RAGE_JOAAT("VAGNER"),
	VEHICLE_VIGILANTE = RAGE_JOAAT("VIGILANTE"),
	VEHICLE_VISIONE = RAGE_JOAAT("VISIONE"),
	VEHICLE_VOLTIC = RAGE_JOAAT("VOLTIC"),
	VEHICLE_VOLTIC2 = RAGE_JOAAT("VOLTIC2"),
	VEHICLE_XA21 = RAGE_JOAAT("XA21"),
	VEHICLE_ZENTORNO = RAGE_JOAAT("ZENTORNO"),
};

enum Trailers : Hash
{
	VEHICLE_ARMYTANKER = RAGE_JOAAT("ARMYTANKER"),
	VEHICLE_ARMYTRAILER2 = RAGE_JOAAT("ARMYTRAILER2"),
	VEHICLE_BALETRAILER = RAGE_JOAAT("BALETRAILER"),
	VEHICLE_BOATTRAILER = RAGE_JOAAT("BOATTRAILER"),
	VEHICLE_CABLECAR = RAGE_JOAAT("CABLECAR"),
	VEHICLE_DOCKTRAILER = RAGE_JOAAT("DOCKTRAILER"),
	VEHICLE_GRAINTRAILER = RAGE_JOAAT("GRAINTRAILER"),
	VEHICLE_PROPTRAILER = RAGE_JOAAT("PROPTRAILER"),
	VEHICLE_RAKETRAILER = RAGE_JOAAT("RAKETRAILER"),
	VEHICLE_TR2 = RAGE_JOAAT("TR2"),
	VEHICLE_TR3 = RAGE_JOAAT("TR3"),
	VEHICLE_TR4 = RAGE_JOAAT("TR4"),
	VEHICLE_TRFLAT = RAGE_JOAAT("TRFLAT"),
	VEHICLE_TVTRAILER = RAGE_JOAAT("TVTRAILER"),
	VEHICLE_TANKER = RAGE_JOAAT("TANKER"),
	VEHICLE_TANKER2 = RAGE_JOAAT("TANKER2"),
	VEHICLE_TRAILERLOGS = RAGE_JOAAT("TRAILERLOGS"),
	VEHICLE_TRAILERSMALL = RAGE_JOAAT("TRAILERSMALL"),
	VEHICLE_TRAILERS = RAGE_JOAAT("TRAILERS"),
	VEHICLE_TRAILERS2 = RAGE_JOAAT("TRAILERS2"),
	VEHICLE_TRAILERS3 = RAGE_JOAAT("TRAILERS3"),
};

enum Trains : Hash
{
	VEHICLE_FREIGHT = RAGE_JOAAT("FREIGHT"),
	VEHICLE_FREIGHTCAR = RAGE_JOAAT("FREIGHTCAR"),
	VEHICLE_FREIGHTCONT1 = RAGE_JOAAT("FREIGHTCONT1"),
	VEHICLE_FREIGHTCONT2 = RAGE_JOAAT("FREIGHTCONT2"),
	VEHICLE_FREIGHTGRAIN = RAGE_JOAAT("FREIGHTGRAIN"),
	VEHICLE_TANKERCAR = RAGE_JOAAT("TANKERCAR"),
};

enum Utility : Hash
{
	VEHICLE_AIRTUG = RAGE_JOAAT("AIRTUG"),
	VEHICLE_CADDY = RAGE_JOAAT("CADDY"),
	VEHICLE_CADDY2 = RAGE_JOAAT("CADDY2"),
	VEHICLE_CADDY3 = RAGE_JOAAT("CADDY3"),
	VEHICLE_CARACARA = RAGE_JOAAT("CARACARA"),
	VEHICLE_DOCKTUG = RAGE_JOAAT("DOCKTUG"),
	VEHICLE_FORKLIFT = RAGE_JOAAT("FORKLIFT"),
	VEHICLE_MOWER = RAGE_JOAAT("MOWER"),
	VEHICLE_RIPLEY = RAGE_JOAAT("RIPLEY"),
	VEHICLE_SADLER = RAGE_JOAAT("SADLER"),
	VEHICLE_SADLER2 = RAGE_JOAAT("SADLER2"),
	VEHICLE_SCRAP = RAGE_JOAAT("SCRAP"),
	VEHICLE_TOWTRUCK = RAGE_JOAAT("TOWTRUCK"),
	VEHICLE_TOWTRUCK2 = RAGE_JOAAT("TOWTRUCK2"),
	VEHICLE_TRACTOR = RAGE_JOAAT("TRACTOR"),
	VEHICLE_TRACTOR2 = RAGE_JOAAT("TRACTOR2"),
	VEHICLE_TRACTOR3 = RAGE_JOAAT("TRACTOR3"),
	VEHICLE_UTILLITRUCK = RAGE_JOAAT("UTILLITRUCK"),
	VEHICLE_UTILLITRUCK2 = RAGE_JOAAT("UTILLITRUCK2"),
	VEHICLE_UTILLITRUCK3 = RAGE_JOAAT("UTILLITRUCK3"),
};

enum Vans : Hash
{
	VEHICLE_BISON = RAGE_JOAAT("BISON"),
	VEHICLE_BISON2 = RAGE_JOAAT("BISON2"),
	VEHICLE_BISON3 = RAGE_JOAAT("BISON3"),
	VEHICLE_BOBCATXL = RAGE_JOAAT("BOBCATXL"),
	VEHICLE_BOXVILLE = RAGE_JOAAT("BOXVILLE"),
	VEHICLE_BOXVILLE2 = RAGE_JOAAT("BOXVILLE2"),
	VEHICLE_BOXVILLE3 = RAGE_JOAAT("BOXVILLE3"),
	VEHICLE_BOXVILLE4 = RAGE_JOAAT("BOXVILLE4"),
	VEHICLE_BOXVILLE5 = RAGE_JOAAT("BOXVILLE5"),
	VEHICLE_BURRITO = RAGE_JOAAT("BURRITO"),
	VEHICLE_BURRITO2 = RAGE_JOAAT("BURRITO2"),
	VEHICLE_BURRITO3 = RAGE_JOAAT("BURRITO3"),
	VEHICLE_BURRITO4 = RAGE_JOAAT("BURRITO4"),
	VEHICLE_BURRITO5 = RAGE_JOAAT("BURRITO5"),
	VEHICLE_CAMPER = RAGE_JOAAT("CAMPER"),
	VEHICLE_GBURRITO = RAGE_JOAAT("GBURRITO"),
	VEHICLE_GBURRITO2 = RAGE_JOAAT("GBURRITO2"),
	VEHICLE_JOURNEY = RAGE_JOAAT("JOURNEY"),
	VEHICLE_MINIVAN = RAGE_JOAAT("MINIVAN"),
	VEHICLE_MINIVAN2 = RAGE_JOAAT("MINIVAN2"),
	VEHICLE_PARADISE = RAGE_JOAAT("PARADISE"),
	VEHICLE_PONY = RAGE_JOAAT("PONY"),
	VEHICLE_PONY2 = RAGE_JOAAT("PONY2"),
	VEHICLE_RUMPO = RAGE_JOAAT("RUMPO"),
	VEHICLE_RUMPO2 = RAGE_JOAAT("RUMPO2"),
	VEHICLE_RUMPO3 = RAGE_JOAAT("RUMPO3"),
	VEHICLE_SPEEDO = RAGE_JOAAT("SPEEDO"),
	VEHICLE_SPEEDO2 = RAGE_JOAAT("SPEEDO2"),
	VEHICLE_SPEEDO4 = RAGE_JOAAT("SPEEDO4"),
	VEHICLE_SURFER = RAGE_JOAAT("SURFER"),
	VEHICLE_SURFER2 = RAGE_JOAAT("SURFER2"),
	VEHICLE_TACO = RAGE_JOAAT("TACO"),
	VEHICLE_YOUGA = RAGE_JOAAT("YOUGA"),
	VEHICLE_YOUGA2 = RAGE_JOAAT("YOUGA2"),
};

enum ArenaWar : Hash
{
	VEHICLE_BRUISER = RAGE_JOAAT("BRUISER"),
	VEHICLE_BRUISER2 = RAGE_JOAAT("BRUISER2"),
	VEHICLE_BRUISER3 = RAGE_JOAAT("BRUISER3"),
	VEHICLE_BRUTUS = RAGE_JOAAT("BRUTUS"),
	VEHICLE_BRUTUS2 = RAGE_JOAAT("BRUTUS2"),
	VEHICLE_BRUTUS3 = RAGE_JOAAT("BRUTUS3"),
	VEHICLE_CERBERUS = RAGE_JOAAT("CERBERUS"),
	VEHICLE_CERBERUS2 = RAGE_JOAAT("CERBERUS2"),
	VEHICLE_CERBERUS3 = RAGE_JOAAT("CERBERUS3"),
	VEHICLE_CLIQUE = RAGE_JOAAT("CLIQUE"),
	VEHICLE_DEATHBIKE = RAGE_JOAAT("DEATHBIKE"),
	VEHICLE_DEATHBIKE2 = RAGE_JOAAT("DEATHBIKE2"),
	VEHICLE_DEATHBIKE3 = RAGE_JOAAT("DEATHBIKE3"),
	VEHICLE_DEVESTE = RAGE_JOAAT("DEVESTE"),
	VEHICLE_DEVIANT = RAGE_JOAAT("DEVIANT"),
	VEHICLE_DOMINATOR4 = RAGE_JOAAT("DOMINATOR4"),
	VEHICLE_DOMINATOR5 = RAGE_JOAAT("DOMINATOR5"),
	VEHICLE_DOMINATOR6 = RAGE_JOAAT("DOMINATOR6"),
	VEHICLE_IMPALER = RAGE_JOAAT("IMPALER"),
	VEHICLE_IMPALER2 = RAGE_JOAAT("IMPALER2"),
	VEHICLE_IMPALER3 = RAGE_JOAAT("IMPALER3"),
	VEHICLE_IMPALER4 = RAGE_JOAAT("IMPALER4"),
	VEHICLE_IMPERATOR = RAGE_JOAAT("IMPERATOR"),
	VEHICLE_IMPERATOR2 = RAGE_JOAAT("IMPERATOR2"),
	VEHICLE_IMPERATOR3 = RAGE_JOAAT("IMPERATOR3"),
	VEHICLE_ISSI4 = RAGE_JOAAT("ISSI4"),
	VEHICLE_ISSI5 = RAGE_JOAAT("ISSI5"),
	VEHICLE_ISSI6 = RAGE_JOAAT("ISSI6"),
	VEHICLE_ITALIGTO = RAGE_JOAAT("ITALIGTO"),
	VEHICLE_MONSTER3 = RAGE_JOAAT("MONSTER3"),
	VEHICLE_MONSTER4 = RAGE_JOAAT("MONSTER4"),
	VEHICLE_MONSTER5 = RAGE_JOAAT("MONSTER5"),
	VEHICLE_RCBANDITO = RAGE_JOAAT("RCBANDITO"),
	VEHICLE_SCARAB2 = RAGE_JOAAT("SCARAB2"),
	VEHICLE_SCARAB3 = RAGE_JOAAT("SCARAB3"),
	VEHICLE_SCHLAGEN = RAGE_JOAAT("SCHLAGEN"),
	VEHICLE_SLAMVAN4 = RAGE_JOAAT("SLAMVAN4"),
	VEHICLE_SLAMVAN5 = RAGE_JOAAT("SLAMVAN5"),
	VEHICLE_SLAMVAN6 = RAGE_JOAAT("SLAMVAN6"),
	VEHICLE_TOROS = RAGE_JOAAT("TOROS"),
	VEHICLE_TULIP = RAGE_JOAAT("TULIP"),
	VEHICLE_VAMOS = RAGE_JOAAT("VAMOS"),
	VEHICLE_ZR380 = RAGE_JOAAT("ZR380"),
	VEHICLE_ZR3802 = RAGE_JOAAT("ZR3802"),
	VEHICLE_ZR3803 = RAGE_JOAAT("ZR3803"),
};

enum CasinoUpdate : Hash
{
	VEHICLE_CARACARA2 = RAGE_JOAAT("CARACARA2"),
	VEHICLE_DRAFTER = RAGE_JOAAT("DRAFTER"),
	VEHICLE_DYNASTY = RAGE_JOAAT("DYNASTY"),
	VEHICLE_EMERUS = RAGE_JOAAT("EMERUS"),
	VEHICLE_GAUNTLET3 = RAGE_JOAAT("GAUNTLET3"),
	VEHICLE_GAUNTLET4 = RAGE_JOAAT("GAUNTLET4"),
	VEHICLE_HELLION = RAGE_JOAAT("HELLION"),
	VEHICLE_ISSI7 = RAGE_JOAAT("ISSI7"),
	VEHICLE_JUGULAR = RAGE_JOAAT("JUGULAR"),
	VEHICLE_KRIEGER = RAGE_JOAAT("KRIEGER"),
	VEHICLE_LOCUST = RAGE_JOAAT("LOCUST"),
	VEHICLE_NEBULA = RAGE_JOAAT("NEBULA"),
	VEHICLE_NEO = RAGE_JOAAT("NEO"),
	VEHICLE_NOVAK = RAGE_JOAAT("NOVAK"),
	VEHICLE_PARAGON = RAGE_JOAAT("PARAGON"),
	VEHICLE_PARAGON2 = RAGE_JOAAT("PARAGON2"),
	VEHICLE_PEYOTE2 = RAGE_JOAAT("PEYOTE2"),
	VEHICLE_RROCKET = RAGE_JOAAT("RROCKET"),
	VEHICLE_S80 = RAGE_JOAAT("S80"),
	VEHICLE_THRAX = RAGE_JOAAT("THRAX"),
	VEHICLE_ZION3 = RAGE_JOAAT("ZION3"),
	VEHICLE_ZORRUSSO = RAGE_JOAAT("ZORRUSSO")
};

enum CasinoHeist : Hash
{
	VEHICLE_ASBO = RAGE_JOAAT("ABSO"),
	VEHICLE_EVERON = RAGE_JOAAT("EVERON"),
	VEHICLE_FORMULA = RAGE_JOAAT("FORMULA"),
	VEHICLE_FORMULA2 = RAGE_JOAAT("FORMULA2"),
	VEHICLE_FURIA = RAGE_JOAAT("FURIA"),
	VEHICLE_IMORGON = RAGE_JOAAT("IMORGON"),
	VEHICLE_JB7002 = RAGE_JOAAT("JB7002"),
	VEHICLE_KANJO = RAGE_JOAAT("KANJO"),
	VEHICLE_KOMODA = RAGE_JOAAT("KOMODA"),
	VEHICLE_MINITANK = RAGE_JOAAT("MINITANK"),
	VEHICLE_OUTLAW = RAGE_JOAAT("OUTLAW"),
	VEHICLE_REBLA = RAGE_JOAAT("REBLA"),
	VEHICLE_RETINUE2 = RAGE_JOAAT("RETINUE2"),
	VEHICLE_STRYDER = RAGE_JOAAT("STRYDER"),
	VEHICLE_SUGOI = RAGE_JOAAT("SUGOI"),
	VEHICLE_SULTAN2 = RAGE_JOAAT("SULTAN2"),
	VEHICLE_VAGRANT = RAGE_JOAAT("VAGRANT"),
	VEHICLE_VSTR = RAGE_JOAAT("VSTR"),
	VEHICLE_YOSEMITE2 = RAGE_JOAAT("YOSEMITE2"),
	VEHICLE_ZHABA = RAGE_JOAAT("ZHABA"),
};

enum SummerUpdate : Hash
{
	VEHICLE_CLUB = RAGE_JOAAT("CLUB"),
	VEHICLE_COQUETTE4 = RAGE_JOAAT("VEHICLE_COQUETTE4"),
	VEHICLE_DUKES3 = RAGE_JOAAT("DUKES3"),
	VEHICLE_GAUNTLET5 = RAGE_JOAAT("GAUNTLET5"),
	VEHICLE_GLENDALE2 = RAGE_JOAAT("GLENDALE2"),
	VEHICLE_LANDSTALKER2 = RAGE_JOAAT("LANDSTALKER2"),
	VEHICLE_MANANA2 = RAGE_JOAAT("MANANA2"),
	VEHICLE_OPENWHEEL1 = RAGE_JOAAT("OPENWHEEL1"),
	VEHICLE_OPENWHEEL2 = RAGE_JOAAT("OPENWHEEL2"),
	VEHICLE_PENUMBRA2 = RAGE_JOAAT("PENUMBRA2"),
	VEHICLE_PEYOTE3 = RAGE_JOAAT("PEYOTE3"),
	VEHICLE_SEMINOLE2 = RAGE_JOAAT("SEMINOLE2"),
	VEHICLE_TIGON = RAGE_JOAAT("TIGON"),
	VEHICLE_YOSEMITE3 = RAGE_JOAAT("YOSEMITE3"),
	VEHICLE_YOUGA3 = RAGE_JOAAT("YOUGA3")
};

enum CayoPericoHeist : Hash
{
	VEHICLE_ALKONOST = RAGE_JOAAT("ALKONOST"),
	VEHICLE_ANNIHILATOR2 = RAGE_JOAAT("ANNIHILATOR2"),
	VEHICLE_AVISA = RAGE_JOAAT("AVISA"),
	VEHICLE_BRIOSO2 = RAGE_JOAAT("BRIOSO2"),
	VEHICLE_DINGHY5 = RAGE_JOAAT("DINGHY5"),
	VEHICLE_ITALIRSX = RAGE_JOAAT("ITALIRSX"),
	VEHICLE_KOSATKA = RAGE_JOAAT("KOSATKA"),
	VEHICLE_LONGFIN = RAGE_JOAAT("LONGFIN"),
	VEHICLE_MANCHEZE = RAGE_JOAAT("MANCHEZE"),
	VEHICLE_PATROLBOAT = RAGE_JOAAT("PATROLBOAT"),
	VEHICLE_SEASPARROW2 = RAGE_JOAAT("SEASPARROW2"),
	VEHICLE_SLAMTRUCK = RAGE_JOAAT("SLAMTRUCK"),
	VEHICLE_SQUADDIE = RAGE_JOAAT("SQUADDIE"),
	VEHICLE_TOREADOR = RAGE_JOAAT("TOREADOR"),
	VEHICLE_VERUS = RAGE_JOAAT("VERUS"),
	VEHICLE_VETIR = RAGE_JOAAT("VETIR"),
	VEHICLE_VETO = RAGE_JOAAT("VETO"),
	VEHICLE_VETO2 = RAGE_JOAAT("VETO2"),
	VEHICLE_WEEVIL = RAGE_JOAAT("WEEVIL"),
	VEHICLE_WINKY = RAGE_JOAAT("WINKY")
};

enum LosSantosTuners : Hash
{
	VEHICLE_CALICO = RAGE_JOAAT("CALICO"),
	VEHICLE_COMET6 = RAGE_JOAAT("COMET6"),
	VEHICLE_CYPHER = RAGE_JOAAT("CYPHER"),
	VEHICLE_DOMINATOR7 = RAGE_JOAAT("DOMINATOR7"),
	VEHICLE_DOMINATOR8 = RAGE_JOAAT("DOMINATOR8"),
	VEHICLE_EUROS = RAGE_JOAAT("EUROS"),
	VEHICLE_FREIGHTCAR2 = RAGE_JOAAT("FREIGHTCAR2"),
	VEHICLE_FUTO2 = RAGE_JOAAT("FUTO2"),
	VEHICLE_GROWLER = RAGE_JOAAT("GROWLER"),
	VEHICLE_JESTER4 = RAGE_JOAAT("JESTER4"),
	VEHICLE_PREVION = RAGE_JOAAT("PREVION"),
	VEHICLE_REMUS = RAGE_JOAAT("REMUS"),
	VEHICLE_RT3000 = RAGE_JOAAT("RT3000"),
	VEHICLE_SULTAN3 = RAGE_JOAAT("SULTAN3"),
	VEHICLE_TAILGATER2 = RAGE_JOAAT("TAILGATER2"),
	VEHICLE_VECTRE = RAGE_JOAAT("VECTRE"),
	VEHICLE_WARRENER2 = RAGE_JOAAT("WARRENER2"),
	VEHICLE_ZR350 = RAGE_JOAAT("ZR350")
};

enum TheContract : Hash
{
	VEHICLE_BUFFALO4 = RAGE_JOAAT("BUFFALO4"),
	VEHICLE_GRANGER2 = RAGE_JOAAT("GRANGER2"),
	VEHICLE_IWAGEN = RAGE_JOAAT("IWAGEN"),
	VEHICLE_PATRIOT3 = RAGE_JOAAT("PATRIOT3"),
	VEHICLE_ASTRON = RAGE_JOAAT("ASTRON"),
	VEHICLE_DEITY = RAGE_JOAAT("DEITY"),
	VEHICLE_IGNUS = RAGE_JOAAT("IGNUS"),
	VEHICLE_JUBILEE = RAGE_JOAAT("JUBILEE"),
	VEHICLE_REEVER = RAGE_JOAAT("REEVER"),
	VEHICLE_SHINOBI = RAGE_JOAAT("SHINOBI"),
	VEHICLE_ZENO = RAGE_JOAAT("ZENO"),
	VEHICLE_BALLER7 = RAGE_JOAAT("BALLER7"),
	VEHICLE_CHAMPION = RAGE_JOAAT("CHAMPION"),
	VEHICLE_CINQUEMILA = RAGE_JOAAT("CINQUEMILA"),
	VEHICLE_COMET7 = RAGE_JOAAT("COMET7"),
	VEHICLE_YOUGA4 = RAGE_JOAAT("YOUGA4"),
	VEHICLE_MULE5 = RAGE_JOAAT("MULE5")
};

enum TheCriminalEnterprise : Hash
{
	VEHICLE_TENF = RAGE_JOAAT("TENF"),
	VEHICLE_TENF2 = RAGE_JOAAT("TENF2"),
	VEHICLE_WEEVIL2 = RAGE_JOAAT("WEEVIL2"),
	VEHICLE_TORERO2 = RAGE_JOAAT("TORERO2"),
	VEHICLE_SENTINEL4 = RAGE_JOAAT("SENTINEL4"),
	VEHICLE_POSTLUDE = RAGE_JOAAT("POSTLUDE"),
	VEHICLE_DRAUGUR = RAGE_JOAAT("DRAUGUR"),
	VEHICLE_RHINEHART = RAGE_JOAAT("RHINEHART"),
	VEHICLE_VIGERO2 = RAGE_JOAAT("VIGERO2"),
	VEHICLE_GREENWOOD = RAGE_JOAAT("GREENWOOD"),
	VEHICLE_OMNISEGT = RAGE_JOAAT("OMNISEGT"),
	VEHICLE_RUINER4 = RAGE_JOAAT("RUINER4"),
	VEHICLE_CORSITA = RAGE_JOAAT("CORSITA"),
	VEHICLE_LM87 = RAGE_JOAAT("LM87"),
	VEHICLE_SM722 = RAGE_JOAAT("SM722"),
	VEHICLE_CONADA = RAGE_JOAAT("CONADA"),
	VEHICLE_BRIOSO3 = RAGE_JOAAT("BRIOSO3"),
	VEHICLE_KANJOSJ = RAGE_JOAAT("KANJOSJ")
};

enum DrugWars : Hash
{
	VEHICLE_BOOR = RAGE_JOAAT("boor"),
	VEHICLE_BRICKADE2 = RAGE_JOAAT("brickade2"),
	VEHICLE_BROADWAY = RAGE_JOAAT("broadway"),
	VEHICLE_CARGOPLANE2 = RAGE_JOAAT("cargoplane2"),
	VEHICLE_ENTITY3 = RAGE_JOAAT("entity3"),
	VEHICLE_ENDORA = RAGE_JOAAT("eudora"),
	VEHICLE_EVERSON2 = RAGE_JOAAT("everon2"),
	VEHICLE_ISSI8 = RAGE_JOAAT("issi8"),
	VEHICLE_JOURNEY2 = RAGE_JOAAT("journey2"),
	VEHICLE_MANCHEZ3 = RAGE_JOAAT("manchez3"),
	VEHICLE_PANTHERE = RAGE_JOAAT("panthere"),
	VEHICLE_POWERSURGE = RAGE_JOAAT("powersurge"),
	VEHICLE_R300 = RAGE_JOAAT("r300"),
	VEHICLE_SURFER3 = RAGE_JOAAT("surfer3"),
	VEHICLE_TAHOMA = RAGE_JOAAT("tahoma"),
	VEHICLE_TULIP2 = RAGE_JOAAT("tulip2"),
	VEHICLE_VIRTUE = RAGE_JOAAT("virtue")
};
