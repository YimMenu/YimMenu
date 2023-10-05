#include "hooking.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

#include <network/CNetGamePlayer.hpp>
#include <player/CNonPhysicalPlayerData.hpp>

namespace big
{
	bool hooks::send_non_physical_player_data(CNetGamePlayer* player, __int64 message, int flags, void* a4, CNetGamePlayer* a5)
	{
		auto plyr         = g_player_service->get_by_id(player->m_player_id);
		auto data         = *(CNonPhysicalPlayerData**)(message + 0x10);
		int old_bubble_id = data->m_bubble_id;

		bool result = g_hooking->get_original<hooks::send_non_physical_player_data>()(player, message, flags, a4, a5);

		data->m_bubble_id = old_bubble_id;

		return result;
	}
}