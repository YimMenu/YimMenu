#include "backend/player_command.hpp"
#include "core/settings/notifications.hpp"
#include "core/settings/session.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "services/bad_players/bad_players.hpp"
#include "services/friends/friends_service.hpp"
#include "services/gui/gui_service.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"
#include "util/player.hpp"
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

		auto rockstar_id = net_player_data ? net_player_data->m_gamer_handle.m_rockstar_id : 0;
		auto player_name = net_player_data ? net_player_data->m_name : "";
		auto host_token  = net_player_data ? net_player_data->m_host_token : 0;

		if (new_index == static_cast<uint8_t>(-1))
		{
			g_player_service->player_leave(player);

			if (net_player_data)
			{
				if (g_notifications.player_leave.log)
					LOG(INFO) << "Player left '" << player_name << "' freeing slot #" << (int)player->m_player_id << " with Rockstar ID: " << rockstar_id;
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
				LOG(INFO) << "Player joined '" << player_name << "' allocating slot #" << (int)player->m_player_id << " with Rockstar ID: " << rockstar_id;
			if (g_notifications.player_join.notify)
				g_notification_service->push("Player Joined", std::vformat("{} taking slot", std::make_format_args(player_name)));

			if (player->m_player_id != self::id)
				g_fiber_pool->queue_job([id = player->m_player_id, rockstar_id, player_name, host_token] {
					if (auto plyr = g_player_service->get_by_id(id))
					{
						if (*g_pointers->m_gta.m_is_session_started)
						{
							if (bad_players_nm::is_blocked(rockstar_id))
							{
								auto str = get_blocked_player_joined_log_string(plyr);

								if (g_player_service->get_self()->is_host())
								{
									LOG(WARNING) << str;
									dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(plyr, {});
									return;
								}

								if (plyr->is_spammer)
									LOG(WARNING) << str;
								else
									g_notification_service->push_warning("Carefull", str, true);
							}
							else if (g_session.lock_session && g_player_service->get_self()->is_host() && !friends_service::is_friend(rockstar_id))
							{
								dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(plyr, {});
								g_notification_service->push_warning("Lock Session", std::format("Player {} denied entry to locked session.", player_name), true);
								return;
							}
						}

						if (is_spoofed_host_token(host_token))
							g_reactions.spoofed_host_token.process(plyr, false, Infraction::SPOOFED_HOST_TOKEN, true);
					}
				});
			else
				LOG(INFO) << "Player joined async job skipped for player " << player_name;
		}

		return result;
	}
}
