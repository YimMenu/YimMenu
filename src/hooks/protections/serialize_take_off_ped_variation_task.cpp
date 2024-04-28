#include "hooking/hooking.hpp"
#include "util/notify.hpp"

#include <netsync/nodes/task/ClonedTakeOffPedVariationInfo.hpp>

namespace big
{
	constexpr uint32_t valid_parachute_models[] = {
	    "p_parachute_s"_J,
	    "vw_p_para_bag_vine_s"_J,
	    "reh_p_para_bag_reh_s_01a"_J,
	    "xm_prop_x17_scuba_tank"_J,
	    "lts_p_para_bag_pilot2_s"_J,
	    "lts_p_para_bag_lts_s"_J,
	    "p_para_bag_tr_s_01a"_J,
	    "p_para_bag_xmas_s"_J,
	};

	bool is_valid_parachute_model(rage::joaat_t hash)
	{
		for (auto& model : valid_parachute_models)
			if (model == hash)
				return true;

		return false;
	}

	void hooks::serialize_take_off_ped_variation_task(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer)
	{
		g_hooking->get_original<hooks::serialize_take_off_ped_variation_task>()(info, serializer);
		if (!is_valid_parachute_model(info->m_prop_hash)) [[unlikely]]
		{
			notify::crash_blocked(g.m_syncing_player, "invalid parachute model");
			info->m_prop_hash = 0;
		}
	}
}
