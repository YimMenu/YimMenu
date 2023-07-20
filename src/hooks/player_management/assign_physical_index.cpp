#include "backend/player_command.hpp"
#include "core/data/admin_rids.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "lua/lua_manager.hpp"
#include "packet.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"
#include "util/session.hpp"

#include <network/Network.hpp>


namespace big
{
	inline bool is_spoofed_host_token(std::uint64_t token)
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
			g.m_spoofed_peer_ids.erase(player->get_net_data()->m_host_token);
			g_player_service->player_leave(player);

			if (net_player_data)
			{
				g_lua_manager->trigger_event<menu_event::PlayerLeave>(net_player_data->m_name);

				if (g.notifications.player_leave.log)
					LOG(INFO) << "Player left '" << net_player_data->m_name << "' freeing slot #" << (int)player->m_player_id
					          << " with Rockstar ID: " << net_player_data->m_gamer_handle.m_rockstar_id;

				if (g.notifications.player_leave.notify)
				{
					g_notification_service->push("PLAYER_LEFT"_T.data(),
					    std::vformat("PLAYER_LEFT_INFO"_T,
					        std::make_format_args(net_player_data->m_name,
					            player->m_player_id,
					            net_player_data->m_gamer_handle.m_rockstar_id)));
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
					g_notification_service->push_warning("POTENTIAL_ADMIN_FOUND"_T.data(),
					    std::vformat("PLAYER_DETECTED_AS_ADMIN"_T, std::make_format_args(net_player_data->m_name)));

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
				g_notification_service->push("PLAYER_JOINED"_T.data(),
				    std::vformat("PLAYER_JOINED_INFO"_T,
				        std::make_format_args(net_player_data->m_name,
				            player->m_player_id,
				            net_player_data->m_gamer_handle.m_rockstar_id)));
			}

			auto id = player->m_player_id;

			g_fiber_pool->queue_job([id] {
				if (auto plyr = g_player_service->get_by_id(id))
				{
					if (plyr->get_net_data()->m_gamer_handle.m_rockstar_id != 0)
					{
						if (auto entry = g_player_database_service->get_player_by_rockstar_id(
						        plyr->get_net_data()->m_gamer_handle.m_rockstar_id))
						{
							plyr->is_modder         = entry->is_modder;
							plyr->block_join        = entry->block_join;
							plyr->block_join_reason = entry->block_join_reason;

							if (strcmp(plyr->get_name(), entry->name.data()))
							{
								g_notification_service->push("PLAYERS"_T.data(),
								    std::vformat("PLAYER_CHANGED_NAME"_T, std::make_format_args(entry->name, plyr->get_name())));
								entry->name = plyr->get_name();
								g_player_database_service->save();
							}
						}
					}

					if (plyr->block_join)
					{
						if (g_player_service->get_self()->is_host())
						{
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("breakup")))->call(plyr, {});
						}
						else
						{
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("desync")))->call(plyr, {});
						}
					}

					if (g.session.lock_session && g_player_service->get_self()->is_host())
					{
						if (plyr->is_friend() && g.session.allow_friends_into_locked_session)
						{
							g_notification_service->push_success("Lock Session",
							    std::format("A friend with the name of {} has been allowed to join the locked session",
							        plyr->get_net_data()->m_name));
						}
						else
						{
							dynamic_cast<player_command*>(command::get(RAGE_JOAAT("breakup")))->call(plyr, {});
							g_notification_service->push_warning("Lock Session",
							    std::format("A player with the name of {} has been denied entry", plyr->get_net_data()->m_name));
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
