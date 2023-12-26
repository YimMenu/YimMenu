#pragma once

namespace big
{
	namespace am_launcher
	{
		static const std::unordered_set<Hash> bad_script_hashes = {RAGE_JOAAT("ggsm_arcade"), RAGE_JOAAT("camhedz_arcade"), RAGE_JOAAT("wizard_arcade"), RAGE_JOAAT("puzzle"), RAGE_JOAAT("fm_intro"), RAGE_JOAAT("pilot_school_mp"), RAGE_JOAAT("golf_mp"), RAGE_JOAAT("tennis_network_mp"), RAGE_JOAAT("fm_race_controler"), RAGE_JOAAT("fm_horde_controler"), RAGE_JOAAT("fm_mission_controller"), RAGE_JOAAT("fm_mission_controller_2020"), RAGE_JOAAT("fm_impromptu_dm_controler"), RAGE_JOAAT("fm_deathmatch_controler"), RAGE_JOAAT("fm_bj_race_controler"), RAGE_JOAAT("fm_survival_controller"), RAGE_JOAAT("sctv"), RAGE_JOAAT("am_pi_menu"), RAGE_JOAAT("scroll_arcade_cabinet"), RAGE_JOAAT("grid_arcade_cabinet"), RAGE_JOAAT("degenatron_games"), RAGE_JOAAT("gunslinger_arcade"), RAGE_JOAAT("road_arcade"), RAGE_JOAAT("AM_MP_DRONE")};

		static void START_NEW_SCRIPT_WITH_ARGS(rage::scrNativeCallContext* src)
		{
			const char* const name = src->get_arg<const char*>(0);

			if (bad_script_hashes.contains(rage::joaat(name)))
			{
				src->set_return_value<int>(0);
				return;
			}

			Any* args            = src->get_arg<Any*>(1);
			const int argc       = src->get_arg<int>(2);
			const int stackSize  = src->get_arg<int>(3);

			src->set_return_value<int>(SYSTEM::START_NEW_SCRIPT_WITH_ARGS(name, args, argc, stackSize));
		}
	}
}