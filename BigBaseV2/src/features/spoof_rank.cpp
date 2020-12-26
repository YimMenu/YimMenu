#include "features.hpp"
#include "script_global.hpp"

namespace big
{
	void features::spoof_rank()
	{
		bool bSpoofRank = g_settings.options["spoof_rank"].get<bool*>();

		if (bSpoofRank)
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				*script_global(1590682).at(PLAYER::PLAYER_ID(), 883).at(211).at(6).as<int*>() = g_settings.options["rank"].get<int>();
			}QUEUE_JOB_END_CLAUSE
		}
	}
}