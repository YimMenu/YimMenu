#pragma once
namespace big
{
	#include "gta/enums.hpp"

	struct blip_tp_list
	{
		const std::string_view m_name;
		BlipIcons m_blipsprites;
	};


	struct teleport_list
	{
		const std::string_view m_name;
		Vector3 m_coords;

		teleport_list(const std::string_view name, float x, float y, float z) :
			m_name(name),
			m_coords(x, y, z)
		{
		}
	};

	inline auto blip_business = std::to_array<blip_tp_list>(
	{
		{"Teleport To Yacht"_T, BlipIcons::Yacht},
	    {"Teleport To Personal Vehicle"_T, BlipIcons::PersonalVehicleCar},
	    {"Teleport To Nightclub"_T, BlipIcons::Nightclub},
	    {"Teleport To Race Finish Test"_T, BlipIcons::RaceFinish},
	    {"Teleport To Facility"_T, BlipIcons::IAAFacility},
	    {"Teleport To Hanger"_T, BlipIcons::AircraftHanger},
	    {"Teleport To Bunker"_T, BlipIcons::Bunker},
	    {"Teleport To Terrorbyte"_T, BlipIcons::Terrorbyte}
	});


	inline auto blips_store = std::to_array<blip_tp_list>(
	{
	    {"Teleport To Ammunation"_T, BlipIcons::AmmuNation},
	    {"Teleport To Barber"_T, BlipIcons::Barber},
	    {"Teleport To Convient Store"_T, BlipIcons::ConvenienceStore},
	    {"Teleport To Tattoo Shop"_T, BlipIcons::TattooParlor},
	    {"Teleport To Stripclub"_T, BlipIcons::StripClub},
	    {"Teleport To LSC"_T, BlipIcons::LosSantosCustoms},
	    {"Teleport To Clothes Store"_T, BlipIcons::Clothes},

	});
	inline auto blip_mc = std::to_array<blip_tp_list>(
	{
	    {"Teleport To Weed Buisness"_T, BlipIcons::Weed},
	    {"Teleport To Cocaine Buisness"_T, BlipIcons::Cocaine},
	    {"Teleport To Meth Buisness"_T, BlipIcons::Meth},
	    {"Teleport To Forged Documents Buisness"_T, BlipIcons::ForgedDocuments},
	    {"Teleport To Counterfeit Money Buisness"_T, BlipIcons::CounterfeitMoney},
	});


	inline auto sp_safehouses = std::to_array<teleport_list>(
	{
		{"Franklin's Aunt's House"_T, -14.3803f, -1438.51f, 31.1073f},
		{"Michael's House"_T, -813.603f, 179.474f, 72.1548f},
		{"Franklin's Vinewood House"_T, 7.11903f, 536.615f, 176.028f},
		{"Trevor's Trailer"_T, 1972.61f, 3817.04f, 33.4278f},
		{"Trevor's Meth Lab"_T, 1391.29f, 3608.6f, 38.9429f},
		{"Trevor's Sandy Shores Trailer"_T, 1985.481f, 3812.189f, 32.5f},
		{"Trevor's Airfield"_T, 1727.85f, 3299.08f, 40.0638f},
		{"Trevor's Strip Club"_T, 126.135f, -1278.583f, 29.270f},
		{"Trevor's Pillbox Hill Apartment"_T, -1150.703f, -1520.713f, 10.633f},
		{"Trevor's Warehouse"_T, 1000.976f, -3100.461f, -39.999f},
		{"Trevor's Office"_T, -1151.756f, -1518.68f, 10.633f},
		{"Trevor's Garage"_T, 197.815f, -1002.95f, -99.999f},
		{"Floyd's Apartment"_T, -1151.77f, -1518.14f, 10.6327f},
		{"Vanilla Unicorn Office"_T, 97.2707f, -1290.9940f, 29.2688f}
	});

	inline auto clothings = std::to_array<teleport_list>(
	{
		{"Masks - Vespucci Beach"_T, -1342.185913f, -1280.013428f, 4.443256f},
		{"Discount Store - Polito Bay"_T, -4.509100f, 6521.252930f, 30.571024f},
		{"Discount Store - Grand Senora Desert"_T, 1179.679688f, 2691.378662f, 37.124043f},
		{"Binco - La Puerta"_T, -814.432800, -1085.986938, 10.567306f},
		{"Binco - Strawberry"_T, 411.403564f, -806.654907f, 28.742212f},
		{"Binco - Rockford Hills"_T, -821.584229f, -1073.489014f, 11.328976f},
		{"Binco - Burton"_T, -1457.540527f, -229.017136f, 49.185726f},
		{"Binco - Hawick"_T, 88.2911f, -1391.929f, 29.202f},
		{"Binco - Davis"_T, 12.4152f, -1105.245f, 29.797f},
		{"Binco - Paleto Bay"_T, 4.254f, 6512.813f, 31.877f},
		{"Binco - Sandy Shores"_T, 1693.917f, 4822.811f, 42.063f},
		{"Ponsonbys - Rockford Hills"_T, -725.551453f, -162.833710f, 36.570301f},
		{"Suburban - Harmony"_T, 619.3096f, 2738.7136f, 41.9631f},
		{"Suburban - Hawick"_T, 134.122055f, -200.211334f, 53.864090f}

	});

	inline auto ammunation = std::to_array<teleport_list>(
	{
		{"Ammunation - Chumash"_T, -3155.888672f, 1073.844482f, 20.188726f},
		{"Ammunation - Cypress Flats"_T, 814.442017f, -2130.448486f, 28.867798f},
		{"Ammunation - Great Chaparral"_T, -1108.600830f, 2685.694092f, 18.177374f},
		{"Ammunation - Hawick"_T, 235.666794f, -42.263149f, 69.221313f},
		{"Ammunation - La Mesa"_T, 844.439026f, -1009.422424f, 27.511728f},
		{"Ammunation - Little Seoul"_T, -665.232727f, -952.522522f, 20.866556f},
		{"Ammunation - Morningwood"_T, -1328.592896f, -387.114410f, 36.126881f},
		{"Ammunation - Palomino Freeway"_T, 2571.371826f, 313.879608f, 107.970573f},
		{"Ammunation - Pillbox Hill"_T, 15.6435f, -1121.7327f, 28.8248f},
		{"Ammunation - Polito Bay"_T, -318.859039f, 6074.433105f, 30.614943f},
		{"Ammunation - Sandy Shores"_T, 1704.671997f, 3748.880615f, 33.286053f}
	});

	inline auto car_stuff = std::to_array<teleport_list>(
	{{"Los Santos Customs - Los Santos Airport"_T, -1135.707275f, -1987.154175f, 12.976217f},
		{"Los Santos Customs - La Mesa"_T, 709.295471f, -1081.996216f, 21.975765f},
		{"Los Santos Customs - Burton"_T, -370.533752f, -130.402649f, 38.197617f},
		{"Los Santos Customs - Sandy Shores"_T, 1176.822632f, 2657.973145f, 37.370682f},
		{"Bennys Garage"_T, -196.349442f, -1303.103271f, 30.650515f}

	});


	inline auto airfields = std::to_array<teleport_list>(
	{
		{"Sandy Shores Airfield"_T, 1747.0f, 3273.7f, 41.1f},
		{"Los Santos International Airport"_T, -1075.3876f, -2938.1072f, 13.9463f},
		{"McKenzie Airfield"_T, 2121.7f, 4796.3f, 41.1f}
	});


	inline auto out_locs = std::to_array<teleport_list>(
	{
	    {"Stab City"_T, 126.975f, 3714.419f, 46.827f},
	    {"Weed Farm"_T, 2208.777f, 5578.235f, 53.735f},
	    {"Gods Thumb"_T, -1006.402f, 6272.383f, 1.503f},
	    {"Maze Bank Arena Roof"_T, -324.300f, -1968.545f, 67.002f},
	    {"Cultist Camp"_T, -1170.841f, 4926.646f, 224.295f},
	    {"Police Station"_T, 436.491f, -982.172f, 30.699f} // Removed 'f' suffix
	});

	inline auto activities_tele = std::to_array<teleport_list>( 
	{
		{"Golf"_T, -1379.665039f, 51.105522f, 53.053589f},
		{"Darts"_T, 1997.273071f, 3062.091309f, 46.789749f}
	});

	inline auto misc_tele = std::to_array<teleport_list>(
	{
		{"Casino"_T, 901.9708f, 24.0314f, 79.2593f},
		{"Lester's House"_T, 1273.898f, -1719.304f, 54.771f},
		{"Torture Room"_T, 136.514f, -2203.15f, 7.30914f},
		{"Bank Vault"_T, 255.851f, 217.030f, 101.683f},
		{"Blaine County Savings Bank"_T, -109.299f, 6464.035f, 31.627f}
	});
}