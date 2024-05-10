#include "backend/player_command.hpp"
#include "core/data/admin_rids.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "hooking/hooking.hpp"
#include "lua/lua_manager.hpp"
#include "packet.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/players/player_service.hpp"
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

		if (new_index == static_cast<uint8_t>(-1))
		{
			g_player_service->player_leave(player);

			if (net_player_data)
			{
				g_lua_manager->trigger_event<menu_event::PlayerLeave>(net_player_data->m_name);

				auto rockstar_id = net_player_data->m_gamer_handle.m_rockstar_id;

				if (g.notifications.player_leave.log)
					LOG(INFO) << "Player left '" << net_player_data->m_name << "' freeing slot #" << (int)player->m_player_id << " with Rockstar ID: " << rockstar_id;

				if (g.notifications.player_leave.notify)
				{
					g_notification_service.push("PLAYER_LEFT"_T.data(),
					    std::vformat("PLAYER_LEFT_INFO"_T, std::make_format_args(net_player_data->m_name, player->m_player_id, rockstar_id)));
				}
			}

			return g_hooking->get_original<hooks::assign_physical_index>()(netPlayerMgr, player, new_index);
		}

		const auto result = g_hooking->get_original<hooks::assign_physical_index>()(netPlayerMgr, player, new_index);
		g_player_service->player_join(player);
		if (net_player_data)
		{
			if (g.protections.admin_check)
			{
				if (admin_rids.contains(net_player_data->m_gamer_handle.m_rockstar_id))
				{
					g_notification_service.push_warning("POTENTIAL_ADMIN_FOUND"_T.data(),
					    std::format("{} {}", net_player_data->m_name, "PLAYER_DETECTED_AS_ADMIN"_T));

					LOG(WARNING) << net_player_data->m_name << " (" << net_player_data->m_gamer_handle.m_rockstar_id << ") has been detected as an admin";

					auto id = player->m_player_id;
					if (auto plyr = g_player_service->get_by_id(id))
						plyr->is_admin = true;
				}
			}

			g_lua_manager->trigger_event<menu_event::PlayerJoin>(net_player_data->m_name, player->m_player_id);

			if (g.notifications.player_join.above_map && *g_pointers->m_gta.m_is_session_started) // prevent loading screen spam
				notify::player_joined(player);

			if (g.notifications.player_join.log)
				LOG(INFO) << "Player joined '" << net_player_data->m_name << "' allocating slot #" << (int)player->m_player_id
				          << " with Rockstar ID: " << net_player_data->m_gamer_handle.m_rockstar_id;

			if (g.notifications.player_join.notify)
			{
				g_notification_service.push("PLAYER_JOINED"_T.data(),
				    std::vformat("PLAYER_JOINED_INFO"_T,
				        std::make_format_args(net_player_data->m_name,
				            player->m_player_id,
				            net_player_data->m_gamer_handle.m_rockstar_id)));
			}

			auto id = player->m_player_id;

			g_fiber_pool->queue_job([id] {
				if (auto plyr = g_player_service->get_by_id(id))
				{
					if (auto rockstar_id = plyr->get_rockstar_id(); rockstar_id != 0)
					{
						if (auto entry = g_player_database_service->get_player_by_rockstar_id(rockstar_id))
						{
							plyr->is_trusted = entry->is_trusted;
							if (!(plyr->is_friend() && g.session.trust_friends))
							{
								plyr->is_modder         = entry->is_modder;
								plyr->block_join        = entry->block_join;
								plyr->block_join_reason = entry->block_join_reason;
							}

							if (strcmp(plyr->get_name(), entry->name.data()))
							{
								g_notification_service.push("PLAYERS"_T.data(),
									std::format("{} {}: {}", entry->name, "PLAYER_CHANGED_NAME"_T, plyr->get_name()));
								entry->name = plyr->get_name();
								g_player_database_service->save();
							}
						}
					}

					if (plyr->block_join && *g_pointers->m_gta.m_is_session_started)
					{
						if (g_player_service->get_self()->is_host())
						{
							dynamic_cast<player_command*>(command::get("breakup"_J))->call(plyr, {});
						}
						else
						{
							dynamic_cast<player_command*>(command::get("desync"_J))->call(plyr, {});
						}
					}

					if (g.session.lock_session && g_player_service->get_self()->is_host() && *g_pointers->m_gta.m_is_session_started)
					{
						if ((plyr->is_friend() && g.session.allow_friends_into_locked_session) || plyr->is_trusted)
						{
							g_notification_service.push_success("LOBBY_LOCK"_T.data(),
							    std::vformat("LOBBY_LOCK_ALLOWED"_T.data(),
							        std::make_format_args(plyr->get_net_data()->m_name)));
						}
						else
						{
							dynamic_cast<player_command*>(command::get("smartkick"_J))->call(plyr, {});
							g_notification_service.push_warning("LOBBY_LOCK"_T.data(),
							    std::vformat("LOBBY_LOCK_DENIED"_T.data(), std::make_format_args(plyr->get_net_data()->m_name)));
						}
					}

					if (is_spoofed_host_token(plyr->get_net_data()->m_host_token))
					{
						session::add_infraction(plyr, Infraction::SPOOFED_HOST_TOKEN);
					}
				}
			});
		}
		return result;
	}

}
