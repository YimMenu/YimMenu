#include "hooking.hpp"
#include "natives.hpp"
#include "features/notify.hpp"

namespace big
{
	bool hooks::increment_stat_event(uint64_t net_event_struct, CNetGamePlayer* sender, int64_t a3)
	{
		Hash hash = *reinterpret_cast<DWORD*>(net_event_struct + 0x30);
		Player sender_id = sender->player_id;

		switch (hash)
		{
		case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_VC_HATE"):
		case RAGE_JOAAT("MPPLY_EXPLOITS"):
		case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"):
		case RAGE_JOAAT("MPPLY_TC_HATE"):
			char report[64];
			strcpy(report, "~g~BLOCKED REPORT~s~\nFrom: <C>");
			strcat(report, PLAYER::GET_PLAYER_NAME(sender_id));
			strcat(report, "</C>");

			notify::above_map(report);

			return true;
		}

		return g_hooking->m_increment_stat_hook.get_original<decltype(&increment_stat_event)>()(net_event_struct, sender, a3);
	}
}