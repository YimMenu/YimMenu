#include "hooking/hooking.hpp"
#include "util/sync_trees.hpp"
#include "services/players/player_service.hpp"
#include <netsync/netSyncDataNode.hpp>

namespace big
{
	bool hooks::write_node(rage::netSyncDataNode* node, int sync_type, int a3, rage::netObject* object, rage::datBitBuffer* buffer, int a6, void* log, std::uint8_t player, int* a9, int* a10)
	{
		uint64_t old_sync_cache_val = 0;
		g.m_sync_target_player = player;
		
		if (g.session.harass_players)
		{
			auto& type = sync_node_finder::find(reinterpret_cast<uint64_t>(node));

			if (type == sync_node_id("CPedGameStateDataNode") || type == sync_node_id("CSectorDataNode") || type == sync_node_id("CPlayerSectorPosNode"))
			{
				std::swap(old_sync_cache_val, node->pad4);
				node->flags |= 1;
			}
		}

		if (auto plyr = g_player_service->get_by_id(player); (plyr && plyr->spam_killfeed) || g.session.spam_killfeed)
		{
			auto& type = sync_node_finder::find(reinterpret_cast<uint64_t>(node));

			if (type == sync_node_id("CPedHealthDataNode"))
			{
				std::swap(old_sync_cache_val, node->pad4);
				node->flags |= 1;
			}
		}

		bool ret_val = g_hooking->get_original<hooks::write_node>()(node, sync_type, a3, object, buffer, a6, log, player, a9, a10);

		if (old_sync_cache_val)
			std::swap(old_sync_cache_val, node->pad4);

		return ret_val;
	}
}