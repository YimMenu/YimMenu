#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "persist/PersistCar.h" 

namespace big
{
	static char model[25];
	const char* category[] = { "Boats", "Commercials", "Compacts", "Coupes" , "Cycles" , "Emergency" , "Helicopters" , "Industrial" , "Military" , "Motorcycles" , "Muscle" , "Off-Road" ,
		"Open Wheel" , "Planes" , "SUVs", "Sedans" , "Service" , "Sports" , "Sports Classic" , "Super" , "Trailer" , "Trains", "Utility", "Vans" , "Beach Bum" , "Valentine's Day" 
	, "Business" , "High Life" , "Hipster" , "Independence Day" , "Festive Surprise", "Next Gen", "LTS", "Flight School", "Lowriders", "Ill-Gotten Gains", "Powerful"
	, "Finance & Felony" , "Custom Classics" , "Be My Valentine" , "January 2016" , "Festive Surprise 2015", "Executive Vehicles", "Halloween", "Cunning Stunts",
		"Import/Export", "Bikers Business", "Circuit Vehicle", "Gunrunning", "Smuggler's Run", "The Doomsday Heist" , "Southern SA Super Sport" , "After Hours"
		, "Arena War" , "Casino Resort" , "Casino Heist" , "Summer Special" , "Cayo Perico", "Contract DLC"};

	const char* vehicle_model = "";

	const char* ImportExport[] = {
	"elegy", "tempesta", "italigtb", "italigtb2", "nero",
		"nero2", "specter", "specter2", "diablous", "diablous2",
		"blazer5", "ruiner2", "dune4", "dune5", "phantom2",
		"voltic2", "penetrato", "boxville5", "wastelander", "technical2",
		"fcr", "fcr2", "ruiner3" };

	const char* CunningStunts[] = {
	"bf400", "brioso", "cliffhanger", "contender", "gargoyle", "le7b", "lynx", "omnis", "rallytruck", "sheava", "tampa2",
	"trophytruck", "trophytruck2", "tropos", "tyrus" };

	static char* ContractDLC[] = {
	"CHAMPION", "IGNUS", "ZENO", "COMET7", "BUFFALO4", "MULE5", "CINQUEMILA", "DEITY", "PATRIOT3", "ASTRON", "BALLER7",
	"GRANGER2", "IWAGEN", "JUBILEE", "YOUGA4", "REEVER", "SHINOBI" };

	const char* Gunrunning[] = {
	"trailers4", "xa21", "caddy3", "vagner",
	"phantom3", "technical3", "insurgent3", "apc",
	"tampa3", "dune3", "trailersmall2", "halftrack",
	"ardent", "oppressor" };

	char* SmugglersRun[] = {
"visione", "havok", "retinue", "cyclone",
	"rapidgt3", "vigilante", "alphaz1", "starling",
	"tula", "havok", "microlight", "rogue", "howard",
	"pyro", "hunter", "mogul", "bombushka", "nokota", "seabreeze" };

	const char* SouthernSanAndreasSuperSportSeries[] = {
"caracara", "cheburek", "dominator3", "ellie",
	"entity2", "fagaloa", "flashgt", "gb200", "hotring",
	"issi3", "jester3", "michelli", "seasparrow", "tezeract",
	"taipan", "tyrant" };

	const char* TheDoomsdayHeist[] = {
"akula", "barrage", "chernobog", "raiden", "yosemite", "deluxo",
	"avenger", "avenger2", "thruster", "pariah", "stromberg", "comet4",
	"riot2", "khanjali", "sc1", "riata", "volatol", "hermes", "savestra", "streiter",
	"kamacho", "gt500", "z190", "viseris", "autarch", "comet5", "neon", "revolter", "sentinel3", "hustler" };

	const char* AfterHours[] = {
	"blimp3", "freecrawler", "menacer", "mule4", "oppressor2",
		"patriot2", "pbus2", "pounder2", "scramjet", "speedo4",
		"stafford", "strikeforce", "swinger", "jester3", "terbyte" };

	const char* ArenaWar[] = {
"bruiser", "bruiser2", "bruiser3", "brutus", "brutus2", "brutus3", "cerberus", "cerberus2", "cerberus3", "clique", "deathbike",
	"deathbike2", "deathbike3", "deveste", "deviant", "dominator4", "dominator5", "dominator6", "impaler", "impaler2", "impaler3", "impaler4",
	"imperator", "imperator2", "imperator3", "issi4", "issi5", "issi6", "italigto", "monster3", "monster4", "monster5", "rcbandito", "scarab",
	"scarab2", "scarab3", "schlagen", "slamvan4", "slamvan5", "slamvan6", "toros", "tulip", "vamos", "zr380", "zr3802", "zr3803" };

	const char* TheDiamondCasinoResort[] = {
	"s80", "paragon", "paragon2", "drafter", "thrax", "caracara2", "issi7",
	"neo", "gauntlet3", "gauntlet4", "emerus", "nebula", "locust", "dynasty", "emerus",
	"hellion", "jugular", "krieger", "novak", "peyote2", "rrocket", "zion3", "zorrusso" };

	const char* TheDiamondCasinoHeist[] = {
		"asbo", "everon", "formula", "formula2", "furia", "imorgon", "jb7002", "kanjo", "komoda", "minitank", "outlaw", "rebla",
		"retinue2", "stryder", "sugoi", "sultan2", "vagrant", "vstr", "yosemite2", "zhaba"
	};

	const char* SpecialVehicleCircuit[] = {
		"gp1", "infernus2", "ruston", "turismo2"
	};

	const char* CayoPerico[] = {
		"alkonost", "annihilator2", "avisa", "brioso2", "dinghy5", "italirsx", "kosatka", "longfin",
		"manchez2", "patrolboat", "seasparrow2", "seasparrow3", "slamtruck", "squaddie", "toreador",
		"verus", "vetir", "veto", "veto2", "weevil", "winky" };

	const char* SummerSpecial[] = {
		"club", "coquette4", "dukes3", "gauntlet5", "glendale2", "landstalker2", "manana2", "openwheel1", "openwheel2",
		"penumbra2", "peyote3", "seminole2", "tigon", "yosemite3", "youga3"
	};

	const char* Bikers[] = {
		"avarus", "blazer4", "chimera", "daemon2", "defiler", "esskey", "faggio", "faggio3", "hakuchou2", "manchez",
		"nightblade", "raptor", "ratbike", "sanctus", "shotaro", "tornado6", "vortex", "wolfsbane", "youga2",
		"zombiea", "zombieb"
	};

	const char* FinanceFelony[] = {
		"bestiagts", "brickade", "fmj", "nimbus", "pfister811", "prototipo", "reaper", "rumpo3", "seven70",
		"tug", "volatus", "windsor2", "xls", "xls2"
	};

	const char* CustomClassics[] = {
		"faction3", "minivan2", "sabregt2", "slamvan3", "tornado5", "virgo2", "virgo3"
	};

	const char* BeMyValentine[] = {
		"btype3"
	};

	const char* Jan2016[] = {
		"banshee2", "sultanrs"
	};

	const char* FestiveSurprise[] = {
		"jester2", "massacro2", "ratloader2", "slamvan"
	};

	const char* Executives[] = {
		"bestiagts", "brickade", "fmj", "nimbus", "pfister811", "prototipo", "reaper", "rumpo3",
		"seven70", "tug", "volatus", "windsor2", "xls", "xls2"
	};

	const char* Halloween[] = {
		"btype2", "lurcher"
	};

	const char* Lowriders[] = {
		"buccaneer2", "chino2", "faction", "faction2", "moonbeam", "moonbeam2", "primo2", "voodoo"
	};

	const char* Ill2[] = {
		"brawler", "chino", "coquette3", "t20", "toro", "vindicator","feltzer3", "luxor2", "osiris", "swift2", "virgo", "windsor"
	};

	const char* Heists[] = {
		"barracks3", "boxville4", "casco", "dinghy3", "enduro", "gburrito2", "guardian", "hydra",
		"insurgent", "insurgent2", "kuruma", "kuruma2", "lectro", "mule3", "savage", "slamvan2",
		"tanker2", "technical", "trash2", "valkyrie", "velum2"
	};

	const char* Festive2015[] = {
		"tampa"
	};

	const char* NextGen[] = {
		"blimp2", "blista2", "blista3", "buffalo3", "dodo", "dominator2", "dukes", "dukes2", "gauntlet2",
		"marshall", "stalion", "stalion2", "submersible2"
	};

	const char* LTS[] = {
		"furoregt", "hakuchou", "innovation"
	};

	const char* Flight[] = {
		"besra", "coquette2", "miljet", "swift"
	};

	const char* Independence[] = {
		"monster", "sovereign"
	};

	const char* Hipster[] = {
		"blade", "dubsta3", "glendale", "panto", "pigalle", "rhapsody", "warrener"
	};

	const char* High[] = {
		"huntley", "massacro", "thrust", "zentorno"
	};

	const char* Business[] = {
		"alpha", "jester", "turismor", "vestra"
	};

	const char* Massacre[] = {
		"btype"
	};

	const char* Beach[] = {
		"bifta", "kalahari", "paradise", "speeder"
	};

	inline static const char* Boats[] = {
	"dinghy", "dinghy2", "dinghy3", "dinghy4", "jetmax", "marquis",
	 "seashark", "seashark2", "seashark3", "speeder", "speeder2", "squalo",
	  "submersible", "submersible2", "suntrap", "toro", "toro2", "tropic", "tropic2",
		"tug", "avisa", "dinghy5", "kosatka", "longfin", "patrolboat"
	};


	static char* Commercials[] = {
			"benson", "biff", "cerberus", "cerberus2", "cerberus3", "hauler",
			 "hauler2", "mule", "mule2", "mule3", "mule4", "packer", "phantom",
			  "phantom2", "phantom3", "pounder", "pounder2", "stockade", "stockade3",
			   "terbyte"
	};

	const char* Compacts[] = {
				"asbo", "blista", "brioso", "club", "dilettante", "dilettante2",
				 "kanjo", "issi2", "issi3", "issi4", "issi5", "issi6", "panto",
				  "prairie", "rhapsody", "brioso2", "weevil"
	};


	const char* Coupes[] = {
				   "cogcabrio", "exemplar", "f620", "felon", "felon2",
				   "jackal", "oracle", "oracle2", "sentinel", "sentinel2",
					"windsor", "windsor2", "zion", "zion2"
	};

	const char* Cycles[] = {
					  "bmx", "cruiser", "fixter", "scorcher", "tribike",
					   "tribike2", "tribike3"
	};


	const char* Emergency[] = {
						 "ambulance", "fbi", "fbi2", "firetruck", "lguard",
						  "pbus", "police", "police2", "police3", "police4",
						   "policeb", "polmav", "policeold1", "policeold2",
							"policet", "pranger", "predator", "riot", "riot2",
							   "sheriff", "sheriff2"
	};

	const char* Helicopters[] = {
							  "akula", "annihilator", "buzzard", "buzzard2",
							   "cargobob", "cargobob2", "cargobob3", "cargobob4",
								 "frogger", "frogger2", "havok", "hunter", "maverick", "savage",
								"seasparrow", "skylift", "supervolito", "supervolito2", "swift", "swift2", "valkyrie",
								   "valkyrie2", "volatus", "annihilator2", "seasparrow2", "seasparrow3"
	};



	const char* Industrial[] = {
							   "bulldozer", "cutter", "dump", "flatbed", "guardian", "handler", "mixer",
								"mixer2", "rubble", "tiptruck", "tiptruck2",
	};



	const char* Military[] = {
						  "apc", "barracks", "barracks2", "barracks3", "barrage", "chernobog", "crusader", "halftrack",
						  "khanjali", "minitank", "rhino", "scarab", "scarab2", "scarab3", "thruster", "trailersmall2", "vetir"

	};



	const char* Motorcycles[] = {
						  "akuma", "avarus", "bagger", "bati", "bati2", "bf400", "carbonrs",
							"chimera", "cliffhanger", "daemon", "daemon2", "defiler", "deathbike",
							  "deathbike2", "deathbike3", "diablous", "diablous2", "double", "enduro",
							 "esskey", "faggio", "faggio2", "faggio3", "fcr", "fcr2", "gargoyle", "hakuchou",
							 "hakuchou2", "hexer", "innovation", "lectro", "manchez", "nemesis",
							  "nightblade", "oppressor", "oppressor2", "pcj", "ratbike", "ruffian", "rrocket",
							 "sanchez", "sanchez2", "sanctus", "shotaro", "sovereign", "stryder", "thrust", "vader",
							  "vindicator", "vortex", "wolfsbane", "zombiea", "zombieb", "manchez2"
	};


	const char* Muscle[] = {
						  "blade", "buccaneer", "buccaneer2", "chino", "chino2", "clique", "coquette3", "deviant",
						   "dominator", "dominator2", "dominator3", "dominator4", "dominator5", "dominator6",
							"dukes", "dukes2", "dukes3", "faction", "faction2", "faction3", "ellie", "gauntlet","gauntlet2",
							 "gauntlet3", "gauntlet4", "gauntlet5", "hermes", "hotknife", "hustler", "impaler", "impaler2",
							 "impaler3","impaler4", "imperator", "imperator2", "imperator3", "lurcher", "moonbeam",
							   "moonbeam2", "nightshade", "peyote2", "phoenix", "picador", "ratloader", "ratloader2",
							 "ruiner", "ruiner2", "ruiner3", "sabregt", "sabregt2", "slamvan", "slamvan2", "slamvan3",
							  "slamvan4", "slamvan5", "slamvan6", "stalion", "stalion2", "tampa", "tampa3", "tulip",
							  "vamos", "vigero", "virgo", "virgo2", "virgo3", "voodoo", "voodoo2", "yosemite",
								"yosemite2","yosemite3"
	};

	const char* OffRoad[] = {
						   "bfinjection", "bifta", "blazer", "blazer2", "blazer3", "blazer4", "blazer5", "bodhi2",
							"brawler", "bruiser", "bruiser2", "bruiser3", "brutus", "brutus2", "brutus3", "caracara",
							 "caracara2", "dloader", "dubsta3", "dune", "dune2", "dune3", "dune4", "dune5",
							 "everon", "freecrawler", "hellion", "insurgent", "insurgent2", "insurgent3", "kalahari",
							 "kamacho", "marshall", "mesa3", "monster", "monster3", "monster4", "monster5",
							   "menacer", "outlaw", "nightshark", "rancherxl", "rancherxl2", "rebel", "rebel2",
							  "rcbandito", "riata", "sandking", "sandking2", "technical", "technical2", "technical3",
								 "trophytruck", "trophytruck2", "vagrant", "zhaba", "verus", "winky"
	};



	const char* OpenWheel[] = {
						  "formula", "formula2", "openwheel1", "openwheel2"
	};


	const char* Planes[] = {
					   "alphaz1", "avenger", "avenger2", "besra", "blimp", "blimp2", "blimp3", "bombushka",
						"cargoplane", "cuban800", "dodo", "duster", "howard", "hydra", "jet", "lazer","luxor",
					   "luxor2", "mammatus", "microlight", "miljet", "mogul", "molotok", "nimbus", "nokota",
						"pyro", "rogue", "seabreeze", "shamal", "starling", "strikeforce", "stunt", "titan", "tula", "velum",
					  "velum2", "vestra", "volatol", "alkonost"
	};


	const char* SUVs[] = {
					   "baller", "baller2", "baller3", "baller4", "baller5", "baller6", "bjxl", "cavalcade",
					   "cavalcade2", "contender", "dubsta", "dubsta2", "fq2", "granger", "gresley", "habanero",
					   "huntley", "landstalker", "landstalker2", "mesa", "mesa2", "movak", "patriot", "patriot2",
					  "radi", "rebla", "rocoto", "seminole", "seminole2", "serrano", "toros", "xls", "xls2", "squaddie"
	};

	const char* Sedans[] = {
							 "asea", "asea2", "asterope", "cog55", "cog552", "cognoscenti", "cognoscenti2" ,
							  "emperor", "emperor2", "emperor3", "fugitive", "glendale", "glendale2", "ingot",
							   "intruder", "limo2", "premier", "primo", "primo2", "regina", "romero", "stafford",
							   "stanier", "stratum", "stretch", "superd", "surge", "tailgater", "warrener", "washington"
	};

	const char* Service[] = {
								 "airbus", "brickade", "bus", "coach", "pbus2", "rallytruck", "rentalbus",
								   "taxi", "tourbus", "trash", "trash2", "wastelander"
	};

	const char* Sports[] = {
							 "alpha", "banshee", "bestiagts", "blista2", "blista3", "buffalo", "buffalo2", "buffalo3", "carbonizzare",
							"comet2", "comet3", "comet4", "comet5", "coquette", "coquette4", "drafter", "deveste",
						  "elegy", "elegy2", "feltzer2", "flashgt", "furoregt", "fusilade", "futo", "gb200", "hotring",
						  "komoda", "imorgon", "issi7", "italigto", "jugular", "jester", "jester2", "jester3", "khamelion",
						  "kuruma", "kuruma2", "locust", "lynx", "massacro", "massacro2", "neo", "neon", "ninef",
						  "ninef2", "omnis", "paragon", "paragon2", "pariah", "penumbra", "penumbra2", "raiden", "rapidgt",
						 "rapidgt2", "raptor", "revolter", "ruston", "schafter2", "schafter3", "schafter4", "schafter5", "schafter6",
					   "schlagen", "schwarzer", "sentinel3", "seven70", "specter", "specter2" ,"streiter", "sugoi", "sultan",
						"sultan2", "surano", "tampa2", "tropos", "verlierer2", "vstr", "zr380", "zr3802", "zr3803", "italirsx",
						 "veto", "veto2"
	};

	const char* SportsClassic[] = {
						 "ardent", "btype", "btype2", "btype3", "casco", "cheetah2", "coquette2", "deluxo",
						 "dynasty", "fagaloa", "feltzer3", "gt500", "infernus2", "jb700", "jb7002", "mamba",
						 "manana", "manana2", "michelli", "monroe", "nebula", "peyote", "peyote3", "pigalle",
						  "rapidgt3", "retinue", "retinue2", "savestra", "stinger", "stingergt", "stromberg", "swinger",
						   "torero", "tornado", "tornado2", "tornado3", "tornado4" ,"tornado5", "tornado6", "turismo2",
							"viseris", "z190", "ztype", "zion3","cheburek", "toreador"
	};

	const char* Super[] = {
							 "adder", "autarch", "banshee2", "bullet", "cheetah", "cyclone", "entity2", "entityxf",
							 "emerus", "fmj", "furia", "gp1", "infernus", "italigtb", "italigtb2", "krieger", "le7b", "nero",
								 "nero2", "osiris", "penetrator", "pfister811", "prototipo", "prototipo", "s80", "sc1",
								  "scramjet", "sheava", "sultanrs", "t20", "taipan", "tempesta", "tezeract", "thrax",
								  "tigon", "turismor", "tyrant", "tyrus", "vacca", "vagner", "vigilante", "visione", "voltic",
								  "voltic2", "xa21", "zentorno", "zorrusso"
	};

	const char* Trailer[] = {
							 "armytanker", "armytrailer", "armytrailer2", "baletrailer", "boattrailer", "cablecar",
							  "docktrailer", "freighttrailer", "graintrailer", "proptrailer", "raketrailer", "tr2", "tr3", "tr4",
								"trflat", "tvtrailer", "tanker", "tanker2", "trailerlarge", "trailerlogs", "trailersmall", "trailers",
							  "trailers2", "trailers3", "trailers4"
	};

	const char* Trains[] = {
							   "freight", "freightcar", "freightcont1", "freightcont2", "freightgrain", "metrotrain", "tankercar"
	};

	const char* Utility[] = {
							"airtug", "caddy", "caddy2", "caddy3", "docktug", "forklift", "mower", "ripley", "sadler",
							  "sadler2", "scrap", "towtruck", "towtruck2", "tractor", "tractor2", "tractor3",
							   "utillitruck", "utillitruck2", "utillitruck3", "slamtruck"
	};


	const char* Vans[] = {
							"bison", "bison2", "bison3", "bobcatxl", "boxville", "boxville2", "boxville3", "boxville4",
							 "boxville5", "burrito", "burrito2", "burrito3", "burrito4", "burrito5", "camper", "gburrito",
							  "gburrito2", "journey", "minivan", "minivan2", "paradise", "pony", "pony2", "rumpo",
								 "rumpo2", "rumpo3", "speedo", "speedo2", "speedo4", "surfer", "surfer2", "taco",
								"youga", "youga2", "youga3"
	};

	static int combo_pos = 0;
	static int ContractDLCListPos = 0;
	static int CayoPericoListPos = 0;
	static int SummerSpecialListPos = 0;
	static int DiamondCasinoAndResortListPos = 0;
	static int TheDiamondCasinoHeistListPos = 0;
	static int ArenaWarListPos = 0;
	static int AfterHoursListPos = 0;
	static int SouthernSanAndreasSuperSportSeriesListPos = 0;
	static int TheDoomsdayHeistListPos = 0;
	static int SmugglersRunListPos = 0;
	static int GunrunningListPos = 0;
	static int SpecialVehicleCircuitListPos = 0;
	static int ImportExportListPos = 0;
	static int CunningStuntsListPos = 0;
	static int FinanceFelonyListPos = 0;
	static int Jan2016ListPos = 0;
	static int FestiveSurpriseListPos = 0;
	static int NextGenListPos = 0;
	static int LTSListPos = 0;
	static int FlightListPos = 0;
	static int IndependenceListPos = 0;
	static int HipsterListPos = 0;
	static int HighListPos = 0;
	static int BusinessListPos = 0;
	static int MassacreListPos = 0;
	static int BeachListPos = 0;
	static int FestiveSurprise2015ListPos = 0;
	static int ExecutivesListPos = 0;
	static int HalloweenListPos = 0;
	static int LowridersListPos = 0;
	static int Ill1ListPos = 0;
	static int Ill2ListPos = 0;
	static int HeistsListPos = 0;
	static int BeMyValentineListPos = 0;
	static int CustomClassicsListPos = 0;
	static int BikersListPos = 0;

	static int BoatListPos = 0;
	static int CommercialsListPos = 0;
	static int CompactsListPos = 0;
	static int CoupesListPos = 0;
	static int CyclesListPos = 0;
	static int EmergencyListPos = 0;
	static int HelicoptersListPos = 0;
	static int IndustrialListPos = 0;
	static int MilitaryListPos = 0;
	static int MotorCyclesListPos = 0;
	static int MuscleListPos = 0;
	static int OffRoadListPos = 0;
	static int OpenWheelListPos = 0;
	static int PlanesListPos = 0;
	static int SUVListPos = 0;
	static int SedansListPos = 0;
	static int ServiceListPos = 0;
	static int SportsListPos = 0;
	static int SportsClassicListPos = 0;
	static int SuperListPos = 0;
	static int TrailerListPos = 0;
	static int TrainsListPos = 0;
	static int UtilityListPos = 0;
	static int VansListPos = 0;

	void tab_main::tab_spawn()
	{
		if (ImGui::BeginTabItem("Spawn"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			}QUEUE_JOB_END_CLAUSE

			if (
				ImGui::InputText("Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue) ||
				ImGui::Button("Spawn")
				)
			{
				QUEUE_JOB_BEGIN_CLAUSE(= )
				{
					Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
					Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

					vehicle::spawn((const char*)model, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
				}QUEUE_JOB_END_CLAUSE
			}
			
			ImGui::Separator();
			persist_car::do_presentation_layer();
			ImGui::Separator();
			ImGui::Combo("Vehicle Category", &combo_pos, category, sizeof(category) / sizeof(*category));

			switch (combo_pos) {
			case 0:
				if (ImGui::Combo("Boats", &BoatListPos, Boats, sizeof(Boats) / sizeof(*Boats)))
				{
					vehicle_model = Boats[BoatListPos];
				}
				break;
			case 1:
				if (ImGui::Combo("Commercial", &CommercialsListPos, Commercials, sizeof(Commercials) / sizeof(*Commercials)))
				{
				vehicle_model = Commercials[CommercialsListPos];
				}
				break;
			case 2:
				if (ImGui::Combo("Compacts", &CompactsListPos, Compacts, sizeof(Compacts) / sizeof(*Compacts)))
				{
					vehicle_model = Compacts[CompactsListPos];
				}
				break;
			case 3:
				if (ImGui::Combo("Coupes", &CoupesListPos, Coupes, sizeof(Coupes) / sizeof(*Coupes)))
				{
					vehicle_model = Coupes[CoupesListPos];
				}
				break;
			case 4:
				if (ImGui::Combo("Cycles", &CyclesListPos, Cycles, sizeof(Cycles) / sizeof(*Cycles)))
				{
					vehicle_model = Cycles[CyclesListPos];
				}
				break;
			case 5:
				if (ImGui::Combo("Emergency", &EmergencyListPos, Emergency, sizeof(Emergency) / sizeof(*Emergency)))
				{
					vehicle_model = Emergency[EmergencyListPos];
				}
				break;
			case 6:
				if (ImGui::Combo("Helicopters", &HelicoptersListPos, Helicopters, sizeof(Helicopters) / sizeof(*Helicopters)))
				{
					vehicle_model = Helicopters[HelicoptersListPos];
				}
				break;
			case 7:
				if (ImGui::Combo("Industrial", &IndustrialListPos, Industrial, sizeof(Industrial) / sizeof(*Industrial)))
				{
					vehicle_model = Industrial[IndustrialListPos];
				}
				break;
			case 8:
				if (ImGui::Combo("Military", &MilitaryListPos, Military, sizeof(Military) / sizeof(*Military)))
				{
					vehicle_model = Military[MilitaryListPos];
				}
				break;
			case 9:
				if (ImGui::Combo("Motorcycles", &MotorCyclesListPos, Motorcycles, sizeof(Motorcycles) / sizeof(*Motorcycles)))
				{
					vehicle_model = Motorcycles[MotorCyclesListPos];
				}
				break;
			case 10:
				if (ImGui::Combo("Muscle", &MuscleListPos, Muscle, sizeof(Muscle) / sizeof(*Muscle)))
				{
					vehicle_model = Muscle[MuscleListPos];
				}
				break;
			case 11:
				if (ImGui::Combo("Off-Road", &OffRoadListPos, OffRoad, sizeof(OffRoad) / sizeof(*OffRoad)))
				{
					vehicle_model = OffRoad[OffRoadListPos];
				}
				break;
			case 12:
				if (ImGui::Combo("Open Wheel", &OpenWheelListPos, OpenWheel, sizeof(OpenWheel) / sizeof(*OpenWheel)))
				{
					vehicle_model = OpenWheel[OpenWheelListPos];
				}
				break;
			case 13:
				if (ImGui::Combo("Planes", &PlanesListPos, Planes, sizeof(Planes) / sizeof(*Planes)))
				{
					vehicle_model = Planes[PlanesListPos];
				}
				break;
			case 14:
				if (ImGui::Combo("SUVs", &SUVListPos, SUVs, sizeof(SUVs) / sizeof(*SUVs)))
				{
					vehicle_model = SUVs[SUVListPos];
				}
				break;
			case 15:
				if (ImGui::Combo("Sedans", &SedansListPos, Sedans, sizeof(Sedans) / sizeof(*Sedans)))
				{
					vehicle_model = Sedans[SedansListPos];
				}
				break;
			case 16:
				if (ImGui::Combo("Service", &ServiceListPos, Service, sizeof(Service) / sizeof(*Service)))
				{
					vehicle_model = Service[ServiceListPos];
				}
				break;
			case 17:
				if (ImGui::Combo("Sports", &SportsListPos, Sports, sizeof(Sports) / sizeof(*Sports)))
				{
					vehicle_model = Sports[SportsListPos];
				}
				break;
			case 18:
				if (ImGui::Combo("Sports Classic", &SportsClassicListPos, SportsClassic, sizeof(SportsClassic) / sizeof(*SportsClassic)))
				{
					vehicle_model = SportsClassic[SportsClassicListPos];
				}
				break;
			case 19:
				if (ImGui::Combo("Super", &SuperListPos, Super, sizeof(Super) / sizeof(*Super)))
				{
					vehicle_model = Super[SuperListPos];
				}
				break;
			case 20:
				if (ImGui::Combo("Trailer", &TrailerListPos, Trailer, sizeof(Trailer) / sizeof(*Trailer)))
				{
					vehicle_model = Trailer[TrailerListPos];
				}
				break;
			case 21:
				if (ImGui::Combo("Trains", &TrainsListPos, Trains, sizeof(Trains) / sizeof(*Trains)))
				{
					vehicle_model = Trains[TrainsListPos];
				}
				break;
			case 22:
				if (ImGui::Combo("Utility", &UtilityListPos, Utility, sizeof(Utility) / sizeof(*Utility)))
				{
					vehicle_model = Utility[UtilityListPos];
				}
				break;
			case 23:
				if (ImGui::Combo("Vans", &VansListPos, Vans, sizeof(Vans) / sizeof(*Vans)))
				{
					vehicle_model = Vans[VansListPos];
				}
				break;
			case 24:
				if (ImGui::Combo("Beach Bum", &BeachListPos, Beach, sizeof(Beach) / sizeof(*Beach)))
				{
					vehicle_model = Beach[BeachListPos];
				}
				break;
			case 25:
				if (ImGui::Combo("Valentine's Day", &MassacreListPos, Massacre, sizeof(Massacre) / sizeof(*Massacre)))
				{
					vehicle_model = Massacre[MassacreListPos];
				}
				break;
			case 26:
				if (ImGui::Combo("Business", &BusinessListPos, Business, sizeof(Business) / sizeof(*Business)))
				{
					vehicle_model = Business[BusinessListPos];
				}
				break;
			case 27:
				if (ImGui::Combo("High Life", &HighListPos, High, sizeof(High) / sizeof(*High)))
				{
					vehicle_model = High[HighListPos];
				}
				break;
			case 28:
				if (ImGui::Combo("Hipster", &HipsterListPos, Hipster, sizeof(Hipster) / sizeof(*Hipster)))
				{
					vehicle_model = Hipster[HipsterListPos];
				}
				break;
			case 29:
				if (ImGui::Combo("Independence Day", &IndependenceListPos, Independence, sizeof(Independence) / sizeof(*Independence)))
				{
					vehicle_model = Independence[IndependenceListPos];
				}
				break;
			case 30:
				if (ImGui::Combo("Festive Surprise", &FestiveSurpriseListPos, FestiveSurprise, sizeof(FestiveSurprise) / sizeof(*FestiveSurprise)))
				{
					vehicle_model = FestiveSurprise[FestiveSurpriseListPos];
				}
				break;
			case 31:
				if (ImGui::Combo("Next Gen", &NextGenListPos, NextGen, sizeof(NextGen) / sizeof(*NextGen)))
				{
					vehicle_model = NextGen[NextGenListPos];
				}
				break;
			case 32:
				if (ImGui::Combo("LTS", &LTSListPos, LTS, sizeof(LTS) / sizeof(*LTS)))
				{
					vehicle_model = LTS[LTSListPos];
				}
				break;
			case 33:
				if (ImGui::Combo("Flight School", &FlightListPos, Flight, sizeof(Flight) / sizeof(*Flight)))
				{
					vehicle_model = Flight[FlightListPos];
				}
				break;
			case 34:
				if (ImGui::Combo("Lowriders", &LowridersListPos, Lowriders, sizeof(Lowriders) / sizeof(*Lowriders)))
				{
					vehicle_model = Lowriders[LowridersListPos];
				}
				break;
			case 35:
				if (ImGui::Combo("Ill-Gotten Gains", &Ill2ListPos, Ill2, sizeof(Ill2) / sizeof(*Ill2)))
				{
					vehicle_model = Ill2[Ill2ListPos];
				}
				break;
			case 36:
				if (ImGui::Combo("Powerful", &HeistsListPos, Heists, sizeof(Heists) / sizeof(*Heists)))
				{
					vehicle_model = Heists[HeistsListPos];
				}
				break;
			case 37:
				if (ImGui::Combo("Finance & Felony", &FinanceFelonyListPos, FinanceFelony, sizeof(FinanceFelony) / sizeof(*FinanceFelony)))
				{
					vehicle_model = FinanceFelony[FinanceFelonyListPos];
				}
				break;
			case 38:
				if (ImGui::Combo("Custom Classics", &CustomClassicsListPos, CustomClassics, sizeof(CustomClassics) / sizeof(*CustomClassics)))
				{
					vehicle_model = CustomClassics[CustomClassicsListPos];
				}
				break;
			case 39:
				if (ImGui::Combo("Be My Valentine", &BeMyValentineListPos, BeMyValentine, sizeof(BeMyValentine) / sizeof(*BeMyValentine)))
				{
					vehicle_model = BeMyValentine[BeMyValentineListPos];
				}
				break;
			case 40:
				if (ImGui::Combo("January 2016", &Jan2016ListPos, Jan2016, sizeof(Jan2016) / sizeof(*Jan2016)))
				{
					vehicle_model = Jan2016[Jan2016ListPos];
				}
				break;
			case 41:
				if (ImGui::Combo("Festive Surprise 2015", &FestiveSurprise2015ListPos, Festive2015, sizeof(Festive2015) / sizeof(*Festive2015)))
				{
					vehicle_model = Festive2015[FestiveSurprise2015ListPos];
				}
				break;
			case 42:
				if (ImGui::Combo("Executive Vehicles", &ExecutivesListPos, Executives, sizeof(Executives) / sizeof(*Executives)))
				{
					vehicle_model = Executives[ExecutivesListPos];
				}
				break;
			case 43:
				if (ImGui::Combo("Halloween", &HalloweenListPos, Halloween, sizeof(Halloween) / sizeof(*Halloween)))
				{
					vehicle_model = Halloween[HalloweenListPos];
				}
				break;
			case 44:
				if (ImGui::Combo("Cunning Stunts", &CunningStuntsListPos, CunningStunts, sizeof(CunningStunts) / sizeof(*CunningStunts)))
				{
					vehicle_model = CunningStunts[CunningStuntsListPos];
				}
				break;
			case 45:
				if (ImGui::Combo("Import/Export", &ImportExportListPos, ImportExport, sizeof(ImportExport) / sizeof(*ImportExport)))
				{
					vehicle_model = ImportExport[ImportExportListPos];
				}
				break;
			case 46:
				if (ImGui::Combo("Bikers Business", &BikersListPos, Bikers, sizeof(Bikers) / sizeof(*Bikers)))
				{
					vehicle_model = Bikers[BikersListPos];
				}
				break;
			case 47:
				if (ImGui::Combo("Circuit Vehicle", &SpecialVehicleCircuitListPos, SpecialVehicleCircuit, sizeof(SpecialVehicleCircuit) / sizeof(*SpecialVehicleCircuit)))
				{
					vehicle_model = SpecialVehicleCircuit[SpecialVehicleCircuitListPos];
				}
				break;
			case 48:
				if (ImGui::Combo("Gunrunning", &GunrunningListPos, Gunrunning, sizeof(Gunrunning) / sizeof(*Gunrunning)))
				{
					vehicle_model = Gunrunning[GunrunningListPos];
				}
				break;
			case 49:
				if (ImGui::Combo("Smuggler's Run", &SmugglersRunListPos, SmugglersRun, sizeof(SmugglersRun) / sizeof(*SmugglersRun)))
				{
					vehicle_model = SmugglersRun[SmugglersRunListPos];
				}
				break;
			case 50:
				if (ImGui::Combo("The Doomsday Heist", &TheDoomsdayHeistListPos, TheDoomsdayHeist, sizeof(TheDoomsdayHeist) / sizeof(*TheDoomsdayHeist)))
				{
					vehicle_model = TheDoomsdayHeist[TheDoomsdayHeistListPos];
				}
				break;
			case 51:
				if (ImGui::Combo("Southern SA Super Sport", &SouthernSanAndreasSuperSportSeriesListPos, SouthernSanAndreasSuperSportSeries, sizeof(SouthernSanAndreasSuperSportSeries) / sizeof(*SouthernSanAndreasSuperSportSeries)))
				{
					vehicle_model = SouthernSanAndreasSuperSportSeries[SouthernSanAndreasSuperSportSeriesListPos];
				}
				break;
			case 52:
				if (ImGui::Combo("After Hours", &AfterHoursListPos, AfterHours, sizeof(AfterHours) / sizeof(*AfterHours)))
				{
					vehicle_model = AfterHours[AfterHoursListPos];
				}
				break;
			case 53:
				if (ImGui::Combo("Arena War", &ArenaWarListPos, ArenaWar, sizeof(ArenaWar) / sizeof(*ArenaWar)))
				{
					vehicle_model = ArenaWar[ArenaWarListPos];
				}
				break;
			case 54:
				if (ImGui::Combo("Casino Resort", &TheDiamondCasinoHeistListPos, TheDiamondCasinoResort, sizeof(TheDiamondCasinoResort) / sizeof(*TheDiamondCasinoResort)))
				{
					vehicle_model = TheDiamondCasinoResort[TheDiamondCasinoHeistListPos];
				}
				break;
			case 55:
				if (ImGui::Combo("Casino Heist", &TheDiamondCasinoHeistListPos, TheDiamondCasinoHeist, sizeof(TheDiamondCasinoHeist) / sizeof(*TheDiamondCasinoHeist)))
				{
					vehicle_model = TheDiamondCasinoHeist[TheDiamondCasinoHeistListPos];
				}
				break;
			case 56:
				if (ImGui::Combo("Summer Special", &SummerSpecialListPos, SummerSpecial, sizeof(SummerSpecial) / sizeof(*SummerSpecial)))
				{
					vehicle_model = SummerSpecial[SummerSpecialListPos];
				}
				break;
			case 57:
				if (ImGui::Combo("Cayo Perico", &CayoPericoListPos, CayoPerico, sizeof(CayoPerico) / sizeof(*CayoPerico)))
				{
					vehicle_model = CayoPerico[CayoPericoListPos];
				}
				break;
				case 58:
					if (ImGui::Combo("Contract DLC", &ContractDLCListPos, ContractDLC, sizeof(ContractDLC) / sizeof(*ContractDLC)))
					{
						vehicle_model = ContractDLC[ContractDLCListPos];
					}
					break;
				}

			if (ImGui::Button("spawn selected vehicle")) {
				QUEUE_JOB_BEGIN_CLAUSE(= )
				{
					Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX());
					Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);

					vehicle::spawn(vehicle_model, location, ENTITY::GET_ENTITY_HEADING(player) + 90.f);
				}QUEUE_JOB_END_CLAUSE
			}
			ImGui::EndTabItem();
		}
	}
}