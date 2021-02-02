#include "hooking.hpp"

namespace big
{
	bool hooks::send_net_info_to_lobby(rage::netPlayerData* local_player, int64_t a2, int64_t a3, DWORD* a4)
	{
		// const char name[20] = "How dare you!";
		// memcpy(local_player->m_name, name, sizeof(name));
		local_player->m_online_ip.m_field1 = 69;
		local_player->m_online_ip.m_field2 = 69;
		local_player->m_online_ip.m_field3 = 69;
		local_player->m_online_ip.m_field4 = 69;

		local_player->m_rockstar_id = 1337;

		return g_hooking->m_send_net_info_to_lobby_hook.get_original<decltype(&send_net_info_to_lobby)>()(local_player, a2, a3, a4);
	}
}