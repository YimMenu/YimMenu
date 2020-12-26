#include "features.hpp"
#include "script_global.hpp"

namespace big
{
	void features::off_radar()
	{
		if (g_settings.options["off_radar"].get<bool>())
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				if (PLAYER::IS_PLAYER_ONLINE())
				{
					*script_global(2425869).at(1 + (g_playerId * 443)).at(204).as<int*>() = 1;
					*script_global(2440049).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 999;
				}
			}QUEUE_JOB_END_CLAUSE
		}
	}
}