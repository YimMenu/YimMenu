#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::report_cash_spawn_handler(__int64 creport_cash_spawn_event, CNetGamePlayer* source_player)
	{
		if (source_player->player_id == PLAYER::PLAYER_ID())
		{
			LOG(INFO) << "Blocked self report for spawning modded cash";

			return false;
		}

		LOG(INFO) << "Reported " << source_player->get_name() << " for spawning modded cash.";

		return g_hooking->m_report_cash_spawn_event_hook.get_original<decltype(&hooks::report_cash_spawn_handler)>()(creport_cash_spawn_event, source_player);
	}
}