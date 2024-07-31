#include "hooking/hooking.hpp"
#include "util/sync_trees.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	bool hooks::can_send_node_to_player(void* node, rage::netObject* object, std::uint8_t player, int sync_type, int a5, int a6)
	{
		if (g.session.harass_players)
		{
			auto& type = sync_node_finder::find(reinterpret_cast<uint64_t>(node));

			if (type == sync_node_id("CPedGameStateDataNode") || type == sync_node_id("CSectorDataNode") || type == sync_node_id("CPlayerSectorPosNode"))
			{
				return true;
			}
		}

		if (auto plyr = g_player_service->get_by_id(player); (plyr && plyr->spam_killfeed) || g.session.spam_killfeed)
		{
			auto& type = sync_node_finder::find(reinterpret_cast<uint64_t>(node));

			if (type == sync_node_id("CPedHealthDataNode"))
			{
				return true;
			}
		}

		return g_hooking->get_original<hooks::can_send_node_to_player>()(node, object, player, sync_type, a5, a6);
	}
}