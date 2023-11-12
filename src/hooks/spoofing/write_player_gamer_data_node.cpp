#include "hooking.hpp"

#include <netsync/nodes/player/CPlayerGamerDataNode.hpp>

namespace big
{
	void hooks::write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node)
	{
		g_hooking->get_original<write_player_gamer_data_node>()(player, node);
	}
}
