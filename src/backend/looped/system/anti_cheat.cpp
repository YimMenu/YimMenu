#include "backend/looped/looped.hpp"
#include "services/anti_cheat/anti_cheat_service.hpp"

namespace big
{
	void looped::anti_cheat()
	{
		for (const auto& [name, player] : g_player_service->players())
		{
			if (player != g_player_service->get_self())
			{
				g_anti_cheat_service->modder_check(player->id());
			}
		}
	}
}
