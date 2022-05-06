#include "hooking.hpp"
#include "services/player_service.hpp"
#include "util/notify.hpp"
#include "gta_util.hpp"

namespace big
{
	CNetGamePlayer* net;

	void hooks::player_join(CNetworkObjectMgr* _this, CNetGamePlayer* net_player)
	{
		g_player_service->player_join(net_player);

		if (const rage::netPlayerData* net_player_data = net_player->get_net_data(); net_player_data)
		{
			if (g->notifications.player_join.above_map)
				notify::player_joined(net_player);

			//Spammer auto Desync
			if (net_player_data->m_rockstar_id2 == 1870144302 /*ballstorture*/ || net_player_data->m_rockstar_id2 == 206464061 /*DesktopKitty*/ || net_player_data->m_rockstar_id2 == 187160190 /*Wavy services*/ || net_player_data->m_rockstar_id2 == 6589458795 /*ItzGoated!!*/ || net_player_data->m_rockstar_id2 == 797367953 /*GTAVKRUTKA*/)
			{
				net = net_player;
				g_fiber_pool->queue_job([]
					{
					gta_util::get_network_player_mgr()->RemovePlayer(net);
					LOG(INFO) << "Kicking " << net->m_player_id;
					});
			}

			if (g->notifications.player_join.log)
				LOG(INFO) << "Player joined '" << net_player_data->m_name
						  << "' taking slot #" << (int)net_player->m_player_id
						  << " with Rockstar ID: " << net_player_data->m_rockstar_id2;

			if (g->notifications.player_join.notify)
				g_notification_service->push("Player Joined", fmt::format("{} taking slot #{} with Rockstar ID: {}", net_player_data->m_name, net_player->m_player_id, net_player_data->m_rockstar_id2));
		}

		return g_hooking->m_player_has_joined_hook.get_original<decltype(&hooks::player_join)>()(_this, net_player);
	}
}