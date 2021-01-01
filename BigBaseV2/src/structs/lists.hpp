#pragma once
#include "session_type.hpp"

namespace big
{
	inline const int64_t kick_hashes[]{ 1317868303,-1243454584,-1212832151,-1252906024,-1890951223,-442306200,-966559987,1977655521,1998625272,1070934291,764638896,-345371965,-1559754940,1347850743,495824472,1240585650,1129105265,1192658057,3042061272,2735212356, 3852661096,123310597000,122994296644, -1549630786, -1990292823, 1352706024, 12442595688, 11325146948, 11631995864, 96893296585, 98341941608, 97224492868, 97540793224, 1317868303,-1243454584,-1212832151,-1252906024,-1890951223,-442306200,-966559987,1977655521,1998625272,1070934291,764638896,-345371965,-1559754940,1347850743,495824472,1240585650,1129105265,1192658057,3042061272,2735212356, 3852661096,123310597000,122994296644, -1549630786, -1990292823, 1352706024,
-1549630786, -1990292823, -920663435, -891346918, -1729804184, -966559987, -1890951223, -1252906024, 665709549, -2065346036, 823645419, 1881968783, 2565163112, 2404016073, 3328407309, -977515445, 767605081, -1054826273, 1620254541, 1401831542, 1428412924, 10993950665, 11672069737, 12442595688, 11325146948, 11918341901, 10567590113,
11830075615, 9210190337, 97531341784, 96893296585, 98341941608, 97817687821, 96466936033, 97729421535, 95109536257, 97863584373, 96793954985, 97234617022, 96487905784, 95560214803, 97571415657, 97224492868, 95807148815, 97540793224 };

	inline const char* location_names[] =
	{
	"Eclipse Towers", "West Vinewood", "Las Lagunas", "Spanish Ave", "Power St", "Del Perro",
	"Milton Rd", "The Royale", "La Puerta", "Rockford Dr", "Dream Tower", "San Vitas", "Vespucci Blvd",
	"Cougar Ave", "Prosperity St","Weazel Plaza", "Del Perro Office", "Maze Bank West Office",
	"Arcadius Office", "Maze Bank Office"
	};
	inline int location_ids[] = { 1, 6, 10, 9, 8, 7, 11, 12, 14, 15, 16, 18, 20, 21, 22, 35, 87, 88, 89, 90 };

	inline const char* weather_names[] =
	{
		"Clear",
		"Sunny",
		"Cloudy",
		"Very Cloudy",
		"Rain",
		"Clearing",
		"Thunder",
		"Smog",
		"Foggy",
		"Christmas",
		"Light Snow",
		"Blizzard"
	};

	inline const char* weather_types[] =
	{
		"CLEAR",
		"EXTRASUNNY",
		"CLOUDS",
		"OVERCAST",
		"RAIN",
		"CLEARING",
		"THUNDER",
		"SMOG",
		"FOGGY",
		"XMAS",
		"SNOWLIGHT",
		"BLIZZARD"
	};

	inline session_type sessions[] = {
		{ 0,	"Join Public Session"	},
		{ 1,	"New Public Session"	},
		{ 2,	"Closed Crew Session"	},
		{ 3,	"Crew Session"			},
		{ 6,	"Closed Friend Session"	},
		{ 9,	"Find Friend Session"	},
		{ 10,	"Solo Session"			},
		{ 11,	"Invite Only Session"	},
		{ 12,	"Join Crew Session"		},
		{ -1,	"Leave GTA Online"		}
	};
}