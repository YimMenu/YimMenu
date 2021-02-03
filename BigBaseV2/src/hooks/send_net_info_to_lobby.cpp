#include "hooking.hpp"

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::netPlayerData* local_player, int64_t a2, int64_t a3, DWORD* a4)
	{
		auto& spoof = g_settings.options["spoofing"];

		if (spoof["name"]["enabled"])
		{
			std::string* sName = spoof["name"]["value"].get<std::string*>();
			char name[20];
			strcpy(name, sName->c_str());
			memcpy(local_player->m_name, name, sizeof(name));
		}
		// const char name[20] = "How dare you!";
		// memcpy(local_player->m_name, name, sizeof(name));
		
		if (spoof["ip_address"]["enabled"])
		{
			local_player->m_online_ip.m_field1 = spoof["ip_address"]["address"]["byte0"];
			local_player->m_online_ip.m_field2 = spoof["ip_address"]["address"]["byte1"];
			local_player->m_online_ip.m_field3 = spoof["ip_address"]["address"]["byte2"];
			local_player->m_online_ip.m_field4 = spoof["ip_address"]["address"]["byte3"];
		}

		if (spoof["rockstar_id"]["enabled"])
			local_player->m_rockstar_id = spoof["rockstar_id"]["value"];

		return g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
	}
}