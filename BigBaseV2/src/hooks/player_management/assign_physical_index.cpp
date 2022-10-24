#include "hooking.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"

namespace big
{
	void* hooks::assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		const auto result = g_hooking->m_assign_physical_index_hook.get_original<decltype(&hooks::assign_physical_index)>()(netPlayerMgr, player, new_index);
		const auto* net_player_data = player->get_net_data();
		
		if (new_index == static_cast<uint8_t>(-1))
		{
			g_player_service->player_leave(player);

			if (net_player_data)
			{
				if (g->notifications.player_leave.log)
					LOG(INFO) << "Player left '" << net_player_data->m_name
						<< "' freeing slot #" << (int)player->m_player_id
						<< " with Rockstar ID: " << net_player_data->m_gamer_handle_2.m_rockstar_id;

				if (g->notifications.player_leave.notify)
					g_notification_service->push("Player Left", std::format("{} freeing slot #{} with Rockstar ID: {}", net_player_data->m_name, player->m_player_id, net_player_data->m_gamer_handle_2.m_rockstar_id));
			}

			return result;
		}

		g_player_service->player_join(player);
		if (net_player_data)
		{
			if (g->notifications.player_join.above_map && *g_pointers->m_is_session_started) // prevent loading screen spam
				notify::player_joined(player);

			if (g->notifications.player_join.log)
				LOG(INFO) << "Player joined '" << net_player_data->m_name
					<< "' allocating slot #" << (int)player->m_player_id
					<< " with Rockstar ID: " << net_player_data->m_gamer_handle_2.m_rockstar_id;

			if (g->notifications.player_join.notify)
				g_notification_service->push("Player Joined", std::format("{} taking slot #{} with Rockstar ID: {}", net_player_data->m_name, player->m_player_id, net_player_data->m_gamer_handle_2.m_rockstar_id));
		}
		return result;
	}
}