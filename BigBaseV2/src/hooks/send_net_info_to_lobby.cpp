#include "hooking.hpp"

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::netPlayerData* player, int64_t a2, int64_t a3, DWORD* a4)
	{
		// check so we're 100% sure we modify data only for ourselves
		if (g_local_player->m_player_info->m_net_player_data.m_rockstar_id == player->m_rockstar_id)
		{
			if (g->spoofing.spoof_username)
				memcpy(player->m_name, g->spoofing.username.c_str(), sizeof(player->m_name));

			if (g->spoofing.spoof_ip)
			{
				player->m_external_ip.m_field1 = g->spoofing.ip_address[0];
				player->m_external_ip.m_field2 = g->spoofing.ip_address[1];
				player->m_external_ip.m_field3 = g->spoofing.ip_address[2];
				player->m_external_ip.m_field4 = g->spoofing.ip_address[3];
			}

			if (g->spoofing.spoof_rockstar_id)
			{
				player->m_rockstar_id = g->spoofing.rockstar_id;
				player->m_rockstar_id2 = g->spoofing.rockstar_id;
			}

			if (g->notifications.send_net_info_to_lobby.log)
				LOG(INFO) << "Sending spoofed values to session host";
			if (g->notifications.send_net_info_to_lobby.notify)
				g_notification_service->push("Player Info Spoofing", "Sent spoofed values to lobby host.");
		}

		return g_hooking->m_send_net_info_to_lobby.get_original<decltype(&hooks::send_net_info_to_lobby)>()(player, a2, a3, a4);
	}
}