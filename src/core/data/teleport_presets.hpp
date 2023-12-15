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
		{"TP_TO_YACHT"_T, BlipIcons::Yacht},
	    {"TP_TO_NIGHTCLUB"_T, BlipIcons::Nightclub},
	    {"TP_TO_FACILITY"_T, BlipIcons::IAAFacility},
	    {"TP_TO_HANGER"_T, BlipIcons::AircraftHanger},
	    {"TP_TO_BUNKER"_T, BlipIcons::Bunker},
	    {"TP_TO_TERRORBYTE"_T, BlipIcons::Terrorbyte}
	});


	inline auto blips_store = std::to_array<blip_tp_list>(
	{
	    {"TP_TO_AMMUNATION"_T, BlipIcons::AmmuNation},
	    {"TP_TO_BARBER"_T, BlipIcons::Barber},
	    {"TP_TO_CONVIENT_STORE"_T, BlipIcons::ConvenienceStore},
	    {"TP_TO_TATTOO_SHOP"_T, BlipIcons::TattooParlor},
	    {"TP_TO_STRIPCLUB"_T, BlipIcons::StripClub},
	    {"TP_TO_LSC"_T, BlipIcons::LosSantosCustoms},
	    {"TP_TO_CLOTHES_STORE"_T, BlipIcons::Clothes},

	});
	inline auto blip_mc = std::to_array<blip_tp_list>(
	{
	    {"TP_TO_WEED_BUISNESS"_T, BlipIcons::Weed},
	    {"TP_TO_COCAINE_BUISNESS"_T, BlipIcons::Cocaine},
	    {"TP_TO_METH_BUISNESS"_T, BlipIcons::Meth},
	    {"TP_TO_FORGED_DOCUMENTS_BUISNESS"_T, BlipIcons::ForgedDocuments},
	    {"TP_TO_COUNTERFEIT_MONEY_BUISNESS"_T, BlipIcons::CounterfeitMoney},
	});


	inline auto sp_safehouses = std::to_array<teleport_list>(
	{
		{"TP_TO_FRANKLINS_AUNTS_HOUSE"_T, -14.3803f, -1438.51f, 31.1073f},
		{"TP_TO_MICHAELS_HOUSE"_T, -813.603f, 179.474f, 72.1548f},
		{"TP_TO_FRANKLINS_HOUSE"_T, 7.11903f, 536.615f, 176.028f},
		{"TP_TO_TREVORS_TRAILER"_T, 1972.61f, 3817.04f, 33.4278f},
		{"TP_TO_TREVORS_METH_LAB"_T, 1391.29f, 3608.6f, 38.9429f},
		{"TP_TO_FLOYDS_APARTMENT"_T, -1151.77f, -1518.14f, 10.6327f},
	});

	inline auto ammunation = std::to_array<teleport_list>(
	{
		{"TP_TO_AMMUNATION_CHUMASH"_T, -3155.888672f, 1073.844482f, 20.188726f},
		{"TP_TO_AMMUNATION_CYPRESS_FLATS"_T, 814.442017f, -2130.448486f, 28.867798f},
	});

	inline auto airfields = std::to_array<teleport_list>(
	{
		{"TP_TO_SANDY_SHORES"_T, 1747.0f, 3273.7f, 41.1f},
		{"TP_TO_LSIA"_T, -1075.3876f, -2938.1072f, 13.9463f},
		{"TP_TO_MCKENZIE_AIRFIELD"_T, 2121.7f, 4796.3f, 41.1f}
	});

	inline auto out_locs = std::to_array<teleport_list>(
	{
	    {"TP_TO_STAB_CITY"_T, 126.975f, 3714.419f, 46.827f},
	    {"TP_TO_WEED_FARM"_T, 2208.777f, 5578.235f, 53.735f},
	    {"TP_TO_GODS_THUMB"_T, -1006.402f, 6272.383f, 1.503f},
	    {"TP_TO_MAZE_BANK_ARENA_ROOF"_T, -324.300f, -1968.545f, 67.002f},
	    {"TP_TO_CULTIST_CAMP"_T, -1170.841f, 4926.646f, 224.295f},
	    {"TP_TO_POLICE_STATION"_T, 436.491f, -982.172f, 30.699f} // Removed 'f' suffix
	});

	inline auto activities_tele = std::to_array<teleport_list>( 
	{
		{"TP_TO_GOLF"_T, -1379.665039f, 51.105522f, 53.053589f},
	});

	inline auto misc_tele = std::to_array<teleport_list>(
	{
		{"TP_TO_CASINO"_T, 901.9708f, 24.0314f, 79.2593f},
		{"TP_TO_LESTERS_HOUSE"_T, 1273.898f, -1719.304f, 54.771f},
		{"TP_TO_TORTURE_ROOM"_T, 136.514f, -2203.15f, 7.30914f},
		{"TP_TO_BANK_VAULT"_T, 255.851f, 217.030f, 101.683f},
		{"TP_TO_SAVINGS_BANK"_T, -109.299f, 6464.035f, 31.627f}
	});
}