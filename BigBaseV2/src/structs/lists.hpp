#pragma once
#include "session_type.hpp"

namespace big
{
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