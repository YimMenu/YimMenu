#include "core/globals.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "packet.hpp"
#include "services/player_database/player_database_service.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"

#include <network/Network.hpp>



namespace big
{
	std::vector<std::uint64_t> admin_rids = {67241866, 89288299, 88439202, 179848415, 184360405, 184359255, 182860908, 117639172, 142582982, 115642993, 100641297, 116815567, 88435319, 64499496, 174623946, 174626867, 151972200, 115643538, 144372813, 88047835, 115670847, 173426004, 170727774, 93759254, 174247774, 151975489, 146999560, 179930265, 88435236, 179936743, 179848203, 151158634, 174623904, 179936852, 117639190, 93759401, 103814653, 121970978, 174623951, 174624061, 10552062, 174625194, 174625307, 174625407, 174625552, 174625647, 138273823, 138302559, 139813495, 88435916, 174875493, 171094021, 173213117, 171093866, 88435362, 137601710, 103054099, 104041189, 99453882, 104432921, 147604980, 130291558, 141884823, 131037988, 153219155, 155527062, 114982881, 119266383, 119958356, 216820, 121397532, 121698158, 18965281, 56778561, 63457, 121943600, 123017343, 123849404, 127448079, 129159629, 127403483, 174194059, 131973478, 64234321, 62409944, 64074298, 133709045, 134412628, 137579070, 137714280, 137851207, 130291511, 138075198, 137663665, 9284553, 147111499, 6597634, 23659342, 23659354, 103318524, 132521200, 107713114, 107713060, 23659353, 57233573, 111439945, 81691532, 77205006, 25695975, 24646485, 49770174, 146452200, 54468359, 54462116, 53309582, 85593421, 21088063, 50850475, 31586721, 56583239, 20158753, 20158751, 23659351, 91031119, 91003708, 16396170, 16396157, 16396148, 16396141, 16396133, 16396126, 16396118, 16396107, 16396096, 16396091, 16396080, 16395850, 16395840, 16395850, 16395782, 16395773, 22577458, 22577440, 22577121, 16395782, 20158757, 20158757, 117641111, 173200071, 196222661, 179654627, 214327469, 213560223, 179608067, 209260139, 195489237, 209260788, 201693153, 211750362, 211702584, 211532217, 24037237, 77817603, 205951017, 89705641, 179848153, 193975449, 201727585, 201693153, 193972138, 192796203, 201693551, 204071275, 67241866, 174754789, 135811063, 64624133, 89705672, 89797943, 191415974, 28776717, 41352312, 56176623};
	void* hooks::assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		const auto* net_player_data = player->get_net_data();

		if (new_index == static_cast<uint8_t>(-1))
		{
			g.m_spoofed_peer_ids.erase(player->get_net_data()->m_host_token);
			g_player_service->player_leave(player);

			if (net_player_data)
			{
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
			auto found = std::find(admin_rids.begin(), admin_rids.end(), net_player_data->m_gamer_handle.m_rockstar_id);
			if (found != admin_rids.end())
			{
				g_notification_service->push_warning("Potential Admin Found!",
				    std::format("{} has been detected as admin", net_player_data->m_name));
				LOG(WARNING) << net_player_data->m_name << " (" << net_player_data->m_gamer_handle.m_rockstar_id << ") has been detected as admin";
			}
			if (g.notifications.player_join.above_map && *g_pointers->m_is_session_started) // prevent loading screen spam
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
							plyr->block_join_reason = plyr->block_join_reason;

							if (strcmp(plyr->get_name(), entry->name.data()))
							{
								g_notification_service->push("PLAYERS"_T.data(),
								    std::vformat("PLAYER_CHANGED_NAME"_T, std::make_format_args(entry->name, plyr->get_name())));
								entry->name = plyr->get_name();
								g_player_database_service->save();
							}
						}
					}

					if (auto snplyr = plyr->get_session_player())
					{
						packet msg{};
						msg.write_message(rage::eNetMessage::MsgSessionEstablishedRequest);
						msg.write<uint64_t>(gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id, 64);
						msg.send(snplyr->m_msg_id);
					}
				}
			});
		}
		return result;
	}

}
