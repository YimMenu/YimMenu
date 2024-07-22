#pragma once

namespace big
{
	// Get new values from gameconfig.xml
	constexpr inline static const std::pair<const char*, int> stack_sizes[] = {
	    {"MICRO", 128},
	    {"MINI", 512},
	    {"DEFAULT", 1424},
	    {"SPECIAL_ABILITY", 1828},
	    {"FRIEND", 2050},
	    {"SHOP", 2324},
	    {"CELLPHONE", 2552},
	    {"VEHICLE_SPAWN", 3568},
	    {"CAR_MOD_SHOP", 3750},
	    {"PAUSE_MENU_SCRIPT", 3076},
	    {"APP_INTERNET", 4592},
	    {"MULTIPLAYER_MISSION", 5050},
	    {"CONTACTS_APP", 4000},
	    {"INTERACTION_MENU", 9800},
	    {"SCRIPT_XML", 8344},
	    {"PROPERTY_INT", 19400},
	    {"ACTIVITY_CREATOR_INT", 15900},
	    {"SMPL_INTERIOR", 2512},
	    {"WAREHOUSE", 14100},
	    {"IE_DELIVERY", 2324},
	    {"SHOP_CONTROLLER", 3800},
	    {"AM_MP_YACHT", 5000},
	    {"INGAMEHUD", 4600},
	    {"TRANSITION", 8032},
	    {"FMMC_LAUNCHER", 27000},
	    {"MULTIPLAYER_FREEMODE", 85000},
	    {"MISSION", 62500},
	    {"MP_LAUNCH_SCRIPT", 34750},
	};
}