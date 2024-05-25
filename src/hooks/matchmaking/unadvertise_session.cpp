#include "hooking/hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"

#include <network/MatchmakingId.hpp>

namespace big
{
	bool hooks::unadvertise_session(int profile_index, MatchmakingId* id, rage::rlTaskStatus* status)
	{
		if (g_matchmaking_service) [[likely]]
		{
			if (g_matchmaking_service->handle_unadvertise(id))
			{
				status->status = 2; // nope
				return true;
			}
		}

		return g_hooking->get_original<hooks::unadvertise_session>()(profile_index, id, status);
	}
}