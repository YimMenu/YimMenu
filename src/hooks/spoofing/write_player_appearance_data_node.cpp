#include "hooking.hpp"
#include "util/model_info.hpp"

#include <netsync/nodes/player/CPlayerAppearanceDataNode.hpp>

namespace big
{
	void hooks::write_player_appearance_data_node(rage::netObject* player, CPlayerAppearanceDataNode* node)
	{
		g_hooking->get_original<hooks::write_player_appearance_data_node>()(player, node);
	}
}
