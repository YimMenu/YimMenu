#include "hooking.hpp"

#include <netsync/nodes/player/CPlayerCreationDataNode.hpp>

namespace big
{
	void hooks::write_player_creation_data_node(rage::netObject* player, CPlayerCreationDataNode* node)
	{
		g_hooking->get_original<hooks::write_player_creation_data_node>()(player, node);
	}
}
