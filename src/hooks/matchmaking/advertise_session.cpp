#include "hooking/hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"

#include <network/MatchmakingId.hpp>

namespace big
{
	bool hooks::advertise_session(int profile_index, int num_slots, int available_slots, MatchmakingAttributes* data, std::uint64_t session_id, rage::rlSessionInfo* info, MatchmakingId* out_id, rage::rlTaskStatus* status)
	{
		if (g_matchmaking_service) [[likely]]
			if (g_matchmaking_service->handle_advertise(num_slots, available_slots, info, data, out_id, status))
				return true;

		return g_hooking->get_original<hooks::advertise_session>()(profile_index, num_slots, available_slots, data, session_id, info, out_id, status);
	}
}