#include "fiber_pool.hpp"
#include "function_types.hpp"
#include "hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"

#include <network/Network.hpp>

namespace big
{
	bool hooks::start_matchmaking_find_sessions(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* filter, unsigned int max_sessions, rage::rlSessionInfo* results, int* num_sessions_found, rage::rlTaskStatus* status)
	{
		return g_hooking->get_original<hooks::start_matchmaking_find_sessions>()(profile_index, available_slots, filter, max_sessions, results, num_sessions_found, status);
	}
}