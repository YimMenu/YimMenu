#include "hooking.hpp"
#include "util/model_info.hpp"

#include <netsync/nodes/player/CPlayerAppearanceDataNode.hpp>

namespace big
{
	void hooks::write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node)
	{
		g_hooking->get_original<hooks::write_player_appearance_data_node>()(player, node);

		if (g.spoofing.spoof_player_model)
		{
			if (const auto model_hash = rage::joaat(g.spoofing.player_model); model_info::does_model_exist(model_hash))
			{
				node->m_model_hash = model_hash;
			}
			node->m_has_head_blend_data         = false;
			node->components.m_component_bitset = 0;
		}
	}
}
