#include "hooking.hpp"
#include "pointers.hpp"
#include "services/bad_players/bad_players.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/players/player_service.hpp"
#include "util/player.hpp"

#include <network/CNetGamePlayer.hpp>
#include <player/CNonPhysicalPlayerData.hpp>

namespace big
{
	bool hooks::send_non_physical_player_data(CNetGamePlayer* player, __int64 message, int flags, void* a4, CNetGamePlayer* a5)
	{
		auto data         = *(CNonPhysicalPlayerData**)(message + 0x10);
		int old_bubble_id = data->m_bubble_id;

		const auto* net_player_data = player->get_net_data();
		auto rockstar_id            = net_player_data->m_gamer_handle.m_rockstar_id;

		if (bad_players_nm::is_blocked(rockstar_id) && *g_pointers->m_gta.m_is_session_started && net_player_data)
		{
			data->m_bubble_id = 10;

			if (auto plyr = g_player_service->get_by_id(player->m_player_id); plyr && !plyr->is_blocked)
			{
				auto str = get_blocked_player_joined_log_string(plyr);

				if (plyr->is_spammer)
					LOG(WARNING) << str;
				else
					g_notification_service->push_success("Preventing Join", str, true);
			}
		}

		bool result = g_hooking->get_original<hooks::send_non_physical_player_data>()(player, message, flags, a4, a5);

		data->m_bubble_id = old_bubble_id;

		return result;
	}
}