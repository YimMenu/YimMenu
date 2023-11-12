#include "hooking.hpp"
#include "network/Network.hpp"

namespace big
{
	bool hooks::send_session_matchmaking_attributes(void* a1, rage::rlSessionInfo* info, uint64_t session_id, bool use_session_id, MatchmakingAttributes* attributes)
	{
		return g_hooking->get_original<hooks::send_session_matchmaking_attributes>()(a1, info, session_id, use_session_id, attributes);
	}
}