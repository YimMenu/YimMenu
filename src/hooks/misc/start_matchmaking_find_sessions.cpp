#include "hooking.hpp"
#include "services/matchmaking/matchmaking_service.hpp"
#include <network/Network.hpp>
#include "fiber_pool.hpp"

namespace big
{
	bool hooks::start_matchmaking_find_sessions(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* filter, unsigned int max_sessions, rage::rlSessionInfo* results, int* num_sessions_found, int* status)
	{
		if (g->session_browser.replace_game_matchmaking && filter->m_filter_type == 1)
		{
			*status = 1;
			g_fiber_pool->queue_job([max_sessions, results, num_sessions_found, status]
			{
				if (g_matchmaking_service->matchmake())
				{
					for (int i = 0; i < g_matchmaking_service->get_num_found_sessions(); i++)
					{
						if (g_matchmaking_service->get_found_sessions()[i].is_valid)
						{
							results[*num_sessions_found] = g_matchmaking_service->get_found_sessions()[i].info;
							(*num_sessions_found)++;

							if (max_sessions > *num_sessions_found)
								break;
						}
					}

					*status = 3;
				}
				else
				{
					*status = 2;
				}
			});
			return true;
		}
		else
		{
			return g_hooking->get_original<hooks::start_matchmaking_find_sessions>()(profile_index, available_slots, filter, max_sessions, results, num_sessions_found, status);
		}
	}
}