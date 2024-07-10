#include "hooking/hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"

#include <network/MatchmakingId.hpp>

namespace big
{
	bool hooks::update_session_advertisement(int profile_index, MatchmakingId* id, int num_slots, int available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* data, rage::rlTaskStatus* status)
	{
		if (g_matchmaking_service) [[likely]]
			g_matchmaking_service->handle_update(num_slots, available_slots, info, data, id);

		if (g.spoofing.increase_player_limit)
		{
			num_slots       = 30;
			available_slots = std::max(1, available_slots);
		}

		return g_hooking->get_original<hooks::update_session_advertisement>()(profile_index, id, num_slots, available_slots, info, data, status);
	}
}