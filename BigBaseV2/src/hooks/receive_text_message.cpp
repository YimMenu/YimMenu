#include "hooking.hpp"
#include "pointers.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "util/toxic.hpp"
#include "file_manager.hpp"

namespace big
{
	constexpr static const char* spam[] =
	{
		"QQ",
		"WWW.",
		"GTA",
		"www.",
		".cn",
		".CN",
		".TOP",
		".COM",
		".me",
		"666",
		".gg",
		"TRUSTED",
		"VX",
		"\xE3\x80\x90",
		"\xE9\x87\x91",
	};

	static uint64_t gamerHandle[13];
	static char buffer[160]{};

	void hooks::text_message_received(void* a1, char* message, void* something)
	{
		/*bool found = false;
		if (strlen(message) > 20)
		{
			for (auto v : spam)
			{
				if (strstr(message, v) != NULL)
				{
					found = true;
					break;
				}
			}
		}*/

		strncpy(buffer, message, 159);
		g_pointers->m_get_gamer_handle_from_something(something, gamerHandle, 13 * 8, nullptr); // something = *(CNetGamePlayer + 0x70), can compare that value with everyone in the session to find the player too

		g_fiber_pool->queue_job([/*found*/]{
			Player target = NETWORK::NETWORK_GET_PLAYER_FROM_GAMER_HANDLE((Any*)gamerHandle);

			/*if (found)
			{
				toxic::desync_kick(target->get_net_game_player());
			}*/

			if (auto player = g_pointers->m_get_net_game_player(target)) {
				//std::ofstream chat_log(g_file_manager->get_project_file("./chat.csv").get_path(), std::ios::app);

				rage::netPlayerData& plData = player->m_player_info->m_net_player_data;

				LOG(INFO) << "NAME = " << player->get_name() <<
					", SCID = " << plData.m_rockstar_id <<
					", IP = " << (int)plData.m_external_ip.m_field1 << "." << (int)plData.m_external_ip.m_field2 << "." << (int)plData.m_external_ip.m_field3 << "." << (int)plData.m_external_ip.m_field4 <<
					", MESSAGE = " << buffer <<
					", TYPE = MESSAGE" <<
					std::endl;

				//LOG(INFO) << "Message spammer crashed";
			}
		});

		g_hooking->m_text_message_received_hook.get_original<decltype(&hooks::text_message_received)>()(a1, message, something);
		return;
	}
}