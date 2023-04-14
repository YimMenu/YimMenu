#pragma once

namespace big
{
	namespace am_launcher
	{
		inline void START_NEW_SCRIPT_WITH_ARGS(rage::scrNativeCallContext* src)
		{
			const char* name = src->get_arg<const char*>(0);
			uint64_t* args   = src->get_arg<uint64_t*>(1);
			int argc         = src->get_arg<int>(2);
			int stackSize    = src->get_arg<int>(3);

			Hash name_hash = rage::joaat(name);

			if (name_hash == RAGE_JOAAT("ggsm_arcade") || name_hash == RAGE_JOAAT("camhedz_arcade") || name_hash == RAGE_JOAAT("wizard_arcade") || name_hash == RAGE_JOAAT("puzzle") || name_hash == RAGE_JOAAT("fm_intro") || name_hash == RAGE_JOAAT("pilot_school_mp") || name_hash == RAGE_JOAAT("golf_mp") || name_hash == RAGE_JOAAT("tennis_network_mp") || name_hash == RAGE_JOAAT("fm_race_controler") || name_hash == RAGE_JOAAT("fm_horde_controler") || name_hash == RAGE_JOAAT("fm_mission_controller") || name_hash == RAGE_JOAAT("fm_mission_controller_2020") || name_hash == RAGE_JOAAT("fm_impromptu_dm_controler") || name_hash == RAGE_JOAAT("fm_deathmatch_controler") || name_hash == RAGE_JOAAT("fm_bj_race_controler") || name_hash == RAGE_JOAAT("fm_survival_controller") || name_hash == RAGE_JOAAT("tennis_network_mp") || name_hash == RAGE_JOAAT("sctv") || name_hash == RAGE_JOAAT("am_pi_menu"))
			{
				src->set_return_value<int>(0);
				return;
			}

			src->set_return_value<int>(SYSTEM::START_NEW_SCRIPT_WITH_ARGS(name, (Any*)args, argc, stackSize));
		};
	}
}