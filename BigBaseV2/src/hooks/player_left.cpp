#include "hooking.hpp"
#include "services/player_service.hpp"

namespace big
{
	void hooks::player_leave(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		g_player_service->player_leave(net_player);

		if (const rage::netPlayerData* net_player_data = net_player->get_net_data(); net_player_data)
		{
			if (g->notifications.player_leave.log)
				LOG(INFO) << "Player left '" << net_player_data->m_name
						  << "' freeing slot #" << (int)net_player->m_player_id
						  << " with Rockstar ID: " << net_player_data->m_rockstar_id2;
			if (g->notifications.player_leave.notify)
				g_notification_service->push("Player Left", fmt::format("{} freeing slot #{} with Rockstar ID: {}", net_player_data->m_name, net_player->m_player_id, net_player_data->m_rockstar_id2));
		}


		return g_hooking->m_player_has_left_hook.get_original<decltype(&hooks::player_leave)>()(_this, net_player);
	}
}