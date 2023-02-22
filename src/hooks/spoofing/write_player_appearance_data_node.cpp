#include "hooking.hpp"

#include <netsync/nodes/player/CPlayerAppearanceDataNode.hpp>

namespace big
{
	void hooks::write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node)
	{
		g_hooking->get_original<hooks::write_player_appearance_data_node>()(player, node);

		if (g.spoofing.spoof_player_model)
		{
			node->m_model_hash                  = rage::joaat(g.spoofing.player_model);
			node->m_has_head_blend_data         = false;
			node->components.m_component_bitset = 0;
		}
	}
}
