#pragma once
#include "gta/enums.hpp"
typedef struct
{
	const char* name;
	BlipIcons blipsprites;
} BlipTPlist;



inline std::vector<BlipTPlist> BlipsBuisness{
    {"Teleport To Yacht", BlipIcons::Yacht},
    {"Teleport To Personal Vehicle", BlipIcons::PersonalVehicleCar},
    {"Teleport To Nightclub", BlipIcons::Nightclub},
    {"Teleport To Race Finish Test", BlipIcons::RaceFinish},
    {"Teleport To Facility", BlipIcons::IAAFacility},
    {"Teleport To Hanger", BlipIcons::AircraftHanger},
    {"Teleport To Bunker", BlipIcons::Bunker},
    //	{"Test3", Business},
    {"Teleport To Terrorbyte", BlipIcons::Terrorbyte},
};
inline std::vector<BlipTPlist> BlipsStores{
    {"Teleport To Ammunation", BlipIcons::AmmuNation},
    {"Teleport To Barber", BlipIcons::Barber},
    {"Teleport To Convient Store", BlipIcons::ConvenienceStore},
    {"Teleport To Tattoo Shop", BlipIcons::TattooParlor},
    {"Teleport To Stripclub", BlipIcons::StripClub},
    {"Teleport To LSC", BlipIcons::LosSantosCustoms},
    {"Teleport To Clothes Store", BlipIcons::Clothes},
};
inline std::vector<BlipTPlist> BlipsMC{
    {"Teleport To Weed Buisness", BlipIcons::Weed},
    {"Teleport To Cocaine Buisness", BlipIcons::Cocaine},
    {"Teleport To Meth Buisness", BlipIcons::Meth},
    {"Teleport To Forged Documents Buisness", BlipIcons::ForgedDocuments},
    {"Teleport To Counterfeit Money Buisness", BlipIcons::CounterfeitMoney},
};
struct teleportlist
{
	const char* name;
	Vector3 Coords;
	teleportlist(const char* name, float x, float y, float z) :
	    name(name),
	    Coords(x, y, z)
	{
	}
};
static std::vector<teleportlist> spSafehouses = {{"Franklin's Aunt's House", -14.3803, -1438.51, 31.1073}, {"Michael's House", -813.603, 179.474, 72.1548}, {"Franklin's Vinewood House", 7.11903, 536.615, 176.028}, {"Trevor's Trailer", 1972.61, 3817.04, 33.4278}, {"Trevor's Meth Lab", 1391.29, 3608.6, 38.9429}, {"Trevor's Sandy Shores Trailer", 1985.481, 3812.189, 32.5}, {"Trevor's Airfield", 1727.85, 3299.08, 40.0638}, {"Trevor's Strip Club", 126.135, -1278.583, 29.270}, {"Trevor's Pillbox Hill Apartment", -1150.703, -1520.713, 10.633}, {"Trevor's Warehouse", 1000.976, -3100.461, -39.999}, {"Trevor's Burnt Down House", 0.0, 0.0, 0.0}, {"Trevor's Office", -1151.756, -1518.68, 10.633}, {"Trevor's Garage", 197.815, -1002.95, -99.999}, {"Floyd's Apartment", -1151.77, -1518.14, 10.6327}, {"Vanilla Unicorn Office", 97.2707, -1290.9940, 29.2688}};

static std::vector<teleportlist> clothings = {{"Masks - Vespucci Beach", -1342.185913f, -1280.013428f, 4.443256f}, {"Discount Store - Polito Bay", -4.509100f, 6521.252930f, 30.571024f}, {"Discount Store - Grand Senora Desert", 1179.679688f, 2691.378662f, 37.124043f}, {"Binco - La Puerta", -814.432800, -1085.986938, 10.567306f}, {"Binco - Strawberry", 411.403564f, -806.654907f, 28.742212f}, {"Binco - Rockford Hills", -821.584229f, -1073.489014f, 11.328976f}, {"Binco - Burton", -1457.540527f, -229.017136f, 49.185726f}, {"Binco - Hawick", 88.2911f, -1391.929f, 29.202f}, {"Binco - Davis", 12.4152f, -1105.245f, 29.797f}, {"Binco - Paleto Bay", 4.254f, 6512.813f, 31.877f}, {"Binco - Sandy Shores", 1693.917f, 4822.811f, 42.063f}, {"Binco - Grapeseed", 1693.917f, 4822.811f, 42.063f}, {"Binco - Harmony", 1693.917f, 4822.811f, 42.063f}, {"Binco - Chumash", 1693.917f, 4822.811f, 42.063f}, {"Binco - Paleto Forest", 1693.917f, 4822.811f, 42.063f}, {"Binco - Vinewood", 1693.917f, 4822.811f, 42.063f}, {"Binco - Mirror Park", 1693.917f, 4822.811f, 42.063f}, {"Binco - Little Seoul", 1693.917f, 4822.811f, 42.063f}, {"Binco - Vespucci Beach", 1693.917f, 4822.811f, 42.063f}, {"Binco - La Mesa", 1693.917f, 4822.811f, 42.063f}, {"Binco - Cypress Flats", 1693.917f, 4822.811f, 42.063f}, {"Binco - Mission Row", 1693.917f, 4822.811f, 42.063f}, {"Ponsonbys - Rockford Hills", -725.551453f, -162.833710f, 36.570301f}, {"Suburban - Harmony", 619.3096f, 2738.7136f, 41.9631f}, {"Suburban - Hawick", 134.122055f, -200.211334f, 53.864090f}

};

static std::vector<teleportlist> ammunation = {{"Ammunation - Chumash", -3155.888672f, 1073.844482f, 20.188726f}, {"Ammunation - Cypress Flats", 814.442017f, -2130.448486f, 28.867798f}, {"Ammunation - Great Chaparral", -1108.600830f, 2685.694092f, 18.177374f}, {"Ammunation - Hawick", 235.666794f, -42.263149f, 69.221313f}, {"Ammunation - La Mesa", 844.439026f, -1009.422424f, 27.511728f}, {"Ammunation - Little Seoul", -665.232727f, -952.522522f, 20.866556f}, {"Ammunation - Morningwood", -1328.592896f, -387.114410f, 36.126881f}, {"Ammunation - Palomino Freeway", 2571.371826f, 313.879608f, 107.970573f}, {"Ammunation - Pillbox Hill", 15.6435f, -1121.7327f, 28.8248f}, {"Ammunation - Polito Bay", -318.859039f, 6074.433105f, 30.614943f}, {"Ammunation - Sandy Shores", 1704.671997f, 3748.880615f, 33.286053f}};

static std::vector<teleportlist> carsstuff = {{"Los Santos Customs - Los Santos Airport", -1135.707275f, -1987.154175f, 12.976217f}, {"Los Santos Customs - La Mesa", 709.295471f, -1081.996216f, 21.975765f}, {"Los Santos Customs - Burton", -370.533752f, -130.402649f, 38.197617f}, {"Los Santos Customs - Sandy Shores", 1176.822632f, 2657.973145f, 37.370682f}, {"Bennys Garage", -196.349442f, -1303.103271f, 30.650515f}

};


static std::vector<teleportlist> airfields = {{"Sandy Shores Airfield", 1747.0, 3273.7, 41.1}, {"Los Santos International Airport", -1075.3876, -2938.1072, 13.9463}, {"McKenzie Airfield", 2121.7, 4796.3, 41.1}};


static std::vector<teleportlist> outLocs = {
    {"Stab City", 126.975, 3714.419, 46.827},
    {"Weed Farm", 2208.777, 5578.235, 53.735},
    {"Gods Thumb", -1006.402, 6272.383, 1.503},
    {"Maze Bank Arena Roof", -324.300, -1968.545, 67.002},
    {"Cultist Camp", -1170.841, 4926.646, 224.295},
    {"Police Station", 436.491, -982.172, 30.699} // Removed 'f' suffix
};

static std::vector<teleportlist> activitiestele = {{"Golf", -1379.665039, 51.105522, 53.053589}, {"Darts", 1997.273071, 3062.091309, 46.789749}};

static std::vector<teleportlist> misctele = {{"Casino", 901.9708, 24.0314, 79.2593}, {"Lester's House", 1273.898, -1719.304, 54.771}, {"Torture Room", 136.514, -2203.15, 7.30914}, {"Bank Vault", 255.851, 217.030, 101.683}, {"Blaine County Savings Bank", -109.299, 6464.035, 31.627}};