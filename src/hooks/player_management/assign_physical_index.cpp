#include "backend/player_command.hpp"
#include "core/settings/notifications.hpp"
#include "core/settings/session.hpp"
#include "hooking.hpp"
#include "services/friends/friends_service.hpp"
#include "services/players/player_service.hpp"
#include "services/recent_modders.cpp"
#include "util/notify.hpp"
#include "util/session.hpp"

#include <network/Network.hpp>

namespace big
{
	inline bool is_spoofed_host_token(uint64_t token)
	{
		if (token < 200'000'000)
			return true;

		return false;
	}

	void* hooks::assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		const auto* net_player_data = player->get_net_data();
		auto player_id              = player->m_player_id;
		auto rockstar_id            = net_player_data ? net_player_data->m_gamer_handle.m_rockstar_id : 0;
		auto player_name            = net_player_data ? net_player_data->m_name : "";
		auto host_token             = net_player_data ? net_player_data->m_host_token : 0;

		if (new_index == static_cast<uint8_t>(-1))
		{
			g_player_service->player_leave(player);

			if (net_player_data)
			{
				if (g_notifications.player_leave.log)
					LOG(INFO) << "Player left '" << player_name << "' freeing slot #" << (int)player_id << " with Rockstar ID: " << rockstar_id;
				if (g_notifications.player_leave.notify)
					g_notification_service->push("Player Left", std::vformat("{} freeing slot", std::make_format_args(player_name)));
			}

			return g_hooking->get_original<hooks::assign_physical_index>()(netPlayerMgr, player, new_index);
		}

		const auto result = g_hooking->get_original<hooks::assign_physical_index>()(netPlayerMgr, player, new_index);

		g_player_service->player_join(player);

		if (net_player_data)
		{
			if (g_notifications.player_join.log)
				LOG(INFO) << "Player joined '" << player_name << "' allocating slot #" << (int)player_id << " with Rockstar ID: " << rockstar_id;
			if (g_notifications.player_join.notify)
				g_notification_service->push("Player Joined", std::vformat("{} taking slot", std::make_format_args(player_name)));

			g_fiber_pool->queue_job([player_id, rockstar_id, player_name, host_token] {
				if (auto plyr = g_player_service->get_by_id(player_id))
				{
					auto recent_modder = recent_modders_nm::recent_modders_list.find(rockstar_id);

					if (!*g_pointers->m_gta.m_is_session_started)
						return;

					if (recent_modder != recent_modders_nm::recent_modders_list.end() && recent_modder->second.block_join)
					{
						if (g_player_service->get_self()->is_host())
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(plyr, {});
						else
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("desync")))->call(plyr, {});

						g_notification_service->push_success("Join Block", std::format("Kicking Player {} ", player_name));
					}
					else if (g_session.lock_session && g_player_service->get_self()->is_host() && !friends_service::is_friend(rockstar_id))
					{
						dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(plyr, {});
						g_notification_service->push_warning("Lock Session", std::format("A player with the name of {} has been denied entry", player_name));
					}
					else if (is_spoofed_host_token(host_token))
						session::add_infraction(plyr, Infraction::SPOOFED_HOST_TOKEN);
				}
			});
		}
		return result;
	}
}
