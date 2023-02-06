#pragma once
#include "script_global.hpp"
#include "script_local.hpp"
#include "scripts.hpp"

namespace big::heist::cayo
{
	const int crew_cut			= 1977693 + 823 + 56 + (1 + 0 * 1);
	const int bag_size			= 262145 + 29732;
	const int target_value		= 262145 + 29982;
	const int multiplier_normal	= 262145 + 29988;
	const int multiplier_hard	= 262145 + 29989;
	const int fencing_fee		= 262145 + 29991;
	const int pavel_fee			= 262145 + 29992;

	const int take = 45687 + 1392 + 53;
	const int team_lives = 48647 + 868 + (1 + 0 * 1);
	inline void instant_heist_passed()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")); thread)
		{
			if (scripts::force_host(RAGE_JOAAT("fm_mission_controller_2020")))
			{
				misc::set_bit(script_local(thread, 42279).as<int*>(), 16);
				*script_local(thread, 42279).at(1375).at(0, 1).as<int*>() = 50;
			}
		}
	}
	inline void hack_fingerprint()
	{
		if(auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")); thread)
			*script_local(thread, 22032).as<int*>() = 5;
	}
	inline void plasma_cutter_instant_cut()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")); thread)
			*script_local(thread, 27985).at(3).as<float*>() = 100.0;
	}
	inline void grate_instant_cut()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")); thread)
			*script_local(thread, 26746).as<int*>() = 6;
	}
}

namespace big::heist::casino
{
	const int crew_cut					= 1970895 + 1497 + 736 + 92 + (1 + 0 * 1);	
	const int multiplier_normal			= 262145 + 28786;
	const int multiplier_hard			= 262145 + 28787;
	const int buyer_multiplier_easy		= 262145 + 28788;
	const int buyer_multiplier_normal	= 262145 + 28789;
	const int buyer_multiplier_hard		= 262145 + 28790;
	const int lester_cut				= 262145 + 28791;							
	const int target_value				= 262145 + 28805;
	const int ai_cut					= 262145 + 28817;

	const int take = 19707 + 2686;
	const int team_lives = 26133 + 1325 + (1 + 0 * 1);
	inline void instant_heist_passed()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")); thread)
		{
			if (scripts::force_host(RAGE_JOAAT("fm_mission_controller")))
			{
				misc::set_bit(script_local(thread, 19707).as<int*>(), 16);
				*script_local(thread, 19707).at(1232).at(0, 1).as<int*>() = 105;
			}
		}
	}
	inline void hack_fingerprint()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")); thread)
			*script_local(thread, 52962).as<int*>() = 5;
	}
	inline void hack_keypad()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")); thread)
			*script_local(thread, 54024).as<int*>() = 5;
	}
	inline void break_vault_door()
	{
		if (auto thread = gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")); thread)
			*script_local(thread, 10098).at(7).as<int*>() = *script_local(thread, 10098).at(37).as<int*>();
	}
}

namespace big::heist::doomsday
{
	const int crew_cut				= 1966831 + 812 + 50 + (1 + 0 * 1);
	const int target_value			= 262145 + 9133;
	const int multiplier_normal		= 262145 + 9202;
	const int multiplier_hard		= 262145 + 9203;
}

namespace big::heist::apart
{
	const int crew_cut			= 1937658 + 3008 + (1 + 0 * 1); //https://www.unknowncheats.me/forum/2923446-post841.html
	const int target_value		= 262145 + 9128;
	const int multiplier_easy	= 262145 + 9199;
	const int multiplier_normal	= 262145 + 9200;
	const int multiplier_hard	= 262145 + 9201;
}

namespace big::heist::agency_vip_contract
{
	const int contract_reward = 262145 + 31747;
}

namespace big::heist::auto_shop_contracts
{
	const int contract_reward = 262145 + 31042 + (1 + 0 * 1);
}