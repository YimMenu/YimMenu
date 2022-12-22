#include "hooking.hpp"
#include "pointers.hpp"

constexpr static auto advertisments = std::to_array(
{
	"~h~~r~YimMenu",
	"~h~~g~YimMenu",
	"~h~~b~YimMenu",
	"~h~~y~YimMenu",
	"~h~~o~YimMenu",
	"~h~~p~YimMenu"
});

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::rlGamerInfo* player, int64_t a2, int64_t a3, DWORD* a4)
	{
		const bool is_local_player = g_local_player->m_player_info->m_net_player_data.m_gamer_handle_2.m_rockstar_id == player->m_gamer_handle_2.m_rockstar_id;

		// check so we're 100% sure we modify data only for ourselves
		if (is_local_player)
		{
			if (g.spoofing.spoof_username)
			{
				memcpy(player->m_name, g.spoofing.username.c_str(), sizeof(player->m_name));
			}

			if (g.spoofing.spoof_ip)
			{
				player->m_external_ip.m_field1 = g.spoofing.ip_address[0];
				player->m_external_ip.m_field2 = g.spoofing.ip_address[1];
				player->m_external_ip.m_field3 = g.spoofing.ip_address[2];
				player->m_external_ip.m_field4 = g.spoofing.ip_address[3];
			}

			if (g.spoofing.should_spoof_rockstar_id)
			{
				player->m_gamer_handle.m_rockstar_id = g.spoofing.applied_spoof_rockstar_id;
				player->m_gamer_handle_2.m_rockstar_id = g.spoofing.applied_spoof_rockstar_id;
			}

			if (g.notifications.send_net_info_to_lobby.log)
				LOG(INFO) << "Sending spoofed values to session host";
			if (g.notifications.send_net_info_to_lobby.notify)
				g_notification_service->push("Player Info Spoofing", "Sent spoofed values to lobby host.");
		}
		else
		{
			if (g.session.name_spoof_enabled)
			{
				if (g.session.advertise_menu)
				{
					memcpy(player->m_name, advertisments[rand() % advertisments.size()], sizeof(player->m_name));
				}
				else
				{
					memcpy(player->m_name, g.session.spoofed_name.c_str(), sizeof(player->m_name));
				}
			}
		}

		return g_hooking->get_original<hooks::send_net_info_to_lobby>()(player, a2, a3, a4);
	}
}
